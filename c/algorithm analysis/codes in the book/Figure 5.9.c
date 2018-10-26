Position
Find( ElmentType Key, HashTable H )
{
	Position P;
	List L;

	L = H->TheLists[ Hash( Key, H->TableSize ) ];
	P = L->Next;
	while( P != NULL && P->Element != Key )
		P = P->Next;

	return P;
}