#ifndef FILEOPER_H_INCLUDED
#define FILEOPER_H_INCLUDED

#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <errno.h>
#ifdef WIN32
#include <windows.h>
#include <direct.h>
#include "dirent_loc.h"
#else
#include <dirent.h>
#include <unistd.h>
#define PATH_MAX_STRING_SIZE 256
#endif
using namespace std;

static int mkdir_p(string dir, const mode_t mode){
#ifdef WIN32
  unsigned int pos = 0;
  do{
    //pos = dir.find_first_of("\\/", pos + 1);
    pos = dir.find_first_of("/", pos + 1);
    CreateDirectory(dir.substr(0, pos).c_str(), NULL);
  } while (pos != std::string::npos);
   return 0;
#else
  char tmp[PATH_MAX_STRING_SIZE];
    char *p = NULL;
    struct stat sb;
    size_t len;
    
    /* copy path */
    len = strnlen (dir.c_str(), PATH_MAX_STRING_SIZE);
    if (len == 0 || len == PATH_MAX_STRING_SIZE) {
        return -1;
    }
    memcpy (tmp, dir.c_str(), len);
    tmp[len] = '\0';

    /* remove trailing slash */
    if(tmp[len - 1] == '/') {
        tmp[len - 1] = '\0';
    }

    /* check if path exists and is a directory */
    if (stat (tmp, &sb) == 0) {
        if (S_ISDIR (sb.st_mode)) {
            return 0;
        }
    }
    
    /* recursive mkdir */
    for(p = tmp + 1; *p; p++) {
        if(*p == '/') {
            *p = 0;
            /* test path */
            if (stat(tmp, &sb) != 0) {
                /* path does not exist - create directory */
                if (mkdir(tmp, mode) < 0) {
                    return -1;
                }
            } else if (!S_ISDIR(sb.st_mode)) {
                /* not a directory */
                return -1;
            }
            *p = '/';
        }
    }
    /* test path */
    if (stat(tmp, &sb) != 0) {
        /* path does not exist - create directory */
        if (mkdir(tmp, mode) < 0) {
            return -1;
        }
    } else if (!S_ISDIR(sb.st_mode)) {
        /* not a directory */
        return -1;
    }
    return 0;
  #endif
}

static bool dirExists(const std::string &path) {
  struct stat info;
  if (stat(path.c_str(), &info) == 0 && info.st_mode & S_IFDIR) {
      return true;
  }
  return false;
}

static int getdir(string dir, vector<string> &files){
    DIR *dp;//創立資料夾指標
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL){
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while((dirp = readdir(dp)) != NULL){//如果dirent指標非空
        files.push_back(string(dirp->d_name));//將資料夾和檔案名放入vector
    }
    closedir(dp);//關閉資料夾指標
    return 0;
}
static void create_dir_ifnext( string& path ){
  if(!dirExists( path ))
    mkdir_p( path, 0775);
}
/*int main(void){
  vector<string> files;
  string path;
  cin >> path;
  getdir(path, files);
  for(int i = 0; i < files.size(); i++)
    cout << files[i] << endl;
  return 0;
}*/
#endif