#ifndef ENTRY
#define ENTRY

template<typename T, typename Type>
class entry{
public:
    T key;
    Type value;  
    entry(T, Type);
};

template <typename T, typename Type>
entry<T, Type>::entry(T key, Type value){
    this->key=key;
    this->value=value;
}

#endif