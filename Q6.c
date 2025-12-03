#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];
    char membershipType[10];
    char regDate[20];
    char dob[20];
    char interest[10];
} Student;

Student *students = NULL;
int count = 0;

void loadDatabase(const char *filename) {
    FILE *f;
    long size;
    f = fopen(filename, "rb");
    if (!f) return;
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    rewind(f);
    count = size / sizeof(Student);
    students = (Student*) malloc(size);
    fread(students, sizeof(Student), count, f);
    fclose(f);
}

void saveDatabase(const char *filename) {
    FILE *f;
    f = fopen(filename, "wb");
    if (!f) return;
    fwrite(students, sizeof(Student), count, f);
    fclose(f);
}

void addStudent(Student s, const char *filename) {
    int i;
    for (i = 0; i < count; i++) {
        if (students[i].studentID == s.studentID) return;
    }
    students = (Student*) realloc(students, (count + 1) * sizeof(Student));
    students[count] = s;
    count++;
    saveDatabase(filename);
}

void updateStudent(int id) {
    int i;
    for (i = 0; i < count; i++) {
        if (students[i].studentID == id) {
            printf("New Batch: ");
            scanf("%s", students[i].batch);
            printf("New Membership Type: ");
            scanf("%s", students[i].membershipType);
            return;
        }
    }
}

void deleteStudent(int id) {
    int i;
    int index = -1;
    for (i = 0; i < count; i++) {
        if (students[i].studentID == id) {
            index = i;
            break;
        }
    }
    if (index == -1) return;
    for (i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }
    count--;
    students = (Student*) realloc(students, count * sizeof(Student));
}

void displayAll() {
    int i;
    for (i = 0; i < count; i++) {
        printf("%d %s %s %s %s %s %s\n",
               students[i].studentID,
               students[i].fullName,
               students[i].batch,
               students[i].membershipType,
               students[i].regDate,
               students[i].dob,
               students[i].interest);
    }
}

void batchReport(char *batchName) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(students[i].batch, batchName) == 0) {
            printf("%d %s %s\n",
                   students[i].studentID,
                   students[i].fullName,
                   students[i].membershipType);
        }
    }
}

int main() {
    int choice;
    int id;
    char batch[20];
    Student s;

    loadDatabase("members.dat");

    while (1) {
        printf("\n1.Add\n2.Update\n3.Delete\n4.View All\n5.Batch Report\n6.Exit\n");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("ID: ");
            scanf("%d", &s.studentID);

            printf("Full Name: ");
            fflush(stdin);
            gets(s.fullName);

            printf("Batch: ");
            scanf("%s", s.batch);

            printf("Membership: ");
            scanf("%s", s.membershipType);

            printf("Reg Date: ");
            scanf("%s", s.regDate);

            printf("DOB: ");
            scanf("%s", s.dob);

            printf("Interest: ");
            scanf("%s", s.interest);

            addStudent(s, "members.dat");
        }
        else if (choice == 2) {
            printf("Student ID: ");
            scanf("%d", &id);
            updateStudent(id);
            saveDatabase("members.dat");
        }
        else if (choice == 3) {
            printf("Student ID: ");
            scanf("%d", &id);
            deleteStudent(id);
            saveDatabase("members.dat");
        }
        else if (choice == 4) {
            displayAll();
        }
        else if (choice == 5) {
            printf("Batch Name: ");
            scanf("%s", batch);
            batchReport(batch);
        }
        else if (choice == 6) {
            saveDatabase("members.dat");
            break;
        }
    }

    free(students);
    return 0;
}
