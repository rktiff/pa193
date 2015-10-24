#include "shopitem.h"
#include <cctype>
#include <cmath>

using namespace std;

ShopItem::ShopItem(){
    m_urls = new Urls();
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

unsigned int ShopItem::computeEanChecksum(const unsigned int digits[]) const{
    int weighted=0;
    int tmp = 0;

    for(int i=0; i<12; i+=2){
        tmp = (digits[i]);
        weighted+= tmp;
    }

    for(int i=1;i<12;i+=2)
        weighted+= 3*digits[i];

    return (10 - (weighted % 10))%10 ;
}

unsigned int ShopItem::computeIsbn10Checksum(const unsigned int digits[]) const{
    int weighted=0;

    for(int i=0; i<10; i++){
        weighted+= (10-i)*digits[i];
    }

    return (11 - (weighted % 11))%11 ;
}


void ShopItem::validateProduct(const string &str)const{
    if(m_product==nullptr)
        throw logic_error("product must be set befor product name");

    if(m_product->find(str, 0)==string::npos)
        throw logic_error("product does not contain product name");
}

void ShopItem::validateId(const std::string & str) const{
    if(str.length()>36)
        throw logic_error("item id too long");

    for(unsigned int i=0;i<str.length();i++){
        if( !!isalnum(str.at(i)) && str.at(i)!=u'\\' && str.at(i)!=u'_')
            throw logic_error("invalid character in id");
    }
}

void ShopItem::setId(const string& id){
    validateId(id);

    m_id=new string(id);
}

void ShopItem::setProdName(const string & name){

    if(name.length()>255)
        throw logic_error("product name too long");

    validateProduct(name);

    m_prodName=new string(name);
}

void ShopItem::setProduct(const string & product){
    if(product.length()>255)
        throw logic_error("product name too long");

    m_product = new string(product);
}

void ShopItem::setDesc(const string & desc){
    m_desc = new string(desc);
}

void ShopItem::setPrice(const double price){
    if(price<0)
        throw logic_error("negative price");

    m_price = price;
}


void ShopItem::setManufacturer(const string manuf){
    if(manuf.length()>255)
        throw logic_error("manufacturer too long");

    validateProduct(manuf);

    m_manufact = new string(manuf);
}

void ShopItem::setEan(const unsigned int ean[]){
    for(unsigned int i=0; i<13;i++){
        if(ean[i]>9)
            throw logic_error("ean contain number not from interval <0, 9>");
    }

    unsigned int checksum = computeEanChecksum(ean);
    if(ean[12]!=checksum)
        throw logic_error("invalid ean checksum");

    for(int i=0;i<13;i++)
        m_ean[i]=ean[i];
}


void ShopItem::setIsbn10(const unsigned int isbn[]){
    for(unsigned int i=0; i<10;i++){
        if(isbn[i]>9)
            throw logic_error("isbn contain number not from interval <0, 9>");
    }

    unsigned int checksum = computeIsbn10Checksum(isbn);
    if(isbn[9]!=checksum)
        throw logic_error("invalid isbn checksum");

    for(int i=0;i<10;i++)
        m_isbn[i]=isbn[i];

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

void ShopItem::addDelivery(const Delivery* delivery){
    //???
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
