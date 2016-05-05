#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "queuear.h"
#include "term.h"

int main(int argc, char* argv[])
{
    // Futuramente será a classe Expression(tm), porém se continuará um stack
    // é um mistério.
    QueueAr<Term> terms;

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
	        }else if ( temp == '+' or temp == '-' or temp == '*' or temp == '/' or temp == '%' or temp == '(' or temp == ')'){ // Fazer função pra checar isso usando hacks de ASCII
	            if ( number.size() > 0 )
                    terms.enqueue( Term( number, true ) );

                number = "";
                terms.enqueue( Term( std::string( 1, temp ), false ) );
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
	    if ( number.size() > 0 ) terms.enqueue( Term( number, true ) );
	    number = "";

	    // Coloca no stack quando termina de ler uma linha para testar
	    // terms.enqueue( Term( "Testing purposes", false ) );
	}

	file.close();

    // Teste
    std::cout << "\n[ ";
    while ( !terms.isEmpty() ){
        Term printingTerm = terms.dequeue();
        std::cout << printingTerm.getValue() << ", ";
    }
    std::cout << "]\n";


    return 0;
}

/*
1. Numeric constant out of range: Um dos operandos da express ̃ao est ́a fora da faixa
permitida.
Ex.: 1000000 − 2, coluna 1.
2. Ill-formed expression or missing term detected: Em alguma parte da express ̃ao est ́a
faltando um operando ou existe algum operando em formato errado.
Ex.: 2+, coluna 3; ou 3 ∗ d, coluna 5.
3. Invalid operand: Existe um s ́ımbolo correspondente a um operador que n ̃ao est ́a na
lista de operadores v ́alidos.
Ex.: 2 = 3, coluna 3; ou 2.3 + 4, coluna 2.
4. Extraneous symbol: Aparentemente o programa encontrou um s ́ımbolo extra “perdido”
na express ̃ao.
Ex.: 2 ∗ 3 4, coluna 7 ou (−3 ∗ 4)(10 ∗ 5), coluna 7.
5. Mismatch ’)’: Existem um parˆentese fechando sem ter um parˆentese abrindo corres-
pondente.
Ex.: )2 − 4, coluna 1; ou 2 − 4), coluna 6; ou 2) − 4. coluna 2.
6. Lost operator: Apareceu um operador sem seus operandos.
2 ∗∗ 3, coluna 4; ou /5 ∗ 10, coluna 1.
7. Missing closing ‘)’ to match opening ‘)’ at: Est ́a faltando um parˆentese de fecha-
mento ’)’ para um parˆentese de abertura ‘(’ correspondente.
Ex.: ((2%3) ∗ 8, coluna 1.
*/

bool parsing( std::string unparsed ){

    // Se número, testa por tamanho
    // Deve haver um operando após um operador
    // Deve haver um operador válido entre operandos
    // Após operando, deve haver um operador
    // Devem haver um número igual de parênteses (Fechado extra)
    // Não podem haver dois operadores seguidos
    // Devem haver um número igual de parênteses (Fechado falta)

    // Parênteses podem ser lindamente parsados com stacks.

}