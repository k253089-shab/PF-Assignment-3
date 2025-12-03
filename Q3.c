#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void displayEmployees(struct Employee emp[], int n) {
    int i;
    printf("\nEmployee Records:\n");
    printf("ID\tName\t\tDesignation\tSalary\n");
    printf("-----------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%s\t\t%s\t%.2f\n",
               emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
    }
}

void findHighestSalary(struct Employee emp[], int n) {
    int i, index = 0;

    for (i = 1; i < n; i++) {
        if (emp[i].salary > emp[index].salary) {
            index = i;
        }
    }

    printf("\nEmployee with Highest Salary:\n");
    printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
           emp[index].id, emp[index].name, emp[index].designation, emp[index].salary);
}

void searchEmployee(struct Employee emp[], int n) {
    int choice;
    int id, i;
    char name[50];
    int found = 0;

    printf("\nSearch By:\n1. Employee ID\n2. Employee Name\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter ID to search: ");
        scanf("%d", &id);

        for (i = 0; i < n; i++) {
            if (emp[i].id == id) {
                printf("\nEmployee Found:\nID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
                found = 1;
                break;
            }
        }
    } 
    else if (choice == 2) {
        printf("Enter Name to search: ");
        scanf("%s", name);

        for (i = 0; i < n; i++) {
            if (strcmp(emp[i].name, name) == 0) {
                printf("\nEmployee Found:\nID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Employee not found.\n");
    }
}

int main() {
    int n, i;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee emp[n];

    for (i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &emp[i].id);

        printf("Name: ");
        scanf("%s", emp[i].name);

        printf("Designation: ");
        scanf("%s", emp[i].designation);

        printf("Salary: ");
        scanf("%f", &emp[i].salary);
    }

    displayEmployees(emp, n);
    findHighestSalary(emp, n);
    searchEmployee(emp, n);

    return 0;
}
