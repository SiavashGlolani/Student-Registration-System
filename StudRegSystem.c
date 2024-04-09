

/*  Function Name: main
Purpose: This is the main function where the program execution starts. It implements the menu for the student registration system. It includes initializing, registering, dropping, and displaying students' registration. It also manages memory allocation and deallocation for various entities in the system such as students, courses, and registration data.
Function in parameters: void
Function out parameter: Integer - 0 if the program executed successfully and there was enough memory to allocate. Otherwise, the function will terminate prematurely if there's not enough memory, hence not returning anything.
Version: 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Student.h"
#include "Course.h"
#include "Register.h"

#define REGISTER 1
#define DROP 2
#define DISPLAY 3
#define EXIT 4

int main(){

    int input, b, numStudents, a, i, studentID, ch, numCourses, studentIndex, courseIndex, reg, num, index, drp;
    char * courseCode;
    char dummy[101];
    int *students;
    char **courses;
    int **registration;

    printf("Welcome to Student Registration System\n");
    printf("\n");

    do{
        printf("Enter the number of students to register: ");
        fflush(stdout);
        a = scanf("%d", &numStudents);

        if(a != 1 || numStudents <= 0)
        {
            printf("Invalid number of students. Try again\n");
            while ((ch = getchar()) != '\n' && ch != EOF);     
        }
    } while(a != 1 || numStudents <= 0);
        
    students = (int *)malloc(numStudents * sizeof(int));
    
    if (students == NULL)
    {
        printf("Could not allocate memory for students.\n");
        return 0;
    }

    for(i = 0; i < numStudents; i++){
        int b = 0;
        do
        {
            studentID = readID(i, 0);
            b = studentExists(students, i, studentID);
            if (b != -1) printf("The student ID %d already exists, enter a different ID.\n", studentID);
        }
        while(b != -1);

        students[i] = studentID;
    }
    
    do {
        printf("Enter the number of courses available: ");
        fflush(stdout);
        a = scanf("%d", &numCourses);

        if(a != 1 || numCourses <= 0)
        {
            printf("Invalid input. Try again\n");
            while ((ch = getchar()) != '\n' && ch != EOF);     
        }
    } while(a != 1 || numCourses <= 0);
        
    courses = (char **)malloc(numCourses * sizeof(char *));

    if (courses == NULL)
    {
        printf("Could not allocate memory for courses.\n");
        return 0;
    }

    for(i = 0; i < numCourses; i++){
        int b = 0;
        do
        {
            courseCode = readCC(i, 0);
            b = courseExists(courses, i, courseCode);
            
            if (b != -1) 
            {
                printf("The course code %s already exists, enter a different ID.\n", courseCode);
                free(courseCode);
            }
        }
        while(b != -1);

        courses[i] = courseCode;
    }

    //Allocating memory for the registration table
    registration = (int **)malloc(numStudents * sizeof(int *));

    if (registration == NULL)
    {
        printf("Could not allocate memory for the registration table.\n");
        return 0;
    }

    for(i = 0; i < numStudents; i++)
    {
        registration[i] = (int *)malloc(numCourses * sizeof(int));
        if (registration[i] == NULL)
        {
            printf("Could not allocate memory for the registration table.\n");
            return 0;
        }
    }

    initialize(registration, numStudents, numCourses);

    do{
        printf("Main Menu: \n");
        printf("[%d] Register a student into a course.\n", REGISTER);
        printf("[%d] Drop a student from a course.\n", DROP);
        printf("[%d] Display Registration table.\n", DISPLAY);
        printf("[%d] Exit.\n", EXIT);
        printf("Enter an option from the menu: ");
        b = scanf("%d", &input);

        if(b != 1)
        {
            printf("Error: Invalid input. Try again\n");
            fgets(dummy, sizeof dummy, stdin);        
            continue;
        }
        switch(input){
            case EXIT:
            printf("Exiting...\n");
            break;

            case REGISTER:
            displayStudents(students, numStudents);
            do
            {
                studentID = readID(0, 1);
                studentIndex = studentExists(students, numStudents, studentID);
                if (studentIndex == -1) printf("The student ID %d does not exist!\n", studentID);
            }
            while(studentIndex == -1);

            
            displayCourses(courses, numCourses);
            do
            {
                courseCode = readCC(0, 1);
                courseIndex = courseExists(courses, numCourses, courseCode);
                if(courseIndex == -1) 
                {
                    printf("The course code %s does not exist!\n", courseCode);
                    free(courseCode);
                }
            }while(courseIndex == -1);

            reg = registerStudent(registration, studentIndex, courseIndex, students, courses);

            if(reg == 1) 
            {
                printf("Registration succesful.\n");
            }
            else
            {
                printf("Student id %d cannot be registered to the course %s.\n", studentID, courseCode);
                printf("Registration Unsuccesful.\n");
            }   

            free(courseCode);
            break;

            case DROP:
            num = display(registration, numStudents, numCourses, students, courses);
            index = -1;

            do{
                printf("Please select Index number to drop student registration: ");
                b = scanf("%d", &index);
                if(b != 1)
                {
                    printf("Invalid Input, Try again.\n");
                    while ((ch = getchar()) != '\n' && ch != EOF);
                }   
                else if (index < 0 || index >= num) 
                    printf("Invalid registration index. Try again.\n");
            }
            while(index < 0 || index >= num);

            searchIndexes(registration, numStudents, numCourses, index, &studentIndex, &courseIndex);

            drp = drop(registration, studentIndex, courseIndex, students, courses);

            if(drp == 1) printf("Drop course successful.\n");
            else
            {
                printf("Student id %d cannot be dropped from from the course %s.\n", students[studentIndex], courses[courseIndex]);
                printf("Drop Unsuccesful.\n");
            }

            break;

            case DISPLAY:
            display(registration, numStudents, numCourses, students, courses);
            break;

            default:
            printf("Error. User may select only options 1 to 4.\n");
        }

    }while(input != EXIT);

    free(students);
    freeCoursesMemory(courses, numCourses);

    for(i = 0; i < numStudents; i++)
        free(registration[i]);

    free(registration);
    return 0;

}
