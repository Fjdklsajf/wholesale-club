#ifndef SET_H
#define SET_H

#include <cassert>
#include <stddef.h>
#include <string>
#include "member.h"

class Set {
    //TYPEDEFINITIONS//
    typedef Member value_type;     // Value type of the set
    typedef size_t size_type;      // Size type for the set

  public:
    /******************************
     ** CONSTRUCTOR & DESTRUCTOR **
     ******************************/
    Set();
    ~Set();
    Set(const Set& source); //IN - source Set

    /***********************************
     ** MODIFICATION MEMBER FUNCTIONS **
     ***********************************/
    Set & operator = (const Set& source);   //IN - source list
    void insert(const value_type& entry);   //IN - the entry to insert
    bool contains(const value_type& target);//IN - the target to check
    bool erase(const value_type& target);   //IN - the target to erase
    void sort(bool (*function)(value_type &, value_type &));
    size_type length();
    value_type & operator [](size_type index);
    

    /*******************************
     ** CONSTANT MEMBER FUNCTIONS **
     *******************************/
    value_type operator[](size_type index) const; //IN - the desired index

  private:
    size_type capacity; //  This is the capacity of the underlying array
    value_type* data;   //  IN/OUT The underlying array that data
    size_type size;     //  IN/OUT The num of used spots in the array
};
/*******************************************************************************
 *  Set Class
 *    A user defined Set class which imitates the std::set
 *******************************************************************************/


/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
 ******************************/

/*******************************************************************************
 *  Set()
 *    Default Constructor; initialize the set
 *    Parameters: none
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  Set(const Set& source)
 *    Copy Constructor; change the set content to values of the other set
 *    Parameters: const Set&
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  ~Set()
 *    Destructor; deletes the dynamic array that hold the values
 *    Parameters: none
 *    Return: void
 *******************************************************************************/


/***********************************
 ** MODIFICATION MEMBER FUNCTIONS **
 ***********************************/

/*******************************************************************************
 *  Set& operator =(const Set& source);
 *
 *    change values in the set the the ones in given parameter
 * -----------------------------------------------------------------------------
 *    Parameters: const Set&
 * -----------------------------------------------------------------------------
 *    Return: Set&
 *******************************************************************************/

/*******************************************************************************
 *  void insert(const value_type& entry);
 *
 *    This function receives receives a pointer that points to the
 *      start of the set's underlying array, the size of the array,
 *      and the entry, then adds the entry to the set
 *      and number then outputs the appropriate header
 * -----------------------------------------------------------------------------
 *    Parameters: cosnt value_type&
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  bool contains(const value_type& target);
 *
 *    This function receives receives a pointer that points to the
 *      start of the set's underlying array, the size of the array,
 *      and a target value, then determines if the target is in the set
 *      - returns true if the set contains the target
 * -----------------------------------------------------------------------------
 *    Parameters: const value_type&
 * -----------------------------------------------------------------------------
 *    Return: bool
 *******************************************************************************/

/*******************************************************************************
 *  bool erase(const value_type& target);
 *
 *    This function receives receives a pointer that points to the
 *      start of the set's underlying array, the size of the array,
 *      and a target value, then erases the target from the set.
 * -----------------------------------------------------------------------------
 *    Parameters: const value_type&
 * -----------------------------------------------------------------------------
 *    Return: bool
 *******************************************************************************/

/*******************************************************************************
 *  void sort(bool (*function)(value_type& , value_type&));
 *
 *    Sort the set with the given lambda function
 * -----------------------------------------------------------------------------
 *    Parameters: bool (*function)(value_type&, value_type&)
 * -----------------------------------------------------------------------------
 *    Return: void
 *******************************************************************************/

/*******************************************************************************
 *  size_type length();
 *
 *    Get the size of the Set
 * -----------------------------------------------------------------------------
 *    Parameters: none
 * -----------------------------------------------------------------------------
 *    Return: size_type
 *******************************************************************************/

/*******************************************************************************
 *  value_type& operator [](size_type index);
 *
 *    Get the value at a given index
 * -----------------------------------------------------------------------------
 *    Parameters: size_type
 * -----------------------------------------------------------------------------
 *    Return: value_type&
 *******************************************************************************/


/*******************************
 ** CONSTANT MEMBER FUNCTIONS **
 *******************************/

/*******************************************************************************
 *  value_type operator [](size_type index) const;
 *
 *    Get the value at a given index
 * -----------------------------------------------------------------------------
 *    Parameters: size_type
 * -----------------------------------------------------------------------------
 *    Return: value_type
 *******************************************************************************/
#endif // SET_H
