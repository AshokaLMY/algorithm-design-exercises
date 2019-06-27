#include<stdio.h>
#include<iostream>
using namespace std;
#define N 100
/*
 *��ϲ�������
 *���ٺϲ�����Ŀ
 **/
int MatrixChain_min(int p[N],int n)
{
    //�����ά����m[i][j]����¼i��j�ĺϲ�����������ʯ����Ŀ
    //�˴���ֵΪ-1
    int m[N][N];
    for(int x=1;x<=n;x++)
        for(int z=1;z<=n;z++)
            m[x][z]=-1;
    int min=0;
    //��һ�������ϲ�ʱ��m[i][i]��Ϊ0����ʾû��ʯ��
    for(int g=1;g<=n;g++) m[g][g]=0;
    //�����ڵ�����ʯ�Ӻϲ�ʱ����ʱ��m�����׿��Կ���������֮��
    for(int i=1;i<=n-1;i++)
    {
        int j=i+1;
        m[i][j]=p[i]+p[j];
    }
    //�����ڵ�3���Լ�������n��ʱ��ִ������ѭ��
    for(int r=3; r<=n;r++)
        for(int i=1;i<=n-r+1;i++)
        {
            int j = i+r-1;//j���Ǿ���i---r-1�ľ���
            int sum=0;
            //��i��j��ʯ�Ӻϲ�ʱ��������ʯ������͵�sum
            for(int b=i;b<=j;b++)
                sum+=p[b];
            //��ʱm[i][j]Ϊi~j��ʯ�Ӽ���m[i][i]+m[i+1][j]+sum�������������һ�ֿ��ܣ���һ��������
            //Ҫ������������Ƚ�
            m[i][j] = m[i+1][j]+sum;
             //������һ���������������������
            for(int k=i+1;k<j;k++)
            {
                int t=m[i][k]+m[k+1][j]+sum;
                if(t<m[i][j])
                    m[i][j] = t;
            }
        }
        //���յõ����Ž�
        min=m[1][n];
        return min;
}
/*
 *��ϲ�������
 *���ϲ�����Ŀ
 **/
int  MatrixChain_max(int p[N],int n)
{
    int m[N][N];
    for(int x=1;x<=n;x++)
    for(int z=1;z<=n;z++)
        m[x][z]=-1;
    int max=0;
    //һ���������ʱ
    for(int g = 1;g<=n;g++) m[g][g]=0;
    //�����������ʱ
    for(int i=1;i<=n-1;i++)
    {
        int j=i+1;
        m[i][j]=p[i]+p[j];
    }
    for(int r=3; r<=n;r++)
        for(int i=1;i<=n-r+1;i++)
        {
            int j = i+r-1;
            int sum=0;
            for(int b=i;b<=j;b++)
                sum+=p[b];
            m[i][j] = m[i+1][j]+sum;

            for(int k=i+1;k<j;k++)
            {
                int t=m[i][k]+m[k+1][j]+sum;
                if(t>m[i][j])
                    m[i][j] = t;
            }
        }
        max=m[1][n];
        return max;
}
int main()
{
      int stone[N];
      int min=0;
      int max=0;
      int n;
      cout<<"��������������";
      cin>>n;
      cout<<"���������������";
      for(int i=1;i<=n;i++)
          cin>>stone[i];
      min= MatrixChain_min(stone,n);
      max= MatrixChain_max(stone,n);
      //��Ϊ��ĿҪ��Բ��ԭ��Ҫ�����������Ҫ���ǵ����ܹ���n�������
      for(int j=1;j<=n-1;j++)
      {
           int min_cache=0;
           int max_cache=0;
           int cache= stone[1];
           for(int k=2;k<=n;k++)
           {
               stone[k-1]=stone[k];
           }
           stone[n]=cache;
           min_cache= MatrixChain_min(stone,n);
           max_cache= MatrixChain_max(stone,n);
           if(min_cache<min)
               min=min_cache;
           if(max_cache>max)
               max=max_cache;
      }
    cout<<"��С�ܴ���Ϊ��"<<min;
    return 1;
}
