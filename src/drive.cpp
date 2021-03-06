/**
 *  \mainpage BARES
 *  \author Gustavo Araújo Carvalho
 *  \author Yuri Alessandro Martins
 *  \date 2016
 *  \version 1.0
 *
 *  \file drive.cpp
 *  \brief Contém a função principal do programa.
 */

#include <iostream>
#include <fstream>
#include "functions.h"
#include "queuear.h"
#include "token.h"
#include "stackar.h"

#define FILENAME "test.txt"

/**
 * \brief Função principal do programa:\n
 * Executa passos importantes para a leitura do arquivo e chama as funções que irão tratá-lo.\n
 * Também chama as funções de tratamento de erro e a função de calculadora propriamente dita.
 */
int main(int argc, char* argv[])
{
    std::string fileName;
    QueueAr<Token> tokens;
    QueueAr<Token> posfixTest;

    if ( argc > 1 )
        fileName = argv[1];
    else
        fileName = FILENAME;

	/* Avisa para o usuário que o arquivo será lido.*/
	std::cout << ">>> Preparing to read file [" << fileName << "], please wait...\n";

	/* Abre o arquivo como somente leitura. */
	std::ifstream file( fileName );

	/* Retorna falso se o arquivo não for encontrado. */
	if( !file.is_open() ){
        std::cout << ">>>>Falha na abertura" << std::endl;
    	return EXIT_FAILURE;
    }

    /* Início do processo de parsing e tokenização */
    std::string currentLine;
    int column;
    int errorId;

    int res;

    /* Loop do arquivo */
	while ( std::getline( file, currentLine ) ) {
        column = 1;
        errorId = parseAndTokenize( tokens, currentLine, column );

        /* Em caso de erro: O imprime na tela, faz a limpeza necessária e
         * continua o loop. */
        if ( errorId ) {
            std::cout << "E" << errorId << " " << column << std::endl;
            tokens.makeEmpty();
            continue;
        }

        /* Transforma em pós-fixo e realiza os cálculos. */
        toPostfix( tokens, posfixTest );
        res = analysis( posfixTest, errorId  );

        /* Em caso de erro: O imprime na tela, faz a limpeza necessária e
         * continua o loop. */
        if ( errorId ) {
            std::cout << "E" << errorId << std::endl;
            posfixTest.makeEmpty();
            continue;
        }

        /* Imprime o resultado */
        std::cout << res << std::endl;

	}

	file.close();

    return 0;
}
