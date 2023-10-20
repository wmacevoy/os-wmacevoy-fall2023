#include <iostream>
#include <sstream>
#include <string>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "message.h"

int main() {
    const char *name = "example";
    
    // Create a new shared memory object
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Configure the size of the shared memory object
    ftruncate(shm_fd, sizeof(Message4k));
    // Memory map the shared memory object
    void *ptr = mmap(0, sizeof(Message4k), PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // build a Message4k object at this location
    volatile Message4k *message = new (ptr) Message4k();

    for (int i=0; i<10; ++i) {
      std::ostringstream oss;
      oss << "message #" << i << " from sender " << SENDER_ID;
      std::string content=oss.str();
      while (!message->send(RECEIVER_ID,content)) {
	usleep(100000);
      }
      std::cout << "sent '" << content << "' to " << RECEIVER_ID << std::endl;
    }

    while (message->state != Message4k::STATE_RECEIVED) {
      usleep(100000);
    }
    std::cout << "done" << std::endl;
    // not delete - just the destructor
    message->~Message();
    return 0;
}

