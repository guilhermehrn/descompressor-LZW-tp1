/*
 * lzw.cpp
 *
 *  Created on: Oct 09, 2015
 *      Author: guilherme
 */

#include "lzw.hpp"

/**
 * Funcão para comprimir uma imagem. Ela implementa o algoritimo LZW.
 * @param entrada:  sequencia de bits que representa a imagem
 * @param saida: sequencia de bits que representa a imagem a ser descompactada
 */
void compressor(istream &entrada, ostream &saida) {

	using CodeType = uint16_t;
	//Tipo usado para armazenar e gravar a codificação.
	map<vector<char>, CodeType> dicionario; 	//tipo que define o dicionario
	const CodeType dic_max { numeric_limits<CodeType>::max() }; //tipo que define o tamnho maximo do dicionario
	vector<char> s; // vetor que armazena temporariamente a subsequencia a ser codificada
	char aux; //tipo a auxiliar para ler do arquivo

	// Funcão Lambida usada, para resetar o dicionario.
	const auto reset_dicionario = [&dicionario] {

		dicionario.clear();
		const long int minimoc = numeric_limits<char>::min();
		const long int maximoc = numeric_limits<char>::max();

		for (long int c = minimoc; c <= maximoc; c++) {
			const CodeType dicionario_tamanho = dicionario.size();
			dicionario[ {static_cast<char> (c)}] = dicionario_tamanho;
		}
	};

	reset_dicionario();

	while (entrada.get(aux)) {
		//testando para ver se o tamanho máximo foi atingido
		if (dicionario.size() == dic_max) {
			reset_dicionario();
		}

		s.push_back(aux);

		if (dicionario.count(s) == 0) {

			const CodeType dicionario_tam = dicionario.size();
			dicionario[s] = dicionario_tam;
			s.pop_back();
			saida.write(reinterpret_cast<const char *>(&dicionario.at(s)),
					sizeof(CodeType));
			s = {aux};
		}
	}

	if (!s.empty()) {
		saida.write(reinterpret_cast<const char *>(&dicionario.at(s)),
				sizeof(CodeType));
	}
}

/**
 * Função que descomapcta um arquivo compactado pelo algoritimo LZW
 * @param entrada: arquivo de entrada;
 * @param saida: arquivo de saida;
 */
void descompressor(istream &entrada, ostream &saida) {

	using CodeType = uint16_t;
	//Tipo usado para armazenar e escrever a codificação.
	vector<vector<char>> dicionario; //vetor para recompor o dicionario.
	const CodeType dic_max { numeric_limits<CodeType>::max() };

	vector<char> seqaux;
	CodeType chave;

	// Funcão Lambida usada, para resetar o dicionario.
	const auto reset_dicionario = [&dicionario] {
		dicionario.clear();
		dicionario.reserve(dic_max);

		const long int minimoc = numeric_limits<char>::min();
		const long int maximoc = numeric_limits<char>::max();

		for (long int c = minimoc; c <= maximoc; c++)
		dicionario.push_back( {static_cast<char> (c)});
	};

	reset_dicionario();

	while (entrada.read(reinterpret_cast<char *>(&chave), sizeof(CodeType))) {
		//testando para ver se o tamanho máximo foi atingido
		if (dicionario.size() == dic_max)
			reset_dicionario();

		if (chave > dicionario.size())
			throw runtime_error("codigo de compressão invalido");

		if (chave == dicionario.size()) {
			seqaux.push_back(seqaux.front());
			dicionario.push_back(seqaux);
		} else if (!seqaux.empty()) {
			seqaux.push_back(dicionario.at(chave).front());
			dicionario.push_back(seqaux);
		}

		saida.write(&dicionario.at(chave).front(), dicionario.at(chave).size());
		seqaux = dicionario.at(chave);
	}
}

