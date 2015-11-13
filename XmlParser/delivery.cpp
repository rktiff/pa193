#include "delivery.h"

#include <iostream>
#include <cctype>
#include <cmath>

using namespace std;

const string Delivery::ids[id_count] = {
    "CESKA_POSTA",
    "CESKA_POSTA_NA_POSTU",
    "CSAD_LOGISTIK_OSTRAVA",
    "DPD",
    "DHL",
    "DSV",
    "EMS",
    "FOFR",
    "GEBRUDER_WEISS",
    "GEIS",
    "GENERAL_PARCEL",
    "GLS",
    "HDS",
    "HEUREKAPOINT",
    "INTIME",
    "PPL",
    "RADIALKA",
    "SEEGMULLER",
    "TNT",
    "TOPTRANS",
    "UPS",
    "VLASTNI_PREPRAVA",
};

Delivery::Delivery()
    :m_id(NULL), m_price(0), m_price_cod(0)
{
}

Delivery::~Delivery() {
    delete m_id;
}

void Delivery::setId(const string& id){
    validateId(id);

    m_id=new string(id);
}

void Delivery::setPrice(double price){
    validatePrice(price);

    m_price=price;
}

void Delivery::setPriceCod(double price_cod){
    validatePrice(price_cod);

    m_price_cod=price_cod;
}

void Delivery::validatePrice(double price) const
{
    if(price<0)
        throw logic_error("negative value of price");

}

void Delivery::validateId(const string& id) const
{
     if(id.length()==0)//cena s dobierkou minimalne ako normalna cena
             throw logic_error("delivery: invalid constructor parameter");

         bool id_ok = false;
         for(unsigned int i=0; i<id_count; i++){
             if(id==ids[i]){//id musi byt jedno z validnych id
                 id_ok=true;
                 break;
             }
         }

         if(!id_ok)
             throw logic_error("delivery: invalid delivery id");
}
