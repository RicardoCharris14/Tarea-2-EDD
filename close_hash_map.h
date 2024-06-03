#ifndef CLOSE_HASH_MAP
#define CLOSE_HASH_MAP

#include "probing_methods.h"
#include "entry.h"
#include "user.h"
#include <vector>
#include <iostream>
#include <optional>

template<typename K>
class close_hash_map{
    public:
        using Entry = entry<K, user*>*;
        using Vector = std::vector<Entry>*;
    private:
        int size;
        int capacity;
        Vector container;
        int (*probing_method) (K key, int capacity, int i);
    public:
        close_hash_map(int capacity, int (*probing_method)(K, int, int)) : size(0), capacity(capacity), probing_method(probing_method){
            container = new std::vector<Entry>(capacity);
        }
        close_hash_map(int (*probing_method)(K, int, int)) : size(0), capacity(3), probing_method(probing_method){
            container = new std::vector<Entry>(capacity);
        }
        ~close_hash_map() = default;
        user* get(K key);
        void put(K key, user* usuario);
//      user* remove(K key);
        int getSize();
        bool isEmpty();
        void set_probing_method( int (*probing_method)(K, int, int) );
    private:
        int probing(K key, int i);
 //     void duplicate_capacity();
};

template<typename K>
user* close_hash_map<K>::get(K key){

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
    return nullptr;
}

// Inserta el par (key, usuario). En caso de colisión, se utiliza probing para resolver.
// Si el par ya se encuentra en la hash table, no se hace ningún cambio.
template<typename K>
void close_hash_map<K>::put(K key, user* usuario){
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
int close_hash_map<K>::getSize(){
    return size;
}

template<typename K>
bool close_hash_map<K>::isEmpty(){
    return size==0;
}

template<typename K>
int close_hash_map<K>::probing(K key, int i){
    return probing_method(key, capacity, i);
}

#endif
