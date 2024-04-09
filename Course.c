#include <stdio.h>
#include <stdlib.h>
#include "Course.h"


/*
Function Name: validCC
Purpose: Validate the course code. A valid course code has 3 uppercase letters followed by 4 digits.
Function in parameters: char * code - the course code to be validated
Function out parameter: Integer - 1 if the course code is valid, 0 otherwise.
Version: 1
*/
int validCC(char * code)
{
    int i, ch;
    int len = strlen(code);

    if (len != CCLEN)
    {
        printf("Incorrect Course Id length [7-character Id]\n");
        while ((ch = getchar()) != '\n' && ch != EOF);
        return 0;
    }

    for(i = 0; i < 3; i++)
    {
        //checking if the character is a lowercase letter
        if (code[i] >= 'a' && code[i] <= 'z') code[i] -= 32; //Turn the lowercase letter to uppercase letter

        if (!(code[i] >= 'A' && code[i] <= 'Z'))
        {
            printf("Incorrect Course Id input [3-Alphas][4-digits]\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
            return 0;
        }
    }

    for(i = 3; i < len; i++){
        if (!(code[i] >= '0' && code[i] <= '9')) 
        {
            printf("Incorrect Course Id input [3-Alphas][4-digits]\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
            return 0;
        }
    }

    return 1;
}

/*
Function Name: readCC
Purpose: Reads the course code from the input. If the entered code is not valid, it keeps asking for a valid code until one is provided.
Function in parameters: int ind - index of the course, int m - mode (0 for adding a new course, 1 for registering a student in a course)
Function out parameter: char* - the valid course code read from the input
Version: 1
*/
char * readCC(int ind, int m){
    int b;
    char *code = (char *)malloc(CCLEN + 1);
    if (code == NULL)
    {
        printf("Could not allocate memory.\n");
        return NULL;
    }

    while(1){
        if (m == 0) printf("Enter the course index[%d] course id [3-Alphas][4-digits]: ", ind);
        else printf("Enter the course id [3-Alphas][4-digits]: ");
        b = scanf("%7s", code);

        if(b == 1 && validCC(code)) break;
        /*{
            printf("Incorrect Course Id \n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
        else break;*/ 
    }

    return code;
}

/*
Function Name: courseExists
Purpose: Checks whether a course with a given code already exists.
Function in parameters: char **courses - an array of existing course codes, int len - length of the array, char * code - the code of the course to be checked
Function out parameter: Integer - index of the course if the course exists, -1 otherwise
Version: 1
*/
int courseExists(char ** courses, int len, char * code){
    int i;
    for(i = 0; i < len; i++){
        if(strcmp(courses[i], code) == 0)
        {
            return i;
        }
    }

    return -1;
}

/*
Function Name: displayCourses
Purpose: Prints a list of course codes.
Function in parameters: char **courses - an array of existing course codes, int len - length of the array
Function out parameter: void
Version: 1
*/
void displayCourses(char ** courses, int len){
    printf("List of Available Course Id's\n");
    for(int i = 0; i < len; i++){
        printf("Index %d%14s\n", i, courses[i]);
    }
}

/*
Function Name: freeCoursesMemory
Purpose: Frees the memory allocated to the courses array.
Function in parameters: char **courses - an array of existing course codes, int len - length of the array
Function out parameter: void
Version: 1
*/
void freeCoursesMemory(char ** courses, int len)
{
    int i;
    for(i = 0; i < len; i++)
    {
        free(courses[i]);
    }   

    free(courses);
}