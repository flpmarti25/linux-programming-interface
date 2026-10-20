#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "header/error_functions.h"

void freeAll(void *__ptr,int count);

int main(int argc, char *argv[])
{
   
    int opt,sizefd = 0;
    int *fdi = (int *)malloc(argc * sizeof(int));
    int oflag = O_CREAT | O_WRONLY | O_TRUNC ;
    int count = 1;


    while((opt  = getopt(argc,argv,"a")) != -1  ){
        switch (opt){
            case 'a': 
            oflag = O_CREAT | O_WRONLY | O_APPEND;
            break;
        }                
    }


    while(count < argc){
        if(argv[count][0] == 45){
            count++;
            continue;
        }
        char filename[1024] = "files/";
        int fdc = open(strcat(filename,argv[count]), oflag , 0644); 
        if(fdc < 0)
            errMsg("open");
        fdi[sizefd] = fdc;
        sizefd++;
        count++;
    }


    char textline[1024];

     while(fgets(textline,sizeof(textline),stdin) != NULL){
        int *read_files = fdi;
        for (int i = 0; i < sizefd; i++)
        {
            if(write(*read_files,textline,strlen(textline)) < 0)
                errMsg("write %d",*read_files);
            read_files++;

        }
     }

    freeAll(fdi,sizefd);

    return 0;
}

void freeAll(void *__ptr,int sizefd){
    int *read_files = __ptr;

    for (int i = 0; i < sizefd; i++){
        printf("closing  %d\n",*read_files);
        close(*read_files);
        read_files++;
    }
    free(__ptr);
}

