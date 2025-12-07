#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    char branch[20];
    float marks;
};

void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    getchar(); // clear newline

    printf("Enter name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter branch: ");
    fgets(s.branch, sizeof(s.branch), stdin);
    s.branch[strcspn(s.branch, "\n")] = '\0';

    printf("Enter marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);

    printf("Record added successfully.\n");
}

void displayAll() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found (file not present).\n");
        return;
    }

    printf("\n==== All Student Records ====\n");
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        printf("Roll   : %d\n", s.roll);
        printf("Name   : %s\n", s.name);
        printf("Branch : %s\n", s.branch);
        printf("Marks  : %.2f\n", s.marks);
        printf("-------------------------------\n");
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("\nRecord found:\n");
            printf("Roll   : %d\n", s.roll);
            printf("Name   : %s\n", s.name);
            printf("Branch : %s\n", s.branch);
            printf("Marks  : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
    }

    fclose(fp);
}

void modifyStudent() {
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb+");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter roll number to modify: ");
    scanf("%d", &roll);
    getchar(); // clear newline

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("Existing Record:\n");
            printf("Roll   : %d\n", s.roll);
            printf("Name   : %s\n", s.name);
            printf("Branch : %s\n", s.branch);
            printf("Marks  : %.2f\n\n", s.marks);

            printf("Enter new name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';

            printf("Enter new branch: ");
            fgets(s.branch, sizeof(s.branch), stdin);
            s.branch[strcspn(s.branch, "\n")] = '\0';

            printf("Enter new marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -((long)sizeof(struct Student)), SEEK_CUR);
            fwrite(&s, sizeof(struct Student), 1, fp);

            printf("Record updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
    }

    fclose(fp);
}

void deleteStudent() {
    FILE *fp, *fpTemp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    fpTemp = fopen("temp.dat", "wb");
    if (fpTemp == NULL) {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return;
    }

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct Student), 1, fpTemp);
        }
    }

    fclose(fp);
    fclose(fpTemp);

    if (found) {
        remove("students.dat");
        rename("temp.dat", "students.dat");
        printf("Record deleted successfully.\n");
    } else {
        remove("temp.dat");
        printf("Record not found.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n===== STUDENT RECORD MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Student by Roll\n");
        printf("4. Modify Student Record\n");
        printf("5. Delete Student Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            modifyStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            printf("Exiting program...\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
