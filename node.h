#ifndef NODE
#define NODE

template <typename T>
class node{
private:
    T value;
    node<T>* previous;
    node<T>* next;
public:
    node(): value(T()), previous(nullptr), next(nullptr){}
    node(T value, node<T>* prev_n, node<T>* next_n):value(value), previous(prev_n), next(next_n){}
    ~node(){delete next; delete previous;};
    void setValue(T value){this->value = value;}
    void setNext(node<T>* node){this->next = node;}
    void setPrevious(node<T>* node){this->previous = node;}
    T getValue(){return value;}
    node<T>* getNext(){return next;}
    node<T>* getPrevious(){return previous;}
};

#endif
