#ifndef LINKED_LIST
#define LINKED_LIST

#include "node.h"
#include "entry.h"

template <typename T, typename Type>
class linked_list {
public:
    using Entry = entry<T, Type>*;
private:
    node<Entry>* head;
    node<Entry>* tail;
    int large;
public:
    linked_list();
    ~linked_list();
    bool is_empty();
    void push_back(Entry);
    Entry remove(int);
    Entry get(int);
    int size();
    int find(T);
};

template<typename T, typename Type>
linked_list<T, Type>::linked_list():large(0){
    head = new node<Entry>();
    tail = new node<Entry>();
}
template<typename T, typename Type>
linked_list<T, Type>::~linked_list(){
    delete head;
}
template<typename T, typename Type>
bool linked_list<T, Type>::is_empty() {
    return head->getNext() == nullptr;
}
template<typename T, typename Type>
void linked_list<T, Type>::push_back(Entry valor){
    //Si no hay nodos, apuntamos el head y el tail al nodo entrante.
    if(tail->getPrevious() == nullptr){
        auto* nuevo = new node<Entry>(valor, nullptr, nullptr);
        head->setNext(nuevo);
        tail->setPrevious(nuevo);
        large++;
    //Si hay nodos, apuntamos el ultimo nodo al nodo entrante, el entrante al ultimo nodo, y el tail al entrante. 
    } else{
        auto* nuevo = new node<Entry>(valor, tail->getPrevious(), nullptr);
        tail->getPrevious()->setNext(nuevo);
        tail->setPrevious(nuevo);
        large++;
    }
}

template <typename T, typename Type>
entry<T, Type>* linked_list<T, Type>::remove(int index){
    try {
        if(is_empty()) {
            throw std::runtime_error("!LA LISTA ESTA VACIA");
        }else if (index > large){
            throw std::runtime_error("Acceso fuera de los limites");
        }
        
        node<Entry>* tmp = head->getNext();
        for(int i=1 ; i<index ; i++){
            tmp = tmp->getNext();
        }
        if(tmp->getPrevious() == nullptr && tmp->getNext() == nullptr){
            head->setNext(nullptr);
            tail->setPrevious(nullptr);
        } else if(tmp->getPrevious() == nullptr){
            head->setNext(tmp->getNext());
            tmp->getNext()->setPrevious(nullptr);
        } else if(tmp->getNext() == nullptr){
            tail->setPrevious(tmp->getPrevious());
            tmp->getPrevious()->setNext(nullptr);
        }
        large--;
        return tmp->getValue();
    } catch(const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

template <typename T, typename Type>
entry<T, Type>* linked_list<T, Type>::get(int index){
    try {
        if(is_empty() || index > large) {
            throw std::runtime_error("!LA LISTA ESTA VACIA");
        }
        node<Entry>* tmp = head->getNext();
        for(int i=1 ; i<index ; i++){
            tmp = tmp->getNext();
        }
        return tmp->getValue();
    } catch(const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

template <typename T, typename Type>
int linked_list<T, Type>::size() {
    return large;
}
template <typename T, typename Type>
int linked_list<T, Type>::find(T valor) {
    if(large == 0){return -1;}
    node<Entry>* tmp = head->getNext();
    for(int i=1 ; i<=large ; i++){
        if(tmp->getValue()->key == valor){
            return i;
        }
        tmp=tmp->getNext();
    }
    return -1;
}

#endif