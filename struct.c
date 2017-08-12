#include <stdio.h>
#include <cs50.h>

#define STUDENTS 3

typedef struct {
    char *name;
    char *dorm;
} student;



int main(void) {
    
    student students[STUDENTS];
    
    for (int i=0; i< STUDENTS; i++) {
        printf("Name of student #%i: ", i+1);
        students[i].name = get_string();
        printf("Dorm of student #%i: ", i+1);
        students[i].dorm = get_string();
    }
    
    
    for (int i=0; i< STUDENTS; i++) {
        printf("Name of student #%i: %s\n", i+1, students[i].name);
        printf("Dorm of student #%i: %s\n", i+1, students[i].dorm);
    }
}