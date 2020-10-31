#include<bits/stdc++.h>
int main()
{
int d,m,y,c=0,c1,sum=0;
    cin>>d>>m>>y;
    int y1=y;
    int mon[12]={0,3,3,6,1,4,6,2,5,0,3,5};
    int cc[4]={6,4,2,0};
    int f = d%7;
    int s = mon[m-1];
    if(y<2000)
    c1=cc[3];
    else
    c1 = cc[0];

    while(y1>0)
    {
        int r=y1%10;
        c++;

        sum=sum*10+r;
        if(c==2)
            break;
        y1/=10;
    }
    int od = sum%7;
    int ly = (int)sum%4;
    int finalv = f+s+c1+od+ly;
    switch(finalv)
    {
    case 0:
        cout<<"sunday";
        break;
    case 1:
        cout<<"monday";
        break;
    case 2:
        cout<<"tuesday";
        break;
    case 3:
        cout<<"wednesday";
        break;
    case 4:
        cout<<"thursday";
        break;
    case 5:
        cout<<"friday";
        break;
    case 6:
        cout<<"saturdayday";
        break;
    }
    return 0;
    }
