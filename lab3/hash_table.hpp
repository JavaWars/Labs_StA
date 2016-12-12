#ifndef _HASH_TABLE_HPP_
#define _HASH_TABLE_HPP_

struct Key
{
	int m_Row, m_Col;
};

Key * CreateKey(int _row, int _col);

struct HashTable;

HashTable* HashTableCreate ( int _initialSize = 100 );

void HashTableDestroy ( HashTable* _pHT );

void HashTableClear ( HashTable & _ht );

int HashTableNumElements ( const HashTable & _ht );

void HashTableInsert ( HashTable & _ht, Key & _key, int _value );

int HashTableGet ( const HashTable & _ht, Key & _key );

void HashTableRemoveKey ( HashTable & _ht, Key & _key );


#endif //  _HASH_TABLE_HPP_

