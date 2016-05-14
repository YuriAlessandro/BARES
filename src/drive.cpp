#include <iostream>
#include <fstream>
#include "functions.h"
#include "queuear.h"
#include "token.h"
#include "stackar.h"

#define FILENAME "test"

int main(int argc, char* argv[])
{
    std::string fileName;
    QueueAr<Token> tokens;
    QueueAr<Token> posfixTest;

    if ( argc > 1 )
        fileName = argv[1];
    else
        fileName = FILENAME;

    fileName += ".txt";

	/* Avisa para o usuário que o arquivo será lido.*/
	std::cout << ">>> Preparing to read bet file [" << fileName << "], please wait...\n";

	/* Abre o arquivo como somente leitura. */
	std::ifstream file( fileName );

	/* Retorna falso se o arquivo não for encontrado. */
	if( !file.is_open() ){
        std::cout << "Falha na abertura" << "\n";
    	return EXIT_FAILURE;
    }

    // Início do processo de parsing e tokenização
    std::string currentLine;
    int column;
    int errorId;

    // Loop do arquivo
	while ( std::getline( file, currentLine ) ){
        column = 1;
        errorId = parseAndTokenize( tokens, currentLine, column );

        if ( errorId ){
            std::cout << "E" << errorId << " " << column << "\n";
            tokens.makeEmpty();
        } else {

            toPostfix( tokens, posfixTest );

            /* Teste Comum
            std::cout << "[ ";
            while ( !tokens.isEmpty() ){
            Token printingToken;
            tokens.dequeue( printingToken );
            std::cout << printingToken.getValue() << " ";
            }
            std::cout << "]\n";
            */

            // Teste postfix
            std::cout << "[ ";
            while ( !posfixTest.isEmpty() ){
                Token printingToken;
                posfixTest.dequeue( printingToken );
                std::cout << printingToken.getValue() << " ";
            }
            std::cout << "]\n";
            /**/

            // Falta somente a calculadora

        }

        posfixTest.makeEmpty();
	}

	file.close();

    return 0;
}
