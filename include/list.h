#ifndef _LIST_H
#define _LIST_H

#include <iostream> //< std::cout
#include <initializer_list> //< std::initializer_list;

using size_type = unsigned long;
namespace sc
{
	/**
	 * @brief      Lista Abstract Data Type (ADT) baseada em uma lista duplamente encadeada.
	 *
	 * @tparam     T     Representa o tipo do template.
	 */
	template < typename T>
	class list
	{
	private:
		
		/**
		 * @brief      Representação do nó de uma lista.
		 */
		struct Node
		{
			T data;
			Node * prev;
			Node * next;

			/**
			 * @brief      Construtor padrão.
			 *
			 * @param[in]  d     Os dados.
			 * @param      p     O nó anterior.
			 * @param      n     O nó seguinte.
			 */
			Node( const T & d = T(), Node* p = nullptr, Node* n =nullptr ) : data( d ), prev( p ), next( n )
			{
				/* Empty */
			}
		};
	public:
		
		/**
		 * @brief      Iterador constante para a list.
		 */
		class const_iterator
		{
		public:
			
			/**
			 * @brief      Construtor padrão.
			 */
			const_iterator( void ) { /* Empty */ }

			/**
			 * @brief      Operador de desreferenciação.
			 *
			 * @return     O objeto.
			 */
			const T & operator*() const { return this->current->data; }

			/**
			 * @brief      Operador de pré-incremento.
			 *
			 * @return     Um iterarador constante para nó Seguinte.
			 */
			const_iterator & operator++( void )
			{
				this->current = this->current->next;
				return *this;
			}

			/**
			 * @brief      Operador de pós-incremento.
			 *
			 * @return     Um iterarador constante para nó atual.
			 */
			const_iterator operator++( int )
			{
				const_iterator temp( this->current );
				this->operator++();
				return temp;
			}

			/**
			 * @brief      Operador de pré-decremento.
			 *
			 * @return     Um iterarador constante para o nó anterior.
			 */
			const_iterator & operator--( void )
			{
				this->current = this->current->prev;
				return *this;
			}

			/**
			 * @brief      Operador de pós-decremento.
			 *
			 * @return     Um iterarador constante para o nó atual.
			 */
			const_iterator operator--( int )
			{
				const_iterator temp( this->current );
				this->operator--();
				return temp;
			}

			/**
			 * @brief      Operador de igualdade
			 *
			 * @param[in]  rhs   O iterador do lado direito
			 *
			 * @return     true se ambos o iteradores se referem à mesma localização dentro da list.
			 */
			bool operator==( const const_iterator & rhs ) const { return this->current == rhs.current; }
			
			/**
			 * @brief      Operador de desiguldade
			 *
			 * @param[in]  rhs   O iterador do lado direito
			 *
			 * @return     true se ambos o iteradores não se referem à mesma localização dentro da list.
			 */
			bool operator!=( const const_iterator & rhs ) const { return this->current != rhs.current; }
			
			//==DEBUG
			
			/**
			 * @brief      Imprimite o objeto do iterador. <!Apenas para testes!>
			 */
			void print_iterator( )
			{
				std::cout << this->current->data << std::endl;
			}
		protected:
			const_iterator( Node * p ) : current( p ) {}
			Node * current;
			friend class list<T>;
		};

		/**
		 * @brief      Iterador para list.
		 */
		class iterator : public const_iterator
		{
		public:
			iterator( void ) : const_iterator() { /*Empty*/ } //< Preciso criar essas funções?
			
			/**
			 * @brief      Operador de desreferenciação.
			 *
			 * @return     O objeto.
			 */
			const T & operator*() const
			{
				return this->current->data;
			}

			/**
			 * @brief      Operador de desreferenciação.
			 *
			 * @return     O objeto.
			 */
			T & operator*()
			{
				return this->current->data;
			}
	
			/**
			 * @brief      Operador de pré-incremento.
			 *
			 * @return     Um iterarador constante para nó seguinte.
			 */
			iterator & operator++( void )
			{
				this->current = this->current->next;
				return *this;
			}

			/**
			 * @brief      Operador de pós-incremento.
			 *
			 * @return     Um iterarador constante para nó atual.
			 */
			iterator operator++( int )
			{
				iterator temp( this->current );
				this->operator++();
				return temp;
			}

			/**
			 * @brief      Operador de pré-decremento.
			 *
			 * @return     Um iterarador constante para nó anterior.
			 */
			iterator & operator--( void )
			{
				this->current = this->current->prev;
				return *this;
			}

			/**
			 * @brief      Operador de pós-decremento.
			 *
			 * @return     Um iterarador constante para nó atual.
			 */
			iterator operator--( int )
			{
				iterator temp( this->current );
				this->operator--();
				return temp;
			}
		
		protected:
			
			iterator( Node * p ) : const_iterator( p ) {}
			friend class list<T>;
			
		};
		//== SPECIAL MEMBERS
		
		/**
		 * @brief      Construtor padrão. Constrói uma lista vazia.
		 */
		list( void )
		{
			this->m_size = 0;
			this->m_head = new Node(); //< extra node
			this->m_tail = new Node(); //< extra node
			this->m_head->next = this->m_tail;
			this->m_tail->prev = this->m_head;
		}

		/**
		 * @brief      Constrói a lista com count-nós com valor padrão de T.
		 *
		 * @param[in]  count  A quantade de nós.
		 */
		explicit list( size_type count ) : list()
		{
			for( size_type i = 0; i < count; ++i )
			{
				this->push_front( T() );
			}

		} 

		/**
		 * @brief      Constrói a lista com o couteudo do intervalo [first, last].
		 *
		 * @param[in]  first    Primeiro elemento do intervalo.
		 * @param[in]  last     Ultimo elemento do intervalo.
		 *
		 * @tparam     InputIt  Input Iterator
		 */
		template< typename InputIt > 
		list( InputIt first, InputIt last ) : list()
		{
			InputIt tmp = first;
			while( tmp != last )
			{
				this->push_back( *tmp );
				++tmp;
			}
		}
		
		/**
		 * @brief      Construtor copia.
		 *
		 * @param[in]  other  Outra lista.
		 */
		list( const list& other ) : list()
		{
			Node * tmp = other.m_head->next; //< Aponta para o primeiro nó da outra lista.
			//Percorre a outra lista.
			for( size_type i = 0; i < other.m_size; ++i )
			{
				this->push_back( tmp->data );
				tmp = tmp->next; //< aponta para o proximo nó.
			}
		}

		/**
		 * @brief      Construtor para lista inicializadora.
		 *
		 * @param[in]  ilist  A lista inicializadora
		 */
		list( std::initializer_list<T> ilist ) : list()
		{
			for( auto value : ilist ) //< Percorre toda ilist.s
			{
				this->push_back( value );
			}
		}

		/**
		 * @brief      Destrutor
		 */
		~list( void ) { clear(); }

		/**
		 * @brief      Operador de copia por atribuição.
		 *
		 * @param[in]  other  A outra lista.
		 *
		 * @return     Referencia a lista.
		 */
		list& operator=( const list& other )
		{
			if(!empty()) clear(); //< Verifica se está vazio. Se não estiver, limpa.
			//Inicia a LIST
			this->m_size = 0;
			this->m_head = new Node(); //< extra node
			this->m_tail = new Node(); //< extra node
			this->m_head->next = this->m_tail;
			this->m_tail->prev = this->m_head;
			//Fim da inicialização

			Node * temp = other.m_head->next; //< Aponta para o primeiro nó da outra lista.
			//Percorre a outra lista.
			for( size_type i = 0; i <  other.m_size; ++i )
			{
				this->push_back( temp->data );
				temp = temp->next; //< Aponta para o proximo nó.
			}
			return *this;
		}

		/**
		 * @brief      Operador de copia por atribuição.
		 *
		 * @param[in]  ilist  A lista inicializadora.
		 *
		 * @return     Referencia a lista.
		 */
		list & operator=( std::initializer_list<T> ilist )
		{
			if(!empty()) clear(); //< Verifica se está vazio. Se não estiver, limpa.
			//Inicia a LIST
			this->m_size = 0;
			this->m_head = new Node(); //< extra node
			this->m_tail = new Node(); //< extra node
			this->m_head->next = this->m_tail;
			this->m_tail->prev = this->m_head;
			//Fim da inicializaçãos
			for( auto value : ilist ) //< Percorre toda a lista de inicialização.
			{
				this->push_back( value );
			}
			return *this;
		}

		//== Capacity
		
		/**
		 * @brief      Número de nós da lista.
		 *
		 * @return     Tamanho da lista.
		 */
		const size_type size( void ) const { return this->m_size; }
		
		/**
		 * @brief      Verifica se a lista está vazia.
		 *
		 * @return     True se estiver vazia, false caso contrário.
		 */
		bool empty( void ) { return (this->m_size == 0); }

		//== MODIFIERS
		
		/**
		 * @brief      Limpa a lista.
		 */
		void clear( void ) 
		{
			Node * current = this->m_head->next; //< Aponta para ao primeiro nó da lista
			for( size_type i = 1; i <= this->m_size; ++i )
			{
				this->m_head->next = current->next; //< Aponta para o proximo nó da sequencia
				current->next->prev = this->m_head; //< O prev do proximo nó aponta para m_head
				delete current; //< Deleta o nó
				current	= this->m_head->next; //< aponta para o novo primeiro nó da lista.	 
			}
			this->m_size = 0;
		}

		/**
		 * @brief      Insere um novo nó na "cabeça" da lista.
		 *
		 * @param[in]  value  O valor do objeto.
		 */
		void push_front( const T & value )
		{
			Node * new_node = new Node( value, /*prev*/ this->m_head, /*next*/ this->m_head->next );
			this->m_head->next->prev =  new_node; //< Aponta o prev do antigo primeiro nó para o new_node.
			this->m_head->next = new_node;
			++this->m_size;
		}

		/**
		 * @brief      Insere um novo nó na "cauda" da lista.
		 *
		 * @param[in]  value  O valor do objeto.
		 */
		void push_back( const T & value )
		{
			Node * new_node = new Node( value, /*prev*/ this->m_tail->prev, /*next*/ this->m_tail );
			this->m_tail->prev->next = new_node; //< Aponta o next do antigo ultimo nó para o new_node.
			this->m_tail->prev = new_node;
			++this->m_size;
		}

		/**
		 * @brief      Deleta o ultimo nó.
		 */
		void pop_back( void )
		{
			if( !empty() )
			{
				Node * current = this->m_tail->prev; //< Aponta para o ultimo nó.
				this->m_tail->prev = current->prev; //< Aponta para o "penultimo" nó.
				current->prev->next = this->m_tail; //< Faz o "penultimo" nó apontar para tail.
				delete current; //< Deleta o ultimo nó.
				--this->m_size;
			}
		}

		/**
		 * @brief      Deleta o primeiro nó.
		 */
		void pop_front( void )
		{
			if( !empty() )
			{
				Node * current = this->m_head->next; //< Aponta para o primeiro nó.
				this->m_head->next = current->next; //< Aponta para o "segundo" nó.
				current->next->prev = this->m_head; //< Faz o "segundo" nó apontar head..
				delete current; //< Deleta o primeiro nó.
				--this->m_size;
			}
		}

		/**
		 * @brief      Retorna o objeto do ultimo nó.
		 *
		 * @return     O objeto.
		 */
		const T & back() const { return this->m_tail->prev->data ; }

		/**
		 * @brief      Retorna o objeto do primeiro nó.
		 *
		 * @return     O objeto.
		 */
		const T & front() const { return this->m_head->next->data ; }

		/**
		 * @brief      Substitui todo o conteudo da lista por copiar de um valor.
		 *
		 * @param[in]  value  O valor
		 */
		void assign( const T & value )
		{
			if( !empty() )
			{
				Node * temp = this->m_head->next;
				for( size_type i = 1; i <= this->m_size; ++i )
				{
					temp->data = value;
					temp = temp->next;
				}
			}
		}
		
		

		//== ITERATORS

		/**
		 * @brief      Retorna um iterador constante apontando para o primeiro item da lista.
		 *
		 * @return     O iterador constante.
		 */
		const_iterator cbegin() const { return const_iterator( this->m_head->next ); }
		
		/**
		 * @brief      Retorna um iterador constante apontando para cauda da lista.
		 *
		 * @return     O iterador constante.
		 */
		const_iterator cend() const { return const_iterator( this->m_tail ); }
		
		/**
		 * @brief      Retorna um iterador apontando para o primeiro item da lista.
		 *
		 * @return     O iterador.
		 */
		iterator begin() { return iterator( this->m_head->next ); }
		
		/**
		 * @brief      Retorna um iterador  apontando para cauda da lista.
		 *
		 * @return     O iterador.
		 */
		iterator end() { return iterator( this->m_tail ); }
		
		//== MODIFIERS WITH ITERATORS AND CONST ITERATORS

		/**
		 * @brief      Adiciona o valor antes da posição informada.
		 *
		 * @param[in]  pos    A posição.
		 * @param[in]  value  O valor.
		 *
		 * @return     Um iterador apontando para o valor inserido.
		 */
		iterator insert( const_iterator pos, const T & value )
		{
			if( !empty() )
			{
				Node * tmp = pos.current;
				Node * new_node = new Node( value, /*prev*/ tmp->prev, /*next*/ tmp );
				tmp->prev->next = new_node; //Aponta o next do nó anterior pra new_node
				tmp->prev =  new_node; //Aponta o prev do pos para o new_node
				++this->m_size;
				return iterator( new_node );
			}

			//Se estiver vazio
			this->push_back( value );
			return iterator( this->m_head->next );
		}

		/**
		 * @brief      Adiciona o conteudo do intervalo [first, last] antes da posição informada.
		 *
		 * @param[in]  pos    A posição
		 * @param[in]  first  O primeiro elemento do intervalo.
		 * @param[in]  last   O ultimo elemento do intervalo.
		 *
		 * @tparam     InItr  Input Iterator 
		 *
		 * @return     Retorna um interator referenciando o primeiro elemento inserido.
		 */
		template < typename InItr >
		iterator insert( const_iterator pos, InItr first, InItr last )
		{
			InItr currIt = first; //< Iterador atual
			iterator it; //< Iterador para o primeiro item inserido do rage na list
			while( currIt != last )
			{
				//Armazena o iterador para o primeiro item inserido.
				if( currIt == first ) it = insert( pos, *currIt );
				else insert( pos, *currIt );
				++currIt;
			}

			return it; //< Retornar o iterador para o primeiro elemento inserido do rage.
		}

		/**
		 * @brief       Adiciona o conteudo da lista inicializadora antes da posição informada.
		 *
		 * @param[in]  pos    A posição.
		 * @param[in]  ilist  lista inicializadora.
		 *
		 * @return     Retorna um interator referenciando o primeiro elemento inserido.
		 */
		iterator insert( const_iterator pos, std::initializer_list<T> ilist )
		{
			iterator it; //< Aponta para o primeiro item inserido do ilist na list
			size_type aux = 0;
			for( auto i : ilist )
			{
				if( aux == 0 ) //< Verifica se é o primeiro elemento
				{
					it = insert( pos, i );
					++aux;	
				}
				else insert( pos, i );
			}

			return it;
		}

		/**
		 * @brief      Remove o elemento na posição informada.
		 *
		 * @param[in]  pos   A posição
		 *
		 * @return     Um iterador referenciando o nó seguinte à posição.
		 */
		iterator erase( const_iterator pos )
		{
			Node * pc = pos.current; //< Aponta para o nó que vai ser deletado.
			iterator it( pc->next ); //< Iterador para o proximo nó.
			/* 
			 * Verifica se a lista esta fazia e se o node que deseja 
			 * delatar não é o head ou tail.
			 */
			if( !empty() and pc != this->m_tail and pc != this->m_head )
			{
				// O next do nó anterior aponta para o proximo nó da pos.
				pc->prev->next = pc->next;
				// O prev do proximo nó aponta para nó anterior da pos.
				pc->next->prev = pc->prev;
				delete pc; //< Deleta o nó
				//pos.current = nullptr; //< 
				--this->m_size;
			}
			// Retorna um iterador ao nó seguinte de pos.
			return it;
		}
		
		/**
		 * @brief      Remove os elementos do intervalo[first, last].
		 *
		 * @param[in]  first  O primeiro elemento.
		 * @param[in]  last   O ultimo elemento.
		 *
		 * @return     Um iterador para o nó seguinte ao ultimo removido.
		 */
		iterator erase( const_iterator first, const_iterator last )
		{
			const_iterator it = first;
			while( it != last )
			{
				this->erase(it);
				++it;
			}
			// Retorna um iterador para o elemento seguinte a last. 
			return iterator(it.current);
		}

		/**
		 * @brief      Substitui o conteudo da lista por n-copias do valor.
		 *
		 * @param[in]  count  As n-copias.
		 * @param[in]  value  O valor.
		 */
		void assign( size_type count, const T& value )
		{
			this->erase( this->begin(), this->end() ); //< Limpa a lista
			for( size_type i = 0; i < count; ++i)
			{
				this->push_back( value );
			}
		}

		/**
		 * @brief      Substitui o conteudo da lista pela copia do intervalo [first, last]
		 *
		 * @param[in]  first  O primeiro elemento.
		 * @param[in]  last   O ultimo elemento.
		 *
		 * @tparam     InItr  Input Iterator.
		 */
		template < typename InItr >
		void assign( InItr first, InItr last )
		{
			this->erase( this->begin(), this->end() ); //< Limpa a lista
			InItr temp = first;
			while( temp != last )
			{
				push_back( *temp );
				++temp;
			}
		}

		/**
		 * @brief      Substitui o conteudo da lista pela copia da lista inicializadora.
		 *
		 * @param[in]  ilist  A ista inicializadora
		 */
		void assign( std::initializer_list<T> ilist )
		{
			this->erase( this->begin(), this->end() ); //< Limpa a lista
			for( auto i: ilist )
			{
				this->push_back( i );
			}
		}
		

		//== DEBUG

		/**
		  * @brief      Imprimite os valores dentro de cada nó da lista e o tamanho da lista. <!Apenas para testes!>
		  */
		void print_list()
		{
			std::cout << "[ ";
			Node * temp = this->m_head->next;
			for( size_type i = 1; i <= this->m_size; ++i )
			{
				std::cout << temp->data << " ";
				temp = temp->next;
			}
			std::cout << "] - Size: " << this->m_size << std::endl;
		}
	private:
		size_type m_size;
		Node * m_head;
		Node * m_tail;	
	};	
};

//== OPERATOR OVERLOADING

template<typename T>
std::ostream& operator<<(std::ostream& os, const sc::list< T > & l)
{
	os << "[ ";
	auto it = l.cbegin();
	for( size_type i = 1; i <= l.size(); ++i )
	{
		os << *it << " ";
		++it;
	}
	os << "]";
	return os;
}

template<typename T>
bool operator==( const sc::list< T > & lhs, const sc::list< T > & rhs )
{
	if( lhs.size() == rhs.size() )
	{
		//Iterador para o primeiro elemento da list lhs
		auto currLHS = lhs.cbegin();
		//Iterador para o primeiro elemento da list rhs
		auto currRHS = rhs.cbegin();
		for ( size_type i = 1; i <= lhs.size(); ++i)
		{
			if( *currLHS != *currRHS ) return false;
			++currRHS;
			++currLHS;
		}
		return true;
	}
	return false;
}

template<typename T>
bool operator!=( const sc::list< T > &lhs,  const sc::list< T > & rhs )
{
	if( lhs.size() == rhs.size() )
	{
		//Iterador para o primeiro elemento da list lhs
		auto currLHS = lhs.cbegin();
		//Iterador para o primeiro elemento da list rhs
		auto currRHS = rhs.cbegin();
		for ( size_type i = 1; i <= lhs.size(); ++i)
		{
			if( *currLHS != *currRHS ) return true;
			++currRHS;
			++currLHS;
		}
		return false;
	}
	return true;
}

#endif