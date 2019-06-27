#include<stdio.h>
#include<iostream>
using namespace std;
#define N 100
/*
 *求合并过程中
 *最少合并堆数目
 **/
int MatrixChain_min(int p[N],int n)
{
    //定义二维数组m[i][j]来记录i到j的合并过成中最少石子数目
    //此处赋值为-1
    int m[N][N];
    for(int x=1;x<=n;x++)
        for(int z=1;z<=n;z++)
            m[x][z]=-1;
    int min=0;
    //当一个单独合并时，m[i][i]设为0，表示没有石子
    for(int g=1;g<=n;g++) m[g][g]=0;
    //当相邻的两堆石子合并时，此时的m很容易可以看出是两者之和
    for(int i=1;i<=n-1;i++)
    {
        int j=i+1;
        m[i][j]=p[i]+p[j];
    }
    //当相邻的3堆以及到最后的n堆时，执行以下循环
    for(int r=3; r<=n;r++)
        for(int i=1;i<=n-r+1;i++)
        {
            int j = i+r-1;//j总是距离i---r-1的距离
            int sum=0;
            //当i到j堆石子合并时最后里面的石子数求和得sum
            for(int b=i;b<=j;b++)
                sum+=p[b];
            //此时m[i][j]为i~j堆石子间以m[i][i]+m[i+1][j]+sum结果，这是其中一种可能，不一定是最优
            //要与下面的情况相比较
            m[i][j] = m[i+1][j]+sum;
             //除上面一种组合情况外的其他组合情况
            for(int k=i+1;k<j;k++)
            {
                int t=m[i][k]+m[k+1][j]+sum;
                if(t<m[i][j])
                    m[i][j] = t;
            }
        }
        //最终得到最优解
        min=m[1][n];
        return min;
}
/*
 *求合并过程中
 *最多合并堆数目
 **/
int  MatrixChain_max(int p[N],int n)
{
    int m[N][N];
    for(int x=1;x<=n;x++)
    for(int z=1;z<=n;z++)
        m[x][z]=-1;
    int max=0;
    //一个独自组合时
    for(int g = 1;g<=n;g++) m[g][g]=0;
    //两个两两组合时
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
      cout<<"请输入货物堆数：";
      cin>>n;
      cout<<"请输入各货物数：";
      for(int i=1;i<=n;i++)
          cin>>stone[i];
      min= MatrixChain_min(stone,n);
      max= MatrixChain_max(stone,n);
      //因为题目要求圆的原因，要把所有情况都要考虑到，总共有n种情况。
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
    cout<<"最小总代价为："<<min;
    return 1;
}
