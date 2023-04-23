#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <QString>
#include <QDebug>

using std::vector;
using std::string;


/** ***************************************************
 * @struct Entry
 * @tparam [in] Key Type for a key used to map a value
 * @tparam [in] Value Type for a value mapped by a key
 ******************************************************/
template <typename Key, typename Value>
struct Entry
{
    Key    key;     /**< Key used to map a value */
    Value  value;   /**< value mapped by the key */

    Entry()               : key { }, value { }  { }
    Entry(Key k)          : key {k}, value { }  { }
    Entry(Key k, Value v) : key {k}, value {v}  { }
};


/** ***************************************************
 * @class MapBase
 * @brief A base class for an Unordered Map
 * @brief Implimented using a Hash Table
 ******************************************************/
template <typename Key, typename Value>
class MapBase
{
  public:
    using Entry = Entry<Key, Value>;

    /** ************************************************
     * @enum Status
     * @brief Values for the status of a cell in the map
     ***************************************************/
    enum Status : unsigned char
    {
        Empty, Available, Occupied
    };

    /** ***************************************************
     * @struct Cell
     * @brief Structure for the Entrys of the Map
     * @details Contains the Entrys and the status of a cell
     *******************************************************/
    struct Cell
    {
        Entry  entry;   /**< Entry consistying of key-value */
        Status status;  /**< The status of the cell         */

        Cell() : entry { }, status { Status::Empty } { }
    };

    /** *****************************************************
     * @class Iterator
     * @brief A iterator for traversing the cells of the Map
     ********************************************************/
    class Iterator
    {
        friend class MapBase;

      public:
        Value& operator*();

        Iterator operator++();
        Iterator operator--();
        Iterator operator++(int);
        Iterator operator--(int);

        Iterator& operator=(const Iterator& rhs);

        bool operator==(const Iterator& rhs);
        bool operator!=(const Iterator& rhs);

      private:
        Iterator(Cell* cell, MapBase& map)
            : map { map }, current { cell } { }

        MapBase&  map;       /**< Reference to the containing map */
        Cell*     current;   /**< Pointer to the current cell     */
    };


    Iterator put(const Entry& entry);
    Iterator find(const Key& key);
    Iterator begin();
    Iterator end();

    void erase(const Key& key);
    void erase(Iterator p);

    int  size()  const { return  count; }
    bool empty() const { return !count; }
    void print() const;

  protected:
    MapBase(int size = 13);

    unsigned int _h1(unsigned int key) { return key % capacity;  }
    unsigned int _h2(unsigned int key) { return 13 - (key % 13); }

    Iterator  _put(const Entry& entry, unsigned int h1, unsigned int h2);
    Iterator _find(const Key& key,     unsigned int h1, unsigned int h2);
    void    _erase(const Key& key,     unsigned int h1, unsigned int h2);

    vector<Cell> cells;     /**< Vector of cells containing the entrys */
    int          capacity;  /**< The capacity of the vector container  */
    int          count;     /**< The number of entrys in the map       */
};


/**
 * @brief Constructor for the MapBase class
 * @param [in] size The number of cells the map will contain
 * @details Initializes a vector with the specified size, sets the
 * capacity to the specified size, and sets the count to 0
 */
template <typename Key, typename Value>
MapBase<Key, Value>::MapBase(int size) : capacity { size }, count { 0 }
{
    cells = vector<Cell>(size + 1);
}


/**
 * @brief Method to put a new entry into the map
 * @param [in] entry The entry to put into the map
 * @param [in] h1 An integer result from a hash function
 * @param [in] h2 Another integer result from a second hash function
 * @note This is a private method invoked by the class only.
 * @return A Iterator pointing to the position where the Entry was added
 */
template <typename Key, typename Value>
typename MapBase<Key, Value>::Iterator
MapBase<Key, Value>::_put(const Entry& entry, unsigned int h1, unsigned int h2)
{
    int i { };
    int j { };

    do
    {
        i = ((h1 + (j * h2)) % capacity);

        ++j;

    } while (  (cells[i].status == Status::Occupied)
             && entry.key       != cells[i].entry.key );

    if (entry.key != cells[i].entry.key)
    {
        ++count;
    }

    cells[i].entry  = entry;
    cells[i].status = Status::Occupied;

    return Iterator(&cells[i], *this);
}


/**
 * @brief Method to find an entry in the map
 * @param [in] key The key of the entry
 * @param [in] h1 An integer result from a hash function
 * @param [in] h2 Another integer result from a second hash function
 * @note This is a private method invoked by the class only.
 * @return A Iterator pointing to the found position, else null
 */
template <typename Key, typename Value>
typename MapBase<Key, Value>::Iterator
MapBase<Key, Value>::_find(const Key& key, unsigned int h1, unsigned int h2)
{
    int i { };
    int j { };

    do
    {
        i = ((h1 + (j * h2)) % capacity);

        ++j;

    } while (    key             != cells[i].entry.key
             && (cells[i].status != Status::Empty)
             && j < capacity                           );

    return key == cells[i].entry.key ? Iterator(&cells[i], *this) : end();
}


/**
 * @brief Method to erase an entry from the map
 * @param [in] key The key to the entry in the map
 * @param [in] h1 An integer result from a hash function
 * @param [in] h2 Another integer result from a second hash function
 * @note This is a private method invoked by the class only.
 */
template<class Key, class Value>
void MapBase<Key, Value>::_erase(const Key& key, unsigned int h1, unsigned int h2)
{
    int i { };
    int j { };

    do
    {
        i = ((h1 + (j * h2)) % capacity);

        ++j;

    } while (  (cells[i].status != Status::Empty)
             && key             != cells[i].entry.key
             && j < capacity                          );

    if (key == cells[i].entry.key)
    {
        cells[i].status = Status::Available;
    }
}


/**
 * @brief Method to put a entry into the map
 * @param [in] entry The entry to add to the map
 * @details this method calls private methods which
 * hash and put the entry in the map
 * @return An Iterator to the position of the put entry
 */
template <typename Key, typename Value>
typename MapBase<Key, Value>::Iterator
MapBase<Key, Value>::put(const Entry& entry)
{
    return _put(entry, _h1(entry.key), _h2(entry.key));
}


/**
 * @brief method to find an entry in the map
 * @param [in] key The key of the entry to find
 * @details this method calls private methods which
 * compute the hash to find the entry
 * @return A Iterator to the found entry, else null
 */
template <typename Key, typename Value>
typename MapBase<Key, Value>::Iterator
MapBase<Key, Value>::find(const Key& key)
{
    _find(key, _h1(key), _h2(key));
}


/**
 * @brief Method to erase an entry from the map
 * @param [in] key The key of the entry to erase
 * @details calls private methods which compute the hash
 * to find the entry to erase
 */
template <typename Key, typename Value>
void MapBase<Key, Value>::erase(const Key& key)
{
    _erase(key, _h1(key), _h2(key));
}


/**
 * @brief method to erase an entry from the map
 * @param [in] p A Iterator pointing to an entry
 * @details removes the entry pointed to by p
 */
template <typename Key, typename Value>
void MapBase<Key, Value>::erase(Iterator p)
{
    p.current->entry.status = Status::Available;
}


/**
 * @brief Method to get a Iterator to the beggining of the map
 * @return A Iterator pointing to first entry in the map
 */
template <typename Key, typename Value>
inline typename MapBase<Key, Value>::Iterator
MapBase<Key, Value>::begin()
{
    Iterator p(&cells[0], *this);

    if (p.current->status != Status::Occupied) ++p;

    return p;
}


/**
 * @brief Method to get an Iterator to the end of the map
 * @return An Iterator pointing one past the last available cell
 */
template<typename Key, typename Value>
inline typename MapBase<Key, Value>::Iterator
MapBase<Key, Value>::end()
{
    return Iterator(&cells[capacity], *this);
}


/**
 * @brief Overloaded assignment operator for an Iterator
 * @param [in] rhs A reference to another Iterator
 * @return A Iterator assigned the values of the rhs Iterator
 */
template<typename Key, typename Value>
inline typename MapBase<Key, Value>::Iterator&
MapBase<Key, Value>::Iterator::operator=(const Iterator& rhs)
{
    this->map     = rhs.map;
    this->current = rhs.current;

    return *this;
}


/**
 * @brief Overloaded dereference operator for an Iterator
 * @return A reference to an entry the Iterator is pointing to
 */
template<typename Key, typename Value>
inline Value&
MapBase<Key, Value>::Iterator::operator*()
{
    return current->entry.value;
}


/**
 * @brief Overloaded pre-incriment operator for an Iterator
 * @return Iterator pointing to the next occupied cell
 */
template<typename Key, typename Value>
inline typename MapBase<Key, Value>::Iterator
MapBase<Key, Value>::Iterator::operator++()
{
    do
    {
        ++current;

    } while (   current->status != Status::Occupied
             && current         != &map.cells[map.capacity] );

    return *this;
}


/**
 * @brief Overloaded post-incriment operator for an Iterator
 * @details Advances the Iterator to the next occupied cell
 * @return Iterator pointing to the current position
 */
template <typename Key, typename Value>
inline typename MapBase<Key, Value>::Iterator
MapBase<Key, Value>::Iterator::operator++(int)
{
    Iterator p { *this };

    do
    {
        ++current;

    } while (   current->status != Status::Occupied
             && current         != &map.cells[map.capacity] );

    return p;
}


/**
 * @brief Overloaded pre-incriment operator for an Iterator
 * @return Iterator pointing to the previous occupied cell
 */
template <typename Key, typename Value>
inline typename MapBase<Key, Value>::Iterator
MapBase<Key, Value>::Iterator::operator--()
{
    do
    {
        --current;

    } while (   current->status != Status::Occupied
             && current         >= &map.cells[0]    );

    return *this;
}


/**
 * @brief Overloaded post-incriment operator for an Iterator
 * @details decriments the Iterator to the previously occupied cell
 * @return Iterator pointing to the current cell
 */
template <typename Key, typename Value>
inline typename MapBase<Key, Value>::Iterator
MapBase<Key, Value>::Iterator::operator--(int)
{
    Iterator p { *this };

    do
    {
        --current;

    } while (   current->status != Status::Occupied
             && current         >= &map.cells[0]    );

    return p;
}


/**
 * @brief Overloaded equality operator for an Iterator
 * @param [in] rhs Iterator on the right side of the operator
 * @return true if the Iterator points to the same cell, else false
 */
template <typename Key, typename Value>
inline bool MapBase<Key, Value>::Iterator::operator==(const Iterator& rhs)
{
    return current == rhs.current;
}


/**
 * @brief Overloaded inequality operator
 * @param [in] rhs Iterator on the right side of operator
 * @return true if the Iterators doint point to the same cell, else false
 */
template <typename Key, typename Value>
inline bool MapBase<Key, Value>::Iterator::operator!=(const Iterator& rhs)
{
    return current != rhs.current;
}


/**
 * @brief Method to print all the cells in the map
 * @details Prints the entry and/or the status of the cell to the console
 */
template <typename Key, typename Value>
void MapBase<Key, Value>::print() const
{
    int index { };

    for (auto& cell : cells)
    {
        std::cout << "Index[" << index << ']';

        if (index < 10) std::cout << "  =  ";
        else            std::cout << " =  ";

        if      (cell.status == Status::Empty)     std::cout << "Empty";
        else if (cell.status == Status::Available) std::cout << "Available";
        else                                       std::cout << cell.entry.key   << "  "
                                                             << cell.entry.value;

        std::cout << std::endl;

        ++index;
    }
}






// -------------- Base Template for specialization ---------------
template <typename Key, typename Value>
class Map : public MapBase <Key, Value> {};
// ---------------------------------------------------------------



//------- Template Specialization (Key = std::string) -----------

// Prototype:
template <typename Value>
class Map<string, Value> : public MapBase<string, Value>
{
  public:
    using Entry    = Entry<string, Value>;
    using Iterator = typename MapBase<string, Value>::Iterator;

    Map(int size = 13) : MapBase<string, Value>(size) { }

    Iterator put(const Entry& entry);
    Iterator find(const string& key);

    void erase(const string& key);

  private:
    unsigned int hash(const string& key);
};


// Definitions:
template <typename Value>
unsigned int Map<string, Value>::hash(const string& key)
{
    unsigned int hash { };

    for (int i {}; i < key.length(); ++i)
    {
        hash  = (hash << 5) | (hash >> 27);
        hash += static_cast<unsigned int>(key[i]);
    }

    return hash;
}

template <typename Value>
typename Map<string, Value>::Iterator Map<string, Value>::put(const Entry& entry)
{
    unsigned int h { hash(entry.key) };

    return MapBase<string, Value>::_put(entry, Map::_h1(h), Map::_h2(h));
}

template <typename Value>
typename Map<string, Value>::Iterator Map<string, Value>::find(const string& key)
{
    unsigned int h { hash(key) };

    return MapBase<string, Value>::_find(key, Map::_h1(h), Map::_h2(h));
}

template <typename Value>
void Map<string, Value>::erase(const string& key)
{
    unsigned int h { hash(key) };

    MapBase<string, Value>::_erase(key, Map::_h1(h), Map::_h2(h));
}

// ------------- End std::striing specialization -----------------








//------- Template Specialization (Key = QString) -----------

// Prototype:
template <typename Value>
class Map<QString, Value> : public MapBase<QString, Value>
{
  public:
    using Entry    = Entry<QString, Value>;
    using Iterator = typename MapBase<QString, Value>::Iterator;

    Map(int size = 53) : MapBase<QString, Value>(size) {  }

    Iterator  put(const Entry& entry);
    Iterator find(const QString& key);
    void    erase(const QString& key);

  private:
    unsigned int hash(const QString& key);
};


// Definitions:
template <typename Value>
unsigned int Map<QString, Value>::hash(const QString& key)
{
    unsigned int hash { };

    for (int i {}; i < key.length(); ++i)
    {
        hash  = (hash << 5) | (hash >> 27);
        hash += static_cast<unsigned int>(key[i].unicode());
    }

    return hash;
}

template <typename Value>
typename Map<QString, Value>::Iterator Map<QString, Value>::put(const Entry& entry)
{
    unsigned int h { hash(entry.key) };

    return MapBase<QString, Value>::_put(entry, Map::_h1(h), Map::_h2(h));
}

template <typename Value>
typename Map<QString, Value>::Iterator Map<QString, Value>::find(const QString& key)
{
    unsigned int h { hash(key) };

    return MapBase<QString, Value>::_find(key, Map::_h1(h), Map::_h2(h));
}

template <typename Value>
void Map<QString, Value>::erase(const QString& key)
{
    unsigned int h { hash(key) };

    MapBase<QString, Value>::_erase(key, Map::_h1(h), Map::_h2(h));
}


// ------------- End QString specialization -----------------
