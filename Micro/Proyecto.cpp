#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <cstdio>
#include <omp.h>  // Librería para paralelización con OpenMP

// Función para corregir la gramática de una oración utilizando un script de Python
std::string correctGrammar(const std::string& sentence) {
    std::string command = "python3 grammar_check.py \"" + sentence + "\"";  // Comando para ejecutar el script Python
    std::array<char, 128> buffer;
    std::string result;

    FILE* pipe = popen(command.c_str(), "r");  // Abre un pipe para ejecutar el comando
    if (!pipe) {
        std::cerr << "No se pudo ejecutar el comando." << std::endl;
        return sentence;
    }

    // Lee la salida del comando Python y la almacena en result
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    pclose(pipe);  // Cierra el pipe
    return result;
}

int main() {
    double start_time = omp_get_wtime();  // Captura el tiempo de inicio

    std::ifstream infile("oraciones.txt");  // Archivo de entrada con oraciones
    std::ofstream outfile("oraciones_corregidas.txt");  // Archivo de salida para oraciones corregidas

    if (!infile || !outfile) {
        std::cerr << "Error al abrir los archivos." << std::endl;
        return 1;
    }

    std::vector<std::string> sentences;
    std::string line;

    // Lee todas las oraciones del archivo de entrada
    while (std::getline(infile, line)) {
        sentences.push_back(line);
    }

    std::vector<std::string> corrected_sentences(sentences.size());

    // Paralelización de la corrección de oraciones usando OpenMP
    #pragma omp parallel
    {
        #pragma omp single
        {
            for (size_t i = 0; i < sentences.size(); ++i) {
                #pragma omp task  // Crea una tarea para cada corrección de oración
                {
                    corrected_sentences[i] = correctGrammar(sentences[i]);
                }
            }
        }
    }

    // Guarda las oraciones corregidas en el archivo de salida
    for (size_t i = 0; i < corrected_sentences.size(); ++i) {
        outfile << corrected_sentences[i];
        if (i < corrected_sentences.size() - 1) {
            outfile << std::endl;  // Añade un salto de línea si no es la última línea
        }
    }

    infile.close();
    outfile.close();

    double end_time = omp_get_wtime();  // Captura el tiempo de finalización

    std::cout << "Corrección completada y guardada en 'oraciones_corregidas.txt'." << std::endl;
    std::cout << "Tiempo total de ejecución: " << (end_time - start_time) << " segundos." << std::endl;

    return 0;
}
