#include <stdio.h>

void main()
{
    int i;
    int array1[3];
    for (i = 0; i < 6; i++)
    {
        printf("%d (size: %d)\n", i, sizeof(i));
        array1[i] = i;
    }
}
