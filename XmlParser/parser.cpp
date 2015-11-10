#include "parser.h"

using namespace std;

Parser::Parser() {}
//Parser::Parser(ParsingHandler* handler) : m_handler(handler) {}

Parser::~Parser()
{
    free(m_handler);
}

void Parser::nextToken(Token* token)
{
    token->getContent();
}

void Parser::endParse()
{

}


