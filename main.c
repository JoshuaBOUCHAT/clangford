#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <omp.h>

#define u64 __uint64_t
#define u8 unsigned char

#define N 15
#define SIZE (2 * N)
#define ITER ((N) >> 1)
#define STACK_SIZE 128

inline u64 get_base(u8 val)
{
    return (1 << (val + 1)) | 1;
}

int explore(u64 to_explore)
{
    int sum = 0;
    int stack_size = 1;
    u64 vals[STACK_SIZE];
    u8 cnts[STACK_SIZE];
    vals[0] = to_explore;
    cnts[0] = N - 2;
    while (stack_size)
    {
        stack_size--;
        u64 val = vals[stack_size];
        u8 cnt = cnts[stack_size];
        u64 base = get_base(cnt);
        for (int i = 0; i < (SIZE - 1 - cnt); i++)
        {

            u64 test = base << i;
            if ((test & val) == 0)
            {

                if (cnt != 1)
                {
                    vals[stack_size] = val | test;
                    cnts[stack_size] = cnt - 1;
                    stack_size++;
                }
                else
                    sum++;
            }
        }
    }
    return sum;
}
u64 *generate_solutions(u64 *stack)
{
    u64 base0 = get_base(N);
    u64 base1 = get_base(N - 1);

    for (int i = 0; i < (ITER - (N & 1 ^ 1)); i++)
    {
        u64 test0 = base0 << i;
        for (int j = 0; j < N; j++)
        {
            u64 test1 = base1 << j;
            if ((test0 & test1) == 0)
            {
                *stack++ = test0 | test1;
            }
        }
    }
    if ((N & 1) == 0)
    {
        u
    }
}

int main()
{
    int params[ITER];
    u64 base = get_base(N);
#pragma omp parallel for
    for (int i = 0; i < ITER; i++)
    {
        params[i] = explore(base << i);
    }
    if ((N & 1) == 0)
    {
        params[ITER - 1] /= 2;
    }
    int sum = 0;
    for (int i = 0; i < ITER; i++)
    {
        sum += params[i];
    }
    printf("Computed: %d\n", sum);
}