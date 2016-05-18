#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage()
{
    printf("Useless usage message\n");
}

void do_stuff(char *target)
{
    printf("Doing stuff to %s\n",target);
}

int main(int argc, char *argv[])
{
    int arg;
    extern char *optarg;
    char *target;
    while(( arg = getopt(argc, argv, "t:")) != -1 ){
        switch(arg){
            case 't':
                target = optarg;
                break;
            default:
                usage();
        }
    }
    printf("Arguments count: %d\n",argc);
    if(target != NULL)
    {
        do_stuff(target);
    }

return 0;
}


