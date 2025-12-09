#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

int main() {
    FILE *fp;
    struct Employee emp;
    int choice, pos, id, found;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("employee.dat", "wb+");
        if (fp == NULL) {
            printf("Error creating file!\n");
            return 1;
        }
    }

    while (1) {
        printf("\n--- RANDOM ACCESS FILE (EMPLOYEE DETAILS) ---\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by Position\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter Employee ID: ");
            scanf("%d", &emp.id);
            printf("Enter Employee Name: ");
            scanf("%s", emp.name);
            printf("Enter Salary: ");
            scanf("%f", &emp.salary);

            fseek(fp, 0, SEEK_END);
            fwrite(&emp, sizeof(emp), 1, fp);
            printf("Employee added successfully!\n");
            break;

        case 2:
            rewind(fp);
            printf("\n--- EMPLOYEE LIST ---\n");
            while (fread(&emp, sizeof(emp), 1, fp)) {
                printf("ID: %d  Name: %s  Salary: %.2f\n",
                       emp.id, emp.name, emp.salary);
            }
            break;

        case 3:
            printf("Enter record position (starting from 1): ");
            scanf("%d", &pos);

            fseek(fp, (pos - 1) * sizeof(emp), SEEK_SET);

            if (fread(&emp, sizeof(emp), 1, fp)) {
                printf("\nRecord Found:\n");
                printf("ID: %d  Name: %s  Salary: %.2f\n",
                       emp.id, emp.name, emp.salary);
            } else {
                printf("No record found at given position.\n");
            }
            break;

        case 4:
            fclose(fp);
            printf("Exiting program...\n");
            return 0;

        default:
            printf("Invalid option! Try again.\n");
        }
    }
}

