#include<iostream>
using namespace std;

struct List
{
    int element;
    List *next;
};

typedef List *Position;

void PrintMenu();
Position Create();
int Search(Position head, int num);
void Insert(Position head, int num);
void Delete(Position head, int num);
void Output(Position head);
void Merge(Position head_a, Position head_b);


int main()
{
    Position list_a = NULL, list_b = NULL;
    int select, num;

    PrintMenu();
    cin >> select;
    while(select < 7 && select > 0)
    {
        switch(select)
        {
            case 1: if(list_a == NULL) list_a = Create();
                    else list_b = Create();
                    break;
            case 2: cout << "Input the number you find:" << endl;
                    cin >> num;
                    num = Search(list_a, num);
                    if(num > 0) cout << "This number is at " << num << "th node." << endl;
                    else cout << "There is no this number" << endl;  
                    break;
            case 3: cout << "Input the number you want to insert" << endl;
                    cin >> num;
                    Insert(list_a, num);
                    break;
            case 4: cout << "Input the number you want to delete" << endl;
                    cin >> num;
                    Delete(list_a, num);
                    break;
            case 5: Output(list_a);
                    break;
            case 6: Merge(list_a, list_b);
                    break;
        }
        PrintMenu();
        cin >> select;
    }

    return 0;
}

void PrintMenu()
{
    cout << "1.create(only twice)" << endl;
    cout << "2.search" << endl;
    cout << "3.insert" << endl;
    cout << "4.delete" << endl;
    cout << "5.output" << endl;
    cout << "6.merge" << endl;
    cout << "7.quit" << endl;
    cout << "Input your select:" << endl;
}


Position Create()
{
    Position head = NULL;
    Position previous;
    int num, length;
    
    cout << "Input the length of the list:" << endl;
    cin >> length;

    cout << "Input number:" << endl;
    while(length)
    {
        length--;
        cin >> num;

        if(head == NULL)
        {
            head = new List;
            if(head == NULL)
                cout << "Space is full!" << endl;
            head->element = num;
            head->next = NULL;
            previous = head;

            continue;
        }
        
        previous->next = new List;
        if(previous->next == NULL)
            cout << "Space is full!" << endl;

        previous->next->element = num;
        previous->next->next = NULL;
        previous = previous->next;

    }
    

    return head;
}

int Search(Position head, int num)
{
    int count = 1, flag = 0;
    Position current = head;

    while(current != NULL)
    {
        if(num == current->element)
        {
            flag = 1;
            break;
        }
        count++;
        current = current->next;
    }

    if(flag) 
        return count;
    return -1;
}

void Insert(Position head, int num)
{
    Position current = head;

    while(current->next != NULL)
        current = current->next;

    current->next = new List;
    current->next->next = NULL;
    current->next->element = num;
}

void Delete(Position head, int num)
{
    int pos = Search(head, num);
    Position current = head, previous = head;

    if(pos < 0)
        cout << "There is no this number" << endl;
    else
    {
        while(pos-1 > 0)
        {
            pos--;
            previous = current;
            current = current->next;
        }
        
        previous->next = current->next;
        delete current;
    }
}
void Output(Position head)
{
    Position current = head;
    int i = 1;

    while(current != NULL)
    {
        cout << "node " << i << " : " << current->element << endl;
        current = current->next;
        i++;
    }
}

void Merge(Position head_a, Position head_b)
{
    Position la = head_a;

    while(la->next != NULL)
        la = la->next;

    la->next = head_b;
}




























