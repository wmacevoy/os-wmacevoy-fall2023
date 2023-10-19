SHELL=/bin/bash
CXXFLAGS=-g -std=c++17

all: sender receiver
clean:
	/bin/rm -rf sender receiver

sender : sender.cpp message.h
	$(CXX) $(CXXFLAGS) -o $@ $<

receiver : receiver.cpp message.h
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: run
run: sender receiver
	@( set -x \
	  trap 'kill -KILL $$SENDER_PID ; kill -KILL $$RECEIVER_PID' HUP INT EXIT; \
	  ./sender & \
	  SENDER_PID=$$! ;\
	  ./receiver & \
	  RECEIVER_PID=$$! ;\
	  wait; \
	)
