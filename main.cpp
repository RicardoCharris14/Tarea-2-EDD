#include "open_hash_map.h"
#include "close_hash_map.h"
#include "hashing_methods.h"
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>

std::queue<user*> create_users(int cantidad, std::ifstream& file){
    //Creamos los usuarios mediante el csv
    std::queue<user*> usuarios;
    std::string line;
    std::getline(file, line);
    for(int i=0 ; i<cantidad ; i++){
        std::getline(file, line);
        std::string* columnas = new std::string[7];
        std::istringstream ss(line);
        std::string token;
        int j=0;
        while(std::getline(ss, token, ',')){
            columnas[j] = token;
            j++;
        }
        user* tmp_user = new user(columnas[0], std::stoll(columnas[1]), columnas[2], std::stoi(columnas[3]), std::stoi(columnas[4]), std::stoi(columnas[5]), columnas[6]);
        usuarios.push(tmp_user);
    }
    return usuarios;
}


int main(int argc, char** argv){
    // if(argc<3){
    //     std::cerr << "Usage: " << argv[0] << " <cantidad de elementos> <direccion del csv>" << std::endl;
    //     exit(1);
    // }
    // //Número de valores que se usaran en el experimento
    // int n = atoi(argv[1]);
    //Abre el archivo
    std::ifstream file("datasets/dataset.csv");
    //Comprueba si el archivo se abrio correctamente
    if(!file.is_open()){
        std::cerr << "No se pudo abrir el archivo " << "datasets/dataset.csv" << std::endl;
    }

    //Creo los usuarios y el puntero a la funcion hash
    std::queue<user*> usuarios = create_users(10, file);
    int (*hash_function)(long long, int) = div;

    //Iniciamos el temporizador
    auto start = std::chrono::high_resolution_clock::now();

    //Codigo a experimentar
    
    open_hash_map<long long>* mapa = new open_hash_map<long long>(20, hash_function);
    mapa->printCapacity();
    for(int i=0 ; i<10 ; i++){
        std::cout << "hola1" << std::endl;
        mapa->put(usuarios.front()->getID(), usuarios.front());
        std::cout << "hola2" << std::endl;
        usuarios.pop();
        std::cout << "hola3" << std::endl;
    }
    mapa->printSize();

    //Fin del temporizador
    auto end = std::chrono::high_resolution_clock::now();

    //Calculamos el tiempo de ejecución
    double tiempo_ejecucion = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    //Transformamos de nanosegundos a segundos
    tiempo_ejecucion *= 1e-9;

    //Resultados
    std::cout << argv[0] << ';' << 10 << ';' << tiempo_ejecucion << std::endl;


    // int (*hash_function1)(long long, int) = div;
    // open_hash_map<long long>* mapa = new open_hash_map<long long>(hash_function1);
    // user* user1 = new user("Harvard", 1001, "Alice", 200, 150, 300, "Thu Jul 28 07:16:49 +0000 2016");
    // user* user2 = new user("MIT", 315, "Bob", 340, 200, 500, "Mon Aug 22 10:00:00 +0000 2018");
    // user* user3 = new user("Stanford", 487, "Charlie", 150, 180, 350, "Wed Sep 15 12:30:00 +0000 2020");
    // user* user4 = new user("Oxford", 879, "Diana", 450, 300, 600, "Fri Oct 30 09:45:00 +0000 2019");
    // user* user5 = new user("Cambridge", 510, "Eve", 230, 170, 320, "Sun Nov 22 14:00:00 +0000 2017");
    // user* user6 = new user("U. Conecpcion", 241, "Eve", 270, 570, 220, "Sun Nov 22 14:00:00 +0000 2017");



    // mapa->put(user1->getID(), user1);
    // mapa->put(user2->getID(), user2);
    // mapa->put(user3->getID(), user3);
    // mapa->put(user4->getID(), user4);
    // mapa->put(user5->getID(), user5);
    // mapa->put(user6->getID(), user6);

    // for(auto element : mapa->keys()){
    //     std::cout << "Clave: " << element << std::endl;
    // }
    // for(auto element : mapa->values()){
    //     std:: cout << "Usuario: " <<element << std::endl;
    // }

    // mapa->printSize();
    // mapa->remove(487);
    // mapa->remove(510);

    // if(mapa->get(1001)!= nullptr){
    //     mapa->get(1001)->printData();
    // }
    // if(mapa->get(315)!= nullptr){
    //     mapa->get(315)->printData();
    // }
    // if(mapa->get(487)!= nullptr){
    //     mapa->get(487)->printData();
    // }
    // if(mapa->get(259)!= nullptr){
    //     mapa->get(259)->printData();
    // }
    // if(mapa->get(510)!= nullptr){
    //     mapa->get(510)->printData();
    // }

    // mapa->printSize();
    // for(auto element : mapa->keys()){
    //     std::cout << "Clave: " << element << std::endl;
    // }
    // for(auto element : mapa->values()){
    //     std:: cout << "Usuario: " <<element << std::endl;
    // }
}


