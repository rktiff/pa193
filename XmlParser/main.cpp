#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>

#include "shopitem.h"
#include "document.h"
#include "lexer.h"

using namespace std;


int main(int argc, char* argv[])
{
    // Check the number of parameters
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " FILE_NAME" << std::endl;
        return 1;
    }

    int returnCode = 0;

    // Open and parse file
    ParsedDocument document;
    Parser parser(&document);
    Lexer lexer(&parser);

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
            parser.endParse();
        }
        catch (const LexerError& e)
        {
            std::cerr << "Unexpacted lexical error:" << e.what() << std::endl;
            returnCode = 2;
        }
        catch (const ParserError& e)
        {
            std::cerr << "Unexpacted syntax error:" << std::endl << e.what() << std::endl;
            returnCode = 3;
        }
        catch (const exception& e)
        {
            std::cerr << "Unexpacted error:" << std::endl << e.what() << std::endl;
            returnCode = 4;
        }
        xmlfile.close();
    }
    else
    {
        std::cerr << "Unable to open file " << argv[1] << std::endl;
        returnCode = 5;
    }

    if (returnCode == 0)
    {
        // TODO: do something with document.getItems();
        std::list<ShopItem*> items = document.getItems();

        double total_sum = 0;

        std::cout << "=== Parsed data ===" << std::endl;

        for (auto item: items)
        {
            total_sum += item->getPrice();

            std::cout << *(item->getProdName())
                      << " (ID:" << *(item->getId()) << ")" << std::endl;

            std::cout << "  Category: " << *(item->getCatText()) << std::endl;
            std::cout << "  Product: " << *(item->getProduct()) << std::endl;
            std::cout << "  EAN: " << item->getEAN() << std::endl;
            std::cout << "  Price: " << item->getPrice() << std::endl;
            std::cout << "  Description: " << *(item->getDesc()) << std::endl;
            std::cout << std::endl;
        }

        std::cout << "=== Summary ===" << std::endl;
        std::cout << "Parsed: " << items.size() << " items" << std::endl;
        std::cout << "Total sum: " << total_sum << std::endl;

    }

    return returnCode;
}

