#include "lexer.h"

#include <iostream>

using namespace std;

// ------------------------ //
//  Token class definition  //
// ------------------------ //

Token::Token(const std::string& content, TokenTypes type)
    : m_content(new std::string(content)), m_type(type)
{
}

Token::~Token()
{
    delete m_content;
}

std::string* Token::getContent()
{
    return m_content;
}

TokenTypes Token::getType()
{
    return m_type;
}

// ------------------------ //
//  Lexer class definition  //
// ------------------------ //

Lexer::Lexer(Parser* parser)
    : m_parser(parser), m_position(0), m_latest_token_pos(0), m_state(LexerStates::Init),
      m_previous_content(new string())
{

}

Lexer::~Lexer()
{
    delete m_previous_content;
}

void Lexer::tokanize(const std::string& line)
{
    m_current_line = line;
    m_latest_token_pos = 0;
    for (m_position=0; m_position < line.length(); m_position++)
    {
        readChar(line.at(m_position));
    }
    // store multi line content for later use
    if (m_state == LexerStates::ReadingContent_1)
    {
        m_previous_content->append(m_current_line.substr(m_latest_token_pos, m_position - m_latest_token_pos));
        m_previous_content->append("\n");
    }
}

void Lexer::sendToken(TokenTypes type, long start_offset = 0, long length_offset = 0)
{
    size_t from = m_latest_token_pos + start_offset;
    size_t len = m_position - m_latest_token_pos + length_offset;

    if (len > 0)
    {
        Token *token = new Token(*m_previous_content + m_current_line.substr(from, len), type);
        m_previous_content->clear();

        m_parser->nextToken(token);
    }
}

void Lexer::readChar(unsigned char ch)
{
    switch (m_state) {
    // read document start
    case LexerStates::Init:
        readStart(ch);
        break;

    // read BOM
    case LexerStates::ReadingBOM:
    case LexerStates::ReadingBOM_1:
        readBOM(ch);
        break;

    case LexerStates::WaitingForProlog:
        if (ch == '<')
        {
            m_state = LexerStates::ReadingProlog;
        }
        break;

    // read prolog
    case LexerStates::ReadingProlog:
    case LexerStates::ReadingProlog_1:
    case LexerStates::ReadingProlog_2:
        readProlog(ch);
        break;

    // read element
    case LexerStates::ReadingElement:
    case LexerStates::ReadingElement_1:
    case LexerStates::ReadingElement_WS:
    case LexerStates::ReadingElement_SingleEnd:
        readElement(ch);
        break;

    // read content
    case LexerStates::ReadingContent:
    case LexerStates::ReadingContent_1:
        readContent(ch);
        break;

    // TODO: read comment

    // TODO: read <![CDATA[ ... ]]> section

    // TODO: read XML entities

    // TODO: read and validate UTF-8 characters

    // read element closing tag
    case LexerStates::ReadingElementEnd:
    case LexerStates::ReadingElementEnd_1:
        readElementEnd(ch);
        break;
    default:
        throw LexerError("Unexpacted token");
        break;
    }
}

bool Lexer::isElemNameFirstChar(unsigned char ch)
{
    return (ch >= 'A' &&  ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool Lexer::isElemNameChar(unsigned char ch)
{
    return (ch >= 'A' &&  ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '_' || ch == ':';
}

// ----------------------------------- //
//  Methods for XML format processing  //
// ----------------------------------- //

void Lexer::readStart(unsigned char ch)
{
    if (m_state != LexerStates::Init) {
        throw LexerError("Invalid state when document start read");
    }

    switch(ch) {
    case 239:
        // read UTF-8 BOM
        m_state = LexerStates::ReadingBOM;
        break;
    case '<':
        // read prolog, comment or root element
        m_state = LexerStates::ReadingProlog;
        break;
    default:
        throw LexerError("Document have to start with prolog, comment or element");
        break;
    }
}

void Lexer::readBOM(unsigned char ch)
{
    if (m_state != LexerStates::ReadingBOM && m_state != LexerStates::ReadingBOM_1) {
        throw LexerError("Invalid state when reading UTF-8 BOM");
    }

    if (m_state == LexerStates::ReadingBOM && ch == 187)
    {
        // read next byte of BOM
        m_state = LexerStates::ReadingBOM_1;
        return;
    }
    else if (m_state == LexerStates::ReadingBOM_1 && ch == 191)
    {
        // continue as reading document start but without BOM
        m_state = LexerStates::WaitingForProlog;

        return;
    }

    throw LexerError("Invalid UTF-8 BOM section");
}

void Lexer::readProlog(unsigned char ch)
{
    if (m_state == LexerStates::ReadingProlog)
    {
        // read first char after '<' at document start
        switch (ch) {
        case '?':
            m_state = LexerStates::ReadingProlog_1;
            break;
        default:
            m_state = LexerStates::ReadingElement;
            readChar(ch); // test if first char is valid
            break;
        }
    }
    else if (m_state == LexerStates::ReadingProlog_1)
    {
        // read '<?' and waiting for '?>'
        if (isspace(ch))
        {
            if (ch == '\n' || ch == '\r')
            {
                throw LexerError("New lines in XML prolog is not allowed");
            }
            return;
        }
        else if (ch == '?')
        {
            m_state = LexerStates::ReadingProlog_2;
        }
    }
    else if (m_state == LexerStates::ReadingProlog_2)
    {
        if (ch == '>')
        {
            m_state = LexerStates::ReadingContent;
        }
        else
        {
            m_state = LexerStates::ReadingProlog_1;
        }
    }
    else {
        throw LexerError("Invalid state when reading XML Prolog");
    }
}

void Lexer::readElement(unsigned char ch)
{
    if (m_state == LexerStates::ReadingElement)
    {
        // previous char was '<'
        if (ch == '!')
        {
            // comment
            m_state = LexerStates::ReadingComment;
        }
        if (ch == '/')
        {
            // end of element
            sendToken(TokenTypes::ElementContent, 0, -1);
            m_state = LexerStates::ReadingElementEnd;
        }
        else if (isElemNameFirstChar(ch))
        {
            m_latest_token_pos = m_position;
            m_state = LexerStates::ReadingElement_1;
        }
    }
    else if (m_state == LexerStates::ReadingElement_1)
    {
        if (!isElemNameChar(ch))
        {
            if (isspace(ch)) {
                m_state = LexerStates::ReadingElement_WS;
            }
            else
            {
                switch (ch) {
                case '/':
                    m_state = LexerStates::ReadingElement_SingleEnd;
                    break;
                case '>':
                    m_state = LexerStates::ReadingContent;
                    break;
                default:
                    throw LexerError("Invalid element character");
                    break;
                }
            }
            sendToken(TokenTypes::ElementName, 0, 0);
        }
    }
    else if (m_state == LexerStates::ReadingElement_WS)
    {
        if (!isspace(ch)) {
            switch (ch) {
            case '/':
                m_state = LexerStates::ReadingElement_SingleEnd;
                break;
            case '>':
                m_state = LexerStates::ReadingContent;
                break;
            default:
                throw LexerError("Invalid element definition (attributes are not supported)");
                break;
            }
        }
    }
    else if (m_state == LexerStates::ReadingElement_SingleEnd)
    {
        if (ch == '>')
        {
            m_state = LexerStates::ReadingContent;
        }
        else
        {
            throw LexerError("Invalid content '/' of element");
        }
    }
    else {
        throw LexerError("Invalid state when reading element");
    }
}

void Lexer::readContent(unsigned char ch)
{
    if (m_state == LexerStates::ReadingContent)
    {
        if (ch == '<')
        {
            m_state = LexerStates::ReadingElement;
        }
        else
        {
            m_latest_token_pos = m_position;
            m_state = LexerStates::ReadingContent_1;
        }
    }
    else if (m_state == LexerStates::ReadingContent_1)
    {
        if (ch == '<')
        {
            m_state = LexerStates::ReadingElement;
        }
    }
}

void Lexer::readElementEnd(unsigned char ch)
{
    if (m_state == LexerStates::ReadingElementEnd)
    {
        // previous chars was '</'
        if (isElemNameFirstChar(ch))
        {
            m_latest_token_pos = m_position;
            m_state = LexerStates::ReadingElementEnd_1;
        }
        else
        {
            throw LexerError("Invalid element name");
        }
    }
    else if (m_state == LexerStates::ReadingElementEnd_1)
    {
        if (!isElemNameChar(ch))
        {
            if (ch == '>') {
                m_state = LexerStates::ReadingContent;
                sendToken(TokenTypes::ElementEnd, 0, 0);
            }
            else {
                throw LexerError("Invalid element character");
            }
        }
    }
    else {
        throw LexerError("Invalid state when reading element's closing tag");
    }
}
