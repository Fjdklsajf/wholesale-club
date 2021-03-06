#ifndef MEMBER_H_
#define MEMBER_H_

#include <string>
#include <vector>
#include "receipt.h"
#include "date.h"

class Member {
  public:

    /******************************
     ** CONSTRUCTOR & DESTRUCTOR **
     ******************************/
    Member();
    Member(std::string name, unsigned int id, double totalSpent,
           Date expDate, bool isBasic);
    Member(const Member& m);

    /**************
     ** MUTATORS **
     **************/
    void setName(std::string name);
    void setId(unsigned int id);
    void setTotalSpent(double totalSpent);
    void setExpirationDate(Date expDate);
    void setMembershipType(bool isBasic);

    /***************
     ** ACCESSORS **
     ***************/
    std::string getName() const;
    unsigned int getId() const;
    bool isBasic() const;
    double getTotalSpent() const;
    Date getExpDate() const;
    double getDues() const;
    double getRebateAmount() const;
    std::vector<Receipt> getReceipts() const;

    /***********************************
     ** MODIFICATION MEMBER FUNCTIONS **
     ***********************************/
    void addReceipt(Receipt receipt);

    /*******************************
     ** CONSTANT MEMBER FUNCTIONS **
     *******************************/
    bool operator ==(const Member& m) const;
    bool operator !=(const Member& m) const;
    std::vector<Receipt> getReceipts(const Date& start, const Date& end) const;
    
  private:
    double premiumFee;
    double basicFee;
    std::string _name;
    unsigned int _id;
    double _totalSpent;
    Date _expDate;
    std::vector<Receipt> _receipts;
    bool _isBasic;
};
/******************************************************************************************
 *  Member Class
 *    A member in the Wholesale with their information and purchase history
 ******************************************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/******************************************************************************************
 *  Member()
 *    Default Constructor; An "empty" member, variables are initialized
 *    Parameters: none
 *    Return: void
 ******************************************************************************************/

/******************************************************************************************
 *  Member(const Member& m)
 *    Copy Constructor; Copy one member information to another
 *    Parameters: const Member& m
 *    Return: void
 ******************************************************************************************/

/******************************************************************************************
 *  Member(std::string name, unsigned int id, double totalSpent,
 *        Date expDate, bool isBasic)
 *    Constructor; initialize private variables with given aruguments
 *    Parameters: std::string, unsigned int, double, Date, bool
 *    Return: void
 ******************************************************************************************/


/**************
 ** MUTATORS **
 **************/

/******************************************************************************************
 *  void setName(std::string name);
 *
 *    Mutator; This method will update the _name attribute to the parameter name value
 * ----------------------------------------------------------------------------------------
 *    Parameters: std::string
 * ----------------------------------------------------------------------------------------
 *    Return: none
 ******************************************************************************************/

/******************************************************************************************
 *  void setId(unsigned int id);
 *
 *    Mutator; This method will update the _id attribute to the parameter id value
 * ----------------------------------------------------------------------------------------
 *    Parameters: unsigned int
 * ----------------------------------------------------------------------------------------
 *    Return: none
 ******************************************************************************************/

/******************************************************************************************
 *  void setTotalSpent(double totalSpent);
 *
 *    Mutator; This method will update the _totalSpent attribute to the parameter 
 *        totalSpent value
 * ----------------------------------------------------------------------------------------
 *    Parameters: double
 * ----------------------------------------------------------------------------------------
 *    Return: none
 ******************************************************************************************/

/******************************************************************************************
 *  void setExpirationDate(Date expDate);
 *
 *    Mutator; This method will update the _expDate attribute to the parameter expDate value
 * ----------------------------------------------------------------------------------------
 *    Parameters: Date
 * ----------------------------------------------------------------------------------------
 *    Return: none
 ******************************************************************************************/

/******************************************************************************************
 *  void setMembershipType(bool isBasic);
 *
 *    Mutator; This method will update the _isBasic attribute to the parameter isBasic value
 * ----------------------------------------------------------------------------------------
 *    Parameters: bool
 * ----------------------------------------------------------------------------------------
 *    Return: none
 ******************************************************************************************/


/***************
 ** ACCESSORS **
 ***************/

/******************************************************************************************
 *  std::string getName() const;
 *
 *    Accessor; This method will return _name
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: std::string
 ******************************************************************************************/

/******************************************************************************************
 *  unsigned int getId() const;
 *
 *    Accessor; This method will return _id
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: unsigned int
 ******************************************************************************************/

/******************************************************************************************
 *  bool isBasic() const;
 *
 *    Accessor; This method will return _isBasic
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************************/

/******************************************************************************************
 *  double getTotalSpent() const;
 *
 *    Accessor; This method will return _totalSpent
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: double
 ******************************************************************************************/

/******************************************************************************************
 *  Date getExpDate() const;
 *
 *    Accessor; This method will return _expDate
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: Date
 ******************************************************************************************/

/******************************************************************************************
 *  double getDues() const;
 *
 *    Accessor; This method will return basicFee or premiumFee based on member type
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: double
 ******************************************************************************************/

/******************************************************************************************
 *  double getRebateAmount() const;
 *
 *    Accessor; This method will return 5% of totalSpent if preferred member
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: double
 ******************************************************************************************/

/******************************************************************************************
 *  std::vector<Receipt> getReceipts() const;
 *
 *    Accessor; This method will return _receipts
 * ----------------------------------------------------------------------------------------
 *    Parameters: none
 * ----------------------------------------------------------------------------------------
 *    Return: std::vector<Receipt>
 ******************************************************************************************/


/***********************************
 ** MODIFICATION MEMBER FUNCTIONS **
 ***********************************/

/******************************************************************************************
 *  void addReceipt(Receipt receipt);
 *
 *    Add a receipt to the list of receipts the member have
 * ----------------------------------------------------------------------------------------
 *    Parameters: Receipt
 * ----------------------------------------------------------------------------------------
 *    Return: void
 ******************************************************************************************/


/*******************************
 ** CONSTANT MEMBER FUNCTIONS **
 *******************************/

/******************************************************************************************
 *  bool operator ==(const Member& m) const;
 *
 *    Compare the name and id of two members, return true if they are equal
 * ----------------------------------------------------------------------------------------
 *    Parameters: const member&
 * ----------------------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************************/

/******************************************************************************************
 *  bool operator !=(const Member& m) const;
 *
 *    Compare the name and id of two members, return true if they are not equal
 * ----------------------------------------------------------------------------------------
 *    Parameters: const member&
 * ----------------------------------------------------------------------------------------
 *    Return: bool
 ******************************************************************************************/

/******************************************************************************************
 *  std::vecotr<Receipt> operator ==(const Date& start, const Date& end) const;
 *
 *    Return a list of receipt the member has that are within the Date range
 * ----------------------------------------------------------------------------------------
 *    Parameters: const member&
 * ----------------------------------------------------------------------------------------
 *    Return: std::vector<Receipt>
 ******************************************************************************************/


#endif // MEMBER_H_
