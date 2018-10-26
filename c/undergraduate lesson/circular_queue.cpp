#include<iostream>
using namespace std;

const int N = 5;
struct Circular_queue
{
    int cq[N];
    int front;
    int rear;
    int count;
};

Circular_queue *C_queue = new Circular_queue;

void Initia_queue();
void Print_menu();
void Enqueue();
void Dequeue();

int main()
{
    int choice;
    
    Initia_queue();
    Print_menu();
    while(cin >> choice && choice < N)
    {
        switch(choice)
        {
            case 1: Enqueue();break;
            case 2: Dequeue();break;
            case 3: cout << "The length of the queue is: " << C_queue->count << endl;
                    break;
            case 4: cout << "The front element of the queue is: " << C_queue->cq[C_queue->front] << endl;
                    break;
        }
        Print_menu();
    }

    return 0;
}

void Initia_queue()
{
    C_queue->front = 0;
    C_queue->rear = 0;
    C_queue->count = 0;
}

void Print_menu()
{
    cout << "Enter your choice:" << endl;
    cout << "1.enqueue" << endl;
    cout << "2.dequeue" << endl;
    cout << "3.length of queue" << endl;
    cout << "4.front of queue" << endl;
    cout << "5.quit" << endl;
}

void Enqueue()
{
    int num;

    cout << "Enter the number you want to insert:" << endl;
    cin >> num;
    if(C_queue->count <= N)
    {
        C_queue->cq[C_queue->rear] = num;
        if(C_queue->rear == N-1)
            C_queue->rear = 0;
        else C_queue->rear++;
        C_queue->count++;
    }
    else cout << "Queue is full" << endl;
}

void Dequeue()
{
    if(C_queue->front == N-1)
        C_queue->front = 0;
    else C_queue->front++;

    C_queue->count--;
}
