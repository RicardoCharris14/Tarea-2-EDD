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
        int (*hash_function)(T, int);
        std::vector<T> keySet;
        std::vector<user*> valueSet;
    public:
        open_hash_map(int capacity, int (*hash_function)(T, int)) : size(0), capacity(capacity), hash_function(hash_function){
            container = new std::vector<Linked_list>(capacity);
        }
        open_hash_map(int (*hash_function)(T, int)) : size(0), capacity(5), hash_function(hash_function) {
            container = new std::vector<Linked_list>(capacity);
        }
        ~open_hash_map();
        user* get(T);
        void put(T, user*, bool duplicating = false);
        user* remove(T);
        int getSize();
        bool isEmpty();
        int function(T);
        std::vector<T> keys();
        std::vector<user*> values();
        void printCapacity(){
            std::cout << "Capacidad: "<< capacity << std::endl;
        }
        void printSize(){
            std::cout << "Size: "<< size << std::endl;
        }
    private:
        void duplicate();  

};

//Elimina los punteros 'user*' que se encuentrarn dentro de valueSet y los contenedores.
template <typename T>
open_hash_map<T>::~open_hash_map(){
    for(long long unsigned i=0 ; i<valueSet.size() ; i++){
        delete valueSet[i];
    }
}

//Obtiene el valor asociado a la key ingresada por parametro en caso de que se encuentre en el hash map.
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
    int index = function(key);
    Entry newEntry = new entry<T, user*>(key, usuario);
    if((*container)[index] != nullptr){
        (*container)[index]->push_back(newEntry);
        if(!duplicating){
            size++;
            keySet.push_back(key);
            valueSet.push_back(usuario);
            duplicate();
        }
    }
    else{
        (*container)[index] = new linked_list<T, user*>();
        (*container)[index]->push_back(newEntry);
        if(!duplicating){
            size++;
            keySet.push_back(key);
            valueSet.push_back(usuario);
            duplicate();
        }
    }
}

//elimina el par con clave 'key'
template <typename T>
user* open_hash_map<T>::remove(T key){
    int index = function(key);
    if((*container)[index]){
        int list_index = (*container)[index]->find(key);
        Entry tmp = (*container)[index]->remove(list_index);
        if((*container)[index]->is_empty()){
            delete (*container)[index];
            (*container)[index] = nullptr;
        }
        size--;
        for(long long unsigned i=0 ; i<keySet.size() ; i++){
            if(keySet[i]== key){
                keySet.erase(keySet.begin() + i);
                valueSet.erase(valueSet.begin() + i);
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

//Ejecuta la funcion hash, que se ingreso en el constructor, para le key ingresada.
template <typename T>
int open_hash_map<T>::function(T key){
    return hash_function(key, capacity);
}

template <typename T>
std::vector<T> open_hash_map<T>::keys(){
    return keySet;
}

template <typename T>
std::vector<user*> open_hash_map<T>::values(){
    return valueSet;
}

//Duplica el tamaño del contenedor en caso de que hayan una cantidad de elementos igual al 90% del tamaño del contenedor.
template <typename T>
void open_hash_map<T>::duplicate(){
    if(size >= int(capacity * 0.9f)){
        //Crea un hash map con el doble de tamaño para no tener que recorrer
        open_hash_map* tmp_map = new open_hash_map(2 * capacity, hash_function);
        for(auto key : keySet){
            user* tmp_user = get(key);
            tmp_map->put(key, tmp_user, true);
        }

        delete container;

        container = new std::vector<Linked_list>(capacity * 2);
        capacity *= 2;
        for(auto key : keySet){
            user* tmp_user = tmp_map->get(key);
            put(key, tmp_user, true);
        }
        delete tmp_map;
    }
}



#endif