
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


typedef enum
{

    OK = 0,

    INVALID_ARGC,
    INVALID_ARGV,

    BAD_ALLOC,

    NO_FILE,

    PRESENCE,
    ABSENCE,

    PROCESS_CREATE_FAIL,

} EXIT_CODE;


typedef struct
{

    size_t allocated;
    size_t occupied;

    char* word;

} String;






void EC_handle (EXIT_CODE c);



EXIT_CODE string_init (String **dest);


EXIT_CODE string_append (String *dest, char to_add);


EXIT_CODE purge_str (String *dest);


void string_destr (String **dest);






EXIT_CODE input_handle (int argc, char **argv);



EXIT_CODE processing (FILE *input, char *to_find);


EXIT_CODE collect_paths (FILE *input, char ***dest, size_t *sz);


EXIT_CODE file_proper (FILE **dest, char *src);


EXIT_CODE get_path (String *dest, char *c, FILE *src);


EXIT_CODE search_str (FILE *src, char *to_find);


EXIT_CODE left_shift (String *dest);





int main ()//int argc, char **argv
{

    int argc = 3;

    char *data[] = {"y", "base.txt", "gay"};
    char **argv = data;

    EC_handle(input_handle(argc, argv));

    return 0;

}


void EC_handle (EXIT_CODE c)
{

    switch (c)
    {
        case OK:
            printf("Success!\n");
            break;

        case INVALID_ARGC:
            printf("Invalid argument amount!\n");
            break;

        case INVALID_ARGV:
            printf("Invalid argument content!\n");
            break;

        case NO_FILE:
            printf("File seems to be absenced!\n");
            break;

        case BAD_ALLOC:
            printf("Memory fault!\n");
            break;
        
        case PROCESS_CREATE_FAIL:
            printf("Process creation failed!\n");
            break;

        default:
            break;
    }

}



EXIT_CODE string_init (String **dest)
{

    String *buff = (String*)malloc(sizeof(String));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->word = NULL;

    buff->allocated = 1;

    buff->occupied = 1;

    *dest = buff;

    return OK;

}


EXIT_CODE string_append (String *dest, char to_add)
{

    if (dest->allocated == dest->occupied)
    {

        dest->allocated += 1;

        dest->allocated *= 2;

        char *temp = (char*)realloc(dest->word, sizeof(char) * dest->allocated);

        if (!temp)
        {
            return BAD_ALLOC;
        }

        dest->word = temp;

    }

    *(dest->word + (dest->occupied - 1)) = to_add;

    *(dest->word + dest->occupied) = '\0';

    dest->occupied++;

    return OK;

}


EXIT_CODE purge_str (String *dest)
{

    free(dest->word);
    dest->word = NULL;

    dest->allocated = 1;
    dest->occupied = 1;

    return OK;

}


void string_destr (String **dest)
{

    free((*dest)->word);
    (*dest)->word = NULL;

    (*dest)->allocated = 0;

    (*dest)->occupied = 0;

    free((*dest));
    (*dest) = NULL;

}






EXIT_CODE input_handle (int argc, char **argv)
{

    EXIT_CODE sup = 0;

    if (argc != 3)
    {
        return INVALID_ARGC;
    }

    FILE *input = NULL;
    sup = file_proper(&input, *(argv + 1));

    if (sup)
    {
        return sup;
    }

    sup = processing(input, *(argv + 2));

    fclose(input);

    return sup;

}



EXIT_CODE processing (FILE *input, char *to_find)
{

    EXIT_CODE sup = 0;
    
    size_t size = 0;

    char **path_col = (char**)malloc(sizeof(char*));

    if (!path_col)
    {
        return BAD_ALLOC;
    }

    collect_paths(input, &path_col, &size);

    pid_t pid = 1;

    for (int i = 0; i < size && pid != 0; i++)
    {

        pid = fork();

        if (pid == -1)
        {
            EC_handle(PROCESS_CREATE_FAIL);
			return PROCESS_CREATE_FAIL;
        }
        else if (pid == 0)
        {
            FILE *search_base = NULL;

            if (file_proper(&search_base, path_col[i]) == NO_FILE)
            {
                EC_handle(NO_FILE);
            }
            else 
            {
                sup = search_str(search_base, to_find);

                if (sup == PRESENCE)
                {
                    printf("\"%s\" has been detected in %s file\n", to_find, path_col[i]);
                }
                else if (sup == ABSENCE)
                {
                    printf("%s file detection FAILED!\n", path_col[i]);
                }
                fclose(search_base);
            }
 
            free(path_col[i]);

        }
    }

    free(path_col);

    return OK;

}


EXIT_CODE collect_paths (FILE *input, char ***dest, size_t *sz)
{

    String *buff_path = NULL;
    string_init(&buff_path);

    char c = 1;
    size_t allocated = 1;

    while (c > 0)
    {
        get_path(buff_path, &c, input);

        if (allocated == *sz)
        {

            allocated = (allocated + 1) * 2;

            char **temp = (char**)realloc((*dest), sizeof(char*) * allocated);

            if (!temp)
            {
                return BAD_ALLOC;
            }

            (*dest) = temp;

        }

        (*dest)[*sz] = (char*)malloc(sizeof(char) * buff_path->occupied);

        strcpy((*dest)[*sz], buff_path->word);

        (*sz)++;

        purge_str(buff_path);

    }

    string_destr(&buff_path);

    return OK;

}


EXIT_CODE file_proper (FILE **dest, char *src)
{

    FILE *temp = fopen(src, "r");

    if (!temp)
    {
        return NO_FILE;
    }

    *dest = temp;

    return OK;

}


EXIT_CODE get_path (String *dest, char *c, FILE *src)
{

    EXIT_CODE sup = 0;

    while ((*c = fgetc(src)) > 0 && *c != '\n' && (!sup))
    {

        sup = string_append(dest, *c);

    }

    return sup;

}


EXIT_CODE search_str (FILE *src, char *to_find)
{

    String *buff = NULL;
    string_init(&buff);

    size_t length = strlen(to_find);

    char c = 1;

    while (buff->occupied != length + 1)
    {   
        if ((c = fgetc(src)) < 0)
        {
            return ABSENCE;
        }
        string_append(buff, c);
    }


    while (1)
    {

        if (!strcmp(buff->word, to_find))
        {
            string_destr(&buff);
            return PRESENCE;
        }

        if ((c = fgetc(src)) < 0)
        {
            string_destr(&buff);
            break;
        }

        left_shift(buff);
        string_append(buff, c);

    } 
    
    return ABSENCE;

}


EXIT_CODE left_shift (String *dest)
{
    
    for (int i = 1; i < dest->occupied; i++)
    {

        dest->word[i - 1] = dest->word[i];

    }

    dest->occupied -= 1;

    return OK;

}



