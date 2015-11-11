#ifndef DOCUMENT
#define DOCUMENT

#include "parser.h"
#include "shopitem.h"

class ParsedDocument : public ParsingHandler
{
    std::list<ShopItem*> m_items;
    ShopItem* m_current_item;
    Delivery* m_current_delivery;
    Param* m_current_param;
public:
    ParsedDocument();

    ~ParsedDocument();

    std::list<ShopItem*> getItems();

    void elementStart(const std::string& element);

    void elementEnd(const std::string& elementName, const std::string& content);
};

#endif // DOCUMENT

