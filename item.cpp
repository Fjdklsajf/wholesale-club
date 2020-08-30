#include <string>
#include "item.h"

/******************************************************************************************
 *
 *  Constructor Item
 *_________________________________________________________________________________________
 *  initialize the member variables _name and _price
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _name and _price are initalized to the parameter values
 ******************************************************************************************/
Item::Item(std::string name, double price) : _name(name), _price(price){
}

/******************************************************************************************
 *
 *  Mutator setName: Class Item
 *_________________________________________________________________________________________
 *  change the name of the item
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _name is set to the parameter name
 ******************************************************************************************/
void Item::setName(std::string name) {
    _name = name;
}

/******************************************************************************************
 *
 *  Mutator setPrice: Class Item
 *_________________________________________________________________________________________
 *  change the price of the item
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _price is set to the parameter price
 ******************************************************************************************/
void Item::setPrice(double price) {
    _price = price;
}

/******************************************************************************************
 *
 *  Accessor getName: Class Item
 *_________________________________________________________________________________________
 *  returns _name
 *  - returns std::string
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _name is returned
 ******************************************************************************************/
std::string Item::getName() const {
    return _name;
}

/******************************************************************************************
 *
 *  Accessor getPrice: Class Item
 *_________________________________________________________________________________________
 *  returns _price
 *  - returns double
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _price is returned
 ******************************************************************************************/
double Item::getPrice() const {
    return _price;
}

/******************************************************************************************
 *
 *  Overload operator<: Class Item
 *_________________________________________________________________________________________
 *  Compares the item names. Return true if _name comes before parameter itme's name,
 *      false otherwise. (Needed when creating a map)
 *  - returns bool
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    return true or false base on the alphebetical order
 ******************************************************************************************/
bool Item::operator <(const Item& item) const {
    return _name.compare(item._name) < 0;
}
