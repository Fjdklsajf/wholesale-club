#ifndef RECEIPT_H_
#define RECEIPT_H_

#include <map>
#include "date.h"
#include "item.h"

class Receipt {
  public:
    /******************************
     ** CONSTRUCTOR & DESTRUCTOR **
     ******************************/
    Receipt();
    explicit Receipt(const Date& date);
    Receipt(const Date& date, const Item& item, int quantity);
    Receipt(const Date& date, const std::map<Item, int>& items);

    /**************
     ** MUTATORS **
     **************/
    void setDate(const Date& date);

    /***************
     ** ACCESSORS **
     ***************/
    std::map<Item, int> getItems() const;
    Date getDate() const;

    /***********************************
     ** MODIFICATION MEMBER FUNCTIONS **
     ***********************************/
    void addItem(const Item& item, int quantity);
    void addItems(const std::map<Item, int>& items);
    void operator +=(Receipt receipt);
    void operator =(const Receipt& receipt);

    /*******************************
     ** CONSTANT MEMBER FUNCTIONS **
     *******************************/
    double totalCost() const;
    Receipt operator +(const Receipt& receipt) const;
    std::string printItems() const;
    int itemsSize() const;
    double getItemCost(const Item& item) const;
    int getItemQuantity(const Item& item) const;

  public:
    Date _date;
    std::map<Item, int> _items;
};
/******************************************************************************************
 *  Receipt Class
 *    A Receipt has a Date and a list of Items purchased with their corresponding quantity
 *      Items are automatically sorted by their names
 ******************************************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/******************************************************************************************
 *  Receipt()
 *    Default Constructor; _date is set to null and _items is empty
 *    Parameters: none
 *    Return: void
 ******************************************************************************************/

/******************************************************************************************
 *  explicit Receipt(const Date& date);
 *    Constructor; _date is set to the given parameter Date and _items is empty
 *    Parameters: const Date&
 *    Return: void
 ******************************************************************************************/

/******************************************************************************************
 *  Receipt(const Date& date, const Item& item, int quantity);
 *    Constructor; _date is set to the given parameter Date and given Item is added to
 *      _items along with its given quantity
 *    Parameters: const Date&, const Item&, int
 *    Return: none
 ******************************************************************************************/

/******************************************************************************************
 *  Receipt(const Date& date, const std::map<Item, int>& items);
 *    Constructor; _date and _items are set to the given parameter values
 *    Parameters: const Date&, const std::map<Item, int>& items;
 *    Return: none
 ******************************************************************************************/


/**************
 ** MUTATORS **
 **************/

/******************************************************************************************
 *  void setDate(const Date& date);
 *
 *    Mutator; This method will update the _date attribute to the parameter date value
 * ----------------------------------------------------------------------------------------
 *    Parameters: const Date&
 * ----------------------------------------------------------------------------------------
 *    Return: none
 ******************************************************************************************/


/***************
 ** ACCESSORS **
 ***************/

/******************************************************************************************
 *  std::map<Item, int> getItems() const;
 *
 *    Accessor; This method will return _items
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: std::map<Item, int>
 ******************************************************************************************/

/******************************************************************************************
 *  Date getDate() const;
 *
 *    Accessor; This method will return _date
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: Date
 ******************************************************************************************/


/***********************************
 ** MODIFICATION MEMBER FUNCTIONS **
 ***********************************/

/******************************************************************************************
 *  void addItem(const Item& item, int quantity);
 *
 *    Add the parameter item and quantity to _items
 *      if item already exist in _items, just increase the quantity
 * ----------------------------------------------------------------------------------------
 *    Parameters: const Items&, int
 * ----------------------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************************/

/******************************************************************************************
 *  void addItems(const std::map<Item, int>& items);
 *
 *    Add the map of items to _items
 *      if a particular item already exist in _items, just increase the quantity
 * ----------------------------------------------------------------------------------------
 *    Parameters: const std::map<Item, int>&
 * ----------------------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************************/

/******************************************************************************************
 *  void operator +=(Receipt receipt);
 *
 *    Operator Overload; The items in the parameter Receipt are added to the current _items
 *      And the current Date is set to "null"
 * ----------------------------------------------------------------------------------------
 *    Parameters: const Items&, int
 * ----------------------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************************/

/******************************************************************************************
 *  void operator =(const Receipt& receipt);
 *
 *    Operator Overload; set _date and _items identical to the given Receipt
 * ----------------------------------------------------------------------------------------
 *    Parameters: const Receipt& receipt
 * ----------------------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************************/


/*******************************
 ** CONSTANT MEMBER FUNCTIONS **
 *******************************/

/******************************************************************************************
 *  double totalCost() const;
 *
 *    Return the total cost for all the items on the Receipt
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: double
 ******************************************************************************************/

/******************************************************************************************
 *  Receipt operator +(const Receipt& receipt) const;
 *
 *    Operator Overload; Return a Recipt that contains the sum of items and quantities from
 *      the current Receipt and paramter Receipt. The Date is set to "null".
 * ----------------------------------------------------------------------------------------
 *    Parameters: const Receipt& receipt
 * ----------------------------------------------------------------------------------------
 *    Return: double
 ******************************************************************************************/

/******************************************************************************************
 *  std::string printItems() const;
 *
 *    Return a string of items on the Receipt in the format of:
 *      ->itemName ($price) xitemQuantity
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: std::string
 ******************************************************************************************/

/******************************************************************************************
 *  int itemsSize() const;
 *
 *    Return the number of unique items on the Receipt
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: int
 ******************************************************************************************/

/******************************************************************************************
 *  double getItemCost(const Item& item) const;
 *
 *    Return the total cost of a particular item (item price * item quantity), 0 if not found
 * ----------------------------------------------------------------------------------------
 *    Parameters: const Item&
 * ----------------------------------------------------------------------------------------
 *    Return: double
 ******************************************************************************************/

/******************************************************************************************
 *  int itemsSize(const Item& item) const;
 *
 *    Return the the quantity of a particular item, 0 if not found
 * ----------------------------------------------------------------------------------------
 *    Parameters: const Item&
 * ----------------------------------------------------------------------------------------
 *    Return: int
 ******************************************************************************************/


#endif // RECEIPT_H_
