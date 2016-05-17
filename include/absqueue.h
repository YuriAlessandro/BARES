/**
 * \file absqueue.h
 * \brief Classe interface da fila (não pode ser instanciada).
 */
 
template <class Object>
class AbsQueue{
public:
    AbsQueue() { /* Empty */ } // Default constructor
    virtual ~AbsQueue() { /* Empty */ } // Default destructor

    // Basic members
    virtual void enqueue( const Object & x ) = 0;
    virtual bool dequeue( Object & _value ) = 0;
    virtual Object getFront() const = 0;

    virtual bool isEmpty() const = 0;
    virtual void makeEmpty() = 0;

private:
    /**
     * \brief Desabilita o construtor cópia
     */
    AbsQueue ( const AbsQueue & ) { /* Empty */ }
};
