#include "lzw.hpp"

// Main do Programa de descompressão LZW
// @param argc             numero de parametros
// @param argv             array com os parametros
// @retval EXIT_FAILURE    se falhar na execução
// @retval 0               se executar corretamente
int main(int argc, char *argv[]) {

	cout << "TRABALHO PRATICO 1 - INTRODUCAO A COMPUTACAO VISUAL - DCC - UFMG" << endl;
	cout << "NOME : Guilherme Henrique Rodrigues Nascimento" << endl;
	cout << "MATRICULA: 2010054460" << endl;
	cout << "Programa de descompressão do LZW" << endl;

	ifstream arquivo_ent(argv[1], ios_base::binary);

	if (!arquivo_ent.is_open()) {
		cout << argv[1] << " não pode ser aberto" << endl;
		return EXIT_FAILURE;
	}

	string nome = argv[1];
	int tamanho = (int) nome.size();
	cout<<tamanho;
	string nomesaida = nome.substr(0, tamanho -11) ;

	ofstream arquivo_saida(nomesaida.append(".saida.png"), ios_base::binary);

	if (!arquivo_saida.is_open()) {
		cout << "arquivo de saida " << argv[2] << " não pode ser criado." << endl;
		return EXIT_FAILURE;
	}

	descompressor(arquivo_ent, arquivo_saida);

	cout << "Aquivo descompactado 1" << endl;

	return 0;
}

