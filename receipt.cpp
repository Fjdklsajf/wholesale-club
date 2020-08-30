#include <map>
#include <iostream>
#include <iomanip>
#include "receipt.h"
#include "item.h"

/******************************************************************************************
 *
 *  Default Constructor Receipt
 *_________________________________________________________________________________________
 *  _date is set to "null" and _items is empty
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date is set to "null"
 ******************************************************************************************/
Receipt::Receipt() {
    _date.setNull();
}

/******************************************************************************************
 *
 *  Constructor Receipt
 *_________________________________________________________________________________________
 *  _date is set to the given parameter Date and _items is empty
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date is initailzed with given parameter Date
 ******************************************************************************************/
Receipt::Receipt(const Date& date) {
    _date = date;
}

/******************************************************************************************
 *
 *  Constructor Receipt
 *_________________________________________________________________________________________
 *  _date is set to the given parameter Date and given Item is added to _items along with
 *      its given quantity
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date is initailzed with given parameter Date
 *    _item contains given Item with its quantity
 ******************************************************************************************/
Receipt::Receipt(const Date& date, const Item& item, int quantity) {
    _date = date;
    addItem(item, quantity);
}

/******************************************************************************************
 *
 *  Method Receipt
 *_________________________________________________________________________________________
 *  _date and _items are set to the given parameter values
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date and _items are initailzed with the given parameters
 ******************************************************************************************/
Receipt::Receipt(const Date& date, const std::map<Item, int>& items) {
    _date = date;

    for(auto it = items.begin(); it != items.end(); it++) {
        _items.insert({it->first, it->second});
    }
}

/******************************************************************************************
 *
 *  Mutator setDate: Class Receipt
 *_________________________________________________________________________________________
 *  This method will update the _date attribute to the parameter date value
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date is changed to the given Date
 ******************************************************************************************/
void Receipt::setDate(const Date& date) {
    _date = date;
}

/******************************************************************************************
 *
 *  Accessor getItems: Class Receipt
 *_________________________________________________________________________________________
 *  This method will return _items
 *  - returns sdt::map<Item, int>
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _items is returned
 ******************************************************************************************/
std::map<Item, int> Receipt::getItems() const {
    return _items;
}

/******************************************************************************************
 *
 *  Accessor getDate: Class Receipt
 *_________________________________________________________________________________________
 *  This method will return _date
 *  - returns Date
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _date is returned
 ******************************************************************************************/
Date Receipt::getDate() const {
    return _date;
}

/******************************************************************************************
 *
 *  Method addItem: Class Receipt
 *_________________________________________________________________________________________
 *  Add the parameter item along with its quantity to _items
 *      if item already exist in _items, just increase the quantity
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Given item and its quantity is added to _items
 ******************************************************************************************/
void Receipt::addItem(const Item& item, int quantity) {
    if(_items.find(item) != _items.end()) {
        _items.at(item) = _items.at(item) + quantity;
    } else {
        _items.insert({item, quantity});
    }
}

/******************************************************************************************
 *
 *  Method addItem: Class Receipt
 *_________________________________________________________________________________________
 *  Add the map of items to _items
 *      if a particular item already exist in _items, just increase the quantity
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Each item in the given map of items is added to _items
 ******************************************************************************************/
void Receipt::addItems(const std::map<Item, int>& items) {
    for(std::map<Item, int>::const_iterator it = items.begin(); it != items.end(); it++) {
        addItem(it->first, it->second);
    }
}

/******************************************************************************************
 *
 *  Overload operator +=: Class Receipt
 *_________________________________________________________________________________________
 *  The items in the parameter Receipt are added to the current _items
 *      And the current Date is set to "null"
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    receipt items are added to _items
 *    _date is set to "null"
 ******************************************************************************************/
void Receipt::operator +=(Receipt receipt) {
    addItems(receipt.getItems());
    _date.setNull();
}

/******************************************************************************************
 *
 *  Overload operator =: Class Receipt
 *_________________________________________________________________________________________
 *  set _date and _items identical to the given Receipt
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _items and _date are updated to receipt's items and dates
 ******************************************************************************************/
void Receipt::operator =(const Receipt& receipt) {
    _date = receipt._date;
    _items = receipt._items;
}

/******************************************************************************************
 *
 *  Method totalCost: Class Receipt
 *_________________________________________________________________________________________
 *  Return the total cost for all the items on the Receipt
 *  - returns double
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Total cost for the items on the receipt are returned
 ******************************************************************************************/
double Receipt::totalCost() const {
    double sum = 0;
    for(std::map<Item, int>::const_iterator it = _items.begin(); it != _items.end(); it++) {
        Item item = it->first;
        sum += item.getPrice() * it->second;
    }

    return sum;
}

/******************************************************************************************
 *
 *  Overload operator +: Class Receipt
 *_________________________________________________________________________________________
 *  Return a Recipt that contains the sum of items and quantities from
 *      the current Receipt and paramter Receipt. The Date is set to "null".
 *  - returns Receipt
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    A new receipt with "null" Date and the two map of items combined
 ******************************************************************************************/
Receipt Receipt::operator +(const Receipt& receipt) const {
    Receipt result = *this;
    result += receipt;
    return result;
}

/******************************************************************************************
 *
 *  Method printItems: Class Receipt
 *_________________________________________________________________________________________
 *  Return a string of items on the Receipt in the format of:
 *      ->itemName ($price) xitemQuantity
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    Items on the Receipt and its price and quantity are printed
 ******************************************************************************************/
std::string Receipt::printItems() const {
    std::string str = "";
    for(std::map<Item, int>::const_iterator it = _items.begin(); it != _items.end(); it++) {
        Item item = it->first;
        int price = item.getPrice() * 100;
        str += item.getName() + " ($" + std::to_string(price/100) + '.';
        if(price % 100 < 10) {
            str += '0';
        }
        str += std::to_string(price%100) + ") x" + std::to_string(it->second) + '\n';
    }
    return str;
}

/******************************************************************************************
 *
 *  Method itemsSize: Class Receipt
 *_________________________________________________________________________________________
 *  Return the number of unique items on the Receipt
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    return the size of _items
 ******************************************************************************************/
int Receipt::itemsSize() const {
    return _items.size();
}

/******************************************************************************************
 *
 *  Method getItemCost: Class Receipt
 *_________________________________________________________________________________________
 *  Return the total cost of a particular item (item price * item quantity), 0 if not found
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    return the total cost of the given item
 ******************************************************************************************/
double Receipt::getItemCost(const Item& item) const {
    if(_items.find(item) == _items.end()) {
        return 0;
    }
    return _items.at(item) * item.getPrice();
}

/******************************************************************************************
 *
 *  Method getItemQuantity: Class Receipt
 *_________________________________________________________________________________________
 *  Return the the quantity of a particular item, 0 if not found
 *  - returns void
 *_________________________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    return the quantity of the given item
 ******************************************************************************************/
int Receipt::getItemQuantity(const Item& item) const {
    if(_items.find(item) == _items.end()) {
        return 0;
    }
    return _items.at(item);
}
