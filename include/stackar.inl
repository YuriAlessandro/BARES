template<typename Object>
void StackAr<Object>::resize( const int & _newSize ){

	Object *_newStack = new Object[ _newSize ];

	for ( auto i = 0; i < m_top; i++ ) {
		_newStack[ i ] = m_stack[ i ];
	}

	delete[] m_stack;

	m_stack =_newStack;

	m_capacity = _newSize;
}

template<typename Object>
void StackAr<Object>::push( const Object & _new )
{
	if ( m_top == m_capacity )
		this->resize( 2 * m_capacity );

	m_stack[ m_top++ ] = _new;
}

template<typename Object>
Object StackAr<Object>::pop()
{
	if ( isEmpty() )
		throw std::out_of_range ("[pop()]: Sem elementos no stack");

	return m_stack[ --m_top ];
}

template<typename Object>
Object StackAr<Object>::top() const{
	return m_stack[ m_top-1 ];
	std::cout << "Funcao ";

}

template<typename Object>
bool StackAr<Object>::isEmpty() const{
	return m_top == 0;
}

template<typename Object>
void StackAr<Object>::makeEmpty(){
	m_top = 0;
}
