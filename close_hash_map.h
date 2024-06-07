#ifndef CLOSE_HASH_MAP
#define CLOSE_HASH_MAP

#include "entry.h"
#include "user.h"
#include <vector>
#include <stack>
#include <iostream>

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
            container = new std::vector<Entry>(capacity, nullptr);
        }
        close_hash_map(int (*probing_method)(K, int, int)) : size(0), capacity(503), probing_method(probing_method){
            container = new std::vector<Entry>(capacity, nullptr);
        }
        ~close_hash_map() = default;
        user* get(K key);
        void put(K key, user* usuario, bool duplicating = false);
//      user* remove(K key);

        size_t calculate_used_space();
    private:
        int probing(K key, int i);
        void duplicate();
};

template<typename K>
user* close_hash_map<K>::get(K key){
    int index = probing(key, 0);
    int max_probing = capacity;
    // Manejo de colisiones.
    for(int i=0 ; i<max_probing ; i++) {
        if ((*container)[index] == nullptr) {
            return nullptr;
        } else if ((*container)[index]->key == key) {
            return (*container)[index]->value;
        }
        // Colisión
        index = probing(key, i+1);
        if(i == capacity){
//            std::cout << "No se encontro nada:\n" << "Size: " << size << "\nCapacity:" << capacity << std::endl;
            return nullptr;
        }
    }
    // Si se llega hasta acá, no se encontro el usuario.
    return nullptr;
}

// Inserta el par (key, usuario). En caso de colisión, se utiliza probing para resolver.
// Si el par ya se encuentra en la hash table, no se hace ningún cambio.
template<typename K>
void close_hash_map<K>::put(K key, user* usuario, bool duplicating){
    int i = 0;
    int index = probing(key, i);

    // Manejo de colisiones.
    while ((*container)[index]) {
        if ((*container)[index]->key == key) { // El par ya existe en la table
            return;
        }
        index = probing(key, ++i);
        if(i == 2 * capacity){
            duplicate();
            i = 0;
        }
    }
    (*container)[index] = new entry<K, user*>(key, usuario);
    if(!duplicating) size++;
    if (size >= int(capacity * 0.9f)) duplicate();
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
size_t close_hash_map<K>::calculate_used_space(){
    size_t used_space = 0;
    used_space += sizeof(*this);
    used_space += sizeof(size);
    used_space += sizeof(capacity);
    used_space += sizeof(*container);
    for(int i=0 ; i<capacity ; i++){
        if((*container)[i]){
            used_space += sizeof(*((*container)[i]));
            used_space += sizeof((*container)[i]->key);
            used_space += sizeof(*((*container)[i]->value));
            used_space += sizeof((*container)[i]->value->getID());
            used_space += sizeof((*container)[i]->value->getUsername());
            used_space += sizeof(int) * 3;
            used_space += sizeof(std::string) * 2;
        }
    }
    return used_space;
}


template<typename K>
int close_hash_map<K>::probing(K key, int i){
    return probing_method(key, capacity, i);
}

template<typename K>
void close_hash_map<K>::duplicate(){

    //Crea un hash map con el doble de tamaño para no tener que recorrer
    close_hash_map<K>* tmp_map = new close_hash_map<K>(2 * capacity, probing_method);

    //Pasa todos los datos del hash map actual al temporal
    std::stack<Entry> tmp_users;
    for(int i=0 ; i<capacity ; i++){
        if((*container)[i]){
            user* tmp_user = (*container)[i]->value;
            K key = (*container)[i]->key;
            tmp_map->put(key, tmp_user);
            tmp_users.push((*container)[i]);
        }
    }

    delete container;

    container = new std::vector<Entry>(capacity * 2);
    capacity *= 2;
    while(!tmp_users.empty()){
        Entry tmp_user = tmp_users.top();
        tmp_users.pop();
        put(tmp_user->key, tmp_user->value, true);
    }
    delete tmp_map;
}


#endif
