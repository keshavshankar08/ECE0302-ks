#include "Database.hpp"

template <typename T>
Database<T>::Database() {
    actualSize = 0;
}

template <typename T>
bool Database<T>::isEmpty() {
    return actualSize == 0;
}

template <typename T>
std::size_t Database<T>::getNumberOfEntries() {
    return actualSize;
}

template <typename T>
bool Database<T>::add(std::string key1, std::string key2, const T& item) {
    //dummy variable to pass in
    size_t pos;

    //if can successfully add keys to trees
    if(!tree1.retrieve(key1, pos) && !tree2.retrieve(key2, pos)){
        tree1.insert(key1, data.getLength());
        tree2.insert(key2, data.getLength());
        //create new data entry
        EntryObj<T> newEntry;

        //set its vars and add to the list
        newEntry.setMembers(item, key1, key2);
        data.insert(data.getLength(), newEntry);
        actualSize++;

        return true;
    }
    //else cant add
    else{
        return false;
    }
}

template <typename T>
bool Database<T>::remove(std::string key) {
    //dummy variable to pass in
    size_t pos;
    
    //if key exists in tree 1, get it and remove key2 in other tree
    if(tree1.retrieve(key, pos)){
        std::string k2 = data.getEntry(pos).key2;

        //remove the entry data
        tree1.remove(key);
        tree2.remove(k2);
        actualSize--;

        return true;
    }
    //if key exists in tree 2, get it and remove key1 in other tree
    else if(tree2.retrieve(key, pos)){
        std::string k1 = data.getEntry(pos).key1;

        //remove the entry data
        tree1.remove(k1);
        tree2.remove(key);
        actualSize--;
        
        return true;
    }
    //else no key
    else{
        return false;
    }
}

template <typename T>
void Database<T>::clear() {
    //destroy everything 
    data.clear();
    tree1.destroy();
    tree2.destroy();
    actualSize = 0;
}

template <typename T>
T Database<T>::getValue(std::string key) {
    //dummy variable
    size_t pos;

    //if pos exists in either tree, get the item there
    if(tree1.retrieve(key, pos) || tree2.retrieve(key, pos)){
        return data.getEntry(pos).item;
    }
    //else return
    else{
        return T();
    }
}

template <typename T>
bool Database<T>::contains(std::string key) {
    //dummy variable
    size_t pos;

    //return success if found
    return tree1.retrieve(key, pos) || tree2.retrieve(key, pos);
}
