#ifndef _HashSep_H

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable( int TableSize );
void DestroyTable( HashTable H );
Position Find( ElementType Key, HashTable H );
void Insert( ElementType Key, HashTable H );
ElementType Retrieve( Position P );
/* Routines such as Delete and MakeEmpty are omitted */

#endif


/* Place in the implementation file */
struct ListNode
{
	ElementType Element;
	Position	Next;
};

typedef Position List;

/* The lists use headers (for simplicity), */
/* though this wastes space */
struct HashTbl
{
	int TableSize;
	List *TheLists;
};