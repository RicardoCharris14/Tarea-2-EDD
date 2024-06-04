#include "../close_hash_map.h"
#include "../open_hash_map.h"
#include "../probing_methods.h"
#include "create_users.h"
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <unordered_map>

int main(int argc, char** argv){
    if(argc<4){
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos> <direccion del csv> <0:open hashing ; 1:linear probing ; 2:double probing ; 3: cuadratic probing ; 4: stl hash table>" << std::endl;
        exit(1);
    }
    //Número de valores que se usaran en el experimento
    int n = atoi(argv[1]);

    //Obtengo los primeros n usuarios del archivo csv
    std::ifstream file(argv[2]);
    if(!file.is_open()){
        std::cerr << argv[2] << std::endl;
    }
    std::queue<user*> usuarios_insert = create_users(n, file);
    file.close();

    //Reabre el archivo para obtener los mismos usuarios
    std::ifstream file1(argv[2]);
    if(!file1.is_open()){
        std::cerr << argv[2] << std::endl;
    }
    std::queue<user*> usuarios_search = create_users(n, file1);
    file1.close();

    //definicion para que no lance error en el codigo de experimentacion por crear el mapa y los punteros a funciones dentro del switch
    open_hash_map<long long> *mapa1;
    close_hash_map<long long> *mapa2;
    std::unordered_map<long long, user*>* mapa3;   
    int (*hash_function1)(long long, int);
    int (*hash_function2)(long long, int, int);

    //Switch para seleccionar el tipo de hashing
    switch(argv[3][0]){
        case '0':
            hash_function1 = mult;
            mapa1 = new open_hash_map<long long>(100, hash_function1);
            break;
        case '1':
            hash_function2 = id_linear_probing;
            mapa2 = new close_hash_map<long long>(22000, hash_function2);
            break;
        case '2':
            hash_function2 = id_double_probing;
            mapa2 = new close_hash_map<long long>(22000, hash_function2);
            break;
        case '3':
            hash_function2 = id_quadratic_probing;
            mapa2 = new close_hash_map<long long>(22000, hash_function2);
            break;
        case '4':
            mapa3 = new std::unordered_map<long long, user*>;
            break;
        default:
            std::cerr << "Opcion no valida, ingrese una de las siguientes opciones: <0:open hashing ; 1:linear probing ; 2:double probing ; 3: cuadratic probing ; 4: stl hash table>" << std::endl;
            exit(1);
    }
    //Iniciamos el temporizador para calcular el timepo de insercion de datos
    auto start_ins = std::chrono::high_resolution_clock::now();

    //Codigo del experimento
    switch(argv[3][0]){
        case('0'):
            while(!usuarios_insert.empty()){
                user* tmp_user = usuarios_insert.front();
                mapa1->put(tmp_user->getID(), tmp_user);
                usuarios_insert.pop();
            }
            break;
        case('1'):
        case('2'):
        case('3'):
            while(!usuarios_insert.empty()){
                user* tmp_user = usuarios_insert.front();
                mapa2->put(tmp_user->getID(), tmp_user);
                usuarios_insert.pop();
            }
            break;
        case('4'):
            while(!usuarios_insert.empty()){
                user* tmp_user = usuarios_insert.front();
                mapa3->insert({tmp_user->getID(), tmp_user});
                usuarios_insert.pop();
            }
            break;
    }
    //Fin del temporizador
    auto end_ins = std::chrono::high_resolution_clock::now();
    std::cout << "Fin de la prueba de insercion." << std::endl;
    //Calculamos el tiempo de ejecución
    double tiempo_ejecucion_insercion = std::chrono::duration_cast<std::chrono::nanoseconds>(end_ins - start_ins).count();
    //Transformamos de nanosegundos a segundos
    tiempo_ejecucion_insercion *= 1e-9;

    //Inicio del temporizador
    auto start_search = std::chrono::high_resolution_clock::now();

    //Busqueda de usuarios que estan en el hash map
    switch(argv[3][0]){
        case('0'):
            while(!usuarios_search.empty()){
                user* tmp_user = usuarios_search.front();
                mapa1->get(tmp_user->getID());
                usuarios_search.pop();
            }
            break;
        case('1'):
        case('2'):
        case('3'):
            while(!usuarios_search.empty()){
                user* tmp_user = usuarios_search.front();
                mapa2->get(tmp_user->getID());
                usuarios_search.pop();
            }
            break;
        case('4'):
            while(!usuarios_search.empty()){
                user* tmp_user = usuarios_search.front();
                mapa3->find(tmp_user->getID());
                usuarios_search.pop();
            }
            break;
    }

    //Fin del temporizador
    auto end_search = std::chrono::high_resolution_clock::now();
    std::cout << "Fin de la prueba de busqueda." << std::endl;
    //Calculamos el tiempo de ejecución
    double tiempo_ejecucion_busqueda= std::chrono::duration_cast<std::chrono::nanoseconds>(end_search - start_search).count();
    //Transformamos de nanosegundos a segundos
    tiempo_ejecucion_busqueda *= 1e-9;



    //Prueba para datos que no estan en la hash table(crear usuarios al azar o un csv con usuarios que no estan en el csv original);







    //Eliminamos la memoria asignada por el puntero a la tabla hash
    switch(argv[3][0]){
        case '0':
            delete mapa1;
            break;
        case '1':
        case '2':
        case '3':
            delete mapa2;
            break;
        case '4':
            delete mapa3;
            break;
    }

    //Resultados
    std::cout << argv[0] << ';' << n << ';' << tiempo_ejecucion_insercion << ';' << tiempo_ejecucion_busqueda << std::endl;
}