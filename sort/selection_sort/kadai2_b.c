#include <stdio.h>

void swap(int *x, int *y)
{
    int tempX = *x;
    *x = *y;
    *y = tempX;
}

void selection_sort(int D[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int max = D[0];
        int max_index = 0;
        for (int j = 1; j <= i; j++)
        {
            if (D[j] >= max)
            {
                max = D[j];
                max_index = j;
            }
        }
        swap(&D[max_index], &D[i]);
        for (int k = 0; k < n; k++)
        {
            printf("\x1b[49m"); /* 背景色をデフォルトに戻す */
            if (k == max_index || k == i)
                printf("\x1b[42m"); /* 背景色を緑に */
            printf("%d ", D[k]);
            printf("\x1b[49m"); /* 背景色をデフォルトに戻す */
        }
        printf("\n");
    }
}

int main()
{
    int data[10];
    printf("整数を10個入力してください\n");
    for (int i = 0; i < 10; i++)
    {
        printf("x[ %d ] = ", i);
        scanf("%d", &data[i]);
    }

    printf("\nソート開始:\n");
    for (int k = 0; k < 10; k++)
    {
        printf("%d ", data[k]);
    }
    printf("\n");

    selection_sort(data, 10);
    printf("昇順にソートします\n");
    for (int j = 0; j < 10; j++)
    {
        printf("data[%d] = %d\n", j, data[j]);
    }
    return 0;
}