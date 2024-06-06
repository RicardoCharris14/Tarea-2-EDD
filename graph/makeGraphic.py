import pandas as pd
import matplotlib.pyplot as plt

df1 = pd.read_csv('./double_probing_id.csv', sep=';')
df2 = pd.read_csv('./double_probing_name.csv', sep=';')
df3 = pd.read_csv('./linear_probing_id.csv', sep=';')
df4 = pd.read_csv('./linear_probing_name.csv', sep=';')
df5 = pd.read_csv('./quadratic_probing_id.csv', sep=';')
df6 = pd.read_csv('./quadratic_probing_name.csv', sep=';')
df7 = pd.read_csv('./open_hashing_id.csv', sep=';')
df8 = pd.read_csv('./open_hashing_name.csv', sep=';')
df9 = pd.read_csv('./unordered_map_id.csv', sep=';')
df10 = pd.read_csv('./unordered_map_name.csv', sep=';')

# Grafico de tiempo de insercion segun user_name
plt.figure()
plt.subplot(2, 1, 1)
plt.plot(df2['num_usuarios'], df2['tiempo_insercion'])
plt.plot(df4['num_usuarios'], df4['tiempo_insercion'])  
plt.plot(df6['num_usuarios'], df6['tiempo_insercion'])
plt.plot(df8['num_usuarios'], df8['tiempo_insercion'])
plt.plot(df10['num_usuarios'], df10['tiempo_insercion'])
plt.xlabel('número de usuarios')
plt.ylabel('Tiempo de inserción')
plt.title('Tiempo de inserción según user_name')
plt.legend(['Double Probing', 'Linear Probing', 'Quadratic Probing', 'Open Hashing', 'Unordered Map'])

# Grafico de tiempo de insercion segun id_usuario
plt.subplot(2, 1, 2)
plt.plot(df1['num_usuarios'], df1['tiempo_insercion'])
plt.plot(df3['num_usuarios'], df3['tiempo_insercion'])
plt.plot(df5['num_usuarios'], df5['tiempo_insercion'])
plt.plot(df7['num_usuarios'], df7['tiempo_insercion'])
plt.plot(df9['num_usuarios'], df9['tiempo_insercion'])
plt.xlabel('número de usuarios')
plt.ylabel('Tiempo de insercion')
plt.title('Tiempo de inserción según id_usuario')
plt.legend(['Double Probing', 'Linear Probing', 'Quadratic Probing', 'Open Hashing', 'Unordered Map'])

plt.tight_layout()



#Grafico de tiempo de busqueda de usuarios existentes segun user_name
plt.figure()
plt.subplot(2, 1, 1)
plt.plot(df2['num_usuarios'], df2['tiempo_busqueda1'])
plt.plot(df4['num_usuarios'], df4['tiempo_busqueda1'])  
plt.plot(df6['num_usuarios'], df6['tiempo_busqueda1'])
plt.plot(df8['num_usuarios'], df8['tiempo_busqueda1'])
plt.plot(df10['num_usuarios'], df10['tiempo_busqueda1'])
plt.xlabel('número de usuarios')
plt.ylabel('Tiempo de busqueda')
plt.title('Tiempo de busqueda(usuarios existentes) según user_name')
plt.legend(['Double Probing', 'Linear Probing', 'Quadratic Probing', 'Open Hashing', 'Unordered Map'])

#gafico de tiempo de busqueda de usuarios existentes segun id_usuario
plt.subplot(2, 1, 2)
plt.plot(df1['num_usuarios'], df1['tiempo_busqueda1'])
plt.plot(df3['num_usuarios'], df3['tiempo_busqueda1'])
plt.plot(df5['num_usuarios'], df5['tiempo_busqueda1'])
plt.plot(df7['num_usuarios'], df7['tiempo_busqueda1'])
plt.plot(df9['num_usuarios'], df9['tiempo_busqueda1'])
plt.xlabel('número de usuarios')
plt.ylabel('Tiempo de insercion')
plt.title('Tiempo de busqueda(usuarios existentes) según id_usuario')
plt.legend(['Double Probing', 'Linear Probing', 'Quadratic Probing', 'Open Hashing', 'Unordered Map'])

plt.tight_layout()



#Grafico de tiempo de busqueda de usuarios inexistentes segun user_name
plt.figure()
plt.subplot(2, 1, 1)
plt.plot(df2['num_usuarios'], df2['tiempo_busqueda2'])
plt.plot(df4['num_usuarios'], df4['tiempo_busqueda2'])  
plt.plot(df6['num_usuarios'], df6['tiempo_busqueda2'])
plt.plot(df8['num_usuarios'], df8['tiempo_busqueda2'])
plt.plot(df10['num_usuarios'], df10['tiempo_busqueda2'])
plt.xlabel('número de usuarios')
plt.ylabel('Tiempo de busqueda')
plt.title('Tiempo de busqueda(usuarios inexistentes) según user_name')
plt.legend(['Double Probing', 'Linear Probing', 'Quadratic Probing', 'Open Hashing', 'Unordered Map'])

#gafico de tiempo de busqueda de usuarios inexistentes segun id_usuario
plt.subplot(2, 1, 2)
plt.plot(df1['num_usuarios'], df1['tiempo_busqueda2'])
plt.plot(df3['num_usuarios'], df3['tiempo_busqueda2'])
plt.plot(df5['num_usuarios'], df5['tiempo_busqueda2'])
plt.plot(df7['num_usuarios'], df7['tiempo_busqueda2'])
plt.plot(df9['num_usuarios'], df9['tiempo_busqueda2'])
plt.xlabel('número de usuarios')
plt.ylabel('Tiempo de insercion')
plt.title('Tiempo de busqueda(usuarios inexistentes) según id_usuario')
plt.legend(['Double Probing', 'Linear Probing', 'Quadratic Probing', 'Open Hashing', 'Unordered Map'])

plt.tight_layout()

plt.show()