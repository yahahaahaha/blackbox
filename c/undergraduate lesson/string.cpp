#include<iostream>
using namespace std;

int Length( char *S );
void Copy( char *S, char *T );
void Cat( char *S, char *T );
void Get_se_string( char *S, char *T );
void Match( char *S, char *T );
void Print_Menu()
{
    cout << "1.copy" << endl;
    cout << "2.cat" << endl;
    cout << "3.sequence" << endl;
    cout << "4.match" << endl;
    cout << "5.length" << endl;
    cout << "6.quit" << endl;
    cout << "input your select number: " << endl;
}


int main()
{
    char S[20] = "abcd";
    char T[10] = "cd";
    int select;
    Print_Menu();
    cin >> select;
    while( select >0 && select < 6 )
    {
        switch( select )
        {
            case 1: Copy( S, T ); cout << T << endl; break;
            case 2: Cat( S, T ); cout << S << endl;break;
            case 3: Get_se_string( S, T ); cout << T << endl;break;
            case 4: Match( S, T ); break;
            case 5: cout << "String's length is: " << Length( S ) << endl; break;
        }
        Print_Menu();
        cin >> select;
    }

    return 0;
}

int Length( char *S )
{
    int count = 0;

    while( S[count] != '\0' )
        count++;
    return count;
}

void Copy( char *S, char *T )
{
    int i;
    for( i = 0; S[i] != '\0'; i++ )
        T[i] = S[i];
    T[i] = '\0';
}

void Cat( char *S, char *T )
{
    int s_length = Length( S );
    int t_length = Length( T );
    int i;

    for( i = 0; i < t_length; i++ )
        S[i+s_length] = T[i];
    S[i+s_length] = '\0';
}

void Get_se_string( char *S, char *T )
{
    int num, i;

    cout << "Enter the number: " << endl;
    cin >> num;
    for( i = 0; i < num; i++)
        T[i] = S[i];
    T[i] = '\0';
}

void Match( char *S, char *T )
{
    int s_length = Length( S );
    int t_length = Length( T );
    int i = 0, j = 0;

    //cout << t_length << endl;

    while( i < s_length && j < t_length )
    {
        if( S[i] == T[j] )
        {
            i++; j++;
        }
        else {
            i = i - j + 1; j = 0;
        }
    }
    //cout << j << endl;

    if( j >= t_length ) cout << 
        "The first character in main string is: " << i - t_length << endl;
    else cout << "No match!" << endl;
}
