#ifndef _HASHTBL_H_
#define _HASHTBL_H_

#include <functional> //< std::hash and std::equal_to
#include <forward_list> //< std::forward_list
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
		~HashTbl();
	
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

		bool insert( const KeyType & k_, const DataType & d_ )
		{
			
		}
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