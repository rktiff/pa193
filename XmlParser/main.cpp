#include <iostream>
#include <fstream>
#include <string>

#include "lexer.h"
#include "shopitem.h"

using namespace std;

class MyParsingHandler : public ParsingHandler
{
public:
    void elementStart(std::string* elementName)
    {
        std::cout << "elementStart " << elementName << std::endl;
    }

    void elementTextContent(std::string* elementName, std::string* content)
    {
        std::cout << "elementTextContent " << elementName << " = " << content << std::endl;
    }

    void elementEnd(std::string* elementName)
    {
        std::cout << "elementEnd " << elementName << std::endl;
    }

    void attribute(std::string* attributeName, std::string* attributeValue)
    {
        std::cout << "attribute " << attributeName << " = " << attributeValue << std::endl;
    }
};

int main(int argc, char* argv[])
{
    // Check the number of parameters
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " FILE_NAME" << std::endl;
        return 1;
    }

    int returnCode = 0;

    // Open and parse file
//    MyParsingHandler handler;
    Parser parser;
    Lexer lexer(parser);

    std::string line;
    std::ifstream xmlfile(argv[1]);
    if (xmlfile.is_open())
    {
        try
        {
            while (getline(xmlfile, line))
            {
                lexer.tokanize(line);
            }
        }
        catch (const LexerError& e)
        {
            std::cerr << e.what() << std::endl;
            returnCode = 2;
        }
        xmlfile.close();
    }
    else
    {
        std::cerr << "Unable to open file " << argv[1] << std::endl;
        returnCode = 3;
    }

    return returnCode;
}

