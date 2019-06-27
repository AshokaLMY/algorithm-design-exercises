/* Solution:
    使用回溯法，马每一步至多有8种跳法，遍历这8种跳法，得到结果。这是一个子集树的回溯问题，每一个step[i]都在[0, 7]之间。设棋盘大小为N * N，则时间复杂度为O(8^(N * N))，当N = 8时，算法很慢。
    优化：当每准备跳一步时，设准备跳到(x, y)点，计算(x, y)这一点可能往几个方向跳（即向前看两步），将这个数目设为(x, y)点的权值，将所     有可能的(x, y)按权值排序，从最小的开始，循环遍历所有可能的(x, y)，回溯求出结果。算法可以求出所有可能的马跳棋盘路径，算出一个可行      的结果很快，但当N = 8时，要计算所有可能的结果仍然很慢，原因是结果太多了。BackTrace()函数实现了这种思想。
*/
#include <iostream>
#include <time.h>
using namespace std;
#define X 8
#define Y 8

int chess[X][Y];

/**
 * 打印棋盘，棋盘中每个格子的数值就是遍历的次序
 */
void Print()
{
    int i, j;
    for(i = 0; i < X; i++)
    {
        for(j = 0; j < Y; j++)
        {
            cout<<chess[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

/**
 * 找到基于马当前在棋盘中的位置的(x,y)坐标的下一个可走的位置的坐标，如果成功找到则返回1，且直接修改原来位置的坐标；
 * 否则返回0
 * 成功找到的条件是该位置存在且还没有被马走过
 * @param x：当前马所在棋盘位置的x坐标
 * @param y：当前马所在棋盘位置的y坐标
 * @param count：不考虑边缘的情况，马在任意一位置的下一个位置都可能有八种情况，count就是对这八种情况进行判断
                 只要找到其中一种就返回1
 */
int NextXY(int *x, int *y, int count)
{
    switch(count)
    {
    case 1:
        if(*x + 2 <= X - 1 && *y - 1 >= 0 && chess[*x + 2][*y - 1] == 0)
        {
            *x += 2;
            *y -= 1;
            return 1;
        }
        break;
    case 2:
        if(*x + 2 <= X - 1 && *y + 1 <= Y - 1 && chess[*x + 2][*y + 1] == 0)
        {
            *x += 2;
            *y += 1;
            return 1;
        }
        break;
    case 3:
        if(*x + 1 <= X - 1 && *y - 2 >= 0 && chess[*x + 1][*y - 2] == 0)
        {
            *x += 1;
            *y -= 2;
            return 1;
        }
        break;
    case 4:
        if(*x + 1 <= X - 1 && *y + 2 <= Y - 1 && chess[*x + 1][*y + 2] == 0)
        {
            *x += 1;
            *y += 2;
            return 1;
        }
        break;
    case 5:
        if(*x - 2 >= 0 && *y - 1 >= 0 && chess[*x - 2][*y - 1] == 0)
        {
            *x -= 2;
            *y -= 1;
            return 1;
        }
        break;
    case 6:
        if(*x - 2 >= 0 && *y + 1 <= Y - 1 && chess[*x - 2][*y + 1] == 0)
        {
            *x -= 2;
            *y += 1;
            return 1;
        }
        break;
    case 7:
        if(*x - 1 >= 0 && *y - 2 >= 0 && chess[*x - 1][*y - 2] == 0)
        {
            *x -= 1;
            *y -= 2;
            return 1;
        }
        break;
    case 8:
        if(*x - 1 >= 0 && *y + 2 <= Y - 1 && chess[*x - 1][*y + 2] == 0)
        {
            *x -= 1;
            *y += 2;
            return 1;
        }
        break;
    default:
        break;
    }
    return 0;
}

/**
 * 深度优先遍历棋盘
 * @param x：当前马即将要走的位置的x坐标
 * @param y：当前马即将要走的位置的y坐标
 * @param step：当前马即将要走的这个位置是第step步，也就是说马已经走过了step-1个棋盘
 */
int TraversalChessBoard(int x, int y, int step)
{
    // 定义x1和y1变量保存马即将要走的这个位置的坐标
    int x1 = x, y1 = y;
    // flag保存是否有下一个可走的位置；count用于循环判断八种可走的位置
    int flag = 0, count = 1;

    // 标记该位置已经走过了
    chess[x][y] = step;
    // 如果此时step等于棋盘格子的个数，则说明已经把棋盘的每一个格子都走过一次了
    // 则打印棋盘输出走过的顺序；这也是下面的递归的返回条件吧
    if(step == X * Y)
    {
        Print();
        return 1;
    }

    // 如果还没有走完棋盘，则选择下一个位置，依次判断那八种可能的情况
    flag = NextXY(&x1, &y1, count);
    while(flag == 0 && count < 8)
    {
        count++;
        flag = NextXY(&x1, &y1, count);
    }

    // 在当前位置找到下一个可走的位置
    while(flag)
    {
        // 递归调用走向下一个位置，因为在NextXY函数中直接修改了当前位置的坐标，所以此时的x1和y1就表示下一个可走位置的坐标
        // 如果此时返回的是1，说明棋盘已经走完了，继续向上返回1
        if(TraversalChessBoard(x1, y1, step + 1))
        {
            return 1;
        }
        // 返回的不是1，则返回上一个位置，在上一个位置重新选择一个可走位置继续
        x1 = x;
        y1 = y;
        // 前count种可走位置的情况都判断过了，从count+1种情况继续判断
        count++;
        flag = NextXY(&x1, &y1, count);
        while(flag == 0 && count < 8)
        {
            count++;
            flag = NextXY(&x1, &y1, count);
        }
    }

    // 八种可能的情况都判断过了，还是没有下一个可走的位置了
    // 那么说明该次深度遍历失败，此种走法不行，则应该从当前位置回退到上一个位置
    // 所以重新标记当前位置还没有被走过
    if(0 == flag)
    {
        chess[x][y] = 0;
    }

    // 如果都没有可走的位置了，则返回0，代表继续向后回退
    return 0;
}

int main()
{
    int i, j;
    clock_t start, finish;
    start = clock();

    for(i = 0; i < X; i++)
    {
        for(j = 0; j < Y; j++)
        {
            chess[i][j] = 0;   // 初始化棋盘
        }
    }

    // 从坐标(2,0)开始走
    if(!TraversalChessBoard(2, 0, 1))
    {
        cout<<"遍历棋盘失败"<<endl;
    }
    finish = clock();
    cout<<"本次遍历共耗时："<<(double)(finish - start)/CLOCKS_PER_SEC<<"秒"<<endl;
    return 0;
}
