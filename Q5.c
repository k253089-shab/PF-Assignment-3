#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Editor structure */
typedef struct {
    char **lines;
    size_t size;
    size_t capacity;
} Editor;

void *safeMalloc(size_t n) {
    void *p = malloc(n);
    if (p == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    return p;
}

void *safeRealloc(void *ptr, size_t n) {
    void *p = realloc(ptr, n);
    if (p == NULL && n != 0) {
        printf("Memory reallocation failed!\n");
        exit(1);
    }
    return p;
}

char *readLineFile(FILE *fp) {
    size_t cap = 80;
    size_t len = 0;
    char *buf = safeMalloc(cap);

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') break;

        if (len + 1 >= cap) {
            cap *= 2;
            buf = safeRealloc(buf, cap);
        }
        buf[len++] = (char)ch;
    }

    if (len == 0 && ch == EOF) {
        free(buf);
        return NULL;
    }

    buf[len] = '\0';
    buf = safeRealloc(buf, len + 1);
    return buf;
}

char *readLineStdin(const char *msg) {
    printf("%s", msg);
    return readLineFile(stdin);
}

void initEditor(Editor *ed) {
    ed->size = 0;
    ed->capacity = 4;
    ed->lines = safeMalloc(ed->capacity * sizeof(char *));
}

void ensureCapacity(Editor *ed, size_t needed) {
    if (ed->capacity >= needed) return;

    size_t newCap = ed->capacity * 2;
    while (newCap < needed) newCap *= 2;

    ed->lines = safeRealloc(ed->lines, newCap * sizeof(char *));
    ed->capacity = newCap;
}

void insertLine(Editor *ed, size_t index, const char *text) {
    if (index > ed->size) {
        printf("Invalid index!\n");
        return;
    }

    ensureCapacity(ed, ed->size + 1);

    if (index < ed->size) {
        memmove(&ed->lines[index + 1],
                &ed->lines[index],
                (ed->size - index) * sizeof(char *));
    }

    size_t len = strlen(text);
    char *copy = safeMalloc(len + 1);
    strcpy(copy, text);

    ed->lines[index] = copy;
    ed->size++;
}

void deleteLine(Editor *ed, size_t index) {
    if (index >= ed->size) {
        printf("Invalid index!\n");
        return;
    }

    free(ed->lines[index]);

    if (index + 1 < ed->size) {
        memmove(&ed->lines[index],
                &ed->lines[index + 1],
                (ed->size - index - 1) * sizeof(char *));
    }

    ed->size--;
}

void printAllLines(Editor *ed) {
    printf("\n----- BUFFER -----\n");
    for (size_t i = 0; i < ed->size; i++) {
        printf("%zu: %s\n", i, ed->lines[i]);
    }
}

void shrinkToFit(Editor *ed) {
    if (ed->size == 0) return;

    ed->lines = safeRealloc(ed->lines,
                            ed->size * sizeof(char *));
    ed->capacity = ed->size;

    printf("Buffer shrunk to exact size.\n");
}

void freeAll(Editor *ed) {
    for (size_t i = 0; i < ed->size; i++)
        free(ed->lines[i]);

    free(ed->lines);
    ed->lines = NULL;
    ed->size = 0;
    ed->capacity = 0;
}

void saveToFile(Editor *ed, const char *file) {
    FILE *fp = fopen(file, "w");
    if (!fp) {
        printf("File open failed!\n");
        return;
    }

    for (size_t i = 0; i < ed->size; i++)
        fprintf(fp, "%s\n", ed->lines[i]);

    fclose(fp);
}

void loadFromFile(Editor *ed, const char *file) {
    FILE *fp = fopen(file, "r");
    if (!fp) {
        printf("File open failed!\n");
        return;
    }

    freeAll(ed);
    initEditor(ed);

    char *line;
    while ((line = readLineFile(fp)) != NULL) {
        insertLine(ed, ed->size, line);
        free(line);
    }

    fclose(fp);
}

int main() {
    Editor ed;
    initEditor(&ed);

    while (1) {
        printf("\n1.Insert  2.Delete  3.Print  4.Save  5.Load  6.Shrink  7.Exit\nChoice: ");
        int choice;
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            char *text = readLineStdin("Enter text: ");
            size_t index;
            printf("Index: ");
            scanf("%zu", &index); getchar();

            insertLine(&ed, index, text);
            free(text);
        }
        else if (choice == 2) {
            size_t index;
            printf("Index: ");
            scanf("%zu", &index); getchar();
            deleteLine(&ed, index);
        }
        else if (choice == 3) {
            printAllLines(&ed);
        }
        else if (choice == 4) {
            char name[100];
            printf("Filename: ");
            gets(name);
            saveToFile(&ed, name);
        }
        else if (choice == 5) {
            char name[100];
            printf("Filename: ");
            gets(name);
            loadFromFile(&ed, name);
        }
        else if (choice == 6) {
            shrinkToFit(&ed);
        }
        else if (choice == 7) {
            freeAll(&ed);
            break;
        }
    }

    return 0;
}
