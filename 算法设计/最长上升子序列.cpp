#include <stdio.h>
#include <iostream>
using namespace std;
#define  MAX 1000
int seq[MAX+10];
int seqlen[MAX+10];
int main()
{start:
    int i,j,k,N,max,maxlen=1;
    for(i=1;i<=9;i++)
        seqlen[i]=1;        //seqlen数组存以第i个数为终点的最长上升序列
    cout<<"请输入数组长度：";
    cin>>N;
    cout<<"请输入数组元素："<<endl;
    for(i=1;i<=N;i++)
        cin>>seq[i];       //seq数组保存序列数组
    for (i=2;i<=N;i++)
    {
        max=0;
        for (j=1;j<=i-1;j++)
        {
            if(seq[j]<seq[i]&&seqlen[j]>max)  //在前i-1个序列中，寻找以终点小于seq[i]的最长的子序列，即最优子状态
                max=seqlen[j];
        }
        seqlen[i]=max+1;
        if(seqlen[i]>maxlen)           //seqlen中保存的是第i个数为终点的最长上升序列，找出这个数组中最大的值即为最优序列长度
            maxlen=seqlen[i];
    }
    cout<<"最长上升子序列长度为："<<maxlen<<endl;
begin:
    int choose;
    cout<<"输入选择：1.重新建立新数组；  2.退出   "<<endl;
    cin>>choose;
    if(choose==1)    goto start;
    else if(choose==2) return 0;
    else {cout<<"输入命令有误，请重新输入命令！"<<endl;goto begin;}
}
