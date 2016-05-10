#ifndef _QUEUEAR_H_
#define _QUEUEAR_H_

#include "AbsQueue.h"
#include <stdexcept>

template <typename Object>
class QueueAr : public AbsQueue<Object>
{
private:
    Object * m_queue;
    int m_capacity;
    int m_front;
    int m_back;

    //Apesar de ser um pouco mais complexa que o necessário,
    //pode ser usada até mesmo se a lista não estiver cheia.
    void resize( ){
    	Object *_newQueue = new Object[ 2 * m_capacity ];

        /////// Cópia profunda ///////
    	int i = 0;

        for ( int _tempFront = m_front;
            _tempFront != m_capacity && m_back + 1 != _tempFront;
            i++, _tempFront++ ){
            _newQueue[ i ] = m_queue[ _tempFront ];
        }

        // Para o caso da fila fazer um "loop" em si mesmo
        if ( m_back < m_front ){
            int j = 0;
            for ( /* Empty */; j <= m_back; j++ )
                _newQueue[ i + j ] = m_queue[ j ];

            i += j;
        }

        m_front = 0;
        m_back = i - 1;
        //// Fim da cópia profunda ////

    	delete[] m_queue;

    	m_queue = _newQueue;

    	m_capacity = 2 * m_capacity;
    }

public:

    QueueAr( int _size = 20 ){
        // A capacidade fica como 1 caso o usuário insira um número menor que 0
        m_capacity = ( _size > 0 ) ? _size : 1;

        m_queue = new Object [ m_capacity ];

        m_front = -1;
        m_back = -1;
    }

    virtual ~QueueAr(){
        delete [] m_queue;
    }

    //////// FUNÇÕES BÁSICAS ////////
    void enqueue( const Object & x ){
        if ( m_front == -1 )
            m_front = 0;

        if ( ( m_back != -1 ) and ( m_back + 1 ) % m_capacity == m_front )
            this->resize();

        m_back = ( m_back + 1 ) % m_capacity;
        m_queue[ m_back ] = x;
    }

    Object dequeue( ){

        if ( isEmpty() )
            throw std::out_of_range ("[dequeue()]: Sem elementos na fila");

        int _oldFront = m_front;

        // Caso especial
        if ( m_front == m_back ){
            m_front = -1;
            m_back = -1;
        }else{
            m_front = ( m_front + 1 ) % m_capacity;
        }
        return m_queue[ _oldFront ];
    }

    Object getFront( ) const{
        if ( isEmpty() )
            throw std::out_of_range ("[dequeue()]: Sem elementos na fila");

        return m_queue[ m_front ];
    }

    bool isEmpty( ) const{
        return ( m_front == -1 );
    }

    void makeEmpty( ){
        m_front = -1;
        m_back = -1;
    }
    
};

#endif
