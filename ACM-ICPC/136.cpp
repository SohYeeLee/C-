#include<stdio.h>
#include <iostream>

using namespace std;
int p;
int q;
int r;
int ugly[1501]={0};

int main()
{
    int P,Q,R;
    ugly[0]=1;
    p=q=r=0;
    int i=1;
    while(ugly[1499]==0)
    {
        P=(ugly[p])*2;
        Q=(ugly[q])*3;
        R=(ugly[r])*5;
    if((P<Q)&&(P<R))
    {
        ugly[i]=P;
        i++;
        p++;
    }
    else if((Q<P)&&(Q<R))
    {
        ugly[i]=Q;
        i++;
        q++;
    }
    else if((R<P)&&(R<Q))
    {
        ugly[i]=R;
        i++;
        r++;
    }
    else if(P==Q)
    {
        q++;
    }
    else if(P==R)
    {
        r++;
    }
    else if(R==Q)
    {
        r++;
    }

    }
    printf("The 1500'th ugly number is %d.\n",ugly[1499]);
    return 0;
}
