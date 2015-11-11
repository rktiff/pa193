#include "delivery.h"

#include <iostream>
#include <cctype>
#include <cmath>

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

Delivery::Delivery()
    :m_id(NULL), m_price(0), m_price_cod(0)
{
}

Delivery::~Delivery() {
    delete m_id;
}

void Delivery::setId(const string& id){
    // validateId(id);

    m_id=new string(id);
}

void Delivery::setPrice(double price){
    // validatePrice(price);

    m_price=price;
}

void Delivery::setPriceCod(double price_cod){
    // validatePrice(price);

    m_price_cod=price_cod;
}

