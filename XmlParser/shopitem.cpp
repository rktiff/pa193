#include "shopitem.h"
#include <cctype>
#include <cmath>

using namespace std;

ShopItem::ShopItem()
    :m_id( nullptr), m_prodName( nullptr),m_product( nullptr),m_desc( nullptr), m_urls(new Urls()),
     m_price(0), m_itemType( nullptr),m_manufact( nullptr),
     m_catText( nullptr), m_heuCpc(0), m_groupId( nullptr), m_dues(0)
{
}


ShopItem::~ShopItem(){
    delete m_id;
    delete m_prodName;
    delete m_product;
    delete m_desc;

    delete m_urls;

    delete m_itemType;
    delete m_manufact;
    delete m_catText;

    for(list<Delivery*>::const_iterator iterator = m_delivery.begin(); iterator!=m_delivery.end(); ++iterator){
        free(*iterator);
    }

    delete  m_groupId;
}

unsigned int ShopItem::computeEanChecksum(const unsigned long long digits) const{
    int weighted=0;

    for(unsigned long long tmpDigits = digits / 100; tmpDigits > 0; tmpDigits /= 100) { //vazena suma
        weighted += tmpDigits % 10;
    }


    for(unsigned long long tmpDigits = digits / 10; tmpDigits > 0; tmpDigits /= 100) {//vazena suma
        weighted += 3 * (tmpDigits % 10);
    }

    return (10 - (weighted % 10))%10 ;
}

unsigned int ShopItem::computeIsbn10Checksum(const unsigned long long digits) const {
    int weighted = 0, i = 0;

    for(unsigned long long tmpDigits = digits; tmpDigits > 0; tmpDigits /= 10) { //vazena suma
        weighted += ++i * (tmpDigits % 10);
    }

    return weighted % 11;
}


void ShopItem::validateProduct(const string &str) const{
    if(str.length()>255)
        throw logic_error("string too long");

    if(m_product->find(str, 0)==string::npos)//retazec musi byt obsiahnuty v "m_product"
        throw logic_error("string does not contain product name");
}

void ShopItem::validateId(const std::string & str) const{
    if(str.length()>36)//dlzka id max 36 znakov
        throw logic_error("item id too long");

    for(unsigned int i=0;i<str.length();i++){//validne znaky [a-z][A-Z][0-9] - _
        if( !isalnum(str.at(i)) && str.at(i)!=u'-' && str.at(i)!=u'_')
            throw logic_error("invalid character in id");
    }
}

void ShopItem::setId(const string& id){
    validateId(id);

    m_id=new string(id);
}

void ShopItem::setProdName(const string & name){
    // TODO: validate when shopitem instance is completly set
    // validateProduct(name);

    m_prodName=new string(name);
}

void ShopItem::setProduct(const string & product){
    if(product.length()>255)
        throw logic_error("product name too long");

    m_product = new string(product);
}

void ShopItem::setDesc(const string & desc){
    if(desc.length()>2000)//podla dokumentacie nebolo ziadne obmedzenie, tak som pridal aspon na pocet znakov
        throw logic_error("product name too long");

    m_desc = new string(desc);
}

void ShopItem::setPrice(const double price){
    if(price<0)
        throw logic_error("negative price");

    m_price = price;
}

void ShopItem::setItemType(const std::string& type){
    if(type.length()>2000)
        throw logic_error("item type too long");

    m_itemType = new string(type);

}

void ShopItem::setManufacturer(const string& manuf){
    // TODO: Use correct validation
    // validateProduct(manuf);

    m_manufact = new string(manuf);
}

void ShopItem::setCatText(const std::string& category){
    if(category.length()>2000)
        throw logic_error("category too long");

    // TODO accept UTF-8 multibyte characters
//    for(unsigned int i=0;i<category.length();i++){//validne znaky [a-z][A-Z][0-9]\s - _ |
//        if( !isalnum(category[i]) && !isspace(category[i]) && category[i] != u'|' && category[i]!=u'-' && category[i]!=u'_')
//            throw logic_error("invalid character in category");
//    }

    m_catText = new string(category);
}

void ShopItem::setEan(const unsigned long long ean) {
    if (ean > 9999999999999) {
        throw logic_error("ean contain number not from interval <0, 9>");
    }

    unsigned int checksum = computeEanChecksum(ean);
    if(ean % 10 != checksum)
        throw logic_error("invalid ean checksum");

    m_ean = ean;
}


void ShopItem::setIsbn10(const unsigned long long isbn){
    if (isbn > 9999999999) {
            throw logic_error("Invalid ISBN size");
    }

    unsigned int checksum = computeIsbn10Checksum(isbn);
    if(checksum != 0) {
        throw logic_error("invalid ISBN checksum");
    }

    m_isbn = isbn;
}

void ShopItem::setHeuCpc(const double val){
    if(val>100 || val<0)
        throw logic_error("value of heu_cpc not from interval <0, 100>");

    m_heuCpc = val;
}

void ShopItem::setItemGroupId(const std::string & id){
    validateId(id);

    m_groupId = new string(id);
}

void ShopItem::addAccessory(const std::string& accessory){
    validateId(accessory);

    m_accessory.push_front(accessory);
}

void ShopItem::setDues(const double due){
    if(due<0)
        throw logic_error("negative value of dues");

    m_dues=due;
}

void ShopItem::addDelivery(Delivery* delivery){
    // mozno takto
    m_delivery.push_back(delivery);
}

void ShopItem::setUrl(const string& url){

   m_urls->setUrl(url);
}

void ShopItem::setImgUrl(const string& url){

    m_urls->setImgUrl(url);
}

void ShopItem::addAltUrl(const string& url){

   m_urls->addAltUrl(url);
}

void ShopItem::setVidUrl(const string& url){
    m_urls->setVidUrl(url);
}

string* ShopItem::getId() const{
    return m_id;
}
