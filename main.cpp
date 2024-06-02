#include "open_hash_map.h"
#include "close_hash_map.h"
#include "hashing_methods.h"
#include <chrono>
#include <iostream>

int main(int argc, char** argv){
    // if(argc<2){
    //     std::cerr << "Usage: " << argv[0] << " <cantidad de elementos>" << std::endl;
    //     exit(1);
    // }

    // //Número de valores que se usaran en el experimento
    // int n = atoi(argv[1]);

    // //Iniciamos el temporizador
    // auto start = std::chrono::high_resolution_clock::now();

    // //Codigo a experimentar
    









    // //Fin del temporizador
    // auto end = std::chrono::high_resolution_clock::now();

    // //Calculamos el tiempo de ejecución
    // double tiempo_ejecucion = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // //Transformamos de nanosegundos a segundos
    // tiempo_ejecucion *= 1e-9;

    // //Resultados
    // std::cout << argv[0] << ';' << n << ';' << tiempo_ejecucion << std::endl;
    int (*hash_function1)(long long, int) = div;
    open_hash_map<long long>* mapa = new open_hash_map<long long>(hash_function1);
    user* user1 = new user("Harvard", 1001, "Alice", 200, 150, 300, "Thu Jul 28 07:16:49 +0000 2016");
    user* user2 = new user("MIT", 315, "Bob", 340, 200, 500, "Mon Aug 22 10:00:00 +0000 2018");
    user* user3 = new user("Stanford", 487, "Charlie", 150, 180, 350, "Wed Sep 15 12:30:00 +0000 2020");
    user* user4 = new user("Oxford", 879, "Diana", 450, 300, 600, "Fri Oct 30 09:45:00 +0000 2019");
    user* user5 = new user("Cambridge", 510, "Eve", 230, 170, 320, "Sun Nov 22 14:00:00 +0000 2017");
    user* user6 = new user("U. Conecpcion", 241, "Eve", 270, 570, 220, "Sun Nov 22 14:00:00 +0000 2017");



    mapa->put(user1->getID(), user1);
    mapa->put(user2->getID(), user2);
    mapa->put(user3->getID(), user3);
    mapa->put(user4->getID(), user4);
    mapa->put(user5->getID(), user5);
    mapa->put(user6->getID(), user6);

    for(auto element : mapa->keys()){
        std::cout << "Clave: " << element << std::endl;
    }
    for(auto element : mapa->values()){
        std:: cout << "Usuario: " <<element << std::endl;
    }

    mapa->printSize();
    mapa->remove(487);
    mapa->remove(510);

    if(mapa->get(1001)!= nullptr){
        mapa->get(1001)->printData();
    }
    if(mapa->get(315)!= nullptr){
        mapa->get(315)->printData();
    }
    if(mapa->get(487)!= nullptr){
        mapa->get(487)->printData();
    }
    if(mapa->get(259)!= nullptr){
        mapa->get(259)->printData();
    }
    if(mapa->get(510)!= nullptr){
        mapa->get(510)->printData();
    }

    mapa->printSize();
    for(auto element : mapa->keys()){
        std::cout << "Clave: " << element << std::endl;
    }
    for(auto element : mapa->values()){
        std:: cout << "Usuario: " <<element << std::endl;
    }
}

