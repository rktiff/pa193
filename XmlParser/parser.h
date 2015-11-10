#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stack>

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
    const std::string& m_content;
    TokenTypes m_type;
public:
    Token(const std::string& content, TokenTypes type);

    ~Token();

    const std::string& getContent();

    TokenTypes getType();
};

class ParsingHandler
{
public:
    virtual void elementStart(std::string* elementName);

    virtual void elementTextContent(std::string* elementName, std::string* content);

    virtual void elementEnd(std::string* elementName);

    virtual void attribute(std::string* attributeName, std::string* attributeValue);
};

class Parser
{
    std::stack<Token*> m_stack;
    ParsingHandler* m_handler;
public:
    Parser();

    ~Parser();

    void nextToken(Token* token);

    void endParse();
};

#endif // PARSER_H

