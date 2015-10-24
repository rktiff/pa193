#ifndef SHOPITEM_H
#define SHOPITEM_H

#include <iostream>
#include <stdexcept>
#include <list>

#include "urls.h"
#include "delivery.h"

class ShopItem{
    std::string* m_id; //musi byt unikatne, max 36 znakov [a-z][A-Z][0-9] - _
    std::string* m_prodName;//musi byt v product, max 255 znakov, kopa povinnych veci(nedokoncene)
    std::string* m_product; // max 255 znakov
    std::string* m_desc;

    Urls* m_urls; //(validacia nedokoncena)

    double m_price;//2 desatinne miesta
    std::string* m_itemType;
    std::string* m_manufact;//musi byt v product name
    std::string* m_catText; //psycho (nedokoncene)
    unsigned int m_ean[13] = {0}; //povinny pre kinhy
    unsigned int m_isbn[10] = {0};//isbn10, isbn13
    double m_heuCpc; // max 100, 2 desatinne miesta

    std::list<Delivery*> m_delivery;

    std::string* m_groupId;//max 36 znakov [a-z][A-Z][0-9] - _
    std::list<std::string> m_accessory; //obsahuje id inych poloziek
    double m_dues;//ine poplatky

    void validateId(const std::string & str) const;
    void validateProduct(const std::string& str) const;
    unsigned int computeEanChecksum(const unsigned int digits[]) const;
    unsigned int computeIsbn10Checksum(const unsigned int digits[]) const;
public:

    ShopItem();

    ~ShopItem();

    void setId(const std::string & id);

    void setProdName(const std::string & name);

    void setProduct(const std::string & product);

    void setDesc(const std::string & desc);

    void setPrice(const double price);

    void setManufacturer(const std::string& manuf);

    void setEan(const unsigned int ean[]);

    void setIsbn10(const unsigned int isbn[]);

    void setHeuCpc(const double val);

    void setItemGroupId(const std::string & id);

    void addAccessory(const std::string& accessory);

    void setDues(const double due);

    void addDelivery(const Delivery* delivery);

    void setUrl(const std::string& url);

    void setImgUrl(const std::string& url);

    void addAltUrl(const std::string& url);

    void setVidUrl(const std::string& url);

    std::string* getId() const;
};


#endif // SHOPITEM_H
