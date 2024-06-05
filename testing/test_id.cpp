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
    if(argc<6){
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos> <dirección del dataset.csv> <dirección del FakeData.csv> <hashing (0;1;2;3;4)> <cantidad de pruebas>\n" << std::endl;
        std::cerr << "Opciones para <hashing>:\n0: open hashing\n1: linear probing\n2: double probing\n3: cuadratic probing\n4: stl hash table (unordered_map)\n" << std::endl;
        exit(1);
    }
    //Número de valores que se usaran en el experimento
    int num_valores = atoi(argv[1]);
    int num_pruebas = atoi(argv[5]);

    double tiempo_total_insercion = 0;
    double tiempo_total_busqueda = 0;
    double tiempo_total_fake = 0;

    double tiempo_promedio_insercion;
    double tiempo_promedio_busqueda;
    double tiempo_promedio_fake;

    for (int i = 0; i < num_pruebas; i++) {
        //Obtengo los primeros n usuarios del archivo csv
        std::ifstream file(argv[2]);
        if(!file.is_open()){
            std::cerr << argv[2] << std::endl;
        }
        std::queue<user*> usuarios_insert = create_users(num_valores, file);
        file.close();

        //Reabre el archivo para obtener los mismos usuarios
        std::ifstream file1(argv[2]);
        if(!file1.is_open()){
            std::cerr << argv[2] << std::endl;
        }
        std::queue<user*> usuarios_search = create_users(num_valores, file1);
        file1.close();

        //Abre el archivo para crear usuarios falsos
        std::ifstream file2(argv[3]);
        if(!file2.is_open()){
            std::cerr << argv[3] << std::endl;
        }
        std::queue<user*> fake_users = create_users(num_valores, file2);
        file2.close();

        //definicion para que no lance error en el codigo de experimentacion por crear el mapa y los punteros a funciones dentro del switch
        open_hash_map<long long> *mapa1;
        close_hash_map<long long> *mapa2;
        std::unordered_map<long long, user*>* mapa3;
        int (*hash_function1)(long long, int);
        int (*hash_function2)(long long, int, int);

        //Switch para seleccionar el tipo de hashing
        switch(argv[4][0]){
            case '0':
                hash_function1 = mult;
                mapa1 = new open_hash_map<long long>(100, hash_function1);
                break;
            case '1':
                hash_function2 = id_linear_probing;
                mapa2 = new close_hash_map<long long>(100, hash_function2);
                break;
            case '2':
                hash_function2 = id_double_probing;
                mapa2 = new close_hash_map<long long>(100, hash_function2);
                break;
            case '3':
                hash_function2 = id_quadratic_probing;
                mapa2 = new close_hash_map<long long>(100, hash_function2);
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

        //Insercion de usuarios al hash map
        switch(argv[4][0]){
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
        //std::cout << "Fin de la prueba de insercion." << std::endl;
        //Calculamos el tiempo de ejecución
        double tiempo_ejecucion_insercion = std::chrono::duration_cast<std::chrono::nanoseconds>(end_ins - start_ins).count();
        //Transformamos de nanosegundos a segundos
        tiempo_ejecucion_insercion *= 1e-9;
        tiempo_total_insercion += tiempo_ejecucion_insercion;


        //Inicio del temporizador
        auto start_search = std::chrono::high_resolution_clock::now();

        //Busqueda de usuarios que estan en el hash map
        switch(argv[4][0]){
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
        //std::cout << "Fin de la prueba de busqueda." << std::endl;
        //Calculamos el tiempo de ejecución
        double tiempo_ejecucion_busqueda= std::chrono::duration_cast<std::chrono::nanoseconds>(end_search - start_search).count();
        //Transformamos de nanosegundos a segundos
        tiempo_ejecucion_busqueda *= 1e-9;
        tiempo_total_busqueda += tiempo_ejecucion_busqueda;


        //Inicio del temporizador
        auto start_fake = std::chrono::high_resolution_clock::now();

        //Trata de buscar usuarios que no estan en el hash map;
        switch(argv[4][0]){
            case('0'):
                while(!fake_users.empty()){
                    user* tmp_user = fake_users.front();
                    mapa1->get(tmp_user->getID());
                    fake_users.pop();
                }
                break;
            case('1'):
            case('2'):
            case('3'):
                while(!fake_users.empty()){
                    user* tmp_user = fake_users.front();
                    mapa2->get(tmp_user->getID());
                    fake_users.pop();
                }
                break;
            case('4'):
                while(!fake_users.empty()){
                    user* tmp_user = fake_users.front();
                    mapa3->find(tmp_user->getID());
                    fake_users.pop();
                }
                break;
        }

        //Fin del temporizador
        auto end_fake = std::chrono::high_resolution_clock::now();
        //Calculamos el intervalo de timepo
        double tiempo_ejecucion_fake = std::chrono::duration_cast<std::chrono::nanoseconds>(end_fake - start_fake).count();
        //Transformar tiempo a segundos
        tiempo_ejecucion_fake *= 1e-9;
        tiempo_total_fake += tiempo_ejecucion_fake;




        //Eliminamos la memoria asignada por el puntero a la tabla hash
        switch(argv[4][0]){
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
    }

    tiempo_promedio_insercion = tiempo_total_insercion/num_pruebas;
    tiempo_promedio_busqueda = tiempo_total_busqueda/num_pruebas;
    tiempo_promedio_fake = tiempo_total_fake/num_pruebas;

    //Resultados
    switch (argv[4][0]) {
        case '0':
            std::cout << "open_hashing_id";
            break;
        case '1':
            std::cout << "linear_probing_id";
            break;
        case '2':
            std::cout << "double_probing_id";
            break;
        case '3':
            std::cout << "quadratic_hashing_id";
            break;
        case '4':
            std::cout << "unordered_map_id";
            break;
    }
    std::cout << ';' << num_valores << ';' << tiempo_promedio_insercion << ';' << tiempo_promedio_busqueda << ';' << tiempo_promedio_fake << std::endl;
}
