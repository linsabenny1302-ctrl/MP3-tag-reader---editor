#include<stdio.h>
#include "types.h"
#include "view.h"
#include<string.h>

Status read_and_validate_view_arg(char *argv[],View *view)
{
    if(argv[1] == NULL || argv[2] == NULL)
    {
        printf(RED"Please enter the correct arguments...!"RESET);
        return e_failure;
    }
    if(strstr(argv[2],".mp3") != NULL)
    {
        view -> sample_file_name = argv[2];
    }
    else
    {
        printf(RED".mp3 file is not present\n"RESET);
        return e_failure;
    }
    return e_success;
}

Status do_view_operation(View *view)
{
    if(open_files(view) == e_success)
    {}
    else
    {
        printf(RED"Opening files was unsuccessfull\n"RESET);
        return e_failure;
    }

    if(skip_header_bytes(view) == e_success)
    {}
    else
    {
        return e_failure;
    }

    printf("                  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf(BLUE"                      🎧 MP3 TAG VIEWER DETAILS\n"RESET);
    printf("                  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    if(read_and_print_data(view) == e_success)
    {
        //printf("Read and print is successfull\n");
    }
    else
        return e_failure;

    return e_success;
}

Status open_files(View *view)
{
    view -> fptr_sample_file = fopen(view -> sample_file_name,"r");

    if(view -> fptr_sample_file == NULL)
    {
        printf(RED".mp3 file is not opened\n"RESET);
        return e_failure;
    }
    return e_success;
}

Status skip_header_bytes(View *view)
{
    fseek(view -> fptr_sample_file,10,SEEK_SET);
}

Status read_and_print_data(View *view)
{
    int i = 0;

    while(i < 6)
    {
        char tag[5];
        int size = 0;

        fread(tag,4,1,view -> fptr_sample_file);

        tag[5] = '\0';
        //printf("%s\n",tag);

        fread(&size,4,1,view ->fptr_sample_file);
       
        change_endianess(&size);
        //printf("%d\n",size);
        
        fseek(view ->fptr_sample_file,3,SEEK_CUR);

        char data[size];

        fread(data,size - 1,1,view -> fptr_sample_file);
        data[size - 1] = '\0';
        //printf("%s\n",data);

        if(print(tag,data) == e_success)
            i++;
    }
}

Status change_endianess(int *size)
{
    char *ptr = (char *)size;
    int s = sizeof(int);
    for(int i = 0;i < (s / 2);i++)
    {
        char temp = ptr[i];
        ptr[i] = ptr[s - i - 1];
        ptr[s - i - 1] = temp;
    }
    return e_success;
}

Status print(char *tag,char *data)
{
    
    if(strcmp(tag,"TIT2") == 0)
    {
        printf("\t📋 TITLE   : %s\n",data);
        return e_success;
    }
    else if(strcmp(tag,"TYER") == 0)
    {
        printf("\t📆 YEAR    : %s\n",data);
        return e_success;
    }
    else if(strcmp(tag,"TALB") == 0)
    {
        printf("\t🎼 ALBUM   : %s\n",data);
        return e_success;
    }
    else if(strcmp(tag,"TPE1") == 0)
    {
        printf("\t🎤 ARTIST  : %s\n",data);
        return e_success;
    }
    else if(strcmp(tag,"COMM") == 0)
    {
        printf("\t📝 COMMENT : %s\n",data);
        return e_success;
    }
    else if(strcmp(tag,"TCON") == 0)
    {
        printf("\t🎵 GENRE   : %s\n",data);
        return e_success;
    }
    else
    {
        return e_failure;
    }
}