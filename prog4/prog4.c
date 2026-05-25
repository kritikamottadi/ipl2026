#include <stdio.h>
struct Flag{
    unsigned int a:1;
    unsigned  int b:1;
    unsigned int c:3;


};
int main(){
    struct Flag x;
    x.a=1;
    x.b=0;
    x.c=5;
    printf("values are: %d %d %d\n",x.a,x.b,x.c);
    printf("size of struct Flag: %d\n",sizeof(x));
    printf("size of unsigned int: %d\n",sizeof(unsigned int));
    return 0;
}