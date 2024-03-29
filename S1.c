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



int main(int argc,char* argv[]){
    printf("We will solve this problem!\n");
    if(argc!=2)
    {
        printf("ERROR YOU NEED TO SPECIFY A FILEPATH!\n");
    }
    
    DIR *Directory;
    Directory=opendir(argv[1]);
    char buffer[201]="";
    strcat(buffer,argv[1]);
    
    if(Directory!=NULL)
    {
        printf("We read and initialised a directory %s!!!\n",buffer);
        struct dirent *FileFromFolder;
        while((FileFromFolder=readdir(Directory))!=NULL)
        {
            if(strcmp(FileFromFolder->d_name,".")!=0 )
                if(strcmp(FileFromFolder->d_name,"..")!=0 )
            {
            char AuxBuffer[200];
            strcpy(AuxBuffer,buffer);
            char current[200]="";
            strcat(current,FileFromFolder->d_name);
            strcat(AuxBuffer,"/");
            strcat(AuxBuffer,current);
            printf("Address:%s\n",AuxBuffer);
            
            struct stat st;

            if (lstat(AuxBuffer, &st) == 0) 
            {
                if (S_ISDIR(st.st_mode)) 
                    {
                    printf("it is a directory\n");
                    }
            }
            
            //printf("^\n|\n-is a directory.");

            //printf("%s\n",FileFromFolder->d_name);
            }
        }

    }

    else
    printf("Tough luck you failed :()\n");


    closedir(Directory);

}