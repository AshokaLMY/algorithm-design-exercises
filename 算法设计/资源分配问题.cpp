#include <iostream>
#include <cstdlib>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int resourceAlloc(int m,int n,int **p){
 //fΪ��Ӧ���̶�Ӧ��ͬ��Դ��������dΪ����������������Դ��
 int **f,**d;
 f = new int*[n];
 d = new int*[n];
 for(int i=0;i<n+1;i++){
  f[i] = new int[m+1];
  d[i] = new int[m+1];
 }
 //0��0�в�ʹ�����ݣ��洢Ϊ0
 for(int i=0;i<m+1;i++)
 {
    f[0][i] = 0;
    d[0][i] = 0;
  }
 for(int i=0;i<n+1;i++)
 {
   f[i][0] = 0;
   d[i][0] = 0;
 }
 //��ʼ������1��Ӧ��f[1]��d[1]
 for(int i=1;i<=m;i++)
 {
    f[1][i] = p[1][i];
    d[1][i] = i;
 }
 //���㹤��2----n
 for(int i=2;i<=n;i++)
 {
  for(int x=1;x<=m;x++)
  {
    int max = 0,z = 0;
    for(int j=1;j<=x;j++)
    {
      int temp = p[i][j]+f[i-1][x-j];
      if(temp > max)
      {
        max = temp;
        z=j;
      }
   }
   f[i][x] = max;
   d[i][x] = z;
  }
 }
 //Ѱ��n�����̵��������������Դ��������õ���Դ�Ĺ��������
 int bestp=f[1][1],bestx=1,bestk=1;
 for(int i=1;i<=n;i++)
 {
    for(int j=1;j<=m;j++)
    {
     if(bestp < f[i][j])
     {
       bestp = f[i][j];
       bestx = j;
        bestk = i;
     }
    }
 }
 //����ź���ı�Ų�������Դ
 int *best = new int[n+1];
 if(bestk < n){
  for(int i=bestk+1;i<=n;i++)
   best[i] = 0;
 }
 //��ǰk����Ŀ������Դ���䣬�������Ž�
 for(int i = bestk;i > 0;i--){
  best[i] = d[i][bestx];
  bestx = bestx - best[i];
 }

 //�����Ŀ������Դ
 for(int i=1;i<=n;i++){
  cout<<best[i]<<" ";
 }
 cout<<endl;

 for(int i=0;i<n+1;i++){
  delete[] f[i];
  delete[] d[i];
 }
 delete f;
 delete d;
 return bestp;
}

int main(int argc, char *argv[])
{
 int m,n;
 cout<<"�������豸���ͳ�����:"<<endl;
 cin>>m>>n;
 //�����(n+1)*(m+1),0��0������Ϊ0
 int **p;
 p = new int*[n+1];
 for(int row = 0; row < n+1;row++){
  p[row] = new int[m+1];
 }
 //��ʼ��0��0��
 for(int i=0;i<m+1;i++){
  p[0][i] = 0;
 }
 for(int i=0;i<n+1;i++){
  p[i][0] = 0;
 }
 //��ʼ�������
 cout<<"�����뽫į�豸�ṩ��j�ų���õ�������:"<<endl;
 for(int i=1;i<n+1;i++){
  for(int j=1;j<m+1;j++){
   cin>>p[i][j];
  }
 }
 cout<<"������Ϊ��"<<endl;
 int result = resourceAlloc(m,n,p);
 cout<<"���ӯ��Ϊ��"<<result<<endl;
 for(int i=0;i<n+1;i++)
    delete[] p[i];
 delete p;
 return 0;
}
