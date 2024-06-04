#include "open_hash_map.h"
#include "close_hash_map.h"
#include "hashing_methods.h"
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include "testing/create_users.h"

int main(int argc, char** argv){
    if(argc<3){
        std::cerr << "Usage: " << argv[0] << " <cantidad de elementos> <direccion del csv>" << std::endl;
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
    int (*hash_function)(long long, int) = div;

    //Iniciamos el temporizador
    auto start = std::chrono::high_resolution_clock::now();

    //Codigo a experimentar
    
    open_hash_map<long long>* mapa = new open_hash_map<long long>(20, hash_function);
    for(int i=0 ; i<n ; i++){
        user* tmp_user = usuarios.front();
        mapa->put(tmp_user->getID(), tmp_user);
        usuarios.pop();
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