#include<iostream>
#include<fstream>
#include<queue>
using namespace std;

#define MVNum 20

struct Arc_Node
{
    int head_index;
    struct Arc_Node * next_arc;
    int weight;
};

typedef struct Vertex_Node
{
    int vertex_code;
    Arc_Node *first_arc;
    bool visited;
}AdjList[MVNum];

struct ALGraph{
    AdjList vertices;
    int vertex_num;
    int arc_num;
};

int Located_Vertex_index( ALGraph G, int v )
{
    for( int i = 0; i < G.vertex_num; i++ )
        if( G.vertices[i].vertex_code == v )
            return i;
    cout << "No this vertex" << endl;
    return -1;
}

void Create_DG( ALGraph &G )
{
    ifstream fcin;
    fcin.open( "AOE_data.txt", ios::in );

    fcin >> G.vertex_num >> G.arc_num;
    for( int i = 0; i < G.vertex_num; i++ )
    {
        fcin >> G.vertices[i].vertex_code;
        G.vertices[i].first_arc = NULL;
        G.vertices[i].visited = 0;
    }
    for( int k = 0; k < G.arc_num; k++ )
    {
        int v1,v2,i,j;
        fcin >> v1 >> v2;
        i = Located_Vertex_index( G, v1 );
        j = Located_Vertex_index( G, v2 );
        Arc_Node * arc = new Arc_Node;
        arc->head_index = j;
        arc->next_arc = NULL;
        fcin >> arc->weight;
        arc->next_arc = G.vertices[i].first_arc;
        G.vertices[i].first_arc = arc;
    }
    fcin.close();
}


void DFS( ALGraph &G, int v )
{
    cout << G.vertices[v].vertex_code << " ";
    G.vertices[v].visited = 1;
    Arc_Node * p = G.vertices[v].first_arc;
    while( p != NULL )
    {
        int w = p->head_index;
        if( !G.vertices[w].visited )
        {
            DFS( G, w );
            //cout << G.vertices[w].visited << " ";
        }
        p = p->next_arc;
    }
}

void BFS( ALGraph G, int v )
{
    cout << G.vertices[v].vertex_code << " ";
    G.vertices[v].visited = 1;
    queue<int> Q;
    Q.push( v );
    while( !Q.empty() )
    {
        Arc_Node *p = G.vertices[Q.front()].first_arc;
        for( Arc_Node *i = p; i != NULL ; i = i->next_arc )
        {
            if( !G.vertices[i->head_index].visited )
            {
                cout << G.vertices[i->head_index].vertex_code << " ";
                Q.push( i->head_index );
                G.vertices[i->head_index].visited = 1;
            }
        }
        Q.pop();
    }
}




int main()
{
    ALGraph al_graph;
    Create_DG( al_graph );
    
    cout << "DFS: " << endl;
    DFS( al_graph, 0 );
    cout << endl;
    for( int i = 0; i < al_graph.vertex_num; i++ )
        al_graph.vertices[i].visited = 0;
    cout << "BFS: " << endl;
    BFS( al_graph, 0);
    cout << endl;
    
    return 0;
}
