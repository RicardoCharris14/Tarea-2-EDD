#ifndef HASH_MAP
#define HASH_MAP

#include "entry.h"
#include "user.h"
#include <vector>
#include <iostream>

class hashMap{
    public:
        using Entry = entry<long double, user*>*;
        using Vector = std::vector<Entry>;
    private:
        int size;
        int capacity;
        Vector container;
        std::vector<long double> keysSet;
        std::vector<user*> valuesSet;
    public:
        hashMap() : size(0), capacity(503), container(capacity) {}
        ~hashMap() = default;
        user* get(long double);
        user* put(long double, user*);
        user* remove(long double);
        int getSize();
        bool isEmpty();
        std::vector<long double> keys();
        std::vector<user*> values();
        int function(long double);

};

user* hashMap::get(long double user_id){
    int index = function(user_id);
    if(container[index]){
        return container[index]->value;
    }
    else{
        return nullptr;
    }
}

//Ingresa un nuevo par de elementos al hash map o reemplaza el anterior, y retorna nullPtr o el valor del par anterior, respectivamente. 
user* hashMap::put(long double user_id, user* usuario){
    int index = function(user_id);
    Entry newEntry = new entry<long double, user*>(user_id, usuario);
    if(container[index]){
        Entry tmp = container[index];
        keysSet.push_back(user_id);
        valuesSet.push_back(usuario);
        //Elimina una instancia del valor y de la clave asociados al par eliminado de sus respectivos sets.
        for(long long unsigned int i=0 ; i<valuesSet.size() ; i++){
            if(valuesSet[i] == tmp->value){
                valuesSet.erase(valuesSet.begin() + i);
                keysSet.erase(keysSet.begin() + i);
                break;
            }
        }
        container[index] = newEntry;
        return tmp->value;
    }
    else{
        size++;
        keysSet.push_back(user_id);
        valuesSet.push_back(usuario);
        container[index] = newEntry;
        return nullptr;
    }
}

//elimina el par con clave 'user_id'
user* hashMap::remove(long double user_id){
    int index = function(user_id);
    if(container[index]){
        Entry tmp = container[index];
        container.erase(container.begin()+index);
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

int hashMap::getSize(){
    return size;
}

bool hashMap::isEmpty(){
    return size==0;
}

std::vector<long double> hashMap::keys(){
    return keysSet;
}

std::vector<user*> hashMap::values(){
    return valuesSet;
}

int hashMap::function(long double user_id){
    return int(user_id) % capacity;
}

#endif