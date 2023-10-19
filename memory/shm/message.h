#pragma once

#include <iostream>
#include <stdint.h>
#include <array>

template <uint64_t SIZE>
struct Message {
  enum State {STATE_INIT,STATE_READY,STATE_RECEIVED,STATE_INVALID};
  State state;
  uint32_t to;
  uint32_t length;
  uint8_t data[SIZE];
  
  Message() : state(STATE_INIT), to(0), length(0)
  {
    memset(data,0,SIZE);
  }
  ~Message() {
    state = STATE_INVALID;
  }

  bool send(uint32_t _to, const std::string &content) volatile {
    std::size_t _length = content.length();
    if ((state == STATE_INIT || state == STATE_RECEIVED) && _length <= SIZE) {
      to=_to;
      length=_length;
      memcpy((void*) &data[0],&content[0],_length);
      state = STATE_READY;
      return true;
    }
    return false;
  }

  bool receive(uint32_t recipient, std::string &content) volatile {
    if (state == STATE_READY && to == recipient) {
      content.resize(length);
      memcpy(&content[0],(void*) &data[0],length);
      state = STATE_RECEIVED;
      return true;
    }
    return false;
  }
};

typedef Message<4096> Message4k;
const int SENDER_ID  = 1;
const int RECEIVER_ID  = 2;
