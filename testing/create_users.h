#ifndef CREATE_USERS
#define CREATE_USERS

#include "../user.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>

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

#endif