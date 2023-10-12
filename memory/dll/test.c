#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle;
    double (*square)(double);
    char *error;

    // Load the shared library
    handle = dlopen("./libmysquare.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    // Get the square function from the library
    square = (double (*)(double)) dlsym(handle, "square");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }

    // Use the square function
    printf("Square of 7 is: %f\n", square(7.0));

    // Close the shared library
    dlclose(handle);
    return 0;
}
