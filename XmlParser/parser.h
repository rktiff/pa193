#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stack>
#include <stdexcept>

using namespace std;

enum class TokenTypes
{
    ElementName,
    ElementContent,
    ElementEnd,
    AttributeName,
    AttributeValue
};

class Token
{
    std::string* m_content;
    TokenTypes m_type;
public:
    Token(std::string* content, TokenTypes type);

    ~Token();

    std::string* getContent();

    TokenTypes getType();
};

class ParsingHandler
{
public:
    virtual void elementStart(const std::string& elementName) = 0;

    virtual void elementEnd(const std::string& elementName, const std::string& content) = 0;
};

class Parser
{
    std::stack<Token*> m_stack;
    ParsingHandler* m_handler;
public:
    Parser(ParsingHandler* handler);

    ~Parser();

    void nextToken(Token* token);

    void endParse();
};


// ------------------- //
//  ParserError class  //
// ------------------- //

class ParserError : public std::domain_error
{
public:
    using std::domain_error::domain_error;
};

#endif // PARSER_H

