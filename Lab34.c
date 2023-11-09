
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>

#include "Procedure.h"




EXIT_CODE free_str (int amount, ...)
{

    va_list to_free;

    va_start(to_free, amount);

    for (int i = 0; i < amount; i++)
    {

        String* buff = va_arg(to_free, String*);

        printf("%u?\n", buff->capacity);
        free(buff);
        printf("%u?\n", buff->capacity);

    }

    va_end(to_free);

    return OK;

}


/*-----------------------------------String-handle----------------------------------------*/

size_t char_length (char* str)
{

    char* crawler = str;

    while (*crawler != '\0')
    {
        crawler++;
    }

    return (crawler - str);

}


EXIT_CODE char_copy (char* dest, char* src)
{

    char* src_crawler = src;
    char* dest_crawler = dest;

    do 
    {

        *dest_crawler = *src_crawler;

        dest_crawler++;
        src_crawler++;

    } while (*src_crawler != '\0');

    *dest_crawler = *src_crawler;

    return OK;

}



String* create_str (char* src)
{

    size_t length = char_length(src);


    String* dest = (String*)malloc(sizeof(String) * 1);
    
    if (!dest)
    {
        return NULL;
    }


    dest->lex = (char*)malloc(sizeof(char) * length + 1);

    if (!dest->lex)
    {

        free(dest);
        return NULL;

    }

    char_copy(dest->lex, src);

    dest->capacity = length + 1;

    dest->stored = length;

    return dest;

}


EXIT_CODE* purge_str (String* dest)
{

    free(dest->lex);

    dest->lex = NULL;
    dest->capacity = 0;
    dest->stored = 0;

    return OK;

}


int comp_length_str (String* str1, String* str2)
{

    if (str1->stored != str2->stored)
    {
        return (str1->stored - str2->stored);
    }

    else 
    {
        return (comp_lex_str(str1, str2));
    }

}


int comp_lex_str (String* str1, String* str2)
{

    char* ch_1 = str1->lex;
    char* ch_2 = str2->lex;

    while (ch_1 > 0 && ch_2 > 0)
    {

        if (ch_1 != ch_2)
        {
            return (ch_1 - ch_2);
        }

    }

    if (ch_1 != ch_2)
    {

        return (!ch_1) ? -1 : 1;

    }

    return 0;

}


EXIT_CODE copy_str_to_existing (String* dest, String* src)
{

    if (dest->capacity <= src->stored)
    {

        if (resize_str(dest, (src->stored + 1)) != OK)
        {
            return BAD_ALLOC;
        }

    }

    char_copy(dest->lex, src->lex);

    return OK;

}


EXIT_CODE resize_str (String* to_resize, size_t new_capacity)
{

    char* char_temp = (char*)realloc(to_resize->lex, sizeof(char) * new_capacity);
    
    if (!char_temp)
    {
        return BAD_ALLOC;
    }

    to_resize->lex = char_temp;

    to_resize->capacity = new_capacity;

    to_resize->stored = new_capacity - 1;

    return OK;

}


String* copy_constr (String* to_copy)
{

    String* dest = (String*)malloc(sizeof(String) * 1);
    
    if (!dest)
    {
        return NULL;
    }


    dest->lex = (char*)malloc(sizeof(char) * to_copy->capacity);

    if (!dest->lex)
    {
        free(dest);
        return NULL;
    }

    char_copy (dest->lex, to_copy->lex);

    dest->stored = to_copy->stored;
    
    dest->capacity = to_copy->capacity;

    return dest;

}


EXIT_CODE cat_str2_to_str1 (String* dest, String* to_cat)
{

    size_t new_stored = dest->stored + to_cat->stored;

    char* dest_crawler = dest->lex + dest->stored;
    char* cat_crawler = to_cat->lex;

    if (dest->capacity < (new_stored + 1))
    {
        if (resize_str(dest, (new_stored + 1)) != OK)
        {
            return BAD_ALLOC;
        }
    }

    while (*cat_crawler > 0)
    {

        *dest_crawler = *cat_crawler;

        dest_crawler++;
        cat_crawler++;

    }

    *dest_crawler = *cat_crawler;

    return OK;

}

/*----------------------------------------------------------------------------------------*/




/*----------------------------------------Adress-handle-----------------------------------*/

EXIT_CODE address_constr (Address* node, String* town, String* street, unsigned int house_number, String* build, unsigned int suite, String* id)
{

    node->town = town;
    node->street = street;
    node->house_number = house_number;
    node->build = build;
    node->suite = suite;
    node->id = id;

    return OK;

}


EXIT_CODE address_destr (Address* node)
{

    purge_str(node->town);
    purge_str(node->street);
    purge_str(node->build);
    purge_str(node->id);

    //free_str(4, (*node)->town, (*node)->street, (*node)->build, (*node)->id);
    
    free(node->town);
    free(node->street);
    free(node->build);
    free(node->id);

    return OK;

}

/*----------------------------------------------------------------------------------------*/




/*----------------------------------------Mail-handle-------------------------------------*/

EXIT_CODE mail_constr (Mail* dest, Address* address, double weight, String* mail_id, String* creation_time, String* delivery_time)
{

    if((char_length(mail_id->lex) != 14) || (char_length(creation_time->lex) != 19) || (char_length(delivery_time->lex) != 19))
    {
        return INVALID;
    }

    dest->intel = address;
    dest->weight = weight;
    dest->mail_id = mail_id;
    dest->creation_time = creation_time;
    dest->delivery_time = delivery_time;

    return OK;

}


EXIT_CODE mail_destr (Mail* dest)
{

    address_destr(dest->intel);

    free(dest->intel);

    purge_str(dest->mail_id);
    purge_str(dest->creation_time);
    purge_str(dest->delivery_time);

    free(dest->mail_id);
    free(dest->creation_time);
    free(dest->delivery_time);

    return OK;

}

/*----------------------------------------------------------------------------------------*/





/*----------------------------------------BST-hadle---------------------------------------*/

/*int *comp(Mail* m1, Mail* m2)
{

    if (m1->intel->id != m2->intel->id)
    {
        return (m1->intel->id - m2->intel->id);
    }

    return


}


EXIT_CODE BST_constr (mail_base_BST* base, int *comp(Mail* m1, Mail* m2))
{

    base->root = NULL;

    base->comp = comp;

}


EXIT_CODE create_new_root (Mail* root, Mail* new_node, int *comp(Mail* m1, Mail* m2))
{



    return OK;

}
*/

/*----------------------------------------------------------------------------------------*/













/*----------------------------------------MAIN--------------------------------------------*/

int main (int argc, char** argv) 
{

    String* inst1 = create_str("Os");


    String* inst2 = create_str("of");


    String* inst3 = create_str("da");


    String* inst4 = create_str("id!");


    Address* node = (Address*)malloc(sizeof(Address) * 1);
    
    if (!node)
    {
        return -1;
    }

    address_constr(node, inst1, inst2, 1, inst3, 123, inst4);

    printf("%s %s %u %s %u %s\n", node->town->lex, node->street->lex, node->house_number, node->build->lex, node->suite, node->id->lex);


    Mail* base = (Mail*)malloc(sizeof(Mail) * 1);
    
    if (!base)
    {
        return -1;
    }

    if (mail_constr(base, node, 12.3, inst3, inst4, inst3) != OK)
    {

        printf("Invalid input!");

        address_destr(node);
        free(node);

        free(base);
        
        return -1;

    }

    printf("%s %s %u %s %u %s\n", base->intel->town->lex, base->intel->street->lex, base->intel->house_number, base->intel->build->lex, base->intel->suite, base->intel->id->lex);

    printf("%llf %s %s %s\n", base->weight, base->mail_id->lex, base->creation_time->lex, base->delivery_time->lex);

    mail_destr (base);

    free(base);
    
    return 0;
}

/*----------------------------------------------------------------------------------------*/
