#include<iostream>
#include<fstream>
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
    int indegree;
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
        G.vertices[i].indegree = 0;
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

void Find_Indegree( ALGraph &G )
{
    for( int i = 0; i < G.vertex_num; i++ )
    {
        Arc_Node *this_arc_node = G.vertices[i].first_arc;
        while( this_arc_node != NULL )
        {
            G.vertices[this_arc_node->head_index].indegree++;
            this_arc_node = this_arc_node->next_arc;
        }
    }
}

void Topo_Logical_Sort( ALGraph G, int *topo )
{
    Find_Indegree( G );
    //for( int i = 0; i < G.vertex_num; i++)
    //    cout << G.vertices[i].indegree << endl;
    int S[MVNum], top_of_stack = -1;
    for( int i = 0; i < G.vertex_num; i++)
        if( G.vertices[i].indegree == 0 )
        {
            top_of_stack++;
            S[top_of_stack] = G.vertices[i].vertex_code;
        }
    int count_vertex = 0;
    while( top_of_stack > -1 )
    {
        topo[count_vertex] = S[top_of_stack];
        count_vertex++;
        Arc_Node * p = G.vertices[S[top_of_stack]].first_arc; 
        top_of_stack--;
        while( p != NULL )
        {
            int k = p->head_index;
            G.vertices[k].indegree--;
            if( G.vertices[k].indegree == 0 )
            {
                top_of_stack++;
                S[top_of_stack] = G.vertices[k].vertex_code;
            }
            p = p->next_arc;
        }
    }

    if( count_vertex < G.vertex_num )
        cout << "It can't be proceeded!!!" << endl;
    else cout << "It can be proceeded!!!" << endl;
}

void Cal_event_earliest_happen_time( ALGraph G, int *topo, int *eeht )
{
    for( int i = 0; i < G.vertex_num; i++ )
        eeht[i] = 0;
    for( int i = 0; i < G.vertex_num; i++ )
    {
        int topo_vertex_index = topo[i];
        Arc_Node *p_to_arc = G.vertices[topo_vertex_index].first_arc;
        while( p_to_arc != NULL )
        {
            int vertex_index = p_to_arc->head_index;
            if( eeht[vertex_index] < eeht[topo_vertex_index] + p_to_arc->weight )
                eeht[vertex_index] = eeht[topo_vertex_index] + p_to_arc->weight;
            p_to_arc = p_to_arc->next_arc;
        }
    }
}

void Cal_event_latest_happen_time( ALGraph G, int *topo, int *eeht, int *elht )
{
    for( int i = 0; i < G.vertex_num; i++ )
        elht[i] = eeht[G.vertex_num - 1];
    for( int i = G.vertex_num - 1; i >= 0; i-- )
    {
        int topo_vertex_index = topo[i];
        Arc_Node *p_to_arc = G.vertices[topo_vertex_index].first_arc;
        while( p_to_arc != NULL )
        {
            int vertex_index = p_to_arc->head_index;
            if( elht[topo_vertex_index] > elht[vertex_index] - p_to_arc->weight )
                elht[topo_vertex_index] = elht[vertex_index] - p_to_arc->weight;
            p_to_arc = p_to_arc->next_arc;
        }

    }
}

void Judge_and_Print_key_event( ALGraph G, int *eeht, int *elht )
{
    for( int i = 0; i < G.vertex_num; i++ )
    {
        Arc_Node *p_to_arc = G.vertices[i].first_arc;
        while( p_to_arc != NULL )
        {
            int vertex_index = p_to_arc->head_index;
            int e = eeht[i];
            int l = elht[vertex_index] - p_to_arc->weight;
            if( e == l )
            {
                cout << "<" <<G.vertices[i].vertex_code << ", " << G.vertices[vertex_index].vertex_code << "> ";
                cout << "earliest time: " << e << ", The latest time: " << l << endl; 
            }
            p_to_arc = p_to_arc->next_arc;
        }
    }
}

int main()
{
    ALGraph al_graph;
    Create_DG( al_graph );

    int topo[MVNum];
    Topo_Logical_Sort( al_graph, topo );

    int event_earliest_happen_time[MVNum];
    int event_latest_happen_time[MVNum];
    Cal_event_earliest_happen_time( al_graph, topo, event_earliest_happen_time );
    Cal_event_latest_happen_time( al_graph, topo, event_earliest_happen_time, event_latest_happen_time );
    cout << "Finish this program need at least: " << event_earliest_happen_time[al_graph.vertex_num-1] << endl;
    Judge_and_Print_key_event( al_graph, event_earliest_happen_time, event_latest_happen_time );
    
    //for( int i = 0; i < al_graph.vertex_num; i++)
    //    cout << "early: " << event_earliest_happen_time[i] << ", late: " << event_latest_happen_time[i] << endl;
    return 0;
}
