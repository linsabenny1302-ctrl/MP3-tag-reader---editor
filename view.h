#ifndef VIEW_H
#define VIEW_H

#include "types.h"

typedef struct VIEW_
{
    char *sample_file_name;
    FILE *fptr_sample_file;

}View;


OperationType check_operation_type(char *argv[]);

Status read_and_validate_view_arg(char *argv[],View *view);

Status do_view_operation(View *view);

Status open_files(View *view);

Status skip_header_bytes(View *view);

Status read_and_print_data(View *view);

Status change_endianess(int *size);

Status print(char *tag,char *data);

#endif