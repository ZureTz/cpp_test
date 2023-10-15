#include <stdio.h>
#include <stdlib.h>

typedef struct TEST
{
    int *array;
    int *(*append)(int *, int, int);
    int *(*copy_expand)(int *, int);
} test;

int *test_copy_and_expand(int *src, int length);
int *test_append(int *vec, int length, int num);
void test_initialization(test *tst);

int main(int argc, char const *argv[])
{
    test tst;
    test_initialization(&tst);

    const int length = 6;
    tst.array = (int *)calloc(sizeof(int), length);
    for (int i = 0; i < length; i++)
    {
        tst.array[i] = i + 1;
    }
    for (int i = 0; i < 10; i++)
    {
        tst.array = tst.append(tst.array, length + i, i);
    }
    
    for (int i = 0; i < length + 10; i++)
    {
        printf("%d\n", tst.array[i]);
    }

    free(tst.array);
    return 0;
}

int *test_copy_and_expand(int *src, int length)
{
    int *dest = (int *)calloc(sizeof(int), length + 1);
    for (int i = 0; i < length; i++)
    {
        dest[i] = src[i];
    }
    dest[length] = 0;
    return dest;
}

int *test_append(int *vec, int length, int num)
{
    int *new_vec = test_copy_and_expand(vec, length);
    new_vec[length] = num;

    free(vec);
    return new_vec;
}

void test_initialization(test *tst)
{
    tst->append = test_append;
    tst->copy_expand = test_copy_and_expand;
}