#include <iostream>
#include <string>
#include <set>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

class NonASCIIFilenameSearcher {
public:
    NonASCIIFilenameSearcher(const std::string &directoryPath) : rootPath(directoryPath) {}

    void search() {
        std::set<ino_t> visited;
        doSearch(rootPath, visited);
    }

private:
    const std::string rootPath;

    bool hasVisitedInode(std::set<ino_t> &visited, ino_t inode) {
        return visited.find(inode) != visited.end();
    }

    void markVisitedInode(std::set<ino_t> &visited, ino_t inode) {
        visited.insert(inode);
    }

    void doSearch(const std::string &path, std::set<ino_t> &visited) {
        DIR *dir = opendir(path.c_str());
        if (dir == nullptr) {
            perror("opendir");
            return;
        }

        struct dirent *entry;
        while ((entry = readdir(dir))) {
            if (entry->d_name[0] == '.' && (entry->d_name[1] == '\0' || (entry->d_name[1] == '.' && entry->d_name[2] == '\0'))) {
                continue; // Skip "." and ".." directories
            }

            std::string fullpath = path + "/" + entry->d_name;

            struct stat st;
            if (lstat(fullpath.c_str(), &st) == -1) {
                perror("lstat");
                continue;
            }

            // Check if it's a symbolic link
            if (S_ISLNK(st.st_mode)) {
                // Handle symbolic link based on your requirements
                // For example, you can choose to follow it or skip it
            } else if (S_ISDIR(st.st_mode) && !hasVisitedInode(visited, st.st_ino)) {
                // It's a directory and not visited before, so recurse into it
                markVisitedInode(visited, st.st_ino);
                doSearch(fullpath, visited);
            } else if (containsNonASCII(entry->d_name)) {
                std::cout << fullpath << std::endl;
            }
        }

        closedir(dir);
    }

    bool containsNonASCII(const char *str) {
        while (*str) {
            if (*str < 0) {
                return true; // Found a non-ASCII character
            }
            str++;
        }
        return false; // All characters are ASCII
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <directory_path>" << std::endl;
        return 1;
    }

    std::string directoryPath = argv[1];

    NonASCIIFilenameSearcher searcher(directoryPath);
    searcher.search();

    return 0;
}
