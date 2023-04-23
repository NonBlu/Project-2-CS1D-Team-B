#pragma once

#include <memory>


/** ***************************************************************
 * @class Vector
 * @brief A templated Vector class.
 * @tparam T User defined type for elements in the Vector.
 * @details Uses an array as the underlying data structure.
 ******************************************************************/
template <typename T>
class Vector
{
  public:

    /* Default Constructor */
    Vector();

    /* Overloaded Constructor */
    Vector(int capacity);

    /* Overloaded Constructor */
    Vector(int capacity, const T& value);

    /* Copy Constructor */
    Vector(const Vector& source);

    /* Move Constructor */
    Vector(Vector&& source) noexcept;

    /* Destructor */
    ~Vector();

    /* Copy assignment operator*/
    const Vector& operator=(const Vector& rhs);

    /* Move assignment operator */
    Vector& operator=(Vector&& rhs) noexcept;

    /* Overloaded subscript operator */
          T& operator[](int index)       { return elem[index]; }
    const T& operator[](int index) const { return elem[index]; }

    /*  Iterators  */
    using Iterator = T*;
    using ConstIterator = const T*;

    Iterator insert(Iterator ptr, const T& value);
    Iterator erase(Iterator ptr);

          Iterator begin()       { return &elem[0];     }
    ConstIterator  begin() const { return &elem[0];     }
          Iterator end()         { return &elem[sizeV]; }
    ConstIterator  end()   const { return &elem[sizeV]; }

    /* Accessors */
    int size()     const { return sizeV; }
    int capacity() const { return space; }

    /* Mutators */
    void resize(int size);
    void reserve(int capacity);
    void pushBack(const T& element);
    void remove(const T& element);
    void clear();
    void sort();

  private:
    int sizeV;    /**<  Number of elements in vector  */
    int space;    /**<  Total capacity                */
    T*  elem;     /**<  Pointer to array of elements  */
};




/**
 * @brief Constructor (Default)
 *
 * @tparam T User defined type for the elements of the Vector.
 *
 * @details All data members are set to a value 0.
*/
template <typename T>
Vector<T>::Vector()
    : sizeV { 0 }, space { 2 }, elem { new T[2] {0} } {}



/**
 * @brief Constructer (overloaded)
 *
 * @param [in] space The initial capacity of the Vector.
 *
 * @details Allocates memory on the heap to hold the amount of
 * elements specified by the parameter space.
 *
 * @remark Data member sizeV will be set to 0, as no elements have
 * been entered into the Vector.
*/
template <typename T>
Vector<T>::Vector(int space)
    : sizeV { 0 }, space { space }, elem { new T[space] {0} } {}



/**
 * @brief Constructor (Overloaded)
 *
 * @tparam T User defined type for the elements of the Vector.
 *
 * @param [in] space The initial capacity of the Vector.
 * @param [in] value The value to fill the vector with.
 *
 * @details Allocates memory on the heap to store elements of type T.
 *
 * @remark The size and capacity will be set to the value of the
 * parameter space.
 *
 * @remark Every element will be the value passed as an argument.
 */
template <typename T>
Vector<T>::Vector(int space, const T& value)
    : sizeV { space }, space { space }, elem { new T[space] }
{
    for (int index {0}; index < space; ++index)
    {
        elem[index] = value;
    }
}



/**
 * @brief Copy Constructor
 *
 * @param [in] source A reference to another Vector to copy.
 *
 * @details Performs a deep copy of the Vector passed as an argument.
*/
template <typename T>
Vector<T>::Vector(const Vector& source)
    : sizeV { source.sizeV }, space { source.space }, elem { new T[source.space] }
{
    for (int index {0}; index < sizeV; ++index)
    {
        elem[index] = source.elem[index];
    }
}



/**
 * @brief Move Constructor
 *
 * @param [in] source A reference to a Vector to move from.
 *
 * @details Moves all values from the Vector passed as an argument
 * and assigns them to the Vector being constructed.
 *
 * @warning The Vector passed as an argument is invalidated.
*/
template <typename T>
Vector<T>::Vector(Vector&& source) noexcept
{
    sizeV = std::move(source.sizeV);
    space = std::move(source.space);
    elem  = std::move(source.elem);

    source.elem = nullptr;
}



/**
 * @brief Destructor
 *
 * @details Dealocates all memory associated with the Vector.
*/
template <typename T>
Vector<T>::~Vector()
{
    delete[] elem;
}



/**
 * @brief Overloaded assignment operator (Copy)
 *
 * @param [in] rhs A const reference to a Vector.
 *
 * @details Performes a deep copy of the Vector on the right side.
 *
 * @return A constant reference to a Vector which was assigned the
 * values the Vector on the right side contained.
*/
template <typename T>
const Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
    if (this != &rhs)
    {
        if (sizeV)
        {
            delete[] elem;

            elem  = new T[rhs.space];

            for (int index {0}; index < rhs.sizeV; ++index)
            {
                elem[index] = rhs.elem[index];
            }
        }
        else
        {
            elem = nullptr;
        }

        sizeV = rhs.sizeV;
        space = rhs.space;
    }

    return *this;
}



/**
 * @brief Overloaded assignment operator (Move)
 *
 * @param [in] rhs A reference to a Vector to move values from.
 *
 * @details Moves elements from the Vector on the right side.
 *
 * @return A reference to a Vector which contains the values of the
 * Vector that was on the right side.
 *
 * @warning The Vector that was on the right side will be invalidated.
*/
template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& rhs) noexcept
{
    delete[] elem;

    elem  = std::move(rhs.elem);
    sizeV = std::move(rhs.sizeV);
    space = std::move(rhs.space);

    rhs.elem = nullptr;
}



/**
 * @brief Resizes the Vector.
 *
 * @param [in] size The new size of the Vector.
 *
 * @details If size is smaller then the Vectors size, then all proceeding
 * values are set 0 and size is adjusted. If size is larger then the
 * capacity, then it is essentially the same as calling capacity().
 *
 * @remark If the size argument is the same as the current size, there
 * is no effect.
 */
template <typename T>
void Vector<T>::resize(int size)
{
    if (size < sizeV)
    {
        for (int index {size-1}; index < sizeV; ++index)
        {
            elem[index] = 0;
        }
    }
    else if (size > space)
    {
        reserve(size);
    }

    sizeV = size;
}



/**
 * @brief Adjusts the capacity of the Vector.
 *
 * @param [in] capacity The number of elements the Vector can hold.
 *
 * @details If the capacity argument is greater then the current
 * capacity of the Vector, then the Vectors capacity is increased
 * to the size specified by the capacity argument.
 *
 * @remark The Vector will still contain all of it's elements.
 *
 * @note This method is called by pushBack() anytime the size
 * reaches the capacity. When it does, the capacity doubles.
 */
template <typename T>
void Vector<T>::reserve(int capacity)
{
    T* array;  /**< New array for elements */

    if (capacity > space)
    {
        array = new T[capacity];

        for (int index {0}; index < sizeV; ++index)
        {
            array[index] = std::move(elem[index]);
        }

        delete[] elem;

        elem  = array;
        space = capacity;
    }
}



/**
 * @brief Adds an element to the back of the Vector.
 *
 * @tparam T User defined type for the elements in the Vector.
 *
 * @param [in] value The value to add to the back of the Vector.
 *
 * @note If the size succeeds the current capacity, then the method
 * capacity() is invoked and the capacity is then doubled.
*/
template <typename T>
void Vector<T>::pushBack(const T& element)
{
    if (!sizeV)
    {
        reserve(4);
    }
    else if (sizeV == space)
    {
        reserve(sizeV << 1);
    }

    elem[sizeV] = element;

    ++sizeV;
}



/**
 * @brief Removes a specified element from the Vector.
 *
 * @tparam T User defined Type for the element.
 *
 * @param [in] element The element to remove.
 *
 * @details Searches the list for a matching element,
 * if a match is found, the element is removed.
 */
template <typename T>
void Vector<T>::remove(const T& element)
{
    bool found { false };  /**< Boolean indicating wither the element was found. */
    int  index {   0   };  /**< Current index while searching through Vector.    */

    while (!found && index < sizeV)
    {
        if (elem[index] == element) found = true;
        else                        ++index;
    }

    if (found) erase(&elem[index]);
}


/**
 * @brief Clears the Vector.
 *
 * @details Deletes all elements and sets the size & capcity to 0.
 *
 * @warning This method deletes all elements in the Vector.
*/
template <typename T>
void Vector<T>::clear()
{
    delete[] elem;

    sizeV = 0;
    space = 0;
}



/**
 * @brief Inserts a element at the specified location.
 *
 * @tparam T User defined type for the elements in the Vector.
 *
 * @param ptr Iterator pointing to the position to insert the element.
 * @param value The value to insert into the Vector.
 *
 * @details Inserts a element and increases the Vectors size by 1.
 *
 * @return Iterator to the location where the element was added,
 * or NULL if the Iterator argument was not a valid position.
*/
template <typename T>
typename Vector<T>::Iterator Vector<T>::insert(Iterator itr, const T& value)
{
    Iterator itr2; /**< Iterator that decrements from end().  */
    int      dif;  /**< Calculates offset from the beginning. */

    if (itr >= begin() && itr < end())
    {
        if (sizeV == space)
        {
            dif = itr - begin();

            reserve(space << 1);

            itr = begin() + dif;
        }

        itr2 = end();

        while (itr2 > itr)
        {
            *itr2 = *(itr2 - 1);
            --itr2;
        }

        *itr = value;

        ++sizeV;

        return itr;
    }
    else
    {
        return nullptr;
    }
}



/**
 * @brief Erases an element from the Vector.
 *
 * @param ptr Iterator pointing to the element to erase.
 *
 * @details Erases an element and decreases the Vectors size by 1.
 *
 * @return Iterator that points to the position where the element
 * was removed. Or NULL if the Iterator argument is not valid.
*/
template <typename T>
typename Vector<T>::Iterator Vector<T>::erase(Iterator itr)
{
    if (itr >= begin() && itr < end())
    {
        for (Iterator p = itr; p < end()-1; ++p)
        {
            *p = *(p+1);
        }

        --sizeV;

        *(end()) = 0;
    }
    else
    {
        itr = nullptr;
    }

    return itr;
}



template <typename T>
void Vector<T>::sort()
{
    int x;

    for (int i {}; i < size() - 1; ++i)
    {
        x = i;

        for (int j {i + 1}; j < size(); ++j)
        {
            if (elem[j] < elem[x]) x = j;
        }

        std::swap(elem[i], elem[x]);
    }
}
