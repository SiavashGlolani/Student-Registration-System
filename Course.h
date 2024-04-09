#include <stdio.h>
#include <string.h>

#define CCLEN 7

int validCC(char *);
char * readCC(int, int);
int courseExists(char **, int, char *);
void displayCourses(char **, int);
void freeCoursesMemory(char **, int);
