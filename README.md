# Proyecto de Corrección Gramatical con Paralelización

Este proyecto utiliza la biblioteca `language_tool_python` para realizar correcciones gramaticales en oraciones en inglés. Se implementan dos versiones del programa: una versión secuencial y una versión paralela utilizando OpenMP para comparar el rendimiento.

## Archivos del Proyecto

- **grammar_check.py**: Script de Python que utiliza `language_tool_python` para corregir errores gramaticales en oraciones.
- **Proyecto.cpp**: Versión paralela del programa en C++ que corrige oraciones utilizando OpenMP para la paralelización.
- **ProyectoSecuencial.cpp**: Versión secuencial del programa en C++ para corregir oraciones.

## Descripción de los Archivos

### 1. `grammar_check.py`

Este script de Python se encarga de corregir la gramática de oraciones utilizando la biblioteca `language_tool_python`.

#### Uso
```bash
python3 grammar_check.py "Texto a corregir"
```
#### Funciones Principales
'correct_sentence(sentence)': Toma una oración como entrada y devuelve la versión corregida después de verificar y aplicar sugerencias de corrección gramatical.

### 2. `Proyecto.cpp`
Este archivo C++ implementa la corrección gramatical de múltiples oraciones en paralelo utilizando OpenMP para mejorar el rendimiento en sistemas con múltiples núcleos.

####Compilación y Ejecución
g++ -fopenmp Proyecto.cpp -o ProyectoParalelo
./ProyectoParalelo

### 3. `ProyectoSecuencial.cpp`
Este archivo C++ implementa la corrección gramatical de múltiples oraciones de forma secuencial.

####Compilación y Ejecución
g++ ProyectoSecuencial.cpp -o ProyectoSecuencial
./ProyectoSecuencial

##Instrucciones de configuración

### 1. Instalar Dependencias de Python: Asegúrate de tener Python 3 instalado y ejecuta el siguiente comando para instalar la biblioteca `language_tool.python`
pip install language_tool_python



