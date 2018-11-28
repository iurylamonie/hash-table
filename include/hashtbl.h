#ifndef _HASHTBL_H_
#define _HASHTBL_H_

#include <iostream>
#include <functional> //< std::hash and std::equal_to
#include <forward_list> //< std::forward_list

//#include "list.h"
using size_type = unsigned int;

/**
 * @brief      Determina  se é um determinado valor é primo.
 *
 * @param[in]  value  O valor.
 *
 * @return     True se o valor for primo, False caso contrario.
 */
bool isPrimo( const size_type & value );

namespace ac
{
	template < typename KeyType, //< Tipo da chave.
			   typename DataType > //< Tipo da informação.
	class HashEntry
	{
	public:
		HashEntry( KeyType k_, DataType d_ ) : m_key( k_ ), m_data( d_ )
		{ /* Empty*/ }
		KeyType m_key;
		DataType m_data;
	};

	template < typename KeyType, //< Tipo da chave.
			   typename DataType, //< Tipo da informação.
			   typename KeyHash = std::hash< KeyType >,  //< function hash.
			   typename KeyEqual = std::equal_to< KeyType > > //< function de comparação de chaves.
	class HashTbl
	{
	public:
		using Entry = HashEntry< KeyType, DataType >;

		/**
		 * @brief      Contrói o vetor do hash com um tamanho determinando, que é o menor numero primo maior que o tamanho informado.
		 *
		 * @param[in]  tbl_size_  O tamanho informado.
		 */
		HashTbl( size_type tbl_size_ = DEFAULT_SIZE)
		{
			// Armazena o menor número primo maior que tbl_size.
			size_type primo; 
			// Procuro o menor número primo maior que tbl_size.
			for( size_type i = 1; ; ++i )
			{
				if( isPrimo( tbl_size_ + i ) ) //< Chama a função isPrimo pra verificar se é primo.
				{
					primo = tbl_size_ + i;
					break; //< Break ao encontrar o proximo primo seguinte a tbl_size.
				}
			}
			this->m_size = primo;
			this->m_count = 0;
			this->m_data_table = new std::forward_list< Entry >[primo];
		}
		//~HashTbl();
	
		/**
		 * @brief      Construtor copia.
		 *
		 * @param[in]  other  O hash que vai ser copiado.
		 */
		HashTbl( const HashTbl& other )
		{
			this->m_size = other.m_size;
			this->m_count = other.m_count;
			this->m_data_table = new std::forward_list< Entry >[this->m_size];

			for ( size_type i = 0; i < this->m_size; ++i )
			{
				this->m_data_table[i] = other.m_data_table[i];
			}
		}

		/**
		 * @brief      Verifica se o hash está vazio.
		 *
		 * @return     True se estiver vazio, false caso contrário.
		 */
		bool empty( void ){ return (this->m_count == 0); }

		/**
		 * @brief      Retorna a quantidade de elementos atualmente armazenados na tabela.
		 *
		 * @return     A quantidade de elementos.
		 */
		size_type size( void ) { return this->m_count; }

		/**
		 * @brief      Retorna o atual tamanho da tabela de dispersão.
		 *
		 * @return     O tamanho da tabela.
		 */
		size_type tam( void ) { return this->m_size; }
		
		/**
		 * @brief      Retorna a quantidade de elementos da tabela que estão na lista de colisão associada a chave passada,
		 *
		 * @param[in]  k_    A chave passada.
		 *
		 * @return     A quantidade de elementos.
		 */
		size_type count( const KeyType k_ ) const
		{
			KeyHash hashFunc;
			auto end( hashFunc( k_ ) % this->m_size );
			size_type count  = 0;
			for ( auto it = this->m_data_table[end].begin(); it != this->m_data_table[end].end(); ++it) 
			{ 
				++count; 
			}
			return count;
		}
		
		/**
		 * @brief      Insere na tabela a informação passada e associada a uma chave informada .
		 *
		 * @param[in]  k_    A chave informada.
		 * @param[in]  d_    A informação passada.
		 *
		 * @return     True se a chave já existir na tabela, false caso contrário.
		 */
		bool insert( const KeyType & k_, const DataType & d_ )
		{
			KeyHash hashFunc;
			KeyEqual equalFunc;
			// Armazena o endereço da tabela produzida pela dispersão.
			auto end( hashFunc( k_ ) % this->m_size ); 
			Entry new_entry( k_, d_ ); //< Cria um novo "item" baseada nos argumentos passados.
			if( !this->m_data_table[end].empty() )
			{
				// Percorre toda a lista localizada no endereço especifico da tabela..
				for ( auto it = this->m_data_table[end].begin(); it != this->m_data_table[end].end(); ++it)
				{
					if ( equalFunc( (*it).m_key, k_ ) ) //< Verifica se as chaves são iguais
					{
						(*it).m_data = d_; //< Troca os valores se a chave já existe na lista.
						return false;
					}
				}
			}
			// Insere o novo item na tabela.
			this->m_data_table[end].push_front( new_entry );
			++this->m_count;
			return true; //< Um item não existente 
		}

		/**
		 * @brief      Remove um item de tabela identificado por sua chave.
		 *
		 * @param[in]  k_    A chave.
		 * @return     True se o item for encontrado, false caso contrário.
		 */
		bool erase( const KeyType k_ )
		{
			KeyHash hashFunc;
			KeyEqual equalFunc;
			auto end( hashFunc( k_ ) % this->m_size );

			// Verifica se o hash e a tabela não estão vazias
			if( !this->empty() && !this->m_data_table[end].empty() )
			{
				auto it_slow = this->m_data_table[end].before_begin();
				// Percorre toda a tabela atrás do item com a chave especifica.
				for ( auto it = this->m_data_table[end].begin(); it != this->m_data_table[end].end() ; ++it)
				{
					if( equalFunc( (*it).m_key, k_ ) ) 
					{
						this->m_data_table[end].erase_after( it_slow );
						--this->m_count;
						return true;
					}
					it_slow = it;
				}
			}

			return false;
		}

		/**
		 * @brief      Recupera as informação associada a chave passada como argumento para o método.
		 *
		 * @param[in]  k_    A chave.
		 * @param      d_    Informação associada.
		 *
		 * @return     True se a chave for encontrada, false caso contrário.
		 */
		bool retrieve( const KeyType & k_, DataType & d_ ) const
		{
			KeyHash hashFunc;
			auto end( hashFunc( k_ ) % this->m_size );
			KeyEqual equalFunc;
			
			// Verifica se tabela não estão vazias
			if( !this->m_data_table[end].empty() )
			{
				// Percorre a tabela.
				for ( auto it = this->m_data_table[end].begin(); it != this->m_data_table[end].end(); ++it)
				{
					// Verifica se a chave que procuramos.
					if ( equalFunc( (*it).m_key, k_ ) )
					{
						d_ = (*it).m_data;
						return true;
					}
				}
			}

			return false;
		}

		/**
		 * @brief      Libera toda a memória associada às listas de colisão da tabela, removendo os elementos.
		 */
		void clear( void )
		{
			if( !this->empty() ) //< Verifica se o hash não está vazio.
			{
				for (int i = 0; i < this->m_size; ++i)
				{
					// Verifica se a tabela não está vazia.
					if( !this->m_data_table[i].empty()) this->m_data_table[i].clear();
				}
				this->m_count = 0;
			}
		}

		/**
		 * @brief      Retorna uma referência para o dado associado a chave fornecida, se existir.
		 *	           Se a chave não estiver na tabela, o método realizar a inserção e retorna o novo dado.
		 *
		 * @param[in]  k_    A chave fornecida.
		 *
		 * @return     A referencia ao dado associado.
		 */
		DataType& operator[]( const KeyType& k_ )
		{
			KeyHash hashFunc;
			KeyEqual equalFunc;
			auto end( hashFunc( k_ ) % this->m_size );
			//Percorre a tabela.
			for (auto i = this->m_data_table[end].begin(); i != this->m_data_table[end].end(); ++i)
			{
				// Verifica se é a chave que procuramos.
				if( equalFunc( (*i).m_key,  k_ ) )
				{
					return (*i).m_data;
				}
			}

			this->insert( k_, DataType() ); //< insert chama push_front.
			// O tamanho da tabela pode ter sido alterada, então calculamos o novo end.
			end = hashFunc( k_ ) % this->m_size;
			auto it = this->m_data_table[end].begin();
			// Percorre a tabela atrás do item com a chave especifica.
			while( true )
			{
				if ( equalFunc ( (*it).m_key, k_ ) ) break;
				++it;
			}

			return (*it).m_data;

		}

		DataType& at( const KeyType & k_ )
		{
			
		}
		//template< typename kt, typename dt, typename kh, typename ke> friend std::ostream& operator<<( std::ostream & os, const ac::HashTbl< KeyType, DataType, KeyHash, KeyEqual > h );
	private:
		void rehash() {} 

		size_type m_size;
		size_type m_count;
		std::forward_list< Entry > * m_data_table;
		static const short DEFAULT_SIZE = 11;
	};
};

bool isPrimo( const size_type & value )
{
	for ( size_type i = 2; i <= value/2 ; ++i )
	{
		// Se for divisil, logo não é primo.
		if( value % i == 0 ) return false;
	}

	return true;
}
#endif