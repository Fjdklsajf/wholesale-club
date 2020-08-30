#include <string>
#include "member.h"

/*******************************************************************************
 *
 *  Default Constructor Member
 *______________________________________________________________________________
 *  Creates an empty member, variables are initialized
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    name, id, amount spent set to default
 *    isBasic set to true
 *    premium fee set to 75 basic fee set to 60
 *******************************************************************************/
Member::Member()
{
    _name = "";
    _id = 0;
    _totalSpent = 0;
    _isBasic = true;
    premiumFee = 75.00;
    basicFee = 60.00;
}

/*******************************************************************************
 *
 *  Copy Constructor Member
 *______________________________________________________________________________
 *  Copy one member information to another
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    All private variables are set to the given Member's variables
 *    premium fee set to 75 basic fee set to 60
 *******************************************************************************/
Member::Member(const Member& m)
{
    _expDate = m._expDate;
    _name = m._name;
    _id = m._id;
    _totalSpent=m._totalSpent;
    premiumFee = 75.00;
    basicFee = 60.00;
    _isBasic = m._isBasic;
    _receipts = m._receipts;
}

/*******************************************************************************
 *
 *  Constructor Member
 *______________________________________________________________________________
 *  initialize private variables with given aruguments
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    All private variables are set to the given parameter values
 *    premium fee set to 75 basic fee set to 60
 *******************************************************************************/
Member::Member(std::string name, unsigned int id, double totalSpent,
       Date expDate, bool isBasic)
{
    _name = name;
    _id = id;
    _totalSpent = totalSpent;
    _isBasic = isBasic;
    _expDate = expDate;
    premiumFee = 75.00;
    basicFee = 60.00;
}

/*******************************************************************************
 *
 *  Mutator setName: Class Member
 *______________________________________________________________________________
 *  This method will update the _name attribute to the parameter name value
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _name is set to name
 *******************************************************************************/
void Member::setName(std::string name)
{
    _name = name;
}

/*******************************************************************************
 *
 *  Mutator setId: Class Member
 *______________________________________________________________________________
 *  This method will update the _id attribute to the parameter id value
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _id is set to id
 *******************************************************************************/
void Member::setId(unsigned int id)
{
    _id = id;
}

/*******************************************************************************
 *
 *  Mutator setTotalSpent: Class Member
 *______________________________________________________________________________
 *  This method will update the _totalSpent attribute to the 
 *      parameter totalSpent value
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _totalSpent is set to totalSpent
 *******************************************************************************/
void Member::setTotalSpent(double totalSpent)
{
    _totalSpent = totalSpent;
}

/*******************************************************************************
 *
 *  Mutator setExpirationDate: Class Member
 *______________________________________________________________________________
 *  This method will update the _expDate attribute to the parameter expDate value
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _expDate is set to expDate
 *******************************************************************************/
void Member::setExpirationDate(Date expDate)
{
    _expDate = expDate;
}

/*******************************************************************************
 *
 *  Mutator setMembershipType: Class Member
 *______________________________________________________________________________
 *  This method will update the _isBasic attribute to the parameter isBasic value
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _isBasic is set to isBasic
 *******************************************************************************/
void Member::setMembershipType(bool isBasic)
{
    _isBasic = isBasic;
}

/*******************************************************************************
 *
 *  Accessor getName: Class Member
 *______________________________________________________________________________
 *  This method will return _name
 *  - returns std::string
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _name is returned
 *******************************************************************************/
std::string Member::getName() const
{
    return _name;
}

/*******************************************************************************
 *
 *  Accessor getId: Class Member
 *______________________________________________________________________________
 *  This method will return _id
 *  - returns unsigned int
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _id is returned
 *******************************************************************************/
unsigned int Member::getId() const
{
    return _id;
}

/*******************************************************************************
 *
 *  Accessor isBasic: Class Member
 *______________________________________________________________________________
 *  This method will return _isBasic
 *  - returns bool
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _isBasic is returned
 *******************************************************************************/
bool Member::isBasic() const
{
    return _isBasic;
}

/*******************************************************************************
 *
 *  Accessor getTotalSpent: Class Member
 *______________________________________________________________________________
 *  This method will return _totalSpent
 *  - returns double
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _totalSpent is returned
 *******************************************************************************/
double Member::getTotalSpent() const
{
    return _totalSpent;
}

/*******************************************************************************
 *
 *  Accessor getExpDate: Class Member
 *______________________________________________________________________________
 *  This method will return _expDate
 *  - returns Date
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _expDate is returned
 *******************************************************************************/
Date Member::getExpDate() const
{
    return _expDate;
}

/*******************************************************************************
 *
 *  Accessor getDues: Class Member
 *______________________________________________________________________________
 *  This method will return basicFee or premiumFee based on member type
 *  - returns double
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    basicFee or premiumFee is returned
 *******************************************************************************/
double Member::getDues() const
{
    if (isBasic())
    {
        return basicFee;
    }
    else
        return premiumFee;
}

/*******************************************************************************
 *
 *  Accessor getRebateAmount: Class Member
 *______________________________________________________________________________
 *  This method will return This method will return 5% of totalSpent if preferred member
 *  - returns double
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    0.05 * _totalSpent is returned
 *******************************************************************************/
double Member::getRebateAmount() const
{
    if (_isBasic)
        return 0;
    return .05*_totalSpent;
}

/*******************************************************************************
 *
 *  Accessor getReceipts: Class Member
 *______________________________________________________________________________
 *  This method will return _receipts
 *  - returns std::vector<Receipt>
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _receipts is returned
 *******************************************************************************/
std::vector<Receipt> Member::getReceipts() const
{
    return _receipts;
}

/*******************************************************************************
 *
 *  Method addReceipt: Class Member
 *______________________________________________________________________________
 *  Add a receipt to the list of receipts the member have
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    _totalSpent is adjusted and a receipt is added to the total list
 *******************************************************************************/
void Member::addReceipt(Receipt receipt)
{
    _totalSpent+=(receipt.totalCost())*1.0875;
    _receipts.push_back(receipt);
}

/*******************************************************************************
 *
 *  Overload operator ==: Class Member
 *______________________________________________________________________________
 *  Compare the name and id of two members, return true if they are equal
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    return true if they are equal, false otherwise
 *******************************************************************************/
bool Member::operator == (const Member& m) const
{
    return ((_id == m._id) || (_name == m._name));
}

/*******************************************************************************
 *
 *  Overload operator ==: Class Member
 *______________________________________________________________________________
 *  Compare the name and id of two members, return true if they are not equal
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    return true if they are not equal, false otherwise
 *******************************************************************************/
bool Member::operator !=(const Member& m) const
{
    return !((*this) == m);
}


/*******************************************************************************
 *
 *  Method getReceipts: Class Member
 *______________________________________________________________________________
 *  Return a list of receipt the member has that are within the Date range
 *  - returns std::vecotr<Receipt>
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    The receipts within the Date range are returned
 *******************************************************************************/
std::vector<Receipt> Member::getReceipts(const Date& start, const Date& end) const
{
    std::vector<Receipt> retVal;

    for (size_t i = 0; i < _receipts.size();i++)
    {
        if ((_receipts[i].getDate() < end) && (_receipts[i].getDate() > start))
        {
            retVal.push_back(_receipts[i]);
        }
    }
    return retVal;
}
