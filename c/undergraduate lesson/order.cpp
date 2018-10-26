#include<iostream>
using namespace std;
const int N = 5;

void Insert_sort( int arr[] )
{
    for( int i = 1; i < N; i++ )
    {
        int k = i;
        for( int j = k-1; j >= 0; j-- )
        {
            if( arr[k] < arr[j] )
            {
                arr[k] = arr[k] ^ arr[j];
                arr[j] = arr[k] ^ arr[j];
                arr[k] = arr[k] ^ arr[j];
                k = j;
            }
        }
    }

    for( int i = 0; i < N; i++ )
        cout << arr[i] << " ";
    cout << endl;
}

void Swap_sort( int arr[] )
{
    for( int i = 0; i < N; i++ )
        for( int j = i+1; j < N; j++ )
        {
            arr[i] = arr[i] ^ arr[j];
            arr[j] = arr[i] ^ arr[j];
            arr[i] = arr[i] ^ arr[j];
        }
    for( int i = 0; i < N; i++ )
        cout << arr[i] << " ";
    cout << endl;
}

void Select_sort( int arr[] )
{
    int i,j,min,t;
    for(i=0;i<N-1;i++)
    {
        min=i;
        for(j=i+1;j<N;j++)
            if(arr[min]>arr[j])
                min=j;
        if(min!=i)
        {
            t=arr[min];
            arr[min]=arr[i];
            arr[i]=t;
        }
    }
    for( int i = 0; i < N; i++ )
        cout << arr[i] << " ";
    cout << endl;

}

int main()
{
    int arr[N];
    for( int i = 0; i < N; i++ )
        cin >> arr[i];
    cout << "insert sort:" << endl;    
    Insert_sort( arr );
    cout << "swap sort:" << endl;
    Swap_sort( arr );
    cout << "select sort " << endl;
    Select_sort( arr );

    return 0;
}
