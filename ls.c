#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: filename and argument (-n or -i) required\n");
        exit(1);
    }

    DIR *dirPtr;
    struct dirent *entryPtr;
    struct stat statBuf;
    char permissions[11];
    permissions[10] = '\0';

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
                permissions[0] = '-';
            }else if (S_ISDIR(statBuf.st_mode)){
                permissions[0] = 'd';
            }else if (S_ISLNK(statBuf.st_mode)){
                permissions[0] = 'l';
            }
            if(S_IRUSR & statBuf.st_mode) {
                permissions[1] = 'r';
            }
            else {
                permissions[1] = '-';
            }
            if(S_IWUSR & statBuf.st_mode) {
                permissions[2] = 'w';
            }
            else {
                permissions[2] = '-';
            }
            if(S_IXUSR & statBuf.st_mode) {
                permissions[3] = 'x';
            }
            else {
                permissions[3] = '-';
            }
            if(S_IRGRP & statBuf.st_mode) {
                permissions[4] = 'r';
            }
            else {
                permissions[4] = '-';
            }
            if(S_IWGRP & statBuf.st_mode) {
                permissions[5] = 'w';
            }
            else {
                permissions[5] = '-';
            }
            if(S_IXGRP & statBuf.st_mode) {
                permissions[6] = 'x';
            }
            else {
                permissions[6] = '-';
            }
            if(S_IROTH & statBuf.st_mode) {
                permissions[7] = 'r';
            }
            else {
                permissions[7] = '-';
            }
            if(S_IWOTH & statBuf.st_mode) {
                permissions[8] = 'w';
            }
            else {
                permissions[8] = '-';
            }
            if(S_IXOTH & statBuf.st_mode) {
                permissions[9] = 'x';
            }
            else {
                permissions[9] = '-';
            }
            printf("%-12s %-d %-d %-d %-10d %-25s %s", permissions, statBuf.st_nlink, statBuf.st_uid, statBuf.st_gid, statBuf.st_size, entryPtr->d_name, ctime(&statBuf.st_atime));
        }
        else if (strcmp(argv[1], "-l") == 0) {
            if (S_ISREG(statBuf.st_mode)){
                permissions[0] = '-';
            }else if (S_ISDIR(statBuf.st_mode)){
                permissions[0] = 'd';
            }else if (S_ISLNK(statBuf.st_mode)){
                permissions[0] = 'l';
            }
            if(S_IRUSR & statBuf.st_mode) {
                permissions[1] = 'r';
            }
            else {
                permissions[1] = '-';
            }
            if(S_IWUSR & statBuf.st_mode) {
                permissions[2] = 'w';
            }
            else {
                permissions[2] = '-';
            }
            if(S_IXUSR & statBuf.st_mode) {
                permissions[3] = 'x';
            }
            else {
                permissions[3] = '-';
            }
            if(S_IRGRP & statBuf.st_mode) {
                permissions[4] = 'r';
            }
            else {
                permissions[4] = '-';
            }
            if(S_IWGRP & statBuf.st_mode) {
                permissions[5] = 'w';
            }
            else {
                permissions[5] = '-';
            }
            if(S_IXGRP & statBuf.st_mode) {
                permissions[6] = 'x';
            }
            else {
                permissions[6] = '-';
            }
            if(S_IROTH & statBuf.st_mode) {
                permissions[7] = 'r';
            }
            else {
                permissions[7] = '-';
            }
            if(S_IWOTH & statBuf.st_mode) {
                permissions[8] = 'w';
            }
            else {
                permissions[8] = '-';
            }
            if(S_IXOTH & statBuf.st_mode) {
                permissions[9] = 'x';
            }
            else {
                permissions[9] = '-';
            }
            struct passwd *pw = getpwuid(statBuf.st_uid);
            struct group *gw = getgrgid(statBuf.st_gid);

            printf("%-12s %-d %-s %-s %-10d %-25s %s", permissions, statBuf.st_nlink, pw->pw_name, gw->gr_name, statBuf.st_size, entryPtr->d_name, ctime(&statBuf.st_atime));
        }

    }
    closedir(dirPtr);
    printf("\n");
    return 0;
}
