#include <stdio.h>
#include <stdlib.h>
#include<MyLibrary.h>
#define Highlight 0x70
#define red 0x40
#define green 0x20
#define yellow 0x30
#define normal 0x07
#define up 72
#define dn 80
#define home 71
#define end 79
#define pup 73
#define pdn 81
#define esc 27
#define enter 13
#define right 77
#define left 75
#define NewMenuC 0
//#define len 25
#define backspace 8
#define del 83
#define num_of_char_per_line 100
#define f1 59
#define f2 60
#define f3 61

#define diff 12


int main()
{

    colored_window();
    return 0;
}


int colored_window(){
    int new_line=2;
    int num_c_arr=0;
    int* ch_at_line;
    int curr_pos[2]={0,0};
    int curr_line=0;
    int len=0;
    int cur = 0 ;
    int flag=0;
    char input = " ";

    char** arr;

    printf("Please Enter line numbers recommended (1-8) : ");
    scanf("%d",&len);
    new_line=len+6;
    _flushall();

    arr = malloc(len*sizeof(char));
    ch_at_line = malloc(len*sizeof(int));

     printf("NO of lines                : %d  ",len);
     printf("\nfor new line               : Enter");
     printf("\nfor delete last char       : Backspace");
     printf("\nfor delete first char      : Delete");
     printf("\nto print the text          : F1");
     printf("\nto print arrays info       : F2");
     printf("\nsave the text in o/p file  : F3");

     textattr(red);
     printf("\nPLEASE DO NOT LONG PRESS ON ANY KEY");
     textattr(normal);
     printf("\nPress any key to continue ...");



    for(int i=0; i<len; i++){

        arr[i] = malloc(num_of_char_per_line*sizeof(char));

    }
     char* ptr_start=&arr[0][0];
     char* ptr_end=&arr[0][100-1];
     char* ptr_cur=&arr[0][0];

     char* ptr_start_base = &arr[0][0];//first line
     char* ptr_end_base   = &arr[len-1][0];//last line
        *ptr_start_base='\0';
        for(int i=0;i<len;i++){
            arr[i][0]='\0';
            ch_at_line[i]=0;
            for(int j=0;j<num_of_char_per_line;j++)
                arr[i][j]='\0';
        }




    getch();
    clrscr();


    do{
     gotoxy(curr_pos[1],curr_pos[0]);
     input=getch();
     switch(input){
     case -32:
     case 224:
     case 0:
        input=getch();
        switch(input){
            case f3:

            save_the_text( arr, len, ch_at_line, ptr_start_base);

            break;
            case f2:
                gotoxy(0,25);

            printf("%d arr0\n",&arr[0]);
                        printf("%d arr0.0\n",&arr[0][0]);
                        printf("%d arr0.99\n",&arr[0][99]);
                                            printf("\n");

            printf("%d arr1\n",&arr[1]);
                        printf("%d arr1.0\n",&arr[1][0]);
                        printf("%d arr1.99\n",&arr[1][99]);
                                            printf("\n");

            printf("%d arr2\n",&arr[2]);
                        printf("%d arr2.0\n",&arr[2][0]);
                        printf("%d arr2.99\n",&arr[2][99]);
                                                printf("\n");


            printf("%d arr3\n",&arr[3]);
                        printf("%d arr3.0\n",&arr[3][0]);
                        printf("%d arr3.99\n",&arr[3][99]);
                                                printf("\n");

        for(int i=0; i<len ;i++){

                        printf("%d----: %d----\n",i,(ch_at_line[i]));

                   }

            break;
            case f1:

            // if(*(ptr_start_base)!='\0'){
                textattr(green);

                gotoxy(0,new_line);
                for(int i=0 ; i<len; i++){
                        for(int j=0; j<ch_at_line[i]/*num_of_char_per_line*/; j++){
                                if(arr[i][j]!='\0')
                            printf("%c",(arr[i][j]));
                                else
                                break;

                }
                printf("\n");
                }
                new_line+=len;
                textattr(normal);
               // }

            break;

            case up:
                if (curr_pos[0] > 0){

                    curr_pos[0]-=1;
                     ptr_cur   -= num_of_char_per_line+diff;
                     ptr_start -= num_of_char_per_line+diff;
                     ptr_end   -= num_of_char_per_line+diff;
                     curr_line--;

                }

                break;

            case dn:
                if (curr_pos[0]<len-1){

                  curr_pos[0]+=1;//rows
                   ptr_cur   += num_of_char_per_line+diff;
                   ptr_start += num_of_char_per_line+diff;
                   ptr_end   += num_of_char_per_line+diff;
                   curr_line++;

                }

                break;

            case left:
                if( ptr_cur > ptr_start){
                    ptr_cur--;
                    curr_pos[1]-=1;
                    }
                break;

            case right:
                if(ptr_cur< ptr_end){
                    ptr_cur++;
                    curr_pos[1]+=1;
                    }
                break;

            case home:
                ptr_cur=ptr_start;
                curr_pos[1]=0;
                break;

            case end:
                ptr_cur=ptr_start+ch_at_line[curr_line];
                curr_pos[1]=ch_at_line[curr_line];
                break;

            case pup:
                ptr_cur=ptr_start_base;//first line
                ptr_start = ptr_start_base;
                ptr_end   = ptr_start_base+num_of_char_per_line+diff;
                curr_pos[0]=0;
                curr_pos[1]=0;
                curr_line=0;

                break;

            case pdn:

                ptr_cur=ptr_end_base;//last line
                curr_pos[0]=len-1;
                curr_pos[1]=0;
                   ptr_start = ptr_end_base;
                   ptr_end   = ptr_end_base+num_of_char_per_line+diff;
                curr_line=len-1;


                break;

            case del:
               for(int i=0; i<ch_at_line[curr_line] ;i++){
                    *(ptr_start+i)=*(ptr_start+i+1);
                     gotoxy(i,curr_pos[0]);
                     textattr(Highlight);
                     if(ptr_start+i!='\0')
                        printf("%c",*(ptr_start+i));
                      textattr(normal);
                   }
               for(int j=ch_at_line[curr_line]-1; j<100 ;j++){
                    *(ptr_start+j)='\0';
                      textattr(normal);
                      gotoxy(j,curr_pos[0]);//clear befor highlight
                      printf(" ");
                    }
               if(ptr_cur>ptr_start){
                     ptr_cur--;
                     curr_pos[1]--;
                     if(ch_at_line[curr_line]>0)
                     ch_at_line[curr_line]--;
                     }
                     if(ptr_cur==ptr_start){
                     ch_at_line[curr_line]=0;
                     }


                break;

        }
        break;

     case enter:

            *ptr_cur='\0';
            if(curr_line<len-1){
                curr_pos[0]+=1;
                curr_pos[1]=0;
                ptr_start += num_of_char_per_line+diff;
                ptr_cur = ptr_start ;
                ptr_end+=num_of_char_per_line+diff;
                curr_line++;


                }
        break;


     case backspace:
         if(ptr_cur>ptr_start){

         ptr_cur--;
         curr_pos[1]-=1;
         gotoxy(curr_pos[1],curr_pos[0]);
         *ptr_cur='\0';
         textattr(normal);
         printf(" ");
         if(ch_at_line[curr_line]>0)
         ch_at_line[curr_line]--;

         }
         else if(ptr_cur==ptr_start){

            if(curr_line>0){
                curr_pos[0]-=1;
                curr_line--;
                curr_pos[1]= ch_at_line[curr_line];
                ptr_start -= num_of_char_per_line+diff;
                ptr_end    = ptr_start +(ch_at_line[curr_line]);
                ptr_cur    = ptr_end; ;
                 *ptr_cur='\0';
                }

         }
         break;

     case esc:
        flag=1;
        printf("\nbye");
        break;

     default:
         if(ptr_cur<=ptr_end){


            *ptr_cur=input;
            textattr(Highlight);
             printf("%c",*ptr_cur);
             textattr(normal);
             ptr_cur++;
            //*ptr_cur='\0';

             curr_pos[1]+=1;
             ch_at_line[curr_line]++;
         }else/* if(ptr_cur==ptr_end)*/{

             if(curr_line<len-1){
                curr_pos[0]+=1;
                curr_pos[1]=0;
                ptr_cur = ptr_start + num_of_char_per_line+diff;
                ptr_start += num_of_char_per_line+diff;
                ptr_end+=num_of_char_per_line+diff;
                curr_line++;
                }

         }
         //gotoxy(10,15);
         //printf("%d",ptr_cur);
        }
       }while(flag==0);

      for(int i=0; i<len; i++){

        free(arr[i]);
     //   free(ch_at_line[i]);

    }
    free(arr);
    }

void save_the_text(char** arr,int len,int* ch_at_line,char* ptr_start_base){



 FILE *file;

    // Open the file in write mode (creates the file if it doesn't exist)
    file = fopen("output.txt", "w");

    // Check if the file opened successfully
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return 1; // Return an error code
    }

    // Write the string to the file
    fprintf(file, "%s", arr);

        if(*(ptr_start_base)!='\0'){
                    for(int i=0 ; i<len; i++){
                        for(int j=0; j<ch_at_line[i]; j++){
                            fprintf(file, "%c", arr[i][j]);
                                    }
                        fprintf(file, "%c\n");
                        }
                }

    // Close the file
    fclose(file);
    gotoxy(0,20);
    textattr(yellow);
    printf("Text saved to the file successfully!\n");
    textattr(normal);
    return 0;


}
