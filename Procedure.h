
#ifndef PROCEDURE_H
#define PROCEDURE_H




typedef enum 
{

    OK = 0,

    INVALID,

    BAD_ALLOC,

    OBJECT_ABSENCE,

} EXIT_CODE;




typedef struct
{

    size_t stored;
    
    size_t capacity;

    char* lex;

} String;





typedef struct
{

    String* town;
    
    String* street;

    unsigned int house_number;

    String* build;

    unsigned int suite;

    String* id;

} Address;




typedef struct
{

    Address* intel;

    double weight;

    String* mail_id;

    String* creation_time;

    String* delivery_time;

} Mail;




typedef struct node
{

    Mail* root;

    struct node* left;

    struct node* right;

} mail_node;




typedef struct
{

    mail_node* root;

    int comp;

} mail_base_BST;




typedef struct
{

    Address* mail_post;

    mail_base_BST* client_base;

} Post;














/*-----------------------------------String-handle----------------------------------------*/

//--------------Char*_block-------
size_t char_length (char* str);


EXIT_CODE char_copy (char* dest, char* src);

//--------------------------------



String* create_str (char* src);


EXIT_CODE* purge_str (String* dest);


int comp_length_str (String* str1, String* str2);


int comp_lex_str (String* str1, String* str2);


EXIT_CODE copy_str_to_existing (String* dest, String* src);


EXIT_CODE resize_str (String* to_resize, size_t new_capacity);


String* copy_constr (String* to_copy);
/*----------------------------------------------------------------------------------------*/

#endif