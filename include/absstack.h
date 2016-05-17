/**
 * \file absstack.h
 * \brief Classe interface da pilha (não pode ser instanciada).
 */

template <class Object>
class AbsStack{
public:
	AbsStack() { /* Empty */ } 
	virtual ~AbsStack() { /* Empty */ }

	
	virtual void push( const Object & x ) = 0;
	virtual Object pop() = 0;
	virtual Object top() const = 0;

	virtual bool isEmpty() const = 0;
	virtual void makeEmpty() = 0;

private:
	
	/* 
	 * \brief Desabilita o construtor cópia.
	 */
	AbsStack( const AbsStack & ) { /* Empty */ }
};
