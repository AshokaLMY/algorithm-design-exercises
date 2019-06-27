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
    int nextPosSteps; //表示下一位置有多少种走法；走法少的优先考虑
    int nextPosDirection; //下一位置相对于当前位置的方位
    int nextPosToMidLength; //表示当前位置距中间点距离；距离中间点远的优先考虑
    bool operator < (const NextPos &a) const
    {
        return nextPosSteps > a.nextPosSteps && nextPosToMidLength < a.nextPosToMidLength;
    }
};
int board[100][100];
int M,N; //棋盘大小
//检测这个位置是否可以走
bool check(int x, int y)
{
    if (x >= 0 && x < M && y >= 0 && y < N && board[x][y] == 0)
        return true;
    return false;
}
//下一位置有多少种走法
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
//判断是否回到起点
bool returnStart(int x, int y)
{
    //校验最后是否可以回到起点，也就是棋盘的中间位置
    int midx,midy;
    midx = M / 2 - 1;
    midy = N / 2 - 1;
    for (int i = 0; i < 8; ++i)
        if (x + step[i].x == midx && y + step[i].y == midy)
            return true;
    return false;
}
//输出结果
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
//某一位置距离棋盘中心的距离
int posToMidLength(int x,int y)
{
    int midx = M / 2 - 1;
    int midy = N / 2 - 1;
    return (abs(x - midx) + abs(y - midy));
}
void BackTrace(int t, int x, int y,int xstart,int ystart)
{
    //找到结果
    if (t == M * N && returnStart(x,y)) //遍历了棋盘的所以位置，并且最后可以回到起点，形成回路
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
            //回溯
            board[x][y] = 0;
            x -= step[d].x;
            y -= step[d].y;
        }
    }
}
void horseRun(int xstart,int ystart)
{
    //初始化棋盘
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;
    int midx = M / 2 -1;
    int midy = N / 2 -1;
    board[midx][midy] = 1; //从棋盘的中间的位置开始马周游
    BackTrace(1, midx, midy,xstart,ystart);
}
int main()
{
    //马周游起始位置
    int x, y;
    cout<<"请输入棋盘大小m*n|m-n|<=2 且 m和n都为偶数:";
    cin>>M>>N;
    cout<<"请输入马周游起始位置--横纵坐标0 <= x < "<<M<<"和0 <= y < "<<N<<" :";
    cin>>x>>y;
    horseRun(x,y); //执行马周游
    return 0;
}

