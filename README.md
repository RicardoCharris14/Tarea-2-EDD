# Tarea-2-EDD
Implementación de varias tablas hash, comparando el rendimiento entre ellas.
## Instrucciones de uso
### Compilación, testeo, y gráficos
```bash
make
cd graph
python makeGraphic.py
```
### Compilación
Para compilar los programas de testeo, ejecute en la linea de comandos:
```bash
make test_id test_all
```
### Realización de tests
Para ejecutar todos los tests (esto puede demorar un poco):
```
./test_all.sh 1000 20000 20
```
Si se  desea una prueba rápida, puede reducir el último argumento (correspondiente al numero de veces que se realizara cada test básico, antes de sacar el promedio):
```bash
./test_all.sh 1000 20000 5
```
O incluso algo más rápido:
```bash
./test_all.sh 1000 20000 1
```

Si se desea más flexibilidad, ejecute el script sin argumentos. Esto le dará una descripción de como operar el script en detalle.
#### Tests individuales
Ejecute los programas por si solos para obtener información detallada de como realizar pruebas individuales:
```
test_name
test_id
```
### Gráficos
Una vez ejecutado el script, hallará los datos recolectados en archivos en formato csv en el directorio test_results/

Para visualizarlos:
```bash
cd graph
python makeGraphic.py
```
Los gráficos deberían aparecer en pantalla. También serán exportados automáticamente a imagenes en formato png en el mismo directorio.

## Troubleshooting
### Problemas con test_all.sh
Abra el script en un editor de texto, y aségurese de que las siguientes variables esten correctamente definidas para su caso.
```bash
## CONFIG ##

# Ejecutables
test_id_exe="./test_id"
test_name_exe="./test_name"

# Datasets
dataset="datasets/dataset.csv"
fakedata="datasets/fakeData.csv"

# Output dir
output_dir="test_results"
```
Las variables deben apuntar correctamente a los ejecutables, archivos y directorios, relativo al directorio de ejecución.
### Problemas con makeGraphic.py
Es posible que el script no encuentre los resultados de las pruebas realizadas anteriormente. En dicho caso, asegúrese que los archivos sean correctamente referidos en las siguientes líneas:
```python
df1 = pd.read_csv('../test_results/double_probing_id.csv', sep=';')
df2 = pd.read_csv('../test_results/double_probing_name.csv', sep=';')
df3 = pd.read_csv('../test_results/linear_probing_id.csv', sep=';')
df4 = pd.read_csv('../test_results/linear_probing_name.csv', sep=';')
df5 = pd.read_csv('../test_results/quadratic_probing_id.csv', sep=';')
df6 = pd.read_csv('../test_results/quadratic_probing_name.csv', sep=';')
df7 = pd.read_csv('../test_results/open_hashing_id.csv', sep=';')
df8 = pd.read_csv('../test_results/open_hashing_name.csv', sep=';')
df9 = pd.read_csv('../test_results/unordered_map_id.csv', sep=';')
df10 = pd.read_csv('../test_results/unordered_map_name.csv', sep=';')
```
Edite el script de ser necesario, refiriendo la ubicación de los resultados de testeo relativo al directorio de ejecución del script.
