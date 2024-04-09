#include "Register.h"
#include "Student.h"
#include "Course.h"


/*
Function Name: initialize
Purpose: Initialize the registration table, setting all entries to 0 to represent that no student is registered or dropped from any course.
Function in parameters: int ** regTable, int numRows, int numColumns
Function out parameter: void
Version: 1
*/
void initialize(int ** regTable, int numRows, int numColumns){
    
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numColumns; j++){
            regTable[i][j] = 0;
        }
    }
}

/*
Function Name: display
Purpose: Display the registration table showing all students and their registration status for each course. If a student is registered for a course, the status is "R", if a student is dropped from a course, the status is "D".
Function in parameters: int ** regTable, int numRows, int numColumns, int * students, char ** courses
Function out parameter: Integer - Number of total registered and dropped courses.
Version: 1
*/
int display(int ** regTable, int numRows, int numColumns, int * students, char ** courses)
{
    int i, j, k = 0;

    printf("                       Registration Table\n");
    printf("Registration Index     Student ID     Course ID     Registration Status\n");
    for(i = 0; i < numRows; i++){
        for(j = 0; j < numColumns; j++){
            if(regTable[i][j] == 1)
            {
                printf("%8d%14d%10s       R\n", k, students[i], courses[j]);
                k++;
            }
            if(regTable[i][j] == 2)
            {
                printf("%8d%14d%10s       D\n", k, students[i], courses[j]);
                k++;
            }
        }
    }

    return k;
}

/*
Function Name: registerStudent
Purpose: Register a student in a specific course. If the student has dropped the course or is already registered in it, it does not register the student again and returns 0. Else, it sets the registration status to 1 (Registered) and returns 1.
Function in parameters: int ** regTable, int rowIndex, int columnIndex, int * students, char ** courses
Function out parameter: Integer - 0 if the registration failed, 1 if the registration succeeded.
Version: 1
*/
int registerStudent(int ** regTable, int rowIndex, int columnIndex, int * students, char ** courses)
{   
    if(regTable[rowIndex][columnIndex] ==  2)
    {
        printf("Student id %d have dropped out from the course %s.\n", students[rowIndex], courses[columnIndex]);
        return 0;
    }

    if(regTable[rowIndex][columnIndex] == 1)
    {
        printf("Student id %d is already registered in the course %s.\n", students[rowIndex], courses[columnIndex]);
        return 0;
    }

    regTable[rowIndex][columnIndex] = 1;
    return 1;
}

/*
Function Name: drop
Purpose: Drops a student from a specific course. If the student is not registered or already dropped, it does not drop the student again and returns 0. Else, it sets the registration status to 2 (Dropped) and returns 1.
Function in parameters: int ** regTable, int rowIndex, int columnIndex, int * students, char ** courses
Function out parameter: Integer - 0 if dropping failed, 1 if dropping succeeded.
Version: 1
*/
int drop(int ** regTable, int rowIndex, int columnIndex, int * students, char ** courses)
{
    if(regTable[rowIndex][columnIndex] == 0)
    {
        printf("Student id %d is not registered in the course %s.\n", students[rowIndex], courses[columnIndex]);
        return 0;
    }

    if(regTable[rowIndex][columnIndex] == 2)
    {
        printf("Student id %d is already dropped from the course %s.\n", students[rowIndex], courses[columnIndex]);
        return 0;
    }

    regTable[rowIndex][columnIndex] = 2;
    return 1;
}

/*
Function Name: searchIndexes
Purpose: Search for the registration indexes of a specific registration based on the input index. The function finds the indexes in the registration table where the student has a registration status other than 0.
Function in parameters: int ** regTable, int numRows, int numColumns, int index, int * rowIndex, int * columnIndex
Function out parameter: void - The function doesn't return a value, it modifies the rowIndex and columnIndex variables passed by reference.
Version: 1
*/
void searchIndexes(int ** regTable, int numRows, int numColumns, int index, int * rowIndex, int * columnIndex)
{
    int i, j, k = -1;

    *rowIndex = -1;
    *columnIndex = -1;

    for(i = 0; i < numRows; i++)
    {
        for(j = 0; j < numColumns; j++)
        {
            if (regTable[i][j] != 0)
            {
                k++;
                if (k == index)
                {
                    *rowIndex = i;
                    *columnIndex = j;
                    return;        
                }
            }
        }       
    }   
}