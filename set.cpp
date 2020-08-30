#include <string>
#include "set.h"

/**************************************************************
 *set::set():used(0){}
 * ____________________________________________________________
 * This constructor creates a set
 * ___________________________________________________________
 * Pre-Condition
 * None
 *
 * Post-Condition
 * Now have a set, with 0 used items.
 *************************************************************/
Set::Set()
{
    capacity = 10;
    size = 0;
    data = new value_type[capacity];
}

/*******************************************************************************
 *
 *  Copy Constructor Set
 *______________________________________________________________________________
 *  change the set content to values of the other set
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    the data are set to the same of the source set
 *******************************************************************************/
Set::Set(const Set& source)
{
    data = nullptr;
    *this = source;
}

/*******************************************************************************
 *
 *  Destructor Set
 *______________________________________________________________________________
 *  free the variables
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    noen
 *
 *  POST-CONDITIONS
 *    delte the dynmic array that hold the values
 *******************************************************************************/
Set::~Set()
{
    delete[] data;
}

/*******************************************************************************
 *
 *  Overload operator =: Class Set
 *______________________________________________________________________________
 *  change values in the set the the ones in given parameter
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    this != &source
 *
 *  POST-CONDITIONS
 *    change the set content to values of the source set
 *******************************************************************************/
Set & Set::operator = (const Set& source) //IN - the source set
{
    if (this == &source)
        return *this;
    else
    {
        capacity = source.capacity;
        size = source.size;
        delete [] data;
        data = new value_type[capacity];
        for (size_type i = 0; i < size; i++)
        {
            data[i] = source.data[i];
        }
    }
    return *this;

}

/**************************************************************
 *void set::insert(const value_type& entry)
 * ____________________________________________________________
 * This mutator inserts a particular value.
 * It fails if the value is already in the set
 * ___________________________________________________________
 * Pre-Condition
 * Have a valid set
 *
 * Post-Condition
 * if assertion didn't fail, set now has entry stored
 *************************************************************/
void Set::insert(const value_type& entry)    //IN - the entry to insert
{
    if (!contains(entry))
    {
        if (size < capacity)
        {
            data[size] = entry;
        }

        //PROC - this doubles the capacity of the underlying array
        else
        {
            value_type *tempArray = new value_type[capacity];
            for (size_type i = 0; i < size; i++)
            {
                tempArray[i] = data[i];
            }
            capacity*= 2;
            delete[] data;
            data = new value_type[capacity];
            for (size_type i= 0; i<size;i++)
            {
                data[i] = tempArray[i];
            }
            delete [] tempArray;
            data[size] = entry;
        }
        size++;
    }
}

/**************************************************************
 *bool set::contains(const value_type& target) const
 * ____________________________________________________________
 * This accessor determines if the set contains the target
 * ___________________________________________________________
 * Pre-Condition
 * Have a valid set
 *
 * Post-Condition
 * returns true if the set contains the target
 *************************************************************/
bool Set::contains(const value_type& target) //IN - the target to check
{
    size_type index;

    index = 0;
    while((index < size) && (data[index] != target))
        ++index;

    if(index == size)
        return false;

    return true;
}

/**************************************************************
 *bool set::erase(const value_type& target)
 * ____________________________________________________________
 * This mutator erases the inputted value if found.
 * ___________________________________________________________
 * Pre-Condition
 * Have a valid set
 *
 * Post-Condition
 * the set no longer contains the target
 *************************************************************/
bool Set::erase(const value_type& target)   //IN - the target to erase
{
    size_type index;

    index = 0;
    while((index < size) && (data[index] != target))
        ++index;

    if(index == size)
        return false;

    --size;
    data[index] = data[size];
    return true;
}

/*******************************************************************************
 *
 *  Method sort: Class Set
 *______________________________________________________________________________
 *  Sort the set with the given lambda function
 *  - returns void
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    the set is sorted
 *******************************************************************************/
void Set::sort(bool (*function)(value_type &, value_type &))
//IN - the function pointer to sort by
{
    std::sort(data,data + size, function);
}

/*******************************************************************************
 *
 *  Method length: Class Set
 *______________________________________________________________________________
 *  Get the size of the Set
 *  - returns size_type
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    none
 *
 *  POST-CONDITIONS
 *    size is returned
 *******************************************************************************/
Set::size_type Set::length()
{
    return size;
}

/*******************************************************************************
 *
 *  Overload operator []: Class Set
 *______________________________________________________________________________
 *  Get the value at a given index
 *  - returns value_type
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    index < length()
 *
 *  POST-CONDITIONS
 *    value at index is returned
 *******************************************************************************/
Set::value_type Set::operator[](size_type index) const
//IN - the index to query
{
    return data[index];
}


/*******************************************************************************
 *
 *  Overload operator []: Class Set
 *______________________________________________________________________________
 *  Get the value at a given index
 *  - returns value_type
 *______________________________________________________________________________
 *  PRE-CONDITIONS
 *    index < length()
 *
 *  POST-CONDITIONS
 *    value at index is returned
 *******************************************************************************/
Set::value_type & Set::operator [](size_type index)
//IN - the index to query
{
    return data[index];
}
