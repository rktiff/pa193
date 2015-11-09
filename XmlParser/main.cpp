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

    string product = "vyrobca nazov produktu a cosi ešte";
    string prodName = "nazov produktu";
    string manufacturer = "vyrobca";
    string id = "superId123_---AZaz";
    item.setId(id);
    item.setDesc("Toto je popis, srany kopec");
    item.setProduct(product);
    item.setProdName(prodName);
    item.setManufacturer(manufacturer);
    //item.setCatText(product);
    //string prodName2 = "nazov produktu2";
    //item.setProdName(prodName2);

    string type = "super typ produktu";
    item.setItemType(type);

    item.setEan(3307211667501);
//    item.setEan(4006381333931);

//    item.setIsbn10(8020401059);
    item.setIsbn10(306406152);

    item.addDelivery(&del1);
    item.addDelivery(&del3);

    return 0;
}

