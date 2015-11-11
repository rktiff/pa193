#include <iostream>
#include <fstream>
#include <string>

#include "lexer.h"
#include "shopitem.h"

using namespace std;

class ParsedDocument : public ParsingHandler
{
    std::list<ShopItem*> m_items;
    ShopItem* m_current_item = NULL;
    Delivery* m_current_delivery = NULL;
    // TODO: Param* m_current_param = NULL;
public:
    std::list<ShopItem*> getItems()
    {
        return m_items;
    }

    void elementStart(const std::string& elementName)
    {
        if (elementName == "SHOPITEM")
        {
            m_current_item = new ShopItem();
        }
        else if (elementName == "DELIVERY")
        {
            // TODO:
            // m_current_delivery = new Delivery();
        }
        else if (elementName == "PARAM")
        {
            // TODO:
            // m_current_param = new Param();
        }
    }

    void elementEnd(const std::string& elementName, const std::string& content)
    {
        if (elementName == "SHOP")
        {
            // TODO has to be root
        }
        else if (elementName == "SHOPITEM")
        {
            m_items.push_back(m_current_item);
            m_current_item = NULL;
        }
        else if (elementName == "ITEM_ID")
        {
            m_current_item->setId(content);
        }
        else if (elementName == "PRODUCTNAME")
        {
            m_current_item->setProdName(content);
        }
        else if (elementName == "PRODUCT")
        {
            m_current_item->setProduct(content);
        }
        else if (elementName == "DESCRIPTION")
        {
            m_current_item->setDesc(content);
        }
        else if (elementName == "URL")
        {
            m_current_item->setUrl(content);
        }
        else if (elementName == "IMGURL")
        {
            m_current_item->setImgUrl(content);
        }
        else if (elementName == "IMGURL_ALTERNATIVE")
        {
             m_current_item->addAltUrl(content);
        }
        else if (elementName == "VIDEO_URL")
        {
            m_current_item->setVidUrl(content);
        }
        else if (elementName == "PRICE_VAT")
        {
            // TODO: convert
            // m_current_item->setPrice(content);
        }
        else if (elementName == "ITEM_TYPE")
        {
             m_current_item->setItemType(content);
        }
        else if (elementName == "PARAM_NAME")
        {
            // TODO
            // m_current_item->set(content);
        }
        else if (elementName == "VAL")
        {
            // TODO
            // m_current_item->set(content);
        }
        else if (elementName == "PARAM")
        {
            // TODO
            // m_current_item->set(content);
        }
        else if (elementName == "MANUFACTURER")
        {
            m_current_item->setManufacturer(content);
        }
        else if (elementName == "CATEGORYTEXT")
        {
            m_current_item->setCatText(content);
        }
        else if (elementName == "EAN")
        {
            // TODO: convert
            // m_current_item->setEan(content);
        }
        else if (elementName == "ISBN")
        {
            // TODO: convert
            // m_current_item->setIsbn10(content);
        }
        else if (elementName == "HEUREKA_CPC")
        {
            // TODO: convert
            // m_current_item->setHeuCpc(content);
        }
        else if (elementName == "DELIVERY_DATE")
        {
            // TODO:
            // m_current_item->set(content);
        }
        else if (elementName == "DELIVERY_ID")
        {
            // TODO:
            // m_current_delivery->setId(content);
        }
        else if (elementName == "DELIVERY_PRICE")
        {
            // TODO:
            // m_current_delivery->setPrice(content);
        }
        else if (elementName == "DELIVERY_PRICE_COD")
        {
            // TODO:
            // m_current_delivery->setPriceCOD(content);
        }
        else if (elementName == "DELIVERY")
        {
            m_current_item->addDelivery(m_current_delivery);
        }
        else if (elementName == "ITEMGROUP_ID")
        {
            // TODO:
             m_current_item->setItemGroupId(content);
        }
        else if (elementName == "ACCESSORY")
        {
            m_current_item->addAccessory(content);
        }
        else if (elementName == "DUES")
        {
            // TODO: convert
            // m_current_item->setDues(content);
        }
        else {
            throw logic_error("Unsupported element " + elementName);
        }
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
    }

    return returnCode;
}

