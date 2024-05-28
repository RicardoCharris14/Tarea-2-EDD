#ifndef OPEN_HASH_MAP
#define OPEN_HASH_MAP

#include "entry.h"
#include "user.h"
#include "linked_list.h"
#include <vector>
#include <iostream>

class open_hash_map{
    public:
        using Entry = entry<long double, user*>*;
        using Linked_list = linked_list<long double, user*>*;
        using Vector = std::vector<linked_list<long double, user*>*>*;
    private:
        int size;
        int capacity;
        Vector container;
        std::vector<long double> keysSet;
        std::vector<user*> valuesSet;
    public:
        open_hash_map(int capacity) : size(0), capacity(capacity){
            container = new std::vector<Linked_list>(capacity);
        }
        open_hash_map() : size(0), capacity(5) {
            container = new std::vector<Linked_list>(capacity);
        }
        ~open_hash_map() = default;
        user* get(long double);
        void put(long double, user*, bool);
        user* remove(long double);
        int getSize();
        bool isEmpty();
        std::vector<long double> keys();
        std::vector<user*> values();
        int function(long double);
        void printCapacity(){
            std::cout << "Capacidad: "<< capacity << std::endl;
        }
    private:
        void duplicate();  

};

user* open_hash_map::get(long double user_id){
    int index = function(user_id);
    if((*container)[index]){
        int list_index = (*container)[index]->find(user_id);
        return (*container)[index]->get(list_index)->value;
    }
    else{
        return nullptr;
    }
}

//Ingresa un nuevo par de elementos al hash map o reemplaza el anterior, y retorna nullPtr o el valor del par anterior, respectivamente. 
void open_hash_map::put(long double user_id, user* usuario, bool duplicating = false){
    for(long long unsigned i=0 ; i<keysSet.size() ; i++){
        if(user_id == keysSet[i]){
            return;
        }
    }
    int index = function(user_id);
    Entry newEntry = new entry<long double, user*>(user_id, usuario);
    if((*container)[index]){
        keysSet.push_back(user_id);
        valuesSet.push_back(usuario);
        (*container)[index]->push_back(newEntry);
        size++;
        if(!duplicating){duplicate();}
        
    }
    else{
        size++;
        keysSet.push_back(user_id);
        valuesSet.push_back(usuario);
        (*container)[index] = new linked_list<long double, user*>();
        (*container)[index]->push_back(newEntry);
        if(!duplicating){duplicate();}
    }
}

//elimina el par con clave 'user_id'
user* open_hash_map::remove(long double user_id){
    int index = function(user_id);
    if((*container)[index]){
        int list_index = (*container)[index]->find(user_id);
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

int open_hash_map::getSize(){
    return size;
}

bool open_hash_map::isEmpty(){
    return size==0;
}

std::vector<long double> open_hash_map::keys(){
    return keysSet;
}

std::vector<user*> open_hash_map::values(){
    return valuesSet;
}

int open_hash_map::function(long double user_id){
    return int(user_id) % capacity;
}

//Duplica el tamaño del contenedor en caso de que hayan una cantidad de elementos igual al 90% del tamaño del contenedor.
void open_hash_map::duplicate(){
    if(size >= int(capacity * 0.9f)){
        //Crea un hash map con el doble de tamaño para no tener que recorrer
        open_hash_map* tmp_map = new open_hash_map(2 * capacity);
        for(auto key : keysSet){
            user* tmp_user = get(key);
            tmp_map->put(key, tmp_user);
        }

        delete container;

        container = new std::vector<Linked_list>(capacity * 2);
        std::vector<long double> tmp_keys = tmp_map->keys();
        for(auto key : tmp_keys){
            user* tmp_user = tmp_map->get(key);
            put(key, tmp_user, true);
        }
        delete tmp_map;
        capacity *= 2;
    }
}



#endif