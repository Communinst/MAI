#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>



typedef enum 
{
    OK = 0,

    INVALID_ARGC,

    BAD_ALLOC,

    NO_DIR,

    FILE_ERROR,

} EXIT_CODE;



void EC_handle (EXIT_CODE response);


EXIT_CODE input_handle (int argc, const char **argv);


EXIT_CODE processing (int argc, const char **argv);


EXIT_CODE list_files (const char *dir);





int main()//int argc, const char **argv) 
{

    int argc = 2;

    const char *argv[] = {"h", "/home/communist/moron"};

    EC_handle(input_handle(argc, argv));
    
    return 0;
}


void EC_handle (EXIT_CODE response)
{

    switch (response)
    {
        case OK:
            printf("Success!\n");
            break;

        case INVALID_ARGC:
            printf("Invalid amount of arguments!\n");
            break;
        
        case BAD_ALLOC:
            printf("Memory fault!\n");
            break;

        case NO_DIR:
            printf("Entered directory's missing!\n");
            break;

        case FILE_ERROR:
            printf("File error.\n");
            break;

    }
}


EXIT_CODE input_handle (int argc, const char **argv)
{
    if (argc < 2)
    {
        return INVALID_ARGC;
    }    

    return processing(argc - 1, (argv + 1));

}


EXIT_CODE processing (int argc, const char **argv)
{

    EXIT_CODE sup = OK;

    for (int i = 0; i < argc; i++)
    {
        printf("\t\t%s directory content:\n", argv[i]);
        sup = list_files(argv[i]);

        if (sup)
        {
            printf("%s directory: ", argv[i]);
            EC_handle(sup);
        }

    }

    return OK;

}


EXIT_CODE list_files (const char *dir_name)
{

    DIR *dir = opendir(dir_name);

    if (!dir)
    {
        return NO_DIR;
    }

    struct dirent *entry;
    size_t dir_length = strlen(dir_name);

    struct stat file_stat;

    while ((entry = readdir(dir)))
    {

        size_t entry_length = strlen(entry->d_name);

        char *full_path = (char*)malloc(sizeof(char) * (dir_length + entry_length + 2));

        if (!full_path)
        {
            return BAD_ALLOC;
        } 

        strcpy(full_path, dir_name);
        strcat(full_path, "/");
        strcat(full_path, entry->d_name);
        full_path[dir_length + entry_length + 1] = '\0';

        if (stat(full_path, &file_stat) < 0)
        {
            closedir(dir);

            EC_handle(FILE_ERROR);
        }
        
        else
        {
            printf("%-32s", full_path);

            if (S_ISREG(file_stat.st_mode)) 
            {
                printf("\tRegular file\n");
            }
            else if (S_ISDIR(file_stat.st_mode)) 
            {
                printf("\tDirectory\n");
            }
            else if (S_ISLNK(file_stat.st_mode)) 
            {
                printf("\tSymbolic link\n");
            }
            else if (S_ISFIFO(file_stat.st_mode)) 
            {
                printf("\tFIFO/pipe\n");
            }
            else if (S_ISSOCK(file_stat.st_mode)) 
            {
                printf("\tSocket\n");
            }
            else if (S_ISCHR(file_stat.st_mode)) 
            {
                printf("\tCharacter device\n");
            }
            else if (S_ISBLK(file_stat.st_mode)) 
            {
                printf("\tBlock device\n");
            }

        }

        free(full_path);

    }

    closedir(dir);

}
