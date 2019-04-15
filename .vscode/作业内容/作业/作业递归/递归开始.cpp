#include <stdio.h>
#include <conio.h>
#include <time.h>
#define N 4
#define MAX (N*N)

typedef struct square
{
    int i[MAX+1];
    int remain[MAX+1];
    int totalCount, resultCount, partResultCount;
    int t_start;
} JGG;//创建结构体JGG类型 

int exam(JGG *ps);
void print(JGG s);
void    msquare( JGG *ps, int no); 

int main(int argc, char *argv[])
{
    JGG s;
	//开始初始化s的相应内容 
    s.t_start = clock();
    s.resultCount = s.totalCount = s.partResultCount = 0;

    int     i;

    for(i=1;i<=MAX;i++) {
        s.i[i] = 0;
        s.remain[i] = 1;
    }
	//初始化结束 
    msquare(&s, 0);

    _getch();//取消回显 
}

void    msquare( JGG *ps, int no)
{
    int     i;

	for(i=1;i<=MAX;i++) {
        if ( ps->remain[i]==0 )
            continue;
        ps->i[no] = i;
        ps->remain[i] = 0;//开始对九宫格元素进行赋值，并标记remain[i] 
        if (no==MAX-1) {
            ps->totalCount ++;
            if (exam(ps)) {
                ps->resultCount ++;
                print(*ps);
            }
        } else
        {
            msquare( ps, no + 1);
        }//循环完一组，将i[]和remain[]复原 
        ps->remain[i] = 1;
        ps->i[no] = 0;
    }
}

void print(JGG s)
{
    int j;

    printf("%d\t[ ", s.resultCount);
    for (j = 0; j < MAX; j++)
        printf("%d ", s.i[j]);
    printf("]\t\t[%d] [%d] \ttime:[%ld]\r\n", s.totalCount, s.partResultCount, clock() - s.t_start);
}
//先分别求出对角线，行，列的和，然后检查是否符合要求 
int exam(JGG *ps)
{
    int j, k, flag, n;
    int sum1, sum2, rsum[N], csum[N], aver;

    aver = (MAX+1)*MAX/(N*2);

    for (j = 0; j < N; j++)
    {
        csum[j] = 0;
        rsum[j] = 0;
    }
    sum1 = 0;
    sum2 = 0;
	//开始求和(行和，列和，对角线和) 
    for (j = 0; j < N; j++)
    {
        for (k = 0; k < N; k++)
        {
            csum[k] += ps->i[j * N + k]; 
            rsum[j] += ps->i[j * N + k]; 
        }
        sum1 += ps->i[j * N + j];     
        sum2 += ps->i[j * N + N-1 - j]; 
    }
	//求和结束，开始检查 
    if (sum1 != aver || aver != sum2)
        return 0;

    (ps->partResultCount)++;

    flag = 1;
    for (j = 0; j < N; j++)
    {
        if (csum[j] != aver || rsum[j] != aver)
        {
            flag = 0;
            break;
        }
    }
    return flag;
}
//检查结束，如果符合要求就返回1，不符合要求就返回0 