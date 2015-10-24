#include <iostream>
#include "delivery.h"


using namespace std;


const string Delivery::ids[id_count] = {
    u8"CESKA_POSTA",
    u8"CESKA_POSTA_NA_POSTU",
    u8"CSAD_LOGISTIK_OSTRAVA",
    u8"DPD",
    u8"DHL",
    u8"DSV",
    u8"EMS",
    u8"FOFR",
    u8"GEBRUDER_WEISS",
    u8"GEIS",
    u8"GENERAL_PARCEL",
    u8"GLS",
    u8"HDS",
    u8"HEUREKAPOINT",
    u8"INTIME",
    u8"PPL",
    u8"RADIALKA",
    u8"SEEGMULLER",
    u8"TNT",
    u8"TOPTRANS",
    u8"UPS",
    u8"VLASTNI_PREPRAVA",
};

Delivery::Delivery(const string & id, const double price, const double price_cod)
    :m_id(new string(id)), m_price(price), m_price_cod(price_cod)
{
    if(id.length()==0 || price>price_cod || price<0)//cena s dobierkou minimalne ako normalna cena
        throw logic_error("delivery: invalid constructor parameter");

    bool id_ok = false;
    for(unsigned int i=0; i<id_count; i++){
        if((*m_id)==ids[i]){//id musi byt jedno z validnych id
            id_ok=true;
            break;
        }
    }

    if(!id_ok)
        throw logic_error("delivery: invalid delivery id");
}

Delivery::Delivery(const std::string & id, const double price):Delivery(id, price, price)
{
    m_price_cod=0;//dobierka neni mozna
}

Delivery::~Delivery(){
    delete m_id;
}
