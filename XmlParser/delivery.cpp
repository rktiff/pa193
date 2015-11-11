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

