#include <stdio.h>
#include "mysquare.h"

// linker makes a "stub"
/*
double square(double arg) {
    handle = dlopen("./libmysquare.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    // Get the square function from the library
    " square " = (double (*)(double)) dlsym(handle, "square");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }
}
*/

int main() {
    printf("Square of 7 is: %f\n", square(7.0));
    return 0;
}
