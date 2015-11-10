#ifndef LEXER_H
#define LEXER_H

#include <stdexcept>

#include "parser.h"


enum class LexerStates {
    Init,

    // utf-8 special chars reading
    ReadingBOM,
    ReadingBOM_1,
    Reading2B,
    Reading3B,
    Reading3B_1,
    Reading4B,

    // reading <? ... ?>
    WaitingForProlog,
    ReadingProlog,
    ReadingProlog_1,
    ReadingProlog_2,

    // reading content between elemnts (whitespace, comments, ...)
    ReadingContent,
    ReadingContent_1,

    // XML Element reading
    ReadingElement,
    ReadingElement_1,
    ReadingElement_WS,
    ReadingElement_SingleEnd,
    ReadingElementCDATA,
    ReadingEntity,
    ReadingComment,
    ReadingComment_1,
    ReadingElementEnd,
    ReadingElementEnd_1,

    // XML Attribute reading
    ReadingAttributeName,
    ReadingAttributeValue,
};

class Lexer
{
    // reference to parse
    const Parser& m_parser;

    // reference to currently tokanized line
    std::string m_current_line;

    // current position in line
    std::size_t m_position = 0;

    // latest token position
    std::size_t m_latest_token_pos = m_position;

    // lexer state
    LexerStates m_state = LexerStates::Init;

    // state before attributes processing
    LexerStates m_before_attr_state = LexerStates::Init;

    // common method for reading char
    void readChar(unsigned char ch);

    // helpers
    bool isElemNameFirstChar(unsigned char ch);
    bool isElemNameChar(unsigned char ch);

    // methods for reading particular token
    void readStart(unsigned char ch);
    void readBOM(unsigned char ch);
    void readProlog(unsigned char ch);
    void readElement(unsigned char ch);
    void readContent(unsigned char ch);
    void readElementEnd(unsigned char ch);

    // sends token to the parser
    void sendToken(TokenTypes type, size_t start_offset = 0, size_t length_offset = 0);
public:
    Lexer(const Parser& parser);

    ~Lexer();

    void tokanize(const std::string& line);
};

class LexerError : public std::domain_error
{
public:
    using std::domain_error::domain_error;
};

#endif // LEXER_H

