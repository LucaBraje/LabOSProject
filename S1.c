//S1
//Description: The proposed project combines functionalities for monitoring a directory to manage differences 
//between two captures (snapshots) of it. 
//The user will be able to observe and intervene in the changes in the monitored directory.
//Directory Monitoring:
//The user can specify the directory to be monitored as an argument in the command line,
// and the program will track changes occurring in it and its subdirectories, parsing 
// recursively each entry from the directory.
//With each run of the program, the snapshot of the directory will be updated, storing the metadata of each entry. 


//what we need to do is pass the directory recursifly and for each entry 
//create a program and give the file as 

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>


void PasingFolder(char buffer[201],char currentFile[201],int fd)
{
    DIR *Directory;
    Directory = opendir(buffer);
    if(Directory!=NULL)
        {
            printf("We read and initialised a directory %s!!!\n",currentFile);
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
                            printf("Address:%s\n",AuxBuffer);
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

int FindSnapshotNumber()
{
    FILE *SaveFiles;
    // /home/brajeluca/Desktop/SnapSaves/ this is the place where I will save snapshots
    DIR *Directory;
    char DirectoryPath[201]="/home/brajeluca/Desktop/SnapSaves/";
    Directory = opendir(DirectoryPath);
    if(Directory==NULL)
    printf("YOU SUCK LOSER"); 
    else
    printf("It worked!%s\n",DirectoryPath);
    //now here i want to do something similar and read files from there and consider all are true and see how many files named snapshotNRx i have and add another then return the number + 1 of our current file to be able to integrate a new thingy
    int i=0;
    struct dirent *FileFromFolder;
    while((FileFromFolder=readdir(Directory))!=NULL)
            {
                if(strstr(FileFromFolder->d_name,"SnapShot"))
                i++;
            }
    
    return i;

}




int main(int argc,char* argv[]){
    printf("We will solve this problem!\n");
    if(argc!=2)
    {
        printf("ERROR YOU NEED TO SPECIFY A FILEPATH!\n");
    }
    
    char buffered[201]="";
   strcat(buffered,argv[1]);
    
    
    int VersionNR= FindSnapshotNumber();
    char SnapShot[]="SnapShot_";
    char VersionToString[20];
    sprintf(VersionToString,"%d",VersionNR);
    strcat(SnapShot,VersionToString);



    char DirectoryPath[201]="/home/brajeluca/Desktop/SnapSaves/";
    strcat(DirectoryPath,SnapShot);
    strcat(DirectoryPath,".txt");
    printf("%s",DirectoryPath);

    int fd = open(DirectoryPath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    

    PasingFolder(buffered,argv[1],fd);
    

}