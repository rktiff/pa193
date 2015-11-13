#ifndef DELIVERY_H
#define DELIVERY_H

#include <iostream>
#include <stdexcept>

// TODO: Constrctor withou params + set methods with validations

class Delivery{
    std::string* m_id;
    double m_price;
    double m_price_cod;

    static const std::string ids[];//podla dokumentacie 22 roznych dopravcov
    static const unsigned int id_count = 22;//pocet validnych id
    void validatePrice(double price) const;
    void validateId(const std::string& id) const;

public:
    Delivery();

    ~Delivery();

    void setId(const std::string & id);

    void setPrice(double price);

    void setPriceCod(double price_cod);

};






#endif // DELIVERY_H
