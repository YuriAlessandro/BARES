/**
 * \file stackar.h
 * \brief Implementação de uma TAD pilha.
 */

#ifndef _STACKAR_H_
#define _STACKAR_H_

#include <stdexcept>
#include "absstack.h"

template <typename Object>
class StackAr : public AbsStack<Object>
{
	private:
	Object *m_stack;
	int m_top;
	int m_capacity;

	void resize( const int & );

	public:
	
	StackAr( int _size = 10 ){
		// A capacidade fica como 1 caso o usuário insira um número menor que 0
        m_capacity = ( _size > 0 ) ? _size : 1;

		m_stack = new Object[ m_capacity ];
		m_top = 0;
	}

	~StackAr(){
		delete[] m_stack;
	}

	/**
	 * \brief Insere um elemento no topo da pilha
	 * \param _new elemento a ser inserido
	 */
	void push( const Object & );
	
	/**
	 * \brief Remove e retorna o elemento que está no topo da pilha.
	 * \return Elemento no topo da pilha.
	 */
	Object pop();
	
	/**
	 * \brief Retorna o elemento que está no topo da pilha.
	 * \return Elemento no topo da pilha.
	 */
	Object top() const;

	/**
	 * \brief Informa se a pilha está vazia.
	 * \return True se vazia, False se não.
	 */
	bool isEmpty() const;
	
	/**
	 * \brief Limpa os elementos da pilha.
	 */
	void makeEmpty();

};

#include "stackar.inl"

#endif
