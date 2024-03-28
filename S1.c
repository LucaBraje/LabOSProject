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


int main(int argc,char* argv[]){
    printf("We will solve this problem!\n");
    if(argc!=2)
    {
        printf("ERROR YOU NEED TO SPECIFY A FILEPATH!\n");
    }
    
    DIR *Directory;
    Directory=opendir(argv[1]);
    
    if(Directory!=NULL)
    {
        printf("We read and initialised a directory !!!\n");
        struct dirent *FileFromFolder;
        while((FileFromFolder=readdir(Directory))!=NULL)
        {
            printf("%s",FileFromFolder->d_name);
  
        }

    }

    else
    printf("Tough luck you failed :()\n");


    closedir(Directory);

}