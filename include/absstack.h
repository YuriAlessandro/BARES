/**Classe interface pilha (não pode ser instanciada!). */
template <class Object>
class AbsStack{
public:
	AbsStack() { /* Empty */ } // Default constructor
	virtual ~AbsStack() { /* Empty */ } // Default destructor

	// Basic members
	virtual void push( const Object & x ) = 0;
	virtual Object pop() = 0;
	virtual Object top() const = 0;

	virtual bool isEmpty() const = 0;
	virtual void makeEmpty() = 0;

private:
	// Disable copy constructor
	AbsStack( const AbsStack & ) { /* Empty */ }
};
