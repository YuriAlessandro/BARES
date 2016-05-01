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

	void push( const Object & );
	Object pop();
	Object top() const;

	bool isEmpty() const;
	void makeEmpty();


};

#include "stackar.inl"

#endif
