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
#include <list>

//Funcion que calcula el espacio ocupado por el mapa de la STL
template <typename K>
size_t calculate_used_space_stl_map(std::unordered_map<K, user*>* mapa){
    size_t used_space = 0;
    used_space += sizeof(*mapa);
    used_space += sizeof(mapa->size());
    used_space += sizeof(mapa->max_size());
    used_space += mapa->bucket_count() * sizeof(std::list<typename std::unordered_map<K, user*>::value_type>);

    for(const auto& pair : *mapa){
        used_space += sizeof(pair.first);
        used_space += sizeof(*(pair.second));
        used_space += sizeof(pair.second->getID());
        used_space += sizeof(pair.second->getUsername());
        used_space += sizeof(int) * 3;
        used_space += sizeof(std::string) * 2;
    }
    return used_space;
}


int main(int argc, char** argv){
    // argv[1] = "10";
    // argv[2] = "C:/Users/rica1/OneDrive/Escritorio/Universidad/Semestre 5/Estructuras de datos/Tareas/Tarea EDD 2/datasets/dataset.csv";
    // argv[3] = "2";

    if(argc<5){
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos> <dirección del dataset.csv> <dirección del FakeData.csv> <hashing (0;1;2;3;4)>\n" << std::endl;
        std::cerr << "Opciones para <hashing>:\n0: open hashing\n1: linear probing\n2: double probing\n3: cuadratic probing\n4: stl hash table (unordered_map)\n" << std::endl;
        exit(1);
    }
    
    //Número de valores que se usaran en el experimento
    int num_valores = atoi(argv[1]);
    int num_pruebas = atoi(argv[5]);

    double tiempo_total_insercion = 0;
    double tiempo_total_busqueda = 0;
    double tiempo_total_fake = 0;
    size_t espacio_total_ocupado = 0;

    double tiempo_promedio_insercion;
    double tiempo_promedio_busqueda;
    double tiempo_promedio_fake;
    size_t espacio_promedio_ocupado;

    for (int i = 0; i < num_pruebas; i++) {
        //Obtengo los primeros n usuarios del archivo csv
        std::ifstream file(argv[2]);
        if(!file.is_open()){
            std::cerr << argv[2] << std::endl;
        }
        std::queue<user*> usuarios_insercion = create_users(num_valores, file);
        file.close();

        //Reabre el archivo para obtener los mismos usuarios
        std::ifstream file1(argv[2]);
        if(!file1.is_open()){
            std::cerr << argv[2] << std::endl;
        }
        std::queue<user*> usuarios_busqueda = create_users(num_valores, file1);
        file1.close();

        //Abre el archivo para crear usuarios falsos
        std::ifstream file2(argv[3]);
        if(!file2.is_open()){
            std::cerr << argv[3] << std::endl;
        }
        std::queue<user*> fake_users = create_users(num_valores, file2);
        file2.close();

        //definicion para que no lance error en el codigo de experimentacion por crear el mapa y los punteros a funciones dentro del switch
        open_hash_map<std::string> *mapa1;
        close_hash_map<std::string> *mapa2;
        std::unordered_map<std::string, user*>* mapa3;
        int (*hash_function1)(std::string, int);
        int (*hash_function2)(std::string, int, int);

        //Switch para seleccionar el tipo de hashing
        switch(argv[4][0]){
            case '0':
                hash_function1 = polynomial_accumulation;
                mapa1 = new open_hash_map<std::string>(101, hash_function1);
                break;
            case '1':
                hash_function2 = name_linear_probing;
                mapa2 = new close_hash_map<std::string>(101, hash_function2);
                break;
            case '2':
                hash_function2 = name_double_probing;
                mapa2 = new close_hash_map<std::string>(101, hash_function2);
                break;
            case '3':
                hash_function2 = name_quadratic_probing;
                mapa2 = new close_hash_map<std::string>(101, hash_function2);
                break;
            case '4':
                mapa3 = new std::unordered_map<std::string, user*>;
                break;
            default:
                std::cerr << "Opcion no valida, ingrese una de las siguientes opciones: <0:open hashing ; 1:linear probing ; 2:double probing ; 3: cuadratic probing ; 4: stl hash table>" << std::endl;
                exit(1);
        }

        //Iniciamos el temporizador
        auto start_insert = std::chrono::high_resolution_clock::now();

        //Insercion de usuarios al hash map
        switch(argv[4][0]){
            case('0'):
                while(!usuarios_insercion.empty()){
                    user* tmp_user = usuarios_insercion.front();
                    mapa1->put(tmp_user->getUsername(), tmp_user);
                    usuarios_insercion.pop();
                }
                break;
            case('1'):
            case('2'):
            case('3'):
                while(!usuarios_insercion.empty()){
                    user* tmp_user = usuarios_insercion.front();
                    mapa2->put(tmp_user->getUsername(), tmp_user);
                    usuarios_insercion.pop();
                }
                break;
            case('4'):
                while(!usuarios_insercion.empty()){
                    user* tmp_user = usuarios_insercion.front();
                    mapa3->insert({tmp_user->getUsername(), tmp_user});
                    usuarios_insercion.pop();
                }
                break;
        }
        //Fin del temporizador
        auto end_insert = std::chrono::high_resolution_clock::now();

        // Calculo de memoria
        switch(argv[4][0]){
            case('0'):
                espacio_total_ocupado += mapa1->calculate_used_space();
                break;
            case('1'):
            case('2'):
            case('3'):
                espacio_total_ocupado += mapa2->calculate_used_space();
                break;
            case('4'):
                espacio_total_ocupado += calculate_used_space_stl_map<std::string>(mapa3);
                break;
        }
        //std::cout << "Fin de la prueba" << std::endl;
        //Calculamos el tiempo de ejecución
        double tiempo_ejecucion_insercion = std::chrono::duration_cast<std::chrono::nanoseconds>(end_insert - start_insert).count();
        //Transformamos de nanosegundos a segundos
        tiempo_ejecucion_insercion *= 1e-9;
        tiempo_total_insercion += tiempo_ejecucion_insercion;

        //Iniciamos el temporizador
        auto start_search = std::chrono::high_resolution_clock::now();

        //Busqueda de usuarios en el hash map
        switch(argv[4][0]){
            case('0'):
                while(!usuarios_busqueda.empty()){
                    user* tmp_user = usuarios_busqueda.front();
                    mapa1->get(tmp_user->getUsername());
                    usuarios_busqueda.pop();
                }
                break;
            case('1'):
            case('2'):
            case('3'):
                while(!usuarios_busqueda.empty()){
                    user* tmp_user = usuarios_busqueda.front();
                    mapa2->get(tmp_user->getUsername());
                    usuarios_busqueda.pop();
                }
                break;
            case('4'):
                while(!usuarios_busqueda.empty()){
                    user* tmp_user = usuarios_busqueda.front();
                    mapa3->find(tmp_user->getUsername());
                    usuarios_busqueda.pop();
                }
                break;
        }

        //Finalizamos el temporiazador
        auto end_search = std::chrono::high_resolution_clock::now();
        //std::cout << "Fin de la prueba de busqueda." << std::endl;
        //Calculamos el timepo de ejecucion de la prueba de busqueda
        double tiempo_ejecucion_busqueda = std::chrono::duration_cast<std::chrono::nanoseconds>(end_search - start_search).count();
        //Transformamos de nanosegundos a segundos
        tiempo_ejecucion_busqueda *= 1e-9;
        tiempo_total_busqueda += tiempo_ejecucion_busqueda;

        //Inicio del temporizador
        auto start_fake = std::chrono::high_resolution_clock::now();

        //busca usuarios que no estan en el hash map;

        switch(argv[4][0]){
            case('0'):
                while(!fake_users.empty()){
                    user* tmp_user = fake_users.front();
                    mapa1->get(tmp_user->getUsername());
                    fake_users.pop();
                }
                break;
            case('1'):
            case('2'):
            case('3'):
                while(!fake_users.empty()){
                    user* tmp_user = fake_users.front();
                    mapa2->get(tmp_user->getUsername());
                    fake_users.pop();
                }
                break;
            case('4'):
                while(!fake_users.empty()){
                    user* tmp_user = fake_users.front();
                    mapa3->find(tmp_user->getUsername());
                    fake_users.pop();
                }
                break;
        }

        //std::cout << "Fin prueba busqueda usuarios inexistentes" << std::endl;
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
    espacio_promedio_ocupado = (espacio_total_ocupado/num_pruebas)/1024;
    
    //Resultados
    switch (argv[4][0]) {
        case '0':
            std::cout << "open_hashing_name";
            break;
        case '1':
            std::cout << "linear_probing_name";
            break;
        case '2':
            std::cout << "double_probing_name";
            break;
        case '3':
            std::cout << "quadratic_hashing_name";
            break;
        case '4':
            std::cout << "unordered_map_name";
            break;
    }
    std::cout << ';' << num_valores << ';' << tiempo_promedio_insercion << ';' << tiempo_promedio_busqueda << ';' << tiempo_promedio_fake << ';' << espacio_promedio_ocupado << std::endl;
}
