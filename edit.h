#ifndef EDIT_H
#define EDIT_H

#include "types.h"

typedef struct EDIT_
{
    char user_tag[5];
    char tag_name[20];
    char *user_data;
    char *sample_file_name;
    FILE *fptr_sample_file;
    FILE *fptr_temp_file;

}Edit;


Status read_and_validate_edit_arg(char *argv[],Edit *edit);

Status do_edit_operation(Edit *edit);

Status open_files_e(Edit *edit);

Status read_and_copy_data(Edit *edit);

Status change_endianess(int *size);

Status print(char *tag,char *data);

#endif