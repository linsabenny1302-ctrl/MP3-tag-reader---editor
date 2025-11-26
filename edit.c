#include<stdio.h>
#include "types.h"
#include "edit.h"
#include "view.h"
#include<string.h>

Status read_and_validate_edit_arg(char *argv[],Edit *edit)
{
    if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
    {
        printf(RED"Plaese enter the correct arguments...!\n"RESET);
        return e_failure;
    }
    if(strcmp(argv[2],"-t") == 0)
    {
        strcpy(edit -> user_tag,"TIT2");
        strcpy(edit -> tag_name,"TITLE");
    }
    else if(strcmp(argv[2],"-y") == 0)
    {
        strcpy(edit -> user_tag,"TYER");
        strcpy(edit -> tag_name,"YEAR");
    }
    else if(strcmp(argv[2],"-a") == 0)
    {
        strcpy(edit -> user_tag,"TPE1");
        strcpy(edit -> tag_name,"ARTIST");
    }
    else if(strcmp(argv[2],"-A") == 0)
    {
        strcpy(edit -> user_tag,"TALB");
        strcpy(edit -> tag_name,"ALBUM");
    }
    else if(strcmp(argv[2],"-c") == 0)
    {
        strcpy(edit -> user_tag,"COMM");
        strcpy(edit -> tag_name,"COMMENT");
    }
    else if(strcmp(argv[2],"-g") == 0)
    {
        strcpy(edit -> user_tag,"TCON");
        strcpy(edit -> tag_name,"GENRE");
    }
    else
    {
        printf(RED"Please enter correct arguments...!"RESET);
    }

    if(argv[3] != NULL)
    {
        edit -> user_data = argv[3];
    }
    else
    {
        printf(RED"Please enter correct arguments...!"RESET);
    }
    
    if(strstr(argv[4],".mp3") != NULL)
    {
        //printf(".mp3 file is present\n");
        edit -> sample_file_name = argv[4];
    }
    else
    {
        printf(RED".mp3 file is not present\n"RESET);
        return e_failure;
    }
    return e_success;
}

Status do_edit_operation(Edit *edit)
{
    if(open_files_e(edit) == e_success)
    {
        //printf("opened files successfully\n");
    }
    else
    {
        printf(RED"opening files was unsuccessfull\n"RESET);
        return e_failure;
    }

    if(read_and_copy_data(edit) == e_success)
    {
        printf("                  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf(BLUE"                      ✏️ MP3 TAG EDITOR DETAILS\n"RESET);
        printf("                  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

        printf("\t\t📌 FILE      : %s\n",edit -> sample_file_name);
        printf("\t\t🔨 OPERATION : To edit %s\n",edit -> tag_name);
        printf("\t\t🆕 NEW VALUE : %s\n",edit -> user_data);

        //printf("Read and print is successfull\n");
        remove(edit -> sample_file_name);
        rename("temp.mp3",edit -> sample_file_name);
    }
    else
        return e_failure;


    return e_success;
}

Status open_files_e(Edit *edit)
{
    edit -> fptr_sample_file = fopen(edit -> sample_file_name,"r");

    if(edit -> fptr_sample_file == NULL)
    {
        printf(RED".mp3 file is not opened\n"RESET);
        return e_failure;
    }

    edit -> fptr_temp_file = fopen("temp.mp3","w");

    return e_success;
}

Status read_and_copy_data(Edit *edit)
{
    char header[10];

    fread(header,10,1,edit -> fptr_sample_file);
    fwrite(header,10,1,edit -> fptr_temp_file);

    char tag[5];
    char flag[3];
    int size = 0;

    while(1)
    {
        fread(tag,4,1,edit -> fptr_sample_file);
        tag[4] = '\0';
        int ori_size = 0;
        fread(&size,4,1,edit -> fptr_sample_file);
        ori_size = size;
        fread(flag,3,1,edit -> fptr_sample_file);
        
        change_endianess(&ori_size);

        char data[ori_size];
        fread(data,ori_size - 1,1,edit -> fptr_sample_file);
        data[ori_size - 1] = '\0';
        
        if(strcmp(tag,edit -> user_tag) == 0)
        {
            int ori_new_size = strlen(edit -> user_data) + 1;
            int new_size = ori_new_size;
            change_endianess(&ori_new_size);
            char new_data[new_size];
            strcpy(new_data,edit -> user_data);
           

            fwrite(tag,4,1,edit -> fptr_temp_file);
            fwrite(&ori_new_size,4,1,edit -> fptr_temp_file);
            fwrite(flag,3,1,edit -> fptr_temp_file);
            fwrite(new_data,new_size - 1,1,edit -> fptr_temp_file);

            break;
        }
        else
        {
            fwrite(tag,4,1,edit -> fptr_temp_file);
            fwrite(&size,4,1,edit -> fptr_temp_file);
            fwrite(flag,3,1,edit -> fptr_temp_file);
            fwrite(data,ori_size - 1,1,edit -> fptr_temp_file);

        }    
    }

    char ch;

    while(fread(&ch,1,1,edit -> fptr_sample_file))
    {
        fwrite(&ch,1,1,edit -> fptr_temp_file);
    }
}