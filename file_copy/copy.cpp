#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
using namespace std;
#define len 1024
bool file_copy(string pathname, string copypath){
    char buf[len];
    int err = 1;
    int fdr = open(pathname.c_str(), O_RDONLY, S_IRUSR|S_IWUSR);
    if(fdr == -1){
        cout<<"read file failure"<<endl;
        return false;
    }
    cout<<copypath<<endl;
    int fdn = open(copypath.c_str(), O_WRONLY|O_CREAT, S_IWUSR|S_IRUSR);
    if(fdn == -1){
        cout<<"write file failure"<<endl;
        return false;
    }
    while(err > 0){
        memset(buf, 0, sizeof(buf)-1);
        err = read(fdr, buf, sizeof(buf));
        cout<<"err:"<<err<<endl;
     //   lseek(fdn, 0, SEEK_END);
        write(fdn, buf, strlen(buf));
    }
    close(fdr);
    close(fdn);
    return true;
}
bool dir_copy(string copypath){
    string curpath = copypath;
    cout<<"curpath"<<curpath<<endl;
    if(mkdir(curpath.c_str(), 0777) == -1)
        return false;
    return true;
}
bool mycopy(string path, string copypath){
    struct dirent* fd;
    struct stat buf;
    string curpath;
    string curcopypath;
    if(chdir(path.c_str()))
        exit(EXIT_FAILURE);
    DIR *fddir = opendir(path.c_str());
    while((fd = readdir(fddir)) != NULL){
        curpath = path+"/"+fd->d_name;
        cout<<curpath.c_str()<<endl;
        getchar();
        if(strcmp(fd->d_name, ".") != 0 && strcmp(fd->d_name, "..") != 0){
            if(stat(curpath.c_str(), &buf) == -1){
                cout<<"dir open fail"<<endl;
                exit(EXIT_FAILURE);
            }
            curcopypath = copypath+"/"+fd->d_name;
            if(S_ISDIR(buf.st_mode)){
                dir_copy(curcopypath);
                mycopy(curpath, curcopypath);
            }else{
                file_copy(curpath, curcopypath);
            }
        }
    }
    closedir(fddir);
    return true;       
}
int main(int argc, char **argv){
    bool a;
    if(argc != 3){
        perror("Usage: argc isn't two\n");
        exit(EXIT_FAILURE);
    }
    if(mycopy(argv[1], argv[2]))
        cout<<"copy success : "<<argv[1]<<"to"<<argv[2]<<endl;
    else
        cout<<"copy fail : "<<endl;
    return 0;
}
