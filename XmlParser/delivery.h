#ifndef DELIVERY_H
#define DELIVERY_H

#include <iostream>
#include <stdexcept>


class Delivery{
    std::string* m_id;
    double m_price;
    double m_price_cod;

    static const std::string ids[];//podla dokumentacie 22 roznych dopravcov
    static const unsigned int id_count = 22;//pocet validnych id
public:
    Delivery(const std::string & id, const double price, const double price_cod);

    Delivery(const std::string & id, const double price);

    Delivery(const Delivery & other);

    ~Delivery();
};






#endif // DELIVERY_H
