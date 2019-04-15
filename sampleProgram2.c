#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: filename required\n");
        exit(1);
    }

    DIR *dirPtr;
    struct dirent *entryPtr;
    struct stat statBuf;
    //get options? maybe? idk
    //man 3 getopt

    dirPtr = opendir(argv[1]);
    while((entryPtr = readdir(dirPtr))) {
        if (stat(entryPtr->d_name, &statBuf) < 0) {
            perror("huh?  there is ");
            exit(1);
        }
        struct passwd *pw = getpwuid(statBuf.st_uid);
        
        printf("%-15s %-10s %-10d\n", 
                entryPtr->d_name, 
                pw->pw_name,
                statBuf.st_size
                );
    }

    closedir(dirPtr);
    return 0;
}
