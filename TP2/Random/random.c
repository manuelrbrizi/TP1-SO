#include <time.h>

int get_random(void){
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    return spec.tv_nsec%100;
}