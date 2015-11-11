#ifndef LEXER_H
#define LEXER_H

#include <stdexcept>

#include "parser.h"


enum class LexerStates {
    Init,

    // utf-8 special chars reading
    ReadingBOM,
    ReadingBOM_1,

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
    ReadingElementEnd_1
};

class Lexer
{
    // reference to parse
    Parser* m_parser;

    // reference to currently tokanized line
    std::string m_current_line;

    // current position in line
    std::size_t m_position;

    // latest token position
    std::size_t m_latest_token_pos;

    // lexer state
    LexerStates m_state;

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
    void sendToken(TokenTypes type, bool case_sensitive, size_t start_offset, size_t length_offset);
public:
    Lexer(Parser* parser);

    ~Lexer();

    void tokanize(const std::string& line);
};

// ------------------ //
//  LexerError class  //
// ------------------ //

class LexerError : public std::domain_error
{
public:
    LexerError(std::string const& msg) : std::domain_error(msg) { }
};

#endif // LEXER_H

