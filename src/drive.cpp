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
        std::cout << printingTerm.getValue() << " ";
    }
    std::cout << "]\n";


    return 0;
}

/*
[[[ Erros que precisam ser tratados ]]]
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

/*
[Testes do Parsing]
i1 = 4 -> 19, oldColumn = 5
i2 = 5 -> 12, oldColumn = 11
i3 = 5
column = 20
3 + ( 4 - (5 * 7) )
( ( (ads + 3) ( 4 ) ) ) )
3 + ()
*/

// Chamar na Tokenização como int error = parsing( currentLine, column ); //column = 1.

// Caso o último termo seja um parêntese válido, column ficará além dos bounds da string
// Porém não será um problema mas já será uma expressão válida.

// Existe possibilidade de inserir os elementos na fila já no processo de
// Parsing. Para isso, seria necessário passar a fila por referência e ter
// sorte na hora da implementação.

// Pode ser abusado com 3 + (), tem que ajeitar.

// Como a lógica de Operandos ainda não foi aplicada corretamente, expressões como
// (3 + 4)(5 * 5) ainda são corretas (na verdade tudo é), então lembrar de modificar
// os booleanos na volta da recursão.
int parsing( const std::string & bunparsed, int & column ){

    // Necessário para as lógicas de teste
    bool operatorAllowed = false;
    bool numberAllowed = true;
    bool unaryAllowed = true;
    //bool isEmpty = true;

    // Necessário para a lógica de parêntese
    bool needsClosingBraces = !( column == 1 )

    // i representa a coluna da substring atual
    for ( int i = 0; i < bunparsed.size(); i++, column++ )
    {
        // Pula espaços e tabs (existe mais algum outro whitespace?)
        if ( bunparsed[i] == ' ' or bunparsed[i] == '  ' ) continue;

        // Passo recursivo dos parênteses.
        if ( bunparsed[i] == '(' ){
            int oldColumn = column;
            int error = parsing( bunparsed.substr( i + 1 ), ++column );
            if ( error ) return error;

            i += column - oldColumn;
        } else if ( bunparsed[i] == ')' and needsClosingBraces ){
            return 0;
        } else {
            // Todo resto deve vir aqui.
            // Isto é, procurar pelos erros comuns.
        }
    }

    //[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ Lógica abaixo ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
    // Ordem das operações:
    // Primeiro passe para tratamento de parêntese
    // Segundo passo para procura de erros com recursão e lógica de Operando,
    // Operador e @.

    // Se número, testa por tamanho
    // Deve haver um operando após um operador
    // Deve haver um operador válido entre operandos
    // Após operando, deve haver um operador
    // Devem haver um número igual de parênteses (Fechado extra)
    // Não podem haver dois operadores seguidos
    // Devem haver um número igual de parênteses (Fechado falta)

    // Parênteses podem ser lindamente parsados com stacks.

    // Aprendizados:
       // Número -> Símbolo || ')'
       // Símbolo -> Número || '(' || @
       // @ -> @ || Número || '('
       //
       // Onde:
           // @ : Número -> Número
           // @- = λx. -x
           // @+ = λx. x

       // () : Subset de Número
           // ( Se válido como número, está ok )


    // Uma atenção:
       // Quando chamar recursivamente, jogar ++column.
       // Quando receber corretamente, fazer ++column (já recebida)
       // Isso, para compensar pelos '(' e ')' pulados.

    //[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[ Lógica acima ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


    return 0; // Para sucesso bem-sucedido.
}

/*
[WARNING] TEST AREA [WARNING]

3 + (-4 * ( 3 + d ) ) Não mais merda

3 + ((2 - 3)
3 + (2 - 3))

-2 -----3 + -(4+5)
2 u 3 u u u u - 4 5 + u +

--3 * (5 - 6)
3 u u 5 6 - *

(4 + 5) * ---7
4 5 + 7 u u u *

3 * 2 * - 3
3 2 * 3 u *

*/
