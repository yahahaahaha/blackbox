#include<iostream>
using namespace std;


long first[4] = {1, 1, 1, 0};
long * Cal(int n);
long * Mul(long * x, long * y);

int main()
{
    int n;
    long a[4] = {1, 1, 1, 0};
    long * result;

    cin >> n;

    while(n > 0)
    {
        if(n < 3)
            cout << 1 << endl;
        else{
            result = Cal(n-1);
            cout << result[0] << endl;
        }

        cin >> n;
    }

    delete [] result;
    return 0;
}

long * Cal(int n)
{
    long * next;

    if(n == 1)
        return first;
    else
        if(n % 2 == 0)
        {
            next = Cal(n/2);

            next = Mul(next, next);
        }
        else
        {
            next = Cal((n-1)/2);
            next = Mul(next, next);
            next = Mul(next, first);
        }


    return next;
}

long * Mul(long * x, long * y)
{
    long *product = new long[4];

    product[0] = x[0]*y[0] + x[1]*y[2];
    product[1] = x[0]*y[1] + x[1]*y[3];
    product[2] = x[2]*y[0] + x[3]*y[2];
    product[3] = x[2]*y[1] + x[3]*y[3];

    //cout << product[0] << " " << product[1] << endl;
    //cout << product[2] << " " << product[3] << endl;
    return product;
}



