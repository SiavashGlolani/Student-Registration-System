#include "Student.h"

/*
Function Name: validID
Purpose: Validate whether a student's ID is valid. A valid student ID has 5 digits.
Function in parameters: int id - the student ID to be validated
Function out parameter: Integer - 1 if the student ID is valid, 0 otherwise.
Version: 1
*/
int validID(int id)
{
    if (id >= 10000 && id <= 99999) return 1;
    return 0;
}

/*
Function Name: readID
Purpose: Reads the student ID from the input. If the entered ID is not valid, it keeps asking for a valid ID until one is provided.
Function in parameters: int ind - index of the student, int m - mode (0 for adding a new student, 1 for registering a course for an existing student)
Function out parameter: Integer - the valid student ID read from the input
Version: 1
*/
int readID(int ind, int m)
{
    int id, b, ch;
    while(1){
        if (m == 0) printf("Enter the student index[%d] student id [5-digits]: ", ind);
        else printf("Enter the Student's Id to register a course: ");

        b = scanf("%d", &id);
        if(b != 1)
        {
            printf("Error: Invalid student ID. Try again\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
        else if (!validID(id))
        {
            printf("Student Id must be 5 digits\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
        else break; 
    }

    return id;
}

/*
Function Name: studentExists
Purpose: Checks whether a student with a given ID already exists.
Function in parameters: int *students - an array of existing student IDs, int len - length of the array, int id - the ID of the student to be checked
Function out parameter: Integer - index of the student if the student exists, -1 otherwise
Version: 1
*/
int studentExists(int *students, int len, int id)
{
    int i;

    for(i = 0; i < len; i++){
        if(students[i] == id)
        {
            return i;
        }
    }
    
    return -1;
}

/*
Function Name: displayStudents
Purpose: Prints a list of student IDs.
Function in parameters: int *students - an array of existing student IDs, int len - length of the array
Function out parameter: void
Version: 1
*/
void displayStudents(int *students, int len){
    printf("List of Student IDs\n");
    for(int i = 0; i < len; i++){
        printf("Index %d%12d\n", i, students[i]);
    }
}
