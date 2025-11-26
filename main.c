/*Name : Linsa Benny
  Description : MP3 tag reader and editor
  Sample input : sample.mp3
  sample output : to view and edit music info in the mp3 file*/

#include<stdio.h>
#include "types.h"
#include "view.h"
#include "edit.h"
#include<string.h>

int main(int argc,char *argv[])
{
    if(check_operation_type(argv) == e_view)
    {
        printf("*YOU HAVE CHOOSED VIEW*\n");

        View view;

        if(read_and_validate_view_arg(argv,&view) == e_success)
        {
            if(do_view_operation(&view) == e_success)
            {
                printf(GREEN"\nVIEW OPERATION COMPLETED SUCCESSFULLY\n");
            }
            else
            {
                printf(RED"VIEW IS UNSUCCESSFULL\n"RESET);
                return e_failure;
            }    
        }
        else
        {
            printf(RED"Read and validate is unsuccessfull\n"RESET);
            return e_failure;
        }
    }
    else if(check_operation_type(argv) == e_edit)
    {
        printf("*YOU HAVE CHOOSED EDIT*\n");

        Edit edit;

        if(read_and_validate_edit_arg(argv,&edit) == e_success)
        {
            //printf("Read and validate is successfull\n");

            if(do_edit_operation(&edit) == e_success)
            {
                printf(GREEN"\nEDIT OPERATION COMPLETED SUCCESSFULLY\n");
            }
            else
            {
                printf(RED"EDIT IS UNSUCCESSFULL\n"RESET);
                return e_failure;
            }    
        }
        else
        {
            printf(RED"Read and validate is unsuccessfull\n"RESET);
            return e_failure;
        }
    }
    else if(check_operation_type(argv) == e_help)
    {
        printf("                  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf(BLUE"                            📓 HELP MENU\n"RESET);
        printf("                  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");


        printf("\n🔍 To View  ---> ./a.out -v <file.mp3>\n");
        printf("\n🔨 To Edit  ---> ./a.out -e <operation> <new_data> <file.mp3>\n");
        printf(CYAN"\t---------------------------------------------------\n"RESET);
        printf(CYAN"\t|                  OPERATION                      |\n"RESET);
        printf(CYAN"\t---------------------------------------------------\n"RESET);
        printf(CYAN"\t|         -t     : To edit Title                  |\n"RESET);
        printf(CYAN"\t|         -y     : To edit Year                   |\n"RESET);
        printf(CYAN"\t|         -A     : To edit Album                  |\n"RESET);
        printf(CYAN"\t|         -a     : To edit Artist                 |\n"RESET);
        printf(CYAN"\t|         -c     : To edit Comment                |\n"RESET);
        printf(CYAN"\t|         -g     : To edit Genre                  |\n"RESET);
        printf(CYAN"\t---------------------------------------------------\n"RESET);
       
    }
    else
    {
        printf(YELLOW"Please enter the correct arguments..!😑\n"RESET);
        printf("Use help operation(-h) to pass correct aruments!\n");
    }
    return 0;
}

OperationType check_operation_type(char *argv[])
{
    if(argv[1] == NULL)
        return e_unsupported;
    if(strcmp(argv[1],"-v") == 0)
        return e_view;
    else if(strcmp(argv[1],"-e") == 0)
        return e_edit;
    else if(strcmp(argv[1],"-h") == 0)
        return e_help;
    else
        return e_unsupported;
}

