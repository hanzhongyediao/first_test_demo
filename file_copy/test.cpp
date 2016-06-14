#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;
int main(int argc, char *argv[]){
    int fd;
    struct stat buf;
    if(stat("/home/tom-zx/myfile", &buf) == 0){
        if(S_ISDIR(buf.st_mode))
            cout<<"this is a dir"<<endl;
        if(S_ISREG(buf.st_mode))
            cout<<"this is a file"<<endl;
    }
    if((fd = open("/home/tom-zx/myfile/", O_WRONLY, S_IRUSR|S_IWUSR)) == -1){
        if(errno == EISDIR)
            cout<<"the precess is a dir"<<endl;
        else
            cout<<"other question"<<endl;
    }
    return 0;
}