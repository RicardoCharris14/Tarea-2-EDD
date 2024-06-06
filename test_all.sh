#!/usr/bin/env sh
set -e


## CONFIG ##

# Ejecutables
test_id_exe="./testing/output/test_id"
test_name_exe="./testing/output/test_name"

# Datasets
dataset="datasets/dataset.csv"
fakedata="datasets/fakeData.csv"

# Output dir
output_dir="test_results"

if [ $# -ne 3 ]
then
    cat << EOF
Usage: test_all <step> <max_users> <num_tests>

Se testea con <step> usuarios, y se va incrementando en <step> usuarios hasta
llegar a <max_users>. Cada test se realiza <num_tests> veces, posteriormente
se saca el promedio.

Ej: "test_all 200 1000" realizará los tests con: 200, 400, 600, 800 y 1000
usuarios y escribirá los resultados en archivos separados para cada hashing.
EOF

    exit 1
fi

step=$1
max_users=$2
num_tests=$3

if [ ! -d $output_dir ]
then
    mkdir $output_dir
fi

test_hash() { # Recibe el hashing a testear
    for num_testing in $(seq $step $step $max_users)
    do
        $1 $num_testing
    done
}

open_hashing_id() {
    $test_id_exe $1 $dataset $fakedata 0 $num_tests
}

open_hashing_name() {
    $test_name_exe $1 $dataset $fakedata 0 $num_tests
}

linear_probing_id() {
    $test_id_exe $1 $dataset $fakedata 1 $num_tests
}

linear_probing_name() {
    $test_name_exe $1 $dataset $fakedata 1 $num_tests
}

double_probing_id() {
    $test_id_exe $1 $dataset $fakedata 2 $num_tests
}

double_probing_name() {
    $test_name_exe $1 $dataset $fakedata 2 $num_tests
}

quadratic_probing_id() {
    $test_id_exe $1 $dataset $fakedata 3 $num_tests
}

quadratic_probing_name() {
    $test_name_exe $1 $dataset $fakedata 3 $num_tests
}

unordered_map_id() {
    $test_id_exe $1 $dataset $fakedata 4 $num_tests
}

unordered_map_name() {
    $test_name_exe $1 $dataset $fakedata 4 $num_tests
}

## Aca se hacen los tests
for hashing in open_hashing_id open_hashing_name linear_probing_id linear_probing_name double_probing_id double_probing_name quadratic_probing_id quadratic_probing_name unordered_map_id unordered_map_name
do
    printf "Testeando: %s\n" "$hashing"
    filename=$hashing.csv
    if [ -e $output_dir/$filename ]
    then
        rm $output_dir/$filename
    fi

    printf "hashing;num_usuarios;tiempo_insercion;tiempo_busqueda1;tiempo_busqueda2;KB_Hashmap\n" >> $output_dir/$filename

    for num_testing in $(seq $step $step $max_users)
    do
        printf "%s usuarios..." "$num_testing"
        $hashing $num_testing >> $output_dir/$filename
        printf "done\n"
    done
    printf "\n"
done



