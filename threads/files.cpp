#include <iostream>
#include <fstream>
#include <stdexcept>

int main() {
    std::ifstream file;

    file.open("example.txt");
    std::string content;
    std::getline(file, content);

    std::cout << "content: " << content << std::endl;

    // file is closed automatically by destructor
    return 0;
}
