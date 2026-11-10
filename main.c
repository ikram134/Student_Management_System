#include <stdio.h>
#include <stdlib.h>

struct Student {
int id;
char name[50];
int age;
char course[50];
float grade;
};

// Add Student
void addStudent() {
struct Student s;

FILE *f = fopen("students.dat", "ab");

if (f == NULL) {
printf("Error opening file!\n");
return;
}

printf("Enter ID: ");
scanf("%d", &s.id);

printf("Enter Name: ");
scanf(" %49[^\n]", s.name);

printf("Enter Age: ");
scanf("%d", &s.age);

printf("Enter Course: ");
scanf(" %49[^\n]", s.course);

printf("Enter Grade: ");
scanf("%f", &s.grade);

fwrite(&s, sizeof(s), 1, f);

fclose(f);

printf("Student added successfully!\n");
}

// Display Students
void displayStudents() {
struct Student s;

FILE *f = fopen("students.dat", "rb");

if (f == NULL) {
printf("No students found!\n");
return;
}

printf("\n===== STUDENT LIST =====\n");

while (fread(&s, sizeof(s), 1, f) == 1) {
printf("\nID: %d\n", s.id);
printf("Name: %s\n", s.name);
printf("Age: %d\n", s.age);
printf("Course: %s\n", s.course);
printf("Grade: %.2f\n", s.grade);
}

fclose(f);
}

// Search Student
void searchStudent() {
struct Student s;
int id;
int found = 0;

FILE *f = fopen("students.dat", "rb");

if (f == NULL) {
printf("No students found!\n");
return;
}

printf("Enter Student ID: ");
scanf("%d", &id);

while (fread(&s, sizeof(s), 1, f) == 1) {
if (s.id == id) {
printf("\nStudent Found!\n");
printf("Name: %s\n", s.name);
printf("Age: %d\n", s.age);
printf("Course: %s\n", s.course);
printf("Grade: %.2f\n", s.grade);

found = 1;
break;
}
}

if (found == 0) {
printf("Student not found!\n");
}

fclose(f);
}

// Update Student
void updateStudent() {
struct Student s;
int id;
int found = 0;

FILE *f = fopen("students.dat", "rb+");

if (f == NULL) {
printf("No students found!\n");
return;
}

printf("Enter Student ID: ");
scanf("%d", &id);

while (fread(&s, sizeof(s), 1, f) == 1) {
if (s.id == id) {

printf("Enter New Name: ");
scanf(" %49[^\n]", s.name);

printf("Enter New Age: ");
scanf("%d", &s.age);

printf("Enter New Course: ");
scanf(" %49[^\n]", s.course);

printf("Enter New Grade: ");
scanf("%f", &s.grade);

fseek(f, -(long)sizeof(s), SEEK_CUR);

fwrite(&s, sizeof(s), 1, f);

found = 1;
printf("Student updated successfully!\n");
break;
}
}

if (found == 0) {
printf("Student not found!\n");
}

fclose(f);
}

// Delete Student
void deleteStudent() {
struct Student s;
int id;
int found = 0;

FILE *f = fopen("students.dat", "rb");
FILE *temp = fopen("temp.dat", "wb");

if (f == NULL || temp == NULL) {
printf("File error!\n");

if (f != NULL)
fclose(f);

if (temp != NULL)
fclose(temp);

return;
}

printf("Enter Student ID: ");
scanf("%d", &id);

while (fread(&s, sizeof(s), 1, f) == 1) {

if (s.id == id) {
found = 1;
} else {
fwrite(&s, sizeof(s), 1, temp);
}
}

fclose(f);
fclose(temp);

if (found == 1) {
remove("students.dat");
rename("temp.dat", "students.dat");

printf("Student deleted successfully!\n");
} else {
remove("temp.dat");
printf("Student not found!\n");
}
}

// Main Function
int main() {
int choice;

do {
printf("\n================================\n");
printf(" STUDENT MANAGEMENT SYSTEM\n");
printf("================================\n");

printf("1. Add Student\n");
printf("2. Display Students\n");
printf("3. Search Student\n");
printf("4. Update Student\n");
printf("5. Delete Student\n");
printf("0. Exit\n");

printf("================================\n");

printf("Enter your choice: ");
scanf("%d", &choice);

switch (choice) {

case 1:
addStudent();
break;

case 2:
displayStudents();
break;

case 3:
searchStudent();
break;

case 4:
updateStudent();
break;

case 5:
deleteStudent();
break;

case 0:
printf("Goodbye!\n");
break;

default:
printf("Invalid choice!\n");
}

} while (choice != 0);

return 0;
}
