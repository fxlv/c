#include <stdio.h>
// we need malloc()
#include <stdlib.h>
// we need sleep()
#include <unistd.h>
// we need assert()
#include <assert.h>
// we need getrlimit and friends
#include <sys/resource.h>

void main()
{

    struct rlimit limit; 

    getrlimit(RLIMIT_CORE, &limit);
    // limit.rlim_max and limit.rlim_cur are now available
    if ( limit.rlim_cur != RLIM_INFINITY )
    {
        printf("Please set core limit to 'unlimited' first.\n");
        printf("Current limits are: %d (current) and %d (max)\n", limit.rlim_cur, limit.rlim_max);
        exit(1);
    }

    int i;
    int memory_allocations[200];
    for(i=0; i<20; i++){
        printf("Let's leak some memory\n");
        char *leaky = "SOmething will leak here\n";
        // if the allocation is to small then the system will instead use brk() to allocate larger regions
        // instead of calling malloc for every small pointer
        char *mem = malloc(sizeof(leaky)*4096*4096);
        // if we want to make a leak mean something we have to write something into the memory
        // otherwise we are simply storing the pointer reference instead of the actual string
        mem = strdup(leaky);
        mem = leaky;
        printf("Allocated (%i): %p\n",i, mem);
        //int *memory_allocations[i] = malloc(10);
        assert(mem != NULL);
        usleep(100000);
    }
}
