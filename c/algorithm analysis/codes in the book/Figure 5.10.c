void
Insert( ElementType Key, HashTable H )
{
	Position Pos, NewCell;
	List L;

	Pos = Find( Key, H );
	if( Pos == NULL )
	{
		NewCell = malloc( sizeof( struct ListNode ) );
		if( NewCell == NULL )
			FatalError( "Out of space!!!" );
		else
		{
			L = H->TheLists[ Hash( Key, H->TableSize) ];
			NewCell->Next = L->Next;
			NewCell->Element = Key;
			L->Next = NewCell;
		}
	}
}