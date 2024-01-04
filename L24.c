
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "Procedure.h"





int main ()//int argc, char **argv)
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

}



EXIT_CODE processing (FILE *input, char *to_find)
{

    EXIT_CODE sup = 0;

    char c = 1;

    int found = 0;

    String *path = NULL;
    string_init(&path);

    pid_t pid = 0;

    while (c > 0)
    {

        pid = fork();
        
        if (pid < 0)
        {
            EC_handle(PROCESS_CREATE_FAIL);
			return PROCESS_CREATE_FAIL;
        }
        else if (pid == 0)
        {
            FILE *data = NULL;

            sup = get_path(path, &c, input);
            sup = sup ? sup : file_proper(&data, path->word);

            if (sup)
            {
                purge_str(path);
                return sup;
            }

            sup = search_str(data, to_find);

            if (sup == PRESENCE)
            {
                found++;
                printf("Detected in %s file!\n", path->word);
            }

            purge_str(path);
            fclose(data);
        }
    }

    if (sup = ABSENCE && (!found))
    {
        printf("\"%s\"'s not been detected on entire list\n", to_find);
    }

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
            return INVALID_ARGV;
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

