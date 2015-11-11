#include <algorithm>
#include <list>

#include "document.h"
#include "convert.h"

using namespace std;

ParsedDocument::ParsedDocument()
    : m_current_item(NULL), m_current_delivery(NULL), m_current_param(NULL)
{
}

ParsedDocument::~ParsedDocument()
{
    delete m_current_item;
    delete m_current_delivery;
    delete m_current_param;
}

std::list<ShopItem*> ParsedDocument::getItems()
{
    return m_items;
}

void ParsedDocument::elementStart(const std::string& element)
    {
        // to upper case for simplified matching
        std::string elementName = element;
        std::transform(elementName.begin(), elementName.end(), elementName.begin(), ::toupper);

        if (elementName == "SHOPITEM")
        {
            m_current_item = new ShopItem();
        }
        else if (elementName == "DELIVERY")
        {
            m_current_delivery = new Delivery();
        }
        else if (elementName == "PARAM")
        {
            m_current_param = new Param();
        }
    }

void ParsedDocument::elementEnd(const std::string& element, const std::string& content)
    {
        // to upper case for simplified matching
        std::string elementName = element;
        std::transform(elementName.begin(), elementName.end(), elementName.begin(), ::toupper);

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
            double val;
            if (str2d(val, content) == ConversionResult::Success)
            {
                m_current_item->setPrice(val);
            }
            else {
                throw logic_error("Unable convert price '" + content + "' to decimal.");
            }
        }
        else if (elementName == "ITEM_TYPE")
        {
             m_current_item->setItemType(content);
        }
        else if (elementName == "PARAM_NAME")
        {
            m_current_param->setName(content);
        }
        else if (elementName == "VAL")
        {
            m_current_param->setValue(content);
        }
        else if (elementName == "PARAM")
        {
             m_current_item->addParam(m_current_param);
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
            unsigned long long val;
            if (str2ull(val, content, 10) == ConversionResult::Success)
            {
                m_current_item->setEan(val);
            }
            else {
                throw logic_error("Unable convert EAN '" + content + "' to number.");
            }
        }
        else if (elementName == "ISBN")
        {
            unsigned long long val;
            if (str2ull(val, content, 10) == ConversionResult::Success)
            {
                m_current_item->setIsbn10(val);
            }
            else {
                throw logic_error("Unable convert ISBN '" + content + "' to number.");
            }
        }
        else if (elementName == "HEUREKA_CPC")
        {
            double val;
            if (str2d(val, content) == ConversionResult::Success)
            {
                m_current_item->setHeuCpc(val);
            }
            else {
                throw logic_error("Unable convert HEUREKA_CPC '" + content + "' to decimal.");
            }
        }
        else if (elementName == "DELIVERY_DATE")
        {
            m_current_item->setDeliveryDate(content);
        }
        else if (elementName == "DELIVERY_ID")
        {
            m_current_delivery->setId(content);
        }
        else if (elementName == "DELIVERY_PRICE")
        {
            double val;
            if (str2d(val, content) == ConversionResult::Success)
            {
                m_current_delivery->setPrice(val);
            }
            else {
                throw logic_error("Unable convert DELIVERY_PRICE '" + content + "' to decimal.");
            }
        }
        else if (elementName == "DELIVERY_PRICE_COD")
        {
            double val;
            if (str2d(val, content) == ConversionResult::Success)
            {
                m_current_delivery->setPriceCod(val);
            }
            else {
                throw logic_error("Unable convert DELIVERY_PRICE_COD '" + content + "' to decimal.");
            }
        }
        else if (elementName == "DELIVERY")
        {
            m_current_item->addDelivery(m_current_delivery);
        }
        else if (elementName == "ITEMGROUP_ID")
        {
             m_current_item->setItemGroupId(content);
        }
        else if (elementName == "ACCESSORY")
        {
            m_current_item->addAccessory(content);
        }
        else if (elementName == "DUES")
        {
            double val;
            if (str2d(val, content) == ConversionResult::Success)
            {
                m_current_item->setDues(val);
            }
            else {
                throw logic_error("Unable convert DUES '" + content + "' to decimal.");
            }
        }
        else {
            throw logic_error("Unsupported element " + elementName);
        }
    }


