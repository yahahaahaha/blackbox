#include<iostream>
using namespace std;

struct TreeNode
{
    int element;
    TreeNode *Left;
    TreeNode *Right;
};


void Print_Menu()
{
    cout << "Enter your select: " << endl;
    cout << "1.create binary tree( 0 to quit )" << endl;
    cout << "2.pre-order traversal" << endl;
    cout << "3.in-order traversal" << endl;
    cout << "4.post-order traversal" << endl;
    cout << "5.height" << endl;
    cout << "6.layer traversal" << endl;
    cout << "7.quit" << endl;
}


TreeNode *Create_Tree()
{
    int num;
    cin >> num;
    if( num == 0 )
        return NULL;
    else
    {
        TreeNode *new_node = new TreeNode;
        new_node->element = num;
        new_node->Left = Create_Tree();
        new_node->Right = Create_Tree();
        return new_node;
    }
}

void Pre_Traversal( TreeNode *tree )
{
    if( tree )
    {
        cout << tree->element << " ";
        Pre_Traversal( tree->Left );
        Pre_Traversal( tree->Right );
    }
}

void In_Traversal( TreeNode *tree )
{
    if( tree )
    {
        In_Traversal( tree->Left );
        cout << tree->element << " ";
        In_Traversal( tree->Right );
    }
}

void Post_Traversal( TreeNode *tree )
{
    if( tree )
    {
        Post_Traversal( tree->Left );
        Post_Traversal( tree->Right );
        cout << tree->element << " ";
    }
}

int Cal_height( TreeNode *tree )
{
   int height = 0;

   if( tree )
   {
        height++;
        height += max( Cal_height( tree->Left ), Cal_height( tree->Right ) );
   }

   return height;
}

void Layer_Traversal( TreeNode *tree )
{
    const int N = 100;
    TreeNode *queue[N];
    int front = 0, rear = 0;
    queue[rear++] = tree;

    while( front < rear )
    {
        cout << queue[front]->element << " ";
        if( queue[front]->Left != NULL )
            queue[rear++] = queue[front]->Left;
        if( queue[front]->Right != NULL )
            queue[rear++] = queue[front]->Right;
        front++;
    }

}





int main()
{
    TreeNode *Tree;
    int select;

    Print_Menu();
    cin >> select;
    while( select > 0 && select < 7 )
    {
        switch( select )
        {
            case 1: Tree = Create_Tree(); break;
            case 2: Pre_Traversal( Tree ); cout << endl; break;
            case 3: In_Traversal( Tree ); cout << endl; break;
            case 4: Post_Traversal( Tree ); cout << endl; break;
            case 5: cout << "The height of the tree is: " << Cal_height( Tree ) << endl; break;
            case 6: Layer_Traversal( Tree ); cout << endl; break;
        }
        Print_Menu();
        cin >> select;
    }

    return 0;
}
