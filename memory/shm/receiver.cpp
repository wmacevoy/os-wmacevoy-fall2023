#include <iostream>
#include <strstream>
#include <string>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "message.h"

int main() {
    const char *name = "example";
    int shm_fd = -1;
    void *ptr;

    while ((shm_fd = shm_open(name, O_RDWR, 0666)) == -1) {
      std::cout << "waiting for shared memory" << std::endl;
      usleep(100000);      
    }
    
    // Memory map the shared memory object
    ptr = mmap(0, 1024, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // sender initializes this memory, so I just map it (!)

    volatile Message4k *message = (Message4k*) ptr;

    for (;;) {
      std::string content;
      while (!message->receive(RECEIVER_ID,content)) {
	if (message->state == Message4k::STATE_INVALID) goto break_outer;
	usleep(100000);
      }
      std::cout << RECEIVER_ID << " received " << content << std::endl;
    }

 break_outer:

    shm_unlink(name);

    return 0;
}
