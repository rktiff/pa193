#include <iostream>

#include "shopitem.h"

using namespace std;

int main()
{

    Delivery del1(u8"DSV", 50, 60);
    //Delivery del2(u8"DSVx", 50, 60);
    Delivery del3(u8"DSV", 50);

    ShopItem item;
    item.setPrice(60.0);
    item.setPrice(0);
    //item.setPrice(-0.01);
    item.setHeuCpc(0);
    item.setHeuCpc(100);
    //item.setHeuCpc(-1);
    //item.setHeuCpc(100.01);

    string product = "vyrobca nazov produktu a cosi este";
    string prodName = "nazov produktu";
    string manufacturer = "vyrobca";
    string id = "superId123_---AZaz";
    item.setId(id);
    item.setDesc("Toto je popis, srany kopec");
    item.setProduct(product);
    item.setProdName(prodName);
    item.setManufacturer(manufacturer);
    //string prodName2 = "nazov produktu2";
    //item.setProdName(prodName2);

    unsigned int eanArray[13] = {3,3,0,7,2,1,1,6,6,7,5,0,1};
    item.setEan(eanArray);

    unsigned int isbnArray[10] = {8,0,2,0,4,0,1,0,5,9};
    item.setIsbn10(isbnArray);

    item.addDelivery(&del1);
    item.addDelivery(&del3);

    return 0;
}

