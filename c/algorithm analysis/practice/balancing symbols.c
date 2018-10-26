#include <stdio.h>
#include<string.h>
#include<stddef.h>
#include<stdlib.h>
#define EmptyTOS (-1)

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    char *Array;
};

typedef struct StackRecord * Stack;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(char X, Stack S);
char Top(Stack S);
void Pop(Stack S);








int main()
{
    char test[101];
    int i;

    Stack BS = CreateStack(100);
    
    printf("Input:\n");
    scanf("%s", test);

    for(i = 0; i < strlen(test); i++)
    {
        if(test[i] == '('|| test[i] == '[' || test[i] == '{')
            Push(test[i], BS);

        if(test[i] == ')'|| test[i] == ']' || test[i] == '}')
        {
            if(IsEmpty(BS))
            {
                printf("No opening symbol\n");
                return 0;
            }
            else
                if(   (Top(BS) == '(' && test[i] == ')')
                   || (Top(BS) == '[' && test[i] == ']')
                   || (Top(BS) == '{' && test[i] == '}')
                  )
                  {
                    Pop(BS);
                  }
                else
                    {
                        printf("Not the corresponding opening symbol\n");
                        return 0;
                    }
        }
    }
    if(!IsEmpty(BS))
        printf("Only a opening symbols\n");
    else printf("No problem\n");


    return 0;
}





int IsEmpty(Stack S)
{
    return S->TopOfStack == -1;
}





int IsFull(Stack S)
{
    return S->Capacity <= S->TopOfStack;
}





Stack CreateStack(int MaxElements)
{
    Stack S;

    S = malloc(sizeof(struct StackRecord));
    if(S == NULL)
        printf("Out of space!!!");

    S->Array = malloc(sizeof(char) * MaxElements);
    if(S->Array == NULL)
        printf("Out of space!!!");
    S->Capacity = MaxElements;
    MakeEmpty(S);

    return S;
}





void DisposeStack(Stack S)
{
    if(S != NULL)
    {
        free(S->Array);
        free(S);
    }
}





void MakeEmpty(Stack S)
{
    S->TopOfStack = EmptyTOS;
}





void Push(char X, Stack S)
{
    if(IsFull(S))
        printf("Full stack");
    else
            //printf("aaaaa");
        {
            S->TopOfStack++;
            //printf("%d", S->TopOfStack);
            S->Array[S->TopOfStack] = X;
            //printf("%d", S->TopOfStack);
        }
}





char Top(Stack S)
{
    if(!IsEmpty(S))
        return S->Array[S->TopOfStack];
    printf("Empty stack");
    return 0;
}





void Pop(Stack S)
{
    if(IsEmpty(S))
        printf("Empty stack");
    else
        S->TopOfStack--;
}
