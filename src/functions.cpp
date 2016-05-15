/**
 * \file functions.cpp
 * \brief Funcionalidades gerais para o programa.
 */

#include "functions.h"

/*
[[[ Erros que precisam ser tratados ]]]
1. Numeric constant out of range: Um dos operandos da express ̃ao est ́a fora da faixa
permitida.
Ex.: 1000000 − 2, coluna 1.
2. Ill-formed expression or missing token detected: Em alguma parte da expressão está
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

// Caso o último tokeno seja um parêntese válido, column ficará além dos bounds da string
// Porém não será um problema mas já será uma expressão válida.

bool validOperator( const char & op ){
    return ( op == '+' ) or ( op == '-' ) or ( op == '*' ) or
    ( op == '/' ) or ( op == '^' ) or ( op == '%' );
}

bool isUnary( const char & op ){
    return /*( op == '+' ) or*/ ( op == '-' );
}

bool isOperand( const char & op ){
    return isdigit( op ) or ( op == '(' );
}

bool isOutOfBounds( const int & num ){
    return ( num < -32768 ) or ( num > 32767 );
}

int parseAndTokenize( QueueAr<Token> & tokenQueue, const std::string & bunparsed, int & column ){

    /* Number substring */
    std::string number = "";

    /* Necessário para as lógicas de teste */
    bool previouslyWasNumber = false;
    int negUnaries = 0;
    /*int posUnaries = 0;*/

    /* Necessário para a lógica de parêntese */
    bool needsClosingBraces = !( column == 1 );

    /* i representa a coluna da substring atual */
    for ( auto i = 0u; i < bunparsed.size(); i++, column++ ) {
        /* Pula espaços e tabs (whitespace) */
        if ( bunparsed[i] == ' ' or bunparsed[i] == '\t' ) continue;

        /////// Tratamento dos erros ///////
        /* Precisa de ')' e não tem ')' */
        if ( needsClosingBraces and ( i+1 == bunparsed.size() ) and ( bunparsed[i] != ')' ) ) // 7. Missing closing ‘)’ to match opening ‘)’ at
        {
            /* Precisa de tratamento de erro num grau de recursão acima para as\n
             * colunas, por isso o 70. */
            return 70;
        }

        /* Tenho operador e vem um operador binário conhecido */
        else if ( !previouslyWasNumber and validOperator( bunparsed[i] ) and !isUnary( bunparsed[i] ) ) // 6. Lost operator
        {
            return 6;
        }

        /* Não precisa de ')' e vem ')' */
        else if ( !needsClosingBraces and bunparsed[i] == ')' ) // 5. Mismatch ’)’
        {
            return 5;
        }

        /* Tenho número e vem número */
        else if ( previouslyWasNumber and isOperand( bunparsed[i] ) ) // 4. Extraneous symbol
        {
            return 4;
        }

        /* Tenho número e vem algo estranho */
        else if ( previouslyWasNumber and !validOperator( bunparsed[i] ) and ( bunparsed[i] != ')' ) ) // 3. Invalid operand
        {
            return 3;
        }

        // Não precisa de !validOperator pois já foi tratado em Lost Operator
        /* Tenho operador e vem algo estranho */
        else if ( !previouslyWasNumber and !isOperand( bunparsed[i] )
        and !isUnary( bunparsed[i] ) and ( bunparsed[i] != ')' ) ) // 2. Ill-formed expression
        {
            return 2;
        }

        /* Tenho operador e acaba a recursão sem número */
        else if ( !previouslyWasNumber and !isOperand( bunparsed[i] ) and bunparsed[i] == ')' ) // 2. Missing token detected
        {
            return 2;
        }

        /////// Passo recursivo dos parênteses ///////
        else if ( bunparsed[i] == '(' ){
            tokenQueue.enqueue( Token( "(", false, false ) );

            int oldColumn = column;
            int error = parseAndTokenize( tokenQueue, bunparsed.substr( i + 1 ), ++column );
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
            tokenQueue.enqueue( Token( ")", false, false ) );
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
                column += 1 - number.size() - negUnaries/* - posUnaries*/;
                return 1;
            }

            tokenQueue.enqueue( Token( number, false, false ) );

            number = "";
            negUnaries = 0;
            /*posUnaries = 0;*/
            previouslyWasNumber = true;
        }
        else // Operadores
        {
            if ( !previouslyWasNumber ) /* Unários */
            {
                /*if ( bunparsed[i] == '-' ){*/
                tokenQueue.enqueue( Token( "@m", true, true ) );
                negUnaries++;
                /* } else if ( bunparsed[i] == '+' ) {
                    tokenQueue.enqueue( Token( "@p", true, true ) );
                    posUnaries++;
                }
                */
            }
            else /* Binários */
            {
                tokenQueue.enqueue( Token( std::string( 1, bunparsed[i] ), true, false ) );
                previouslyWasNumber = false;
            }
        }
    }

    // Tenho operador e acaba a linha
    if ( !previouslyWasNumber )
        return 2;

    return 0; // Para sucesso bem-sucedido.
}

int precedence( const std::string & symbol ){
    if ( symbol == "@m" /*or symbol == "@p"*/ ) return 1;
    else if ( symbol == "^" ) return 2;
    else if ( symbol == "*" or symbol == "/" or symbol == "%" ) return 3;
    else if ( symbol == "+" or symbol == "-") return 4;
    else return 5;
}

void toPostfix( QueueAr<Token> & operation, QueueAr<Token> & posfix ){

    StackAr<Token> operators;

    Token temp;

    while ( operation.dequeue( temp ) ){

        /* Se for paranteses, adiciona diretamente a pilha de operadores */
        if ( temp.getValue() == "(" )
            operators.push( temp );

        else if ( temp.getValue() == ")" ){
            while ( !operators.isEmpty() and operators.top().getValue() != "(")
                posfix.enqueue( operators.pop( ) );

            operators.pop();
        }

        /* Se for um operador, verifica precedência e realiza os passos
         * necessários dentro da pilha de operadores */
        else if( temp.isOperator() ){

            while ( !operators.isEmpty() and
            precedence( temp.getValue() ) >= precedence ( operators.top().getValue() ) and
            !( temp.isUnary() and operators.top().isUnary() ) )
                posfix.enqueue( operators.pop( ) );

            operators.push( temp );

        }

        /* Se for um operando, adiciona diretamente a fila de tokens em modo posfixo */
        else
            posfix.enqueue( temp );

    }

    /* Coloca os simbolos que sobraram da pilha de operadores no final do posfixo. */
    while ( ! operators.isEmpty() )
        posfix.enqueue( operators.pop() );

}

int analysis( QueueAr<Token> & posfix, int & errorId ){
    StackAr<int> numbers;
    int a, b;
    int res;

    Token str;
    std::string temp;

    while( posfix.dequeue( str ) and !errorId ){
        res = 0;
        errorId = 0;

        temp = str.getValue();

        /* Se for número, converte para inteiro e adiciona na pilha de valores */
        if( isdigit( temp[0] ) )
            numbers.push ( std::stoi( temp ) );

        /* Se for símbolo únario, transforma o número do topo da pilha */
        else if( temp == "@m" ){
            a = numbers.pop( );
            a *= -1;
            numbers.push( a );
        }/*else if( temp == "@p" ){
            a = numbers.pop( );
            a *= 1;
            numbers.push( a );
        }*/

        /* Se for operador, retira dois números da pilha e calcula */
        else{
            b = numbers.pop( );
            a = numbers.pop( );
            res = calculator( a, b, temp, errorId );
            numbers.push( res );
        }
    }

    return numbers.pop( );
}

int calculator( const int & x, const int & y, const std::string & op, int & errorId ){
    int res;

    switch ( op[0] ){
        case '+':
            res = x + y;
        break;

        case '-':
            res = x - y;
        break;

        case '*':
            res = x * y;
        break;

        case '/':
            if ( y != 0 ) res = x / y;
            else errorId = 8;
        break;

        case '%':
            res = x % y;
        break;

        case '^':
            res = pow( x, y );
        break;
    }

    if ( isOutOfBounds( res ) )
        errorId = 9;

    return res;
}
