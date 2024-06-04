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
    // argv[1] = "1000";
    // argv[2] = "C:/Users/rica1/OneDrive/Escritorio/Universidad/Semestre 5/Estructuras de datos/Tareas/Tarea EDD 2/datasets/dataset.csv";
    // argv[3] = "2";

    if(argc<4){
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos> <direccion del csv> <0:open hashing ; 1:linear probing ; 2:double probing ; 3: cuadratic probing ; 4: stl hash table>" << std::endl;
        exit(1);
    }
    
    //Número de valores que se usaran en el experimento
    int n = atoi(argv[1]);
    //Abre el archivo
    std::ifstream file(argv[2]);
    //Comprueba si el archivo se abrio correctamente
    if(!file.is_open()){
        std::cerr << argv[2] << std::endl;
    }

    //Creo los usuarios y el puntero a la funcion hash
    std::queue<user*> usuarios = create_users(n, file);

    //definicion para que no lance error en el codigo de experimentacion por crear el mapa y los punteros a funciones dentro del switch
    open_hash_map<std::string> *mapa1;
    close_hash_map<std::string> *mapa2;
    std::unordered_map<std::string, user*>* mapa3;   
    int (*hash_function1)(std::string, int);
    int (*hash_function2)(std::string, int, int);

    //Switch para seleccionar el tipo de hashing
    switch(argv[3][0]){
        case '0':
            hash_function1 = polynomial_accumulation;
            mapa1 = new open_hash_map<std::string>(100, hash_function1);
            break;
        case '1':
            hash_function2 = name_linear_probing;
            mapa2 = new close_hash_map<std::string>(22000, hash_function2);
            break;
        case '2':
            hash_function2 = name_double_probing;
            mapa2 = new close_hash_map<std::string>(22000, hash_function2);
            break;
        case '3':
            hash_function2 = name_quadratic_probing;
            mapa2 = new close_hash_map<std::string>(22000, hash_function2);
            break;
        case '4':
            mapa3 = new std::unordered_map<std::string, user*>;
            break;
        default:
            std::cerr << "Opcion no valida, ingrese una de las siguientes opciones: <0:open hashing ; 1:linear probing ; 2:double probing ; 3: cuadratic probing ; 4: stl hash table>" << std::endl;
            exit(1);
    }

    //Iniciamos el temporizador
    auto start = std::chrono::high_resolution_clock::now();

    //Codigo del experimento
    switch(argv[3][0]){
        case('0'):
            while(!usuarios.empty()){
                user* tmp_user = usuarios.front();
                mapa1->put(tmp_user->getUsername(), tmp_user);
                usuarios.pop();
            }
            break;
        case('1'):
        case('2'):
        case('3'):
            while(!usuarios.empty()){
                user* tmp_user = usuarios.front();
                mapa2->put(tmp_user->getUsername(), tmp_user);
                usuarios.pop();
            }
            break;
        case('4'):
            while(!usuarios.empty()){
                user* tmp_user = usuarios.front();
                mapa3->insert({tmp_user->getUsername(), tmp_user});
                usuarios.pop();
            }
            break;
    }
    //Fin del temporizador
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Fin de la prueba" << std::endl;

    //Calculamos el tiempo de ejecución
    double tiempo_ejecucion = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    //Transformamos de nanosegundos a segundos
    tiempo_ejecucion *= 1e-9;

    //Resultados
    std::cout << argv[0] << ';' << n << ';' << tiempo_ejecucion << std::endl;
}