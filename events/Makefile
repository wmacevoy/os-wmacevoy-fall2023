.PHONY: build
build:
	cmake -S . -B build && cmake --build build
.PHONY: test
test : build
	cd build && ctest
.PHONY: clean
clean :
	/bin/rm -rf build
