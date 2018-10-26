#ifdef _Queue_h

struct QueueRecord;
typedef struct QueueRecord *Queue;

int IsEmpty(Queue Q);
int IsFull(Queue Q);
Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);
void MakeEmpty(Queue);
void Enqueue(ElementType X, Queue Q);
ElementType Front(Queue Q);
void Dequeue(Queue Q);
ElementType FrontAndDequeue(Queue Q);

#endif

/* Place int implementation file */
/* Queue implementation is a dynamically allocated array */

#define MinQueueSize (5)

struct QueueRecord
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType *Array;	
};




int IsEmpty(Queue Q);
{
	return Q->Size == 0;
}




void MakeEmpty(Queue Q)
{
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}




static int Succ(int Value, Queue Q)
{
	if(++Value == Q->Capacity)
		Value = 0;
	return Value;
}
void Enqueue(ElementType X, Queue Q)
{
	if(IsFull(Q))
		Error("Full queue");
	else
	{
		Q->Size++;
		Q->Rear = Succ(Q->Rear, Q);
		Q->Array[Q->Rear] = X;
	}
}