#include <iostream>
#include <cstdlib>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int resourceAlloc(int m,int n,int **p){
 //f为相应工程对应不同资源数的利润，d为获得最大利润分配的资源数
 int **f,**d;
 f = new int*[n];
 d = new int*[n];
 for(int i=0;i<n+1;i++){
  f[i] = new int[m+1];
  d[i] = new int[m+1];
 }
 //0行0列不使用数据，存储为0
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
 //初始化工程1对应的f[1]和d[1]
 for(int i=1;i<=m;i++)
 {
    f[1][i] = p[1][i];
    d[1][i] = i;
 }
 //计算工程2----n
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
 //寻找n个工程的最大利润、最优资源分配额及分配得到资源的工程最大编号
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
 //最大编号后面的编号不分配资源
 int *best = new int[n+1];
 if(bestk < n){
  for(int i=bestk+1;i<=n;i++)
   best[i] = 0;
 }
 //对前k个项目进行资源分配，构造最优解
 for(int i = bestk;i > 0;i--){
  best[i] = d[i][bestx];
  bestx = bestx - best[i];
 }

 //输出项目所分资源
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
 cout<<"请输入设备数和车间数:"<<endl;
 cin>>m>>n;
 //利润表(n+1)*(m+1),0行0列数据为0
 int **p;
 p = new int*[n+1];
 for(int row = 0; row < n+1;row++){
  p[row] = new int[m+1];
 }
 //初始化0行0列
 for(int i=0;i<m+1;i++){
  p[0][i] = 0;
 }
 for(int i=0;i<n+1;i++){
  p[i][0] = 0;
 }
 //初始化利润表
 cout<<"请输入将i台设备提供给j号车间得到的利润:"<<endl;
 for(int i=1;i<n+1;i++){
  for(int j=1;j<m+1;j++){
   cin>>p[i][j];
  }
 }
 cout<<"分配结果为："<<endl;
 int result = resourceAlloc(m,n,p);
 cout<<"最大盈利为："<<result<<endl;
 for(int i=0;i<n+1;i++)
    delete[] p[i];
 delete p;
 return 0;
}
