/**
 * \file functions.h
 * \brief Declaração de funções gerais para o programa.
 */

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <iomanip>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include "queuear.h"
#include "token.h"
#include "stackar.h"

/* Checa se é um operador válido */
bool validOperator( const char & op );

/* Checa se é um operador unário válido */
bool isUnary( const char & op );

/* Checa se é um operando válido */
bool isOperand( const char & op );

/* Checa se o valor inserido está dentro dos limites do programa */
bool isOutOfBounds( const int & num );

/* Recebe por parâmetro a fila na qual serão colocados os tokens, a string que \n
 * será tokenizada, e a coluna de início. Retorna o tipo de erro encontrado. \n
 * (É recursiva para tratamento dos parênteses). */
int parseAndTokenize( QueueAr<Token> & tokenQueue, const std::string & bunparsed, int & column );

/* Determina a precedência de um operador */
int precedence( const std::string & symbol );

/* Esvazia operation e preenche posfix já na notação adequada */
void toPostfix( QueueAr<Token> & operation, QueueAr<Token> & posfix );

/* Analisa uma expressão para chamar a calculadora e computar os resultados */
int analysis( QueueAr<Token> & posfix, int & errorId );

/* Calcula as pequenas partes de uma expressão */
int calculator( int x, int y, std::string temp, int & errorId );

#endif