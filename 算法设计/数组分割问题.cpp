#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#define maxn 500+1
int dp[55][55*510]={0};
int p[maxn]={0};
void swap(int *a,int *b){
    int t=*a;
    *a=*b;
    *b=t;
}
int min(int a,int b){
    return a<b?a:b;
}
int main()
{
    int n,i,maxv=0,nn;
    int _max,_min;
    int flag=0;
    cout<<"������μӰκӵ�������";
    cin>>n;
    memset(dp,0,sizeof(dp));
    maxv=0;
    flag=0;
    cout<<"����������κӵ��˵����أ�"<<endl;
    for(i=0;i<n;i++)
    {
        cin>>p[i];
        maxv+=p[i];
    }
        nn=n%2?n/2:n/2-1;
        for(i=0;i<n;i++)
        {//ѡ��������.
           int j;
           for(j=min(nn,i);j>=0;j--)
           {//�Ѿ�ѡ������
              int k;
              for(k=maxv/2;k>=0;k--)
              {//�ܹ�������
                if(j>0)
                {
                    if(k-p[i]>=0)
                    {
                        if(dp[j][k]==0)
                        dp[j][k]=dp[j-1][k-p[i]];
                    }
                }
                else{
                    if(dp[j][k]==0)
                        dp[j][k]=(k==p[i]?1:0);
                    }
                }
            }
          }
          for(i=maxv/2;i>=0;i--)
          {
              if(dp[nn][i])
              {
                 _min=i;
                 _max=maxv-_min;
                 flag=1;
                 break;
              }
           }
           if(_min>_max)  swap(&_min,&_max);
           cout<<"��һ���������Ϊ��"<<_min<<endl<<"�ڶ����������Ϊ��"<<_max<<endl;
           return 0;
}
