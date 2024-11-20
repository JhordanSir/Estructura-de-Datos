# Proyecto Final Estructuras de Datos

## Integrantes

- Miguel Angel Flores Amarillas
- Jhordan Steven Octavio Huamani Huamani (yo no hago nada y me aprueban jajajajajaja)
- Jorge Luis Ortiz Castañeda

# 1. Informe de Avance de Proyecto Final (12/11)


## Descripción del Proyecto
El objetivo de este proyecto es desarrollar una estructura de datos eficiente para almacenar y buscar canciones de un archivo de datos en formato CSV, similar a un dataset de Spotify. Utilizamos un Árbol B como estructura de almacenamiento para manejar la carga de datos y facilitar las búsquedas eficientes de canciones.

## Funcionalidades Implementadas

1. **Estructura de Datos Árbol B:** 
   Se creó una estructura de datos basada en Árbol B, implementando nodos con un número máximo de claves (3 en este caso) para el manejo de las canciones.
   
2. **Lectura de CSV con Campos Complejos:** 
   Se desarrolló un lector de CSV para procesar nombres con comas dentro de comillas y otros formatos numéricos complejos.

3. **Inserción y Búsqueda de Canciones:** 
   Implementación de funciones para insertar canciones en el Árbol B y buscar canciones mediante su ID.

4. **Impresión del Árbol B:** 
   Se creó una función para visualizar la estructura actual del Árbol B en consola.

## Problemas Encontrados

- **Elección de la Estructura de Datos:** 
  Aunque el Árbol B permite inserciones y búsquedas eficientes, surgieron desafíos en la manipulación de nodos y la división de hijos. Por ello, se está considerando la posibilidad de cambiar a una tabla hash para mejorar el rendimiento en búsquedas.

- **Lectura Compleja de CSV:** 
  La estructura del CSV incluye campos con comas dentro de comillas y valores flotantes en notación científica (por ejemplo, `1+e10`). Esto requirió el desarrollo de una función personalizada para leer cada campo y evitar errores de parsing.

## Posibles Mejoras

1. **Cambio a Tabla Hash:** 
   La tabla hash podría ofrecer un rendimiento más rápido para las búsquedas directas de ID de canciones, en comparación con el Árbol B.

2. **Optimización de Lectura CSV:** 
   Mejorar el manejo de casos excepcionales en el lector de CSV, como caracteres especiales y formatos numéricos avanzados, para garantizar una carga de datos más robusta.

3. **Interfaz de Usuario:** 
   Crear una interfaz gráfica o de consola más amigable para interactuar con la estructura de datos, incluyendo opciones de búsqueda y visualización más detalladas.

## Conclusión

Hasta el momento, el proyecto ha avanzado en la implementación básica de un Árbol B para el manejo de canciones, permitiendo la inserción y búsqueda de datos desde un archivo CSV. Sin embargo, se identificaron limitaciones en la estructura de datos y en el procesamiento del archivo CSV, las cuales están siendo revisadas para mejorar la eficiencia y funcionalidad del sistema. La consideración de una tabla hash y la optimización de la lectura del CSV serán los siguientes pasos clave para completar el proyecto.

## Próximos Pasos

1. Evaluar el cambio de estructura de datos a una tabla hash para búsquedas más rápidas.
2. Optimizar el procesamiento de archivos CSV para manejar casos especiales de manera más robusta.
3. Desarrollar una interfaz de usuario para facilitar la interacción y visualización de las canciones almacenadas.
4. Realizar pruebas de rendimiento y realizar ajustes según los resultados obtenidos para asegurar que el sistema funcione eficientemente con grandes volúmenes de datos.
