#include "src/rapidcsv.h"
#include "hash_map.h"

#define DATASET "datasets/dataset.csv"

// Llena el mapa con los datos de las filas row_begin hasta row_end.
void fill_hash_map(hash_map<long long>* mapa, int row_begin, int row_end)
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

// Busca en el mapa con los datos de las filas row_begin hasta row_end.
void search_hash_map(hash_map<long long>* mapa, int row_begin, int row_end, bool print)
{
    rapidcsv::Document doc(DATASET);
    for (size_t row = row_begin; row <= row_end; row++) {
        long long key = doc.GetCell<long long>("user_id", row);
        if (!print) {
            mapa->get(key);
        } else if (mapa->get(key)) {
            (*mapa->get(key))->printData();
        } else {
            std::string user_name = doc.GetCell<std::string>("user_name", row);
            long long user_id = doc.GetCell<long long>("user_id", row);
            std::cout << "User: " << user_name << "\nID: " << user_id << "\nNo fue encontrado.\n\n";
        }
    }
}

int main(void)
{
    hash_map<long long>* mapa = new hash_map<long long>();

    fill_hash_map(mapa, 0, 5);
    search_hash_map(mapa, 3, 7, true);

    // TODO: fixear el segfault, ya me dio sueño
    fill_hash_map(mapa, 0, 100);
    search_hash_map(mapa, 95, 105, true);
}
