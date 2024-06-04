#include "src/rapidcsv.h"
#include "close_hash_map.h"
#include "open_hash_map.h"
#include <chrono>

#define DATASET "datasets/dataset.csv"

// Llena el mapa con los datos de las filas row_begin hasta row_end.
void fill_id_close_hash_map(close_hash_map<long long>* mapa, int row_begin, int row_end)
{
    rapidcsv::Document doc(DATASET);
    for (size_t row = row_begin; row <= row_end; row++) {

        std::string university = doc.GetCell<std::string>("university", row);
        std::string created_at = doc.GetCell<std::string>("created_at", row);
        std::string user_name = doc.GetCell<std::string>("user_name", row);

        long long user_id = doc.GetCell<long long>("user_id", row);
        int number_tweets = doc.GetCell<int>("number_tweets", row);
        int friends_count = doc.GetCell<int>("friends_count", row);
        int followers_count = doc.GetCell<int>("followers_count", row);

        user* newuser = new user(university, user_id, user_name, number_tweets,
                                 friends_count, followers_count, created_at);

        mapa->put(newuser->getID(), newuser);
    }
}

void fill_id_open_hash_map(open_hash_map<long long>* mapa, int row_begin, int row_end){
    rapidcsv::Document doc(DATASET);
    for (size_t row = row_begin; row <= row_end; row++) {

        std::string university = doc.GetCell<std::string>("university", row);
        std::string created_at = doc.GetCell<std::string>("created_at", row);
        std::string user_name = doc.GetCell<std::string>("user_name", row);

        long long user_id = doc.GetCell<long long>("user_id", row);
        int number_tweets = doc.GetCell<int>("number_tweets", row);
        int friends_count = doc.GetCell<int>("friends_count", row);
        int followers_count = doc.GetCell<int>("followers_count", row);

        user* newuser = new user(university, user_id, user_name, number_tweets,
                                 friends_count, followers_count, created_at);

        mapa->put(newuser->getID(), newuser);
    }
}

void fill_name_close_hash_map(close_hash_map<std::string>* mapa, int row_begin, int row_end){
    rapidcsv::Document doc(DATASET);
    for (size_t row = row_begin; row <= row_end; row++) {

        std::string university = doc.GetCell<std::string>("university", row);
        std::string created_at = doc.GetCell<std::string>("created_at", row);
        std::string user_name = doc.GetCell<std::string>("user_name", row);

        long long user_id = doc.GetCell<long long>("user_id", row);
        int number_tweets = doc.GetCell<int>("number_tweets", row);
        int friends_count = doc.GetCell<int>("friends_count", row);
        int followers_count = doc.GetCell<int>("followers_count", row);

        user* newuser = new user(university, user_id, user_name, number_tweets,
                                 friends_count, followers_count, created_at);

        mapa->put(newuser->getUsername(), newuser);
    }
}

void fill_name_open_hash_map(open_hash_map<std::string>* mapa, int row_begin, int row_end){
    rapidcsv::Document doc(DATASET);
    for (size_t row = row_begin; row <= row_end; row++) {

        std::string university = doc.GetCell<std::string>("university", row);
        std::string created_at = doc.GetCell<std::string>("created_at", row);
        std::string user_name = doc.GetCell<std::string>("user_name", row);

        long long user_id = doc.GetCell<long long>("user_id", row);
        int number_tweets = doc.GetCell<int>("number_tweets", row);
        int friends_count = doc.GetCell<int>("friends_count", row);
        int followers_count = doc.GetCell<int>("followers_count", row);

        user* newuser = new user(university, user_id, user_name, number_tweets,
                                 friends_count, followers_count, created_at);

        mapa->put(newuser->getUsername(), newuser);
    }
}

// Busca en el mapa con los datos de las filas row_begin hasta row_end.
void search_id_close_hash_map(close_hash_map<long long>* mapa, int row_begin, int row_end, bool print)
{
    rapidcsv::Document doc(DATASET);
    for (size_t row = row_begin; row <= row_end; row++) {
        long long key = doc.GetCell<long long>("user_id", row);
        if (!print) {
            mapa->get(key);
        } else if (mapa->get(key)) {
            (mapa->get(key))->printData();
        } else {
            std::string user_name = doc.GetCell<std::string>("user_name", row);
            long long user_id = doc.GetCell<long long>("user_id", row);
            std::cout << "User: " << user_name << "\nID: " << user_id << "\nNo fue encontrado.\n\n";
        }
    }
}

void search_id_open_hash_map(open_hash_map<long long>* mapa, int row_begin, int row_end, bool print)
{
    rapidcsv::Document doc(DATASET);
    for (size_t row = row_begin; row <= row_end; row++) {
        long long key = doc.GetCell<long long>("user_id", row);
        if (!print) {
            mapa->get(key);
        } else if (mapa->get(key)) {
            (mapa->get(key))->printData();
        } else {
            std::string user_name = doc.GetCell<std::string>("user_name", row);
            long long user_id = doc.GetCell<long long>("user_id", row);
            std::cout << "User: " << user_name << "\nID: " << user_id << "\nNo fue encontrado.\n\n";
        }
    }
}

int main(int argc, char** argv)
{
    if(argc < 2){
        std::cerr << argv[0] << "<elements number>" << std::endl;
        exit(1);
    }

    //Numero de datos a utilizar en el test 
    int data_quantity = atoi(argv[1]);

    //Funcion hash a utilizar
    int (*hash_function)(long long, int) = div;

    //Inicio del timer
    auto start = std::chrono::high_resolution_clock::now();

    //Codigo a testear
    open_hash_map<long long>* mapa = new open_hash_map<long long>(20, hash_function);

    fill_id_open_hash_map(mapa, 0, data_quantity-1);
    // search_id_open_hash_map(mapa, 0, data_quantity-1, false);

    // // TODO: fixear el segfault, ya me dio sueño
    // fill_hash_map(mapa, 0, 100);
    // search_hash_map(mapa, 95, 105, true);



    //Fin del timer
    auto end = std::chrono::high_resolution_clock::now();
    //calcular tiempo de ejecucion
    double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    //transformamos de nanosegundos a segundos
    running_time *= 1e-9;
    //Imprimimos resultados
    std::cout << argv[0] << ';' << data_quantity << ';' << running_time << std::endl;
}
