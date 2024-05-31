#ifndef OPEN_HASH_MAP
#define OPEN_HASH_MAP

#include "entry.h"
#include "user.h"
#include "linked_list.h"
#include <vector>
#include <iostream>

template <typename T>
class open_hash_map{
    public:
        using Entry = entry<T, user*>*;
        using Linked_list = linked_list<T, user*>*;
        using Vector = std::vector<linked_list<T, user*>*>*;
    private:
        int size;
        int capacity;
        Vector container;
        std::vector<T> keysSet;
        std::vector<user*> valuesSet;
        int (*hash_function)(T);
    public:
        open_hash_map(int capacity, int (*hash_function)(T)) : size(0), capacity(capacity), hash_function(hash_function){
            container = new std::vector<Linked_list>(capacity);
        }
        open_hash_map(int (*hash_function)(T)) : size(0), capacity(5), hash_function(hash_function) {
            container = new std::vector<Linked_list>(capacity);
        }
        ~open_hash_map() = default;
        user* get(T);
        void put(T, user*, bool duplicating = false);
        user* remove(T);
        int getSize();
        bool isEmpty();
        std::vector<T> keys();
        std::vector<user*> values();
        int function(T);
        void printCapacity(){
            std::cout << "Capacidad: "<< capacity << std::endl;
        }
    private:
        void duplicate();  

};

template <typename T>
user* open_hash_map<T>::get(T key){
    int index = function(key);
    if((*container)[index]){
        int list_index = (*container)[index]->find(key);
        return (*container)[index]->get(list_index)->value;
    }
    else{
        return nullptr;
    }
}

//Ingresa un nuevo par de elementos al hash map o reemplaza el anterior, y retorna nullPtr o el valor del par anterior, respectivamente. 
template <typename T>
void open_hash_map<T>::put(T key, user* usuario, bool duplicating){
    for(long long unsigned i=0 ; i<keysSet.size() ; i++){
        if(key == keysSet[i]){
            return;
        }
    }
    int index = function(key);
    Entry newEntry = new entry<T, user*>(key, usuario);
    if((*container)[index]){
        keysSet.push_back(key);
        valuesSet.push_back(usuario);
        (*container)[index]->push_back(newEntry);
        size++;
        if(!duplicating){duplicate();}
        
    }
    else{
        size++;
        keysSet.push_back(key);
        valuesSet.push_back(usuario);
        (*container)[index] = new linked_list<T, user*>();
        (*container)[index]->push_back(newEntry);
        if(!duplicating){duplicate();}
    }
}

//elimina el par con clave 'key'
template <typename T>
user* open_hash_map<T>::remove(T key){
    int index = function(key);
    if((*container)[index]){
        int list_index = (*container)[index]->find(key);
        Entry tmp = (*container)[index]->remove(list_index);
        size--;
        for(long long unsigned int i=0 ; i<valuesSet.size() ; i++){
            if(valuesSet[i] == tmp->value){
                valuesSet.erase(valuesSet.begin() + i);
                keysSet.erase(keysSet.begin() + i);
                break;
            }
        }
        return tmp->value;
    }
    else{
        return nullptr;
    }
}

template <typename T>
int open_hash_map<T>::getSize(){
    return size;
}

template <typename T>
bool open_hash_map<T>::isEmpty(){
    return size==0;
}

template <typename T>
std::vector<T> open_hash_map<T>::keys(){
    return keysSet;
}

template <typename T>
std::vector<user*> open_hash_map<T>::values(){
    return valuesSet;
}

template <typename T>
int open_hash_map<T>::function(T key){
    return hash_function(key) % capacity;
}

//Duplica el tamaño del contenedor en caso de que hayan una cantidad de elementos igual al 90% del tamaño del contenedor.
template <typename T>
void open_hash_map<T>::duplicate(){
    if(size >= int(capacity * 0.9f)){
        //Crea un hash map con el doble de tamaño para no tener que recorrer
        open_hash_map* tmp_map = new open_hash_map(2 * capacity, hash_function);
        for(auto key : keysSet){
            user* tmp_user = get(key);
            tmp_map->put(key, tmp_user);
        }

        delete container;

        container = new std::vector<Linked_list>(capacity * 2);
        std::vector<T> tmp_keys = tmp_map->keys();
        for(auto key : tmp_keys){
            user* tmp_user = tmp_map->get(key);
            put(key, tmp_user, true);
        }
        delete tmp_map;
        capacity *= 2;
    }
}



#endif