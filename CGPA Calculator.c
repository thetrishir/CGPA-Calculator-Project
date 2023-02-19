#include<stdio.h>
#include <stdlib.h>
#include<string.h>
void write();
double numgrd(double num);
void display();
void search();
void modify();
void delete_student();


int main()
{
    int choice;
    FILE *ptr=fopen("CGPA Calculating.txt","a");
    do
    {
        system("cls");
        printf("\t\t\tPROJECT: CALCULATING CGPA\n");
        printf("\tENTRY MENU\n\t1.CREATE STUDENT RECORD\n\t2.DISPLAY ALL\n\t3.SEARCH STUDENT RECORD\n\t4.MODIFY STUDENT RECORD\n\t5.DELETE STUDENT RECORD\n\t6.EXIT\n\tPlease Enter Your Choice (1-6):");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            system("cls");
            write();
            break;
        case 2:
            system("cls");
            display();
            break;
        case 3:
            system("cls");
            search();
            break;
        case 4:
            system("cls");
            modify();
            break;
        case 5:
            system("cls");
            delete_student();
            break;
        case 6:
            exit(0);
        default:
            printf("\a");
        }
    }
    while(choice!='7');
    return 0;
}


void write()
{
    int choice,i,j,n,s;
    char id[20],name[30],code[10],title[50];
    double num,gpa,cgpa,s_cgpa,credit,s_credit=0,pcgpa,p_credit,p_cgpa;
    FILE *ptr=fopen("CGPA Calculating.txt","a");
    if (!ptr)
    {
        printf("File not found or unable to open the input file!!\n");
        return ;
    }
    printf("\nEnter student ID:");
    scanf("%s",&id);
    printf("Enter student name:");
    scanf(" %[^\t\n]",&name);
    fprintf(ptr,"\nID: %s  Name: %s",id,name);
    printf("Enter total semester: ");
    scanf("%d",&n);
    for(i=1; i<=n; i++)
    {
        pcgpa =0;
        p_credit = 0;
        printf("\tEnter total subjects in semester-%d: ",i);
        scanf("%d",&s);
        for(j=0; j<s; j++)
        {
            printf("\tSubject-%d\n",j+1);
            printf("Enter course code: ");
            scanf("%s",&code);
            printf("Enter course title: ");
            scanf(" %[^\t\n]",&title);
            printf("Enter credits per course: ");
            scanf("%lf",&credit);
            printf("Enter grade points (Out of 100): ");
            scanf("%lf",&num);
            gpa=numgrd(num);

            fprintf(ptr,"\n%-10s %-30s %-7.1lf %.2lf",code,title,credit,gpa);
            cgpa = cgpa + (gpa*credit);
            s_credit = s_credit + credit;
            s_cgpa = cgpa / s_credit;

            pcgpa = pcgpa + (gpa*credit);
            p_credit = p_credit + credit;
            p_cgpa = pcgpa / p_credit;
        }
        printf("\nSemester-%d credit %.1lf, GPA %.2lf\n",i,p_credit,p_cgpa);
    }
    printf("\nYour CGPA is: %.2lf\nTotal credit: %.1lf\n", s_cgpa, s_credit);
    fprintf(ptr,"\nGPA: %.2lf CGPA: %.2lf Credit: %.1lf\n",p_cgpa, s_cgpa, s_credit);
    fclose(ptr);

    printf("\nEnter 1 to write student record again: ");
    scanf("%d", &choice);
    switch(choice)
    {
    case 0:
        break;
    case 1:
        write();
        break;
    default:
        printf("\a");
    }
}
double numgrd(double num)
{
    double gpa;
    if(100>=num && num>=97)
        gpa=4;
    else if(num<97&&num>=90)
        gpa=4;
    else if(num<90 && num>=87)
        gpa=3.70;
    else if(num<87 && num>=83)
        gpa=3.30;
    else if(num<83 && num>=80)
        gpa=3.00;
    else if(num<80 && num>=77)
        gpa=2.70;
    else if(num<77 && num>=73)
        gpa=2.30;
    else if(num<73 && num>=70)
        gpa=2.00;
    else if(num<70 && num>=67)
        gpa=1.70;
    else if(num<67 && num>=63)
        gpa=1.30;
    else if(num<63 && num>=60)
        gpa=1.00;
    else if(num<60)
        gpa=0.00;

    return gpa;
}


void display()
{
    int choice;
    char ch;
    FILE *ptr4=fopen("CGPA Calculating.txt","r");
    ch=fgetc(ptr4);
    printf("\n\tNow the content of the file %s is : \n","CGPA Calculating.txt");
    while(ch!=EOF)
    {
        printf("%c",ch);
        ch=fgetc(ptr4);
    }
    fclose(ptr4);
    printf("\n\nEnter 0 to go back to main:");
    scanf("%d", &choice);
    switch(choice)
    {
    case 0:
        break;
    default:
        printf("\a");
    }
}


void search()
{
    int choice, c=0;
    char id[20],tmp[250],fname[30],txt[4]=".txt";
    FILE *ptr5, *ptr2;
    ptr2= fopen("CGPA Calculating.txt", "r");
    printf("Enter student ID or Name you want to search:");
    scanf(" %[^\t\n]",&id);
    strcpy(fname,id);
    strncat(fname,txt,4);
    while(ptr2 && fgets(tmp,sizeof(tmp), ptr2 ))
    {
        if(strstr(tmp,id))
        {
            ptr5=fopen(fname,"w");
            printf("\n%s",tmp);
            fprintf(ptr5,"\n%s",tmp);
            while(fgets(tmp,sizeof(tmp), ptr2)!=strstr(tmp,"GPA"))
            {
                printf("%s",tmp);
                fprintf(ptr5,"%s",tmp);
            }
            if(strstr(tmp,"GPA"))
            {
                printf("%s",tmp);
                fprintf(ptr5,"%s\n",tmp);
                fclose(ptr5);
            }
            c++;
        }
    }
    if(c==0)
        printf("Student ID didn't match with the record.");
    fclose(ptr2);

    printf("\nEnter 0 to go back to main menu and 1 to search again: ");
    scanf("%d", &choice);
    switch(choice)
    {
    case 0:
        break;
    case 1:
        search();
        break;
    default:
        printf("\a");
    }
}


void modify()
{
    int lno=0,lno1,lno2,counter=0,c=0, choice;
    char ch,id[20],str[250],tmp[250],newln[250];
    FILE *fptr, *ptr4;
    ptr4= fopen("CGPA Calculating.txt", "r");
    fptr= fopen("temp.txt", "w");
    printf("Enter student ID you want to modify: ");
    scanf(" %[^\t\n]",&id);

    while(ptr4 && fgets(tmp,sizeof(tmp), ptr4 ))
    {
        lno++; /* count the line number */
        if(strstr(tmp,id))
        {
            lno1=lno;
            printf("\nLine-0: %s",tmp);
            while(fgets(tmp,sizeof(tmp), ptr4)!=strstr(tmp,"GPA"))
            {
                c++;
                printf("Line-%d: %s",c,tmp);
            }
            if(strstr(tmp,"GPA"))
                printf("Line-%d: %s\n",c+1,tmp);
        }
    }
    if(c==0)
        printf("Student ID didn't match with the record.");
    else
    {
        printf("\nInput the line no you want to replace : ");
        scanf("%d", &lno2);
        lno2=lno2+lno1;
        printf("Input the content of the new line : ");
        scanf(" %[^\t\n]",&newln);

        rewind(ptr4);
        while (!feof(ptr4))
        {
            strcpy(str, "\0");
            fgets(str, 250, ptr4);
            if (!feof(ptr4))
            {
                counter++; /* skip the line */
                if (counter!=lno2)
                    fprintf(fptr, "%s", str);
                else
                    fprintf(fptr, "%s\n", newln);
            }
        }
        fclose(ptr4);
        fclose(fptr);
        remove("CGPA Calculating.txt");
        rename("temp.txt","CGPA Calculating.txt");

        printf("\nThe Line has been successfully modified.");
    }
    fclose(ptr4);

    printf("\n\nEnter 0 to go back to main menu and 1 to modify again: ");
    scanf("%d", &choice);
    switch(choice)
    {
    case 0:
        break;
    case 1:
        modify();
        break;
    default:
        printf("\a");
    }
}


void delete_student()
{
    int lno=0,lno1, lno2=0,counter = 0, choice;;
    char ch,id[20],str[250],tmp[250];
    FILE *fptr, *ptr4;
    ptr4= fopen("CGPA Calculating.txt", "r");
    fptr= fopen("temp.txt", "w");
    printf("Enter student ID you want to Delete: ");
    scanf(" %[^\t\n]",&id);

    while(ptr4 && fgets(tmp,sizeof(tmp), ptr4 ))
    {
        lno++; /* count the line number */
        if(strstr(tmp,id))
        {
            lno1=lno;
            while(ptr4 && fgets(tmp,sizeof(tmp), ptr4)!=NULL)
            {
                lno2++;
                if(strstr(tmp,"GPA"))
                    break;
            }
        }
    }
    if(lno2==0)
        printf("\nStudent ID didn't match with the record.");
    else
    {
        lno2=lno2+lno1;

        rewind(ptr4);
        while (!feof(ptr4))
        {
            strcpy(str, "\0");
            fgets(str, 250, ptr4);
            if (!feof(ptr4))
            {
                counter++; /* skip the line */
                if (counter < lno1 || counter > lno2 )
                    fprintf(fptr, "%s", str);
            }
        }
        fclose(ptr4);
        fclose(fptr);
        remove("CGPA Calculating.txt");
        rename("temp.txt","CGPA Calculating.txt");

        ptr4=fopen("CGPA Calculating.txt","r");
        ch=fgetc(ptr4);
        printf("\n\tThe record has been deleted successfully.\n\tNow the content of the file %s is : \n","CGPA Calculating.txt");
        while(ch!=EOF)
        {
            printf("%c",ch);
            ch=fgetc(ptr4);
        }
    }
    fclose(ptr4);

    printf("\nEnter 0 to go back to main menu and 1 to delete again: ");
    scanf("%d", &choice);
    switch(choice)
    {
    case 0:
        break;
    case 1:
        delete_student();
        break;
    default:
        printf("\a");
    }
}
