#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include "queuear.h"
#include "term.h"

// Em breve será completamente alterado.
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

            // Fazer função pra checar isso usando hacks de ASCII
	        }else if ( temp == '+' or temp == '-' or temp == '*' or temp == '/' or temp == '%' or temp == '(' or temp == ')'){
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
2. Ill-formed expression or missing term detected: Em alguma parte da expressão está
faltando um operando ou existe algum operando em formato errado.
Ex.: 2+, coluna 3; ou 3 ∗ d, coluna 5.
3. Invalid operand: Existe um sımbolo correspondente a um operador que nao está na
lista de operadores válidos.
Ex.: 2 = 3, coluna 3; ou 2.3 + 4, coluna 2.
4. Extraneous symbol: Aparentemente o programa encontrou um símbolo extra “perdido”
na expressão.
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
[Testes de cabeça do Parsing]
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

// Trocar "expects" para "previouslyWasNumber"
int parsing( const std::string & bunparsed, int & column ){

    // Number substring
    std::string number = "";

    // Necessário para as lógicas de teste
    bool previouslyWasNumber = false;
    int negUnaries = 0;
    int posUnaries = 0;
    //bool isEmpty = true;

    // Necessário para a lógica de parêntese
    bool needsClosingBraces = !( column == 1 );

    // i representa a coluna da substring atual
    for ( int i = 0; i < bunparsed.size(); i++, column++ ) {
        // Pula espaços e tabs (whitespace)
        if ( bunparsed[i] == ' ' or bunparsed[i] == '  ' ) continue;

        // TODO INTERNO:
        // Implementar já a inserção numa fila de saída porque tá muito na cara

        // Tratamento dos erros
        // Precisa de ')' e não tem ')'
        if ( needsClosingBraces and i+1 = bunparsed.size() and ( bunparsed[i] != ')' ) ) // 7. Missing closing ‘)’ to match opening ‘)’ at
        {
            // Precisa de tratamento de erro num grau de recursão acima para as
            // colunas. Por isso o 70.
            return 70;
        }

        // Tenho operador e vem um operador binário conhecido
        else if ( !previouslyWasNumber and validOperator( bunparsed[i] ) and !isUnary( bunparsed[i] ) ) // 6. Lost operator
        {
            return 6;
        }

        // Não precisa de ')' e vem ')'
        else if ( !needsClosingBraces and bunparsed[i] == ')' ) // 5. Mismatch ’)’
        {
            return 5;
        }

        // Tenho número e vem número
        else if ( previouslyWasNumber and isOperand( bunparsed[i] ) ) // 4. Extraneous symbol
        {
            return 4;
        }

        // Tenho número e vem algo estranho
        else if ( previouslyWasNumber and !validOperator( bunparsed[i] ) ) // 3. Invalid operand
        {
            return 3;
        }

        // Os último caso pode se preocupar com menos caso, pois já foram tratados acima
        // Não precisa de !validOperator pois já foi tratado em Lost Operator
        // Tenho operador e vem algo estranho
        else if ( !previouslyWasNumber and !isOperand( bunparsed[i] ) and !isUnary( bunparsed[i] ) ) // 2. Ill-formed expression
        {
            return 2;
        }

        // Tenho operador e acaba a recursão sem número
        else if ( !previouslyWasNumber and !isOperand( bunparsed[i] ) and bunparsed[i] == ')' ) // 2. Missing term detected
        {
            return 2;
        }

        // Passo recursivo dos parênteses.
        else if ( bunparsed[i] == '(' ){
            int oldColumn = column;
            int error = parsing( bunparsed.substr( i + 1 ), ++column );
            if ( error == 70 ){
                column = oldColumn;
                return 7;
            }

            if ( error ) return error;

            i += column - oldColumn;
            previouslyWasNumber = true;

            continue;

        // Não precisa de needsClosingBraces pois o erro foi tratada acima.
        } else if ( bunparsed[i] == ')' ){
            return 0;
        }

        // Continua se normal
        else {

            if ( isdigit( bunparsed[i] ) ) // Número
            {
                number += bunparsed[i];
                while ( isdigit( bunparsed[ i+1 ] ) ){
                    i++; column++;
                    number += bunparsed[i];
                }

                // Erros de compilação provavelmente serão jogados abaixo.
                if ( isOutOfBounds( pow( -1, negUnaries ) * stoi( number ) ) ) // 1. Numeric constant out of range
                {
                    column += 1 - number.size() - negUnaries - posUnaries;
                    return 1;
                }

                negUnaries = 0;
                posUnaries = 0;
                previouslyWasNumber = true;
            }
            else // Operadores
            {
                if ( !previouslyWasNumber ) // Unários
                {
                    if ( bunparsed[i] == '-' )
                        negUnaries++;
                    // A comparação abaixo é teoricamente desnecessário pois se
                    // não há a possibilidade de erros, a única outra escolha
                    // seria o unário '+'
                    else /* if ( bunparsed[i] == '+' ) */
                        posUnaries++;
                }
                else // Binários
                {
                    previouslyWasNumber = false;
                }
            }

            std::cout << ">>> We're at column " << column << ", no errors found yet.\n";

        }
    }

    // Tenho operador e acaba a linha
    if ( !previouslyWasNumber )
        return 2;

    return 0; // Para sucesso bem-sucedido.
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

}

bool validOperator( const char & op ){
    return ( op == '+' ) or ( op == '-' ) or ( op == '*' ) or
           ( op == '/' ) or ( op == '^' ) or ( op == '%' );
}

bool isUnary( const char & op ){
    return ( op == '+' ) or ( op == '-' );
}

bool isOperand( const char & op ){
    return isdigit( op ) or ( op == '(' );
}

bool isOutOfBounds( const int & num ){
    return ( num < -32768 ) or ( num > 32767 );
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
