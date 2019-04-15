#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc < 3) {
        	printf("Usage: filename and argument (-n or -i) required\n");
        	exit(1);
    	}

    	DIR *dirPtr;
    	struct dirent *entryPtr;
    	struct stat statBuf;
	char temp[20];

    	dirPtr = opendir(argv[2]);
    	while((entryPtr = readdir(dirPtr))) {
	    	if (stat(entryPtr->d_name, &statBuf) < 0) {
            		perror("huh?  there is ");
            		exit(1);
        	}
		if (strcmp(argv[1], "-i") == 0){
			printf("%ld %s   ",
				statBuf.st_ino,
				entryPtr->d_name);
		}
		else if (strcmp(argv[1], "-n") == 0) {
			if (S_ISREG(statBuf.st_mode)){
				temp[0] = "-";
			}else if (S_ISDIR(statBuf.st_mode)){
				temp[0] = "d";
			}else if (S_ISLNK(statBuf.st_mode)){
				temp[0] = "l";
			}
			/*
			if (S_IRUSR(statBuf.st_mode)){
				temp[1] = "r";
			}
			*/
			printf("%s", temp); 
		}
	}	
    	closedir(dirPtr);
	printf("\n");
    	return 0;
}
