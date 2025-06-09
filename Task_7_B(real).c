
//
// Created by adria on 09/06/2025.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100 // Maximum number of students
#define MAX_NAME 50      // Maximum name length

//Student structure
struct Student {
    int id;
    char name[MAX_NAME]; // String for name
    char grade;          // Character for grade A-F
};
// Function to load students from student_list.txt into an array, returning number of students
int loadStudents(struct Student students[]) {
    FILE *file = fopen("student_list.txt", "r"); // Read mode
    if (file == NULL) {
        return 0; // File doesn't exist or call error
    }

    int count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL && count < MAX_STUDENTS) {
        if (sscanf(line, "%d|%49[^|]|%c", &students[count].id, students[count].name, &students[count].grade) == 3) {
            count++;
        }
    }
    fclose(file);
    return count;
}
// Function check if ID exists in student_list.txt
int idExists(int id, struct Student students[], int count) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return 1; // ID found - end
        }
    }
    return 0; // ID not found
}
// Function add a student record to student_list.txt
void addStudent(int id, char *name, char grade) {
    struct Student students[MAX_STUDENTS];
    int count = loadStudents(students);
    if (idExists(id, students, count)) {
        printf("Error: Student with ID %d already exists!\n", id);
        return;
    }
    FILE *file = fopen("student_list.txt", "a"); // Append mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return ;
    }
// Write to file with delimiters
    fprintf(file, "%d|%s|%c\n", id, name, grade);
    printf("Student record added successfully!\n");
    fclose(file);
}

// Function to display all student records from array
void displayStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("No student records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    printf("ID\tName\t\t\tGrade\n");
    printf("--------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%-20s\t%c\n", students[i].id, students[i].name, students[i].grade);
    }
}

int main(void) {
    struct Student students[MAX_STUDENTS]; // Array to store students
    int count; // Number of students loaded
    char choice; // Menu choice
    int id; // Student ID input
    char name[MAX_NAME]; // Student name input
    char grade; // Student grade input

    // Menu loop
    do {
        count = loadStudents(students); // Load students before each operation
        printf("\n++++ STUDENT MANAGEMENT SYSTEM ++++\n");
        printf("1. Add Student\n2. Display Students\n3. Exit\n");
        printf("Enter your choice (1-3): ");
        choice = getchar();
        getchar();
        choice = tolower(choice);

        switch (choice) {
            case '1':
                printf("Enter student ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter student name: ");
                scanf("%[^\n]", name);
                getchar();
                printf("Enter student grade (A-F): ");
                scanf("%c", &grade);
                getchar();
                addStudent(id, name, grade);
                break;
            case '2':
                displayStudents(students, count);
                break;
            case '3':
                printf("EXITING PROGRAM\n----------------\n");
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
                break;
        }
    } while (1); // Loop until exit
}