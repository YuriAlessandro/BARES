/**
 * \file functions.h
 * \brief Declaração de funções gerais para o programa.
 */

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <string>
#include "queuear.h"
#include "token.h"
#include "stackar.h"

/**
 * \brief Checa se é um operador válido.
 * \param op Char que será analisado.
 * \return True se for um operador válido, False se não.
 */
bool validOperator( const char & op );

/**
 * \brief Checa se é um operador unário válido.
 * \param op Char que será analisado.
 * \return True se for um operador unário, False se não.
 */
bool isUnary( const char & op );

/**
 * \brief Checa se é um operando válido.
 * \param op Char que será analisado.
 * \return True se for um operando, False se não.
 */
bool isOperand( const char & op );

/**
 * \brief Checa se o valor inserido está dentro dos limites do programa.
 * \param num Int que será analisado.
 * \return True se está fora da faixa, False se não.
 */
bool isOutOfBounds( const int & num );

/**
 * \brief Realiza o tratamento de erros e a tokenização das expressões.
 * \param tokenQueue Fila na qual serão colocados os tokens.
 * \param bunparsed String a ser tokenizada.
 * \param column Coluna de início.
 * \return O tipo de erro encontrado.
 *
 * Recebe por parâmetro a fila na qual serão colocados os tokens, a string que\n
 * será tokenizada, e a coluna de início. Retorna o tipo de erro encontrado.\n
 * (É recursiva para tratamento dos parênteses). */
int parseAndTokenize( QueueAr<Token> & tokenQueue, const std::string & bunparsed, int & column );

/**
 * \brief Determina a precedência de um operador.
 * \param symbol Operador a ser analizado.
 * \return Precedência do operador.
 */
int precedence( const std::string & symbol );

/**
 * \brief Converte uma expressão para o modo posfixo.
 * \param operation Lista com os tokens da expressão.
 * \param posfix Lista onde ficará armazenada a forma posfixa.
 */
void toPostfix( QueueAr<Token> & operation, QueueAr<Token> & posfix );

/**
 * \brief Analisa uma expressão para chamar a calculadora e computar os resultados.
 * \param posfix Lista com os tokens em formato posfixo.
 * \param errorId Tipo inteiro que determina os casos de erro.
 * \return Resultado da expressão.
 */
int analysis( QueueAr<Token> & posfix, int & errorId );

/**
 * \brief Calcula as operações individuais de uma expressão maior.
 * \param x Primeiro valor da expressão.
 * \param y Segundo valor da expressão.
 * \param op Operador da expressão.
 * \param errorId Int que determina alguns casos de erro.
 * \return Valor final da "sub-expressão".
 */
int calculator( const int & x, const int & y, const std::string & op, int & errorId );

#endif
