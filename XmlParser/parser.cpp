#include "parser.h"

#include <iostream>

using namespace std;

Parser::Parser(ParsingHandler* handler) : m_handler(handler) {}

Parser::~Parser()
{
    while(!m_stack.empty())
    {
        delete m_stack.top();
        m_stack.pop();
    }
}

void Parser::nextToken(Token* token)
{
    if (token->getType() == TokenTypes::ElementName)
    {
        m_handler->elementStart(*token->getContent());
        m_stack.push(token);
    }
    else if (token->getType() == TokenTypes::ElementContent)
    {
        if (!m_stack.empty())
        {
            Token* top = m_stack.top();
            if (top->getType() == TokenTypes::ElementContent) {
                // reduce top of stack (concatenate contents)
                std::string newContent = *top->getContent() + *token->getContent();
                Token newToken(newContent, TokenTypes::ElementContent);

                m_stack.pop();
                m_stack.push(&newToken);
            }
            else
            {
                // add content on stack
                m_stack.push(token);
            }
        }
        else
        {
            throw ParserError("Content without element");
        }
    }
    else if (token->getType() == TokenTypes::ElementEnd)
    {
        if (!m_stack.empty())
        {
            Token* content = m_stack.top(), *elem = NULL;
            m_stack.pop();
            if (content->getType() == TokenTypes::ElementContent) {
                elem = m_stack.top();
                m_stack.pop();
            }
            else if (content->getType() == TokenTypes::ElementName) {
                elem = content;
                content = NULL;
            }
            else {
                throw ParserError("Unexpacted top of stack during parsing");
            }

            if (elem->getType() == TokenTypes::ElementName)
            {
                if (elem->getContent()->compare(*token->getContent()) == 0)
                {
                    m_handler->elementEnd(*elem->getContent(), content != NULL ? *content->getContent() : "");
                }
                else
                {
                    throw ParserError("Elements " + *elem->getContent() + " and " + *token->getContent() + " overlaps");
                }
            }
        }
        else
        {
            throw ParserError("Element end without element start");
        }
    }
}

void Parser::endParse()
{
    if (!m_stack.empty())
    {
        throw ParserError("Missing closing tag for " + *m_stack.top()->getContent());
    }
}


