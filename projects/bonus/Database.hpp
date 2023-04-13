
#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "list.hpp"
#include "binary_search_tree.hpp"

//struct to store information of each entry in the database
template <typename T>
struct EntryObj{
  //information vars
  T item;
  std::string key1, key2;

  //helper to set vars
  void setMembers(T i, std::string k1, std::string k2){
    item = i;//PUB YEAR
    key1 = k1;//ISBN
    key2 = k2;//CATALOG ID
  }
};

template <typename T>
class Database
{
public:
  Database();

  // determine if the database is empty
  bool isEmpty();

  // return current number of entries
  std::size_t getNumberOfEntries();

  // insert entry 
  bool add(std::string key1, std::string key2, const T& item);

  // remove entry 
  bool remove(std::string key);

  // remove all entries
  void clear();

  // retrieve the value of the entry associated with the input key
  T getValue(std::string key);

  // return true if an entry exists associated with the input key
  bool contains(std::string key);

private:
    //list of entry objects
    List<EntryObj<T>> data;

    //trees of key1's and key2's 
    BinarySearchTree<std::string, std::size_t> tree1, tree2; 

    //var for keeping track of size, since built in size is inaccurate when removing elements from tree & list
    int actualSize;
};

#include "Database.tpp"
#endif // _DATABASE_H_