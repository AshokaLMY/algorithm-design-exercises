#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <queue>
using namespace std;
typedef struct
{
    int x;
    int y;
} Step;
Step step[8] = { {-2, -1}, {-1, -2}, { 1, -2}, { 2, -1}, { 2, 1}, { 1, 2}, {-1, 2}, {-2,1} };
typedef struct NextPos
{
    int nextPosSteps; //��ʾ��һλ���ж������߷����߷��ٵ����ȿ���
    int nextPosDirection; //��һλ������ڵ�ǰλ�õķ�λ
    int nextPosToMidLength; //��ʾ��ǰλ�þ��м����룻�����м��Զ�����ȿ���
    bool operator < (const NextPos &a) const
    {
        return nextPosSteps > a.nextPosSteps && nextPosToMidLength < a.nextPosToMidLength;
    }
};
int board[100][100];
int M,N; //���̴�С
//������λ���Ƿ������
bool check(int x, int y)
{
    if (x >= 0 && x < M && y >= 0 && y < N && board[x][y] == 0)
        return true;
    return false;
}
//��һλ���ж������߷�
int nextPosHasSteps(int x, int y)
{
    int steps = 0;
    for (int i = 0; i < 8; ++i)
    {
        if (check(x + step[i].x, y + step[i].y))
            steps++;
    }
    return steps;
}
//�ж��Ƿ�ص����
bool returnStart(int x, int y)
{
    //У������Ƿ���Իص���㣬Ҳ�������̵��м�λ��
    int midx,midy;
    midx = M / 2 - 1;
    midy = N / 2 - 1;
    for (int i = 0; i < 8; ++i)
        if (x + step[i].x == midx && y + step[i].y == midy)
            return true;
    return false;
}
//������
void outputResult(int xstart,int ystart)
{
    int num = M * N;
    int k = num - board[xstart][ystart];
    for (int i = 0; i < M; ++i)
    {
        cout<<endl<<endl;
        for (int j = 0; j < N; ++j)
        {
            board[i][j] = (board[i][j] + k) % num + 1;
            cout<<setw(5)<<board[i][j];
        }
    }
    cout<<endl<<endl;
}
//ĳһλ�þ����������ĵľ���
int posToMidLength(int x,int y)
{
    int midx = M / 2 - 1;
    int midy = N / 2 - 1;
    return (abs(x - midx) + abs(y - midy));
}
void BackTrace(int t, int x, int y,int xstart,int ystart)
{
    //�ҵ����
    if (t == M * N && returnStart(x,y)) //���������̵�����λ�ã����������Իص���㣬�γɻ�·
    {
        outputResult(xstart,ystart);
        exit(1);
    }
    else
    {
        priority_queue<NextPos> nextPosQueue;
        for (int i = 0; i < 8; ++i)
        {
            if (check(x + step[i].x, y + step[i].y))
            {
                NextPos aNextPos;
                aNextPos.nextPosSteps = nextPosHasSteps(x + step[i].x, y + step[i].y);
                aNextPos.nextPosDirection = i;
                aNextPos.nextPosToMidLength = posToMidLength(x + step[i].x,y + step[i].y);
                nextPosQueue.push(aNextPos);
            }
        }
        while(nextPosQueue.size())
        {
            int d = nextPosQueue.top().nextPosDirection;
            nextPosQueue.pop();

            x += step[d].x;
            y += step[d].y;
            board[x][y] = t + 1;
            BackTrace(t + 1, x, y,xstart,ystart);
            //����
            board[x][y] = 0;
            x -= step[d].x;
            y -= step[d].y;
        }
    }
}
void horseRun(int xstart,int ystart)
{
    //��ʼ������
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;
    int midx = M / 2 -1;
    int midy = N / 2 -1;
    board[midx][midy] = 1; //�����̵��м��λ�ÿ�ʼ������
    BackTrace(1, midx, midy,xstart,ystart);
}
int main()
{
    //��������ʼλ��
    int x, y;
    cout<<"���������̴�Сm*n��|m-n|<=2 �� m��n��Ϊż��:";
    cin>>M>>N;
    cout<<"��������������ʼλ��--��������0 <= x < "<<M<<"��0 <= y < "<<N<<" :";
    cin>>x>>y;
    horseRun(x,y); //ִ��������
    return 0;
}

