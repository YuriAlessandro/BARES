#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "stackar.h"
#include "term.h"

int main(int argc, char* argv[])
{
    // Futuramente será a classe Expression(tm), porém se continuará um stack
    // é um mistério.
    StackAr<Term> terms;

	std::string fileName = "test.txt";

	/* Avisa para o usuário que o arquivo será lido.*/
	std::cout << ">>> Preparing to read bet file [" << fileName << "], please wait...\n";

	/* Abre o arquivo como somente leitura. */
	std::ifstream file( fileName );

	/* Retorna falso se o arquivo não for encontrado. */
	if( !file.is_open() ){
        std::cout << "Falha na abertura" << "\n";
    	return EXIT_FAILURE;
    }

    // Definitivamente bem melhor agora, porém o (file >> temp) ignora espaços e
    // símbolos de nova linha, então talvez seja melhor simplesmente usar um
    // getline e trabalhar em cima disso.
    std::string currentLine;
    std::string number;
    int column = 0;

    // Loop do arquivo
	while ( std::getline( file, currentLine ) ){

        // Loop da linha
	    for ( char temp : currentLine )
	    {
	        //std::cout << "temp = " << temp << "\n";
            column++; // Usar essa variável para checar erros

            // Operando
	        if ( isdigit( temp ) ){
	            number += temp;
	        }else if ( temp == '+' or temp == '-' or temp == '*' or temp == '/' or temp == '%' ){ // Fazer função pra checar isso usando hacks de ASCII
	            if ( number.size() > 0 )
                    terms.push( Term( number, true ) );

                number = "";
                terms.push ( Term( std::string( 1, temp ), false ) );
	        }else{
                if ( temp != ' ' ) std::cout << ">>>> I, the program, have no idea of what this might be: "
                << temp << " on column " << column << std::endl;
	            // Tratamento de erros vem aqui.
                // Espaços não são erros, então fica assim até colocar os erros reais.
                // Idealmente vamos pelos erros específicos, sem usar nenhum "else" que possa
                // pegar coisas estranhas.
	        }

        }

	    // jogando restos do loop onde devem ficar, resetando valores
	    if ( number.size() > 0 ) terms.push( Term( number, true ) );
	    number = "";

	    // Coloca no stack quando termina de ler uma linha para testar
	    // terms.push( Term( "Testing purposes", false ) );
	}

	file.close();

    // Teste
    std::cout << "\n[ ";
    while ( !terms.isEmpty() ){
        Term printingTerm = terms.pop();
        std::cout << printingTerm.getValue() << ", ";
    }
    std::cout << "]\n";


    return 0;
}
