#ifndef _Stack_h

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmpty(Stack S);
Stack CreateStack(void);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);

#endif


/*Place in implementation file*/
struct Node
{
	ElementType Element;
	PtrToNode Next;
};





Stack CreateStack(void)
{
	Stack S;
	S = malloc(sizeof(struct Node));
	if(S == NULL)
		FatalError("Out of space!!!");
	MakeEmpty(S);
	return S;
}

void MakeEmpty(Stack S)
{
	if(S == NULL)
		Error("Must use CreateStack first");
	else
		while(!IsEmpty(S))
			Pop(S);
}





void Push(ElementType X, Stack S)
{
	PtrToNode TmpCell;

	TmpCell = malloc(sizeof(struct Node));
	if(TmpCell == NULL)
		FatalError("Out of space!!!");
	else
	{
		TmpCell->Element = X;
		TmpCell->Next = S->Next;
		S->Next = TmpCell;
	}
}


void Pop(Stack S)
{
	PtrToNode FirstCell;

	if(IsEmpty(S))
		Error("Empty stack");
	else
	{
		FirstCell = S->Next;
		S->Next = S->Next->Next;
		free(FirstCell);
	}
}




