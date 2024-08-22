#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <cstdio>
#include <omp.h> // Mantengo omp.h para usar omp_get_wtime()

std::string correctGrammar(const std::string& sentence) {
    std::string command = "python3 grammar_check.py \"" + sentence + "\"";
    std::array<char, 128> buffer;
    std::string result;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "No se pudo ejecutar el comando." << std::endl;
        return sentence;
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    pclose(pipe);
    return result;
}

int main() {
    double start_time = omp_get_wtime();  // Capturamos el tiempo de inicio

    std::ifstream infile("oraciones.txt");
    std::ofstream outfile("oraciones_corregidas.txt");

    if (!infile || !outfile) {
        std::cerr << "Error al abrir los archivos." << std::endl;
        return 1;
    }

    std::vector<std::string> sentences;
    std::string line;

    while (std::getline(infile, line)) {
        sentences.push_back(line);
    }

    std::vector<std::string> corrected_sentences(sentences.size());

    // Procesamiento secuencial de cada oración
    for (size_t i = 0; i < sentences.size(); ++i) {
        corrected_sentences[i] = correctGrammar(sentences[i]);
    }

    // Guardar las oraciones corregidas en el archivo de salida
    for (size_t i = 0; i < corrected_sentences.size(); ++i) {
        outfile << corrected_sentences[i];
        if (i < corrected_sentences.size() - 1) {
            outfile << std::endl; // Solo añade salto de línea si no es la última línea
        }
    }

    infile.close();
    outfile.close();

    double end_time = omp_get_wtime();  // Capturamos el tiempo de finalización

    std::cout << "Corrección completada y guardada en 'oraciones_corregidas.txt'." << std::endl;
    std::cout << "Tiempo total de ejecución: " << (end_time - start_time) << " segundos." << std::endl;

    return 0;
}
