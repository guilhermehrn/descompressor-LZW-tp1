/*
 * lzw.hpp
 *
 *  Created on: Oct 09, 2015
 *      Author: guilherme
 */
#ifndef LZW_HPP_
#define LZW_HPP_

#include <cstdint>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

/**
 * Funcão para comprimir uma imagem. Ela implementa o algoritimo LZW.
 * @param entrada:  sequencia de bits que representa a imagem
 * @param saida: sequencia de bits que representa a imagem a ser descompactada
 */
void compressor(istream &entrada, ostream &saida);

/**
 * Função que descomapcta um arquivo compactado pelo algoritimo LZW
 * @param entrada: arquivo de entrada;
 * @param saida: arquivo de saida;
 */
void descompressor(istream &entrada, ostream &saida);

#endif /* LZW_HPP_ */
