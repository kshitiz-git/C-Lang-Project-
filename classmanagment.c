#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student_records{
    int rollno;
    char name[20];

    struct marks{
        int maths;
        int eng;
        int comp;

    }sub; // earlier i was using pointer sub to point the insider structure but its not working as fwrite was as a whole and do not write pointer after derefrencing it.

}stu;

int main(){

    int i = 1, choice; 
    printf("\t\t:: WELCOME ::\n");

    while(i){
        printf("\t\t:: ENTER CHOICE ::\n");
        printf("\t\t:: 1. ENTER RECORD ::\n");
        printf("\t\t:: 2. PRINT ALL RECORDS::\n");
        printf("\t\t:: 3. SEARCH RECORD ::\n");
        printf("\t\t:: 4. DELETE RECORD ::\n");
        printf("\t\t:: 5. DELETE ALL RECORD ::\n");
        printf("\t\t:: 6. EXIT ::\n\n\n");

        fflush(stdin);
        scanf("%d",&choice);


        stu *student,*readstudent,*searchstudent, *deletestudent;
        switch(choice){
            case(1):
                // Using DMA
                student = (stu*)calloc(1,sizeof(stu));

                FILE *fp;

                fp = fopen("class.txt","ab");
                
                // student->sub = (struct marks*) calloc(1,sizeof(struct marks));

                printf("ENTER NAME OF THE STUDENT\n");
                fflush(stdin);
                fgets(student->name,20,stdin);

                // fflush(stdin);
                printf("ENTER ROLL NO OF THE STUDENT\n");
                scanf("%d",&student->rollno);
            
                // fflush(stdin);
                printf("ENTER NO OF MATHS OF THE STUDENT\n");
                scanf("%d",&student->sub.maths);

                // fflush(stdin);
                printf("ENTER NO OF ENGLISH OF THE STUDENT\n");
                scanf("%d",&student->sub.eng);

                // fflush(stdin);
                printf("ENTER NO OF COMPUTER OF THE STUDENT\n");
                scanf("%d",&student->sub.comp);

                
                fwrite(student, sizeof(stu), 1, fp);

            fclose(fp);
            // free(student->sub);
            free(student);

            break;

            case(2):
                fp = fopen("class.txt","rb");

                fseek(fp,0,SEEK_SET);                        

                // stu *readstudent;
                readstudent = (stu*)calloc(1,sizeof(stu));
                // readstudent->sub = (struct marks*)calloc(1,sizeof(struct marks));
                // if(fread(readstudent,sizeof(stu),1, fp)==1){
                //     printf("GOING TO PRINT RECORDS\n\n");
                // }
                // fseek(fp,0,SEEK_SET);  

                int o = 1;

                while(fread(readstudent,sizeof(stu),1, fp)==1){
                    printf("RECORD %d :\n\n",o);
                    o++;
                    printf("NAME: %s",readstudent->name);
                    printf("ROLL NO: %d\n",readstudent->rollno);
                    printf("MATHS: %d\n",readstudent->sub.maths);
                    printf("ENGLISH: %d\n",readstudent->sub.eng);
                    printf("COMPUTER: %d\n\n",readstudent->sub.comp);
                }
                
                fclose(fp);
                // free(readstudent->sub);
                free(readstudent);
                break;

            case(3):
                printf("\t\t:: ENTER CHOICE ::\n");
                printf("\t\t:: 1. BY NAME ::\n");
                printf("\t\t:: 2. BY ROLL NO ::\n");
                scanf("%d",&choice);

                if(choice == 1) {
                    fp = fopen("class.txt","rb");
                    char name[20];
                    printf("ENTER NAME: \n\t ");
                    fflush(stdin);
                    fgets(name,20,stdin);
                    fflush(stdin);

                    searchstudent = (stu*) calloc(1,sizeof(stu));

                    while(fread(searchstudent,sizeof(stu),1,fp) == 1){
                        if(strcmp(searchstudent->name,name) == 0){
                            printf("NAME: %s",readstudent->name);
                            printf("ROLL NO: %d\n",readstudent->rollno);
                            printf("MATHS: %d\n",readstudent->sub.maths);
                            printf("ENGLISH: %d\n",readstudent->sub.eng);
                            printf("COMPUTER: %d\n\n",readstudent->sub.comp);
                        }
                        
                    }
                    fclose(fp);
                    free(searchstudent);

                }

                if(choice == 2) {
                    fp = fopen("class.txt","rb");
                    int roll_no;
                    printf("ENTER ROLL NO: \n\t ");
                    fflush(stdin);
                    scanf("%d",&roll_no);
                    fflush(stdin);

                    searchstudent = (stu*) calloc(1,sizeof(stu));

                    while(fread(searchstudent,sizeof(stu),1,fp) == 1){
                        if(searchstudent->rollno == roll_no){
                            printf("NAME: %s\n",searchstudent->name);
                            printf("ROLL NO: %d\n",searchstudent->rollno);
                            printf("COMPUTER MARKS: %d\n",searchstudent->sub.comp);
                            printf("ENGLISH MARKS: %d\n",searchstudent->sub.eng);
                            printf("MATHS MARKS: %d\n",searchstudent->sub.maths);
                        }
                        
                    }
                    fclose(fp);
                    free(searchstudent);

                }
                break;
            
            case(4):
                printf("\t\t:: ENTER CHOICE ::\n");
                printf("\t\t:: 1. BY NAME ::\n");
                printf("\t\t:: 2. BY ROLL NO ::\n");
                scanf("%d",&choice);

                if(choice == 1) {
                    fp = fopen("class.txt","rb");
                    char name[20];
                    printf("ENTER NAME: \n\t ");
                    fflush(stdin);
                    fgets(name,20,stdin);
                    fflush(stdin);

                    deletestudent = (stu*) calloc(1,sizeof(stu));
                    FILE *temp;
                    temp = fopen("temp.txt","wb"); // temperory file

                    while(fread(deletestudent,sizeof(stu),1,fp) == 1){
                        if(strcmp(deletestudent->name,name) != 0){
                            fwrite(deletestudent,sizeof(stu),1,temp);
                        }
                    }

                    fclose(temp);
                    fclose(fp);

                    remove("class.txt");
                    rename("temp.txt","class.txt");

                    free(deletestudent);
                    printf("RECORD DELETED\n");
                    break;

                }

                if(choice == 2) {
                    fp = fopen("class.txt","rb");
                    int roll_no;
                    printf("ENTER ROLL NO: \n\t ");
                    fflush(stdin);
                    scanf("%d",&roll_no);
                    fflush(stdin);

                    deletestudent = (stu*) calloc(1,sizeof(stu));
                    FILE *temp;
                    temp = fopen("temp.txt","wb"); // temperory file

                    while(fread(deletestudent,sizeof(stu),1,fp) == 1){
                        if(deletestudent->rollno != roll_no){
                            fwrite(deletestudent,sizeof(stu),1,temp);
                        }
                    }
                    fclose(temp);
                    fclose(fp);
                    
                    remove("class.txt");
                    rename("temp.txt","class.txt");
                    free(deletestudent);
                    printf("RECORD DELETED\n");
                
                    break;
            }

            case(5):
                fp = fopen("class.txt","wb");
                fclose(fp);
                printf("SUCCESSFULLY DELETED ALL RECORDS\n");
                break;

            case(6):
                i= 0;
                break;


            default:
                printf("WRONG CHOICE");


        }        



                                 

                    
 

    }

}

