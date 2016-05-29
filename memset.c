#include <stdio.h>
#include <string.h>


int main()
{   
    char str1[10]; 

    strcpy(str1, "Hi there!");
    puts(str1);
    // fill str1 with 'a' but preserve string terminator at the end
    memset(str1,'a',(sizeof(str1)-1));
    puts(str1);
    return 0;
}
