/**
 * \file functions.cpp
 * \brief Funcionalidades gerais para o programa.
 */

#include "functions.h"

/*
1. Numeric constant out of range:
2. Ill-formed expression or missing token detected:
3. Invalid operand:
4. Extraneous symbol:
5. Mismatch ’)’:
6. Lost operator
7. Missing closing ‘)’ to match opening ‘)’ at:
*/

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

    /* Number substring. */
    std::string number = "";

    /* Necessário para as lógicas de teste. */
    bool previouslyWasNumber = false;
    int negUnaries = 0;
    /*int posUnaries = 0;*/

    /* Necessário para a lógica de parêntese. */
    bool needsClosingBraces = !( column == 1 );

    /* i representa a coluna da substring atual. */
    for ( auto i = 0u; i < bunparsed.size(); i++, column++ ) {
        /* Pula espaços e tabs (whitespace). */
        if ( bunparsed[i] == ' ' or bunparsed[i] == '\t' ) continue;

        /////// Tratamento dos erros ///////
        /* Precisa de ')' e não tem ')'. */
        if ( needsClosingBraces and ( i+1 == bunparsed.size() ) and ( bunparsed[i] != ')' ) ) // 7. Missing closing ‘)’ to match opening ‘)’ at
        {
            /* Ill-Formed Expression tem prioridade no erro. */
            if ( !previouslyWasNumber )
                return 2;
                
            /* Precisa de tratamento de erro num grau de recursão acima para as
             * colunas, por isso o 70. */
            return 70;
        }

        /* Tenho operador e vem um operador binário conhecido. */
        else if ( !previouslyWasNumber and validOperator( bunparsed[i] ) and !isUnary( bunparsed[i] ) ) // 6. Lost operator
        {
            return 6;
        }

        /* Não precisa de ')' e vem ')'. */
        else if ( !needsClosingBraces and bunparsed[i] == ')' ) // 5. Mismatch ’)’
        {
            return 5;
        }

        /* Tenho número e vem número. */
        else if ( previouslyWasNumber and isOperand( bunparsed[i] ) ) // 4. Extraneous symbol
        {
            return 4;
        }

        /* Tenho número e vem algo estranho. */
        else if ( previouslyWasNumber and !validOperator( bunparsed[i] ) and ( bunparsed[i] != ')' ) ) // 3. Invalid operand
        {
            return 3;
        }

        // Não precisa de !validOperator pois já foi tratado em Lost Operator
        /* Tenho operador e vem algo estranho. */
        else if ( !previouslyWasNumber and !isOperand( bunparsed[i] )
        and !isUnary( bunparsed[i] ) and ( bunparsed[i] != ')' ) ) // 2. Ill-formed expression
        {
            return 2;
        }

        /* Tenho operador e acaba a recursão sem número. */
        else if ( !previouslyWasNumber and !isOperand( bunparsed[i] ) and bunparsed[i] == ')' ) // 2. Missing token detected
        {
            return 2;
        }

        /////// Passo recursivo dos parênteses ///////
        else if ( bunparsed[i] == '(' ){
            tokenQueue.enqueue( Token( "(", false, false ) );

            /* Inicia a recursão na substring dentro dos parênteses. */
            int oldColumn = column;
            int error = parseAndTokenize( tokenQueue, bunparsed.substr( i + 1 ), ++column );

            /* Checa por erros e continua a função. */
            if ( error == 70 ){
                column = oldColumn;
                return 7;
            }

            if ( error ) return error;

            i += column - oldColumn;
            previouslyWasNumber = true;

            continue;

        } else if ( bunparsed[i] == ')' ){
            /* Encerra as recursões de forma bem-sucedida. */
            tokenQueue.enqueue( Token( ")", false, false ) );
            return 0;
        }

        /////// Continua se normal ///////
        else if ( isdigit( bunparsed[i] ) ) // Número
        {
            
            /* Continua até receber o número completamente. */
            number += bunparsed[i];
            while ( isdigit( bunparsed[ i+1 ] ) ){
                i++; column++;
                number += bunparsed[i];
            }

            /* Verifica pelo erro de OutOfBounds no número encontrado.*/
            if ( isOutOfBounds( pow( -1, negUnaries ) * stoi( number ) ) ) // 1. Numeric constant out of range
            {
                column += 1 - number.size() - negUnaries/* - posUnaries*/;
                return 1;
            }

            /* Põe o número final na fila de Tokens. */
            tokenQueue.enqueue( Token( number, false, false ) );

            /* Esvazia number e muda váriaveis de lógica. */
            number = "";
            negUnaries = 0;
            /*posUnaries = 0;*/
            previouslyWasNumber = true;
        }
        else // Operadores
        {
            /* Insere na fila caso seja operador e muda variáveis de lógica. */
            
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

    /* Tenho operador e acaba a linha. */
    if ( !previouslyWasNumber )
        return 2;

    return 0; /* Finaliza sem erros. */
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
            if ( y != 0 ) res = x % y;
            else errorId = 8;
        break;

        case '^':
            res = pow( x, y );
        break;
    }

    if ( isOutOfBounds( res ) )
        errorId = 9;

    return res;
}
