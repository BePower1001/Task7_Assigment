//
// Created by adria on 08/06/2025.
//
#include <stdio.h>
#include <ctype.h>


struct Student { // Student structure
    int id;
    char name[50]; // String for name
    char grade;    // String for grade ABCF
};

// Function adding record to students.txt
void addStudent(void) {
    struct Student stu;
    FILE *file = fopen("student_list.txt", "a"); // Append mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Student data input
    printf("Enter student ID: ");
    scanf("%d", &stu.id);
    getchar();
    printf("Enter student name: ");
    scanf("%[^\n]", stu.name); // Read string with space (all white)
    getchar();
    printf("Enter student grade (A-F): ");
    scanf("%c", &stu.grade);
    getchar();

    // Write to file with delimiter
    fprintf(file, "%d|%s|%c\n", stu.id, stu.name, stu.grade); // line | as delimiter
    printf("Student record added successfully!\n");
    fclose(file);
}

// Function to display student records from txt file
void displayStudents(void) {
    FILE *file = fopen("student_list.txt", "r"); // Read mode
    if (file == NULL) {
        printf("Error opening file or file does not exist!\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    printf("ID\tName\t\t\tGrade\n");
    printf("--------------------------------\n");

    char line[100]; //buff for each line
    while (fgets(line, sizeof(line), file) != NULL) {
        struct Student stu;
        // ID|name|grade
        if (sscanf(line, "%d|%49[^|]|%c", &stu.id, stu.name, &stu.grade) == 3) {
            printf("%d\t%-20s\t%c\n", stu.id, stu.name, stu.grade);
        } else {
            printf("Error reading record: %s", line);
        }
    }

    fclose(file);
}

int main(void) {
    char choice; // Menu choice

    // Menu loop
    do {
        printf("\n++++ STUDENT MANAGEMENT SYSTEM ++++\n");
        printf("1. Add Student\n2. Display Students\n3. Exit\n");
        printf("Enter your choice (1-3): ");
        choice = getchar();
        getchar();
        choice = tolower(choice);

        switch (choice) {
            case '1':
                addStudent();
                break;
            case '2':
                displayStudents();
                break;
            case '3':
                printf("EXITING PROGRAM\n----------------\n");
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
                break;
        }
    } while (1);

}