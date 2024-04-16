
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

void PasingFolder(char buffer[201],char currentFile[201],int fd)
{
    DIR *Directory;
    Directory = opendir(buffer);
   // printf("%s\n",buffer);
    if(Directory!=NULL)
        {
            //printf("We read and initialised a directory %s!!!\n",currentFile);
            struct dirent *FileFromFolder;
            while((FileFromFolder=readdir(Directory))!=NULL)
            {
                if(strcmp(FileFromFolder->d_name,".")!=0 )
                    if(strcmp(FileFromFolder->d_name,"..")!=0 )
                {
                char AuxBuffer[201]="";
                strcpy(AuxBuffer,buffer);
                char current[201]="";
                strcat(current,FileFromFolder->d_name);
                strcat(AuxBuffer,"/");
                strcat(AuxBuffer,current);
                
                //printf("Address:%s\n",AuxBuffer);
                
                struct stat st;

                if (lstat(AuxBuffer, &st) == 0) 
                {
                    if (S_ISDIR(st.st_mode)) 
                        {
                        
                        PasingFolder(AuxBuffer,current,fd); // on current it is what we want to open next , and on AuxBuffer the adress
                        }
                        else
                        {
                           // printf("Address:%s\n",AuxBuffer);
                            write(fd,AuxBuffer,strlen(AuxBuffer));
                            write(fd,"\n",1);

                        }
                }
                
                }
            }

        }

        else
        printf("Tough luck you failed :()\n");


        closedir(Directory);
}




char * CreatePath(char outputPath[201],char DirectoryName[201]) //creates the adress to the snapshot folder and what the name of the new Snapshot should be
{
 
    char *DirectoryPath = (char *)malloc(201 * sizeof(char));
    strcpy(DirectoryPath, outputPath);

    strcat(DirectoryPath,"/");
    strcat(DirectoryPath,DirectoryName);
   
    strcat(DirectoryPath,".txt");
    return DirectoryPath;
}

int FileToWriteIn(char outputPath[201],char DirectoryName[201]) // i create a file directory to write in it .
{
    char *filePath = CreatePath(outputPath, DirectoryName);
   // printf("File path: %s\n", filePath); // Debug print
    
    int fd = open(CreatePath(outputPath,DirectoryName), O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }
    return fd;
}



int main(int argc,char* argv[]){
    printf("We will solve this problem!\n");
    
     
   // printf("\nargv[2]=%s",argv[2]);
   // printf("\nargv[3]=%s",argv[4]);



    pid_t pid;
    for(int i=3;i<argc;i++)
    {
        pid=fork();

        if (pid == 0) {
            // This is the child process
            int OutputFile=FileToWriteIn(argv[2],argv[i]);
            char buffered[201]="";
            strcat(buffered,argv[i]);
            PasingFolder(buffered,argv[i],OutputFile);
            
            printf("Child process %d - with PID %d and exit code %d\n", i-2,getpid(),pid);
            return 0; // Child process exits after computation
        } else if (pid < 0) {
            // Error occurred
            fprintf(stderr, "Fork failed\n");
            return 1;
        }


    }

    for (int i = 3; i < argc; ++i) {
        wait(NULL);
    }

    
    
}

