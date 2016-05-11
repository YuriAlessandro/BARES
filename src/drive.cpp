#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include <cmath>
#include "queuear.h"
#include "term.h"
#include "stackar.h"

#define FILENAME "test"

bool validOperator( const char & op );
bool isUnary( const char & op );
bool isOperand( const char & op );
bool isOutOfBounds( const int & num );
int parseAndTokenize( QueueAr<Term> & termQueue, const std::string & bunparsed, int & column );
void to_posfix( QueueAr<Term> & operation, QueueAr<Term> & posfix );

int main(int argc, char* argv[])
{
    std::string fileName;
    QueueAr<Term> terms;
    QueueAr<Term> posfixTest;

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
        errorId = parseAndTokenize( terms, currentLine, column );

        if ( errorId ){
            std::cout << "E" << errorId << " " << column << "\n";
        } else {

            // Toda a parte da calculadora virá aqui.

            to_posfix( terms, posfixTest );

            // Teste
            std::cout << "[ ";
            while ( !posfixTest.isEmpty() ){
                Term printingTerm;
                posfixTest.dequeue( printingTerm );
                std::cout << printingTerm.getValue() << " ";
            }
            std::cout << "]\n";

        }

        posfixTest.makeEmpty();
        terms.makeEmpty();

	}

	file.close();
/*

*/

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


// Caso o último termo seja um parêntese válido, column ficará além dos bounds da string
// Porém não será um problema mas já será uma expressão válida.

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

// Trocar "expects" para "previouslyWasNumber"
int parseAndTokenize( QueueAr<Term> & termQueue, const std::string & bunparsed, int & column ){

    // Number substring
    std::string number = "";

    // Necessário para as lógicas de teste
    bool previouslyWasNumber = false;
    int negUnaries = 0;
    int posUnaries = 0;

    // Necessário para a lógica de parêntese
    bool needsClosingBraces = !( column == 1 );

    // i representa a coluna da substring atual
    for ( auto i = 0u; i < bunparsed.size(); i++, column++ ) {
        // Pula espaços e tabs (whitespace)
        if ( bunparsed[i] == ' ' or bunparsed[i] == '\t' ) continue;

        /////// Tratamento dos erros ///////
        // Precisa de ')' e não tem ')'
        if ( needsClosingBraces and ( i+1 == bunparsed.size() ) and ( bunparsed[i] != ')' ) ) // 7. Missing closing ‘)’ to match opening ‘)’ at
        {
            // Precisa de tratamento de erro num grau de recursão acima para as
            // colunas, por isso o 70.
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
        else if ( previouslyWasNumber and !validOperator( bunparsed[i] ) and ( bunparsed[i] != ')' ) ) // 3. Invalid operand
        {
            return 3;
        }

        // Não precisa de !validOperator pois já foi tratado em Lost Operator
        // Tenho operador e vem algo estranho
        else if ( !previouslyWasNumber and !isOperand( bunparsed[i] )
        and !isUnary( bunparsed[i] ) and ( bunparsed[i] != ')' ) ) // 2. Ill-formed expression
        {
            return 2;
        }

        // Tenho operador e acaba a recursão sem número
        else if ( !previouslyWasNumber and !isOperand( bunparsed[i] ) and bunparsed[i] == ')' ) // 2. Missing term detected
        {
            return 2;
        }

        /////// Passo recursivo dos parênteses ///////
        else if ( bunparsed[i] == '(' ){
            termQueue.enqueue( Term( std::string( 1, '(' ), false, false ) );

            int oldColumn = column;
            int error = parseAndTokenize( termQueue, bunparsed.substr( i + 1 ), ++column );
            if ( error == 70 ){
                column = oldColumn;
                return 7;
            }

            if ( error ) return error;

            i += column - oldColumn;
            previouslyWasNumber = true;

            continue;

        // Não precisa de needsClosingBraces pois o erro foi tratado acima.
        } else if ( bunparsed[i] == ')' ){
            termQueue.enqueue( Term( std::string( 1, ')' ), false, false ) );
            return 0;
        }

        /////// Continua se normal ///////
        else if ( isdigit( bunparsed[i] ) ) // Número
        {
            number += bunparsed[i];
            while ( isdigit( bunparsed[ i+1 ] ) ){
                i++; column++;
                number += bunparsed[i];
            }

            if ( isOutOfBounds( pow( -1, negUnaries ) * stoi( number ) ) ) // 1. Numeric constant out of range
            {
                column += 1 - number.size() - negUnaries - posUnaries;
                return 1;
            }

            termQueue.enqueue( Term( number, false, false ) );

            number = "";
            negUnaries = 0;
            posUnaries = 0;
            previouslyWasNumber = true;
        }
        else // Operadores
        {
            if ( !previouslyWasNumber ) // Unários
            {
                termQueue.enqueue( Term( std::string( 1, bunparsed[i] ), true, true ) );

                if ( bunparsed[i] == '-' )
                    negUnaries++;
                else /* if ( bunparsed[i] == '+' ) */
                    posUnaries++;
            }
            else // Binários
            {
                termQueue.enqueue( Term( std::string( 1, bunparsed[i] ), true, false ) );

                previouslyWasNumber = false;
            }
        }

//        std::cout << ">>> We're at column " << column << ", no errors found yet.\n";
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

// Me coçando pra passar string ao invés de term e não ter que chamar getValue()
// 10000 vezes. "Muh performance!"
int precedence( const Term & symbol ){
    if ( symbol.getValue() == "+" or symbol.getValue() == "-") return 0;
    else if ( symbol.getValue() == "*" or symbol.getValue() == "/" or symbol.getValue() == "%" ) return 1;
    else if ( symbol.getValue() == "^" ) return 2;
    else return -1;
}

// 3 + 4 * 5
// 3 4 5 * +

// 3 * ( 4 + 5 ) * 3

// 3 + 4 + 5 * 6
// 3 4 5 6 * + +

void to_posfix( QueueAr<Term> & operation, QueueAr<Term> & posfix ){

    StackAr<Term> operators;
    StackAr<Term> parentheses;

    Term temp;

    while ( operation.dequeue( temp ) ){

        // Se for um operador:
        if( temp.isOperator() ){

            // Caso seja o primeiro operador, ele é adicionado a pilha de operadores.
            if ( operators.isEmpty() and parentheses.isEmpty() )
                operators.push( temp );

            // Se não tiver parenteses abertos, tira os operadores de maior precedência que tão e adiciona esse novo.
            else if ( parentheses.isEmpty() ){

                // Você não pode ver o topo sem antes checar se está ou não vazio
                while ( !operators.isEmpty() and  precedence( temp ) < precedence ( operators.top() ) ){
                    posfix.enqueue( operators.pop( ) );
                }
                operators.push( temp );
            }

            // Adiciona a pilha de operadores se tiver parentêses abertos
            else operators.push( temp );
        }

        // Se forem paretêses:
        else if ( temp.getValue() == "(" ) parentheses.push( temp );
        else if ( temp.getValue() == ")" ) parentheses.pop();

        // Se for um número ou simbolo unário, adiciona direto ao posfixo:
        else posfix.enqueue( temp );


    }

    // Coloca os simbolos que sobraram de parenteses no final do posfixo.
    while ( ! operators.isEmpty() )
        posfix.enqueue( operators.pop() );

}
