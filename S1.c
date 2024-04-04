//S1
//Description: The proposed project combines functionalities for monitoring a directory to manage differences 
//between two captures (snapshots) of it. 
//The user will be able to observe and intervene in the changes in the monitored directory.
//Directory Monitoring:
//The user can specify the directory to be monitored as an argument in the command line,
// and the program will track changes occurring in it and its subdirectories, parsing 
// recursively each entry from the directory.
//With each run of the program, the snapshot of the directory will be updated, storing the metadata of each entry. 


//S2
/*
-----This is the second part of the project----

The functionality of the program will be updated to allow it to receive an unspecified number of arguments (directories) 
in the command line. The logic for capturing metadata will now apply to all received arguments, meaning the program will 
update snapshots for all directories specified by the user.

For each entry of each directory provided as an argument, 
the user will be able to compare the previous snapshot of the specified directory with the current one. 
If there are differences between the two snapshots, the old snapshot will be updated with the new information 
from the current snapshot.

The functionality of the code will be expanded so that the program receives an additional argument, 
representing the output directory where all snapshots of entries from the specified directories in the command line 
will be stored. This output directory will be specified using the `-o` option. For example, the command to run the 
program will be: `./program_exe -o output input1 input2 ...`. 
*/


// create x different snapshots and keep their names
//we will aslo need a compare between the 2 files and tthings
//i do not understand this comparasion between files tbh


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

int FindSnapshotNumber(char outputPath[201]) //searches in the snapshot folder and counts how many snapshots it finds , to find the new number our snapshot will be
{
    FILE *SaveFiles;
    // /home/brajeluca/Desktop/SnapSaves/ this is the place where I will save snapshots
    DIR *Directory;
    char DirectoryPath[201]="";
    strcpy(DirectoryPath,outputPath);
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

char * CreatePath(char outputPath[201],char DirectoryName[201]) //creates the adress to the snapshot folder and what the name of the new Snapshot should be
{
    int VersionNR= FindSnapshotNumber(outputPath); //we search to see if we found any snapshots in this snapshot file
    char SnapShot[]="SnapShot_";    //now we might
    char VersionToString[20];
    sprintf(VersionToString,"%d",VersionNR);
    strcat(SnapShot,VersionToString);

    char *DirectoryPath = (char *)malloc(201 * sizeof(char));
    strcpy(DirectoryPath, outputPath);
    strcat(DirectoryPath,SnapShot);
    strcat(DirectoryPath,".txt");

    return DirectoryPath;
}

int FileToWriteIn(char outputPath[201],char DirectoryName[201]) // i create a file directory to write in it .
{
    int fd = open(CreatePath(outputPath,DirectoryName), O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return fd;
}

int main(int argc,char* argv[]){
    printf("We will solve this problem!\n");
    if(argc>2)
    {
        printf("ERROR YOU NEED TO SPECIFY A FILEPATH!\n");
    }
    //`./program_exe -o output input1 input2 ...`.
    //argv[1] will be the -o
    //argv[2] will be the output file          
    //argv[3+] will be the directories you want to create a path for;
    char buffered[201]="";
    strcat(buffered,argv[1]);
    int OutputFile=FileToWriteIn(argv[2],argv[3]);

    PasingFolder(buffered,argv[1],OutputFile);
    

}

