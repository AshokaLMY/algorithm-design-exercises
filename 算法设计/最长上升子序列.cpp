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
        seqlen[i]=1;        //seqlen������Ե�i����Ϊ�յ�����������
    cout<<"���������鳤�ȣ�";
    cin>>N;
    cout<<"����������Ԫ�أ�"<<endl;
    for(i=1;i<=N;i++)
        cin>>seq[i];       //seq���鱣����������
    for (i=2;i<=N;i++)
    {
        max=0;
        for (j=1;j<=i-1;j++)
        {
            if(seq[j]<seq[i]&&seqlen[j]>max)  //��ǰi-1�������У�Ѱ�����յ�С��seq[i]����������У���������״̬
                max=seqlen[j];
        }
        seqlen[i]=max+1;
        if(seqlen[i]>maxlen)           //seqlen�б�����ǵ�i����Ϊ�յ����������У��ҳ��������������ֵ��Ϊ�������г���
            maxlen=seqlen[i];
    }
    cout<<"����������г���Ϊ��"<<maxlen<<endl;
begin:
    int choose;
    cout<<"����ѡ��1.���½��������飻  2.�˳�   "<<endl;
    cin>>choose;
    if(choose==1)    goto start;
    else if(choose==2) return 0;
    else {cout<<"�������������������������"<<endl;goto begin;}
}
