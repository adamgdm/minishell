#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    char *str = malloc(sizeof(char) * 10);
    printf("%p\n", str);
    str[0] = 'a';
    free(str);

    str = malloc(sizeof(char) * 10);
    printf("%p\n", str);
    str[0] = 'b';
    free(str);

    str = malloc(sizeof(char) * 10);
    printf("%p\n", str);
    str[0] = 'c';
    free(str);

    printf("%c\n", str[0]);    
}