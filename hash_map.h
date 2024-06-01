#ifndef HASH_MAP
#define HASH_MAP

#include "probing_methods.h"
#include "entry.h"
#include "user.h"
#include <vector>
#include <iostream>
#include <optional>

template<typename K>
class hash_map{
    public:
        using Entry = entry<K, user*>*;
        using Vector = std::vector<Entry>*;
    private:
        int size;
        int capacity;
        Vector container;
        int (*probing_method) (K key, int capacity, int i);
//        std::vector<K> keysSet;
//        std::vector<user*> valuesSet;
    public:
        hash_map() : size(0), capacity(503), probing_method(quadratic_probing){
            container = new std::vector<Entry>(capacity);
        }
        ~hash_map() = default;
        std::optional<user*> get(K key);
        void put(K key, user* usuario);
//        user* remove(K key);
        int getSize();
        bool isEmpty();
        std::vector<K> keys();
        std::vector<user*> values();
        void set_probing_method( int (*probing_method)(K, int, int) );
    private:
        int probing(K key, int i);
 //       void duplicate_capacity();
};

template<typename K>
std::optional<user*> hash_map<K>::get(K key){

    int i = 0;
    int index = probing(key, i);

    // Manejo de colisiones.
    while ((*container)[index]) {
        if ((*container)[index]->key == key) {
            return (*container)[index]->value;
        }
        index = probing(key, ++i);
    }

    // Si se llega hasta acá, no se encontro el usuario.
    return {};
}

// Inserta el par (key, usuario). En caso de colisión, se utiliza probing para resolver.
// Si el par ya se encuentra en la hash table, no se hace ningún cambio.
template<typename K>
void hash_map<K>::put(K key, user* usuario){
//    if (size >= int(capacity * 0.9f)) duplicate_capacity();

    int i = 0;
    int index = probing(key, i);

    // Manejo de colisiones.
    while ((*container)[index]) {
        if ((*container)[index]->key == key) { // El par ya existe en la table
            return;
        }
        index = probing(key, ++i);
    }

    (*container)[index] = new entry<K, user*>(key, usuario);
    size++;
}

/* Complica algo las cosas
//elimina el par con clave 'user_id'
template<typename K>
user* hashMap<K>::remove(K user_id){
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
*/

template<typename K>
int hash_map<K>::getSize(){
    return size;
}

template<typename K>
bool hash_map<K>::isEmpty(){
    return size==0;
}
/*
template<typename K>
std::vector<K> hash_map<K>::keys(){
    return keysSet;
}

template<typename K>
std::vector<user*> hash_map<K>::values(){
    return valuesSet;
}
*/
template<typename K>
int hash_map<K>::probing(K key, int i){
    return probing_method(key, capacity, i);
}

#endif
