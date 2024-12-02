# Proyecto Final Estructuras de Datos

## Integrantes

- Miguel Angel Flores León 
- Jhordan Steven Octavio Huamani Huamaní 
- Jorge Luis Ortiz Castañeda

# 1. Informe de Avance de Proyecto Final (12/11)


## Descripción del Proyecto
El objetivo de este proyecto es implementar una estructura de datos eficiente para almacenar y buscar canciones en un sistema basado en un archivo CSV. Utilizamos la estructura BTree para optimizar las operaciones de inserción y búsqueda, y aplicamos técnicas de programación paralela para mejorar el rendimiento en tareas de búsqueda masiva y ordenamiento.

## Funcionalidades Implementadas

1. **Estructura de Datos BTree:** 
   Se implementó una estructura BTree, diseñada para manejar grandes volúmenes de datos de manera eficiente. Los nodos del árbol permiten múltiples claves y operaciones rápidas de inserción, búsqueda y recorrido.
   
2. **Lectura y Procesamiento de Archivos CSV:** 
   Se desarrolló un lector de CSV capaz de procesar correctamente datos complejos, como nombres con comas entre comillas y formatos numéricos en notación científica.

3. **Inserción y Búsqueda de Canciones:** 
   Implementación de métodos para insertar canciones en el árbol y buscar canciones por identificador o atributos específicos.

4. **Visualización de la Estructura del BTree:** 
   Una funcionalidad para imprimir la estructura del árbol en la consola, permitiendo visualizar su distribución y jerarquía.

5. **Optimización con Programación Paralela:** 
   Uso de hilos para acelerar las operaciones intensivas, como búsquedas masivas en el árbol y el ordenamiento de canciones.

## Problemas Encontrados

- **Manipulación de Nodos en el BTree:** 
  Se presentaron desafíos en la división de nodos y la redistribución de claves, lo cual requirió ajustes para garantizar la consistencia del árbol.
- **Sincronización en Programación Paralela:** 
  Se identificaron conflictos de acceso a recursos compartidos, que fueron solucionados mediante la implementación de mecanismos de sincronización.

## Posibles Mejoras

1. **Ampliación de la Interfaz de Usuario:** 
   Incluir opciones para búsquedas avanzadas y visualización gráfica del árbol.

2. **Implementación de Índices Secundarios:** 
   Añadir índices secundarios para optimizar las búsquedas por atributos como nombre o artista.

## Conclusión

El proyecto avanza con la implementación exitosa de un BTree como estructura de datos principal y el uso de programación paralela para acelerar operaciones intensivas. Aunque se han superado varios desafíos técnicos, todavía hay margen de mejora en el procesamiento de archivos y la interacción del usuario. Los siguientes pasos se enfocarán en optimizar la eficiencia del sistema y añadir características que enriquezcan la experiencia del usuario.

