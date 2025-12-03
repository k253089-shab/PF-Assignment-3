#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    int popularity;
    int lastUsed;   // smaller value = older = remove first
};

int findBook(struct Book shelf[], int capacity, int id) {
    int i;
    for (i = 0; i < capacity; i++) {
        if (shelf[i].id == id)
            return i;
    }
    return -1;
}

int findEmptySlot(struct Book shelf[], int capacity) {
    int i;
    for (i = 0; i < capacity; i++) {
        if (shelf[i].id == -1)
            return i;
    }
    return -1;
}

int findLRU(struct Book shelf[], int capacity) {
    int i;
    int index = 0;

    for (i = 1; i < capacity; i++) {
        if (shelf[i].lastUsed < shelf[index].lastUsed)
            index = i;
    }
    return index;
}

int main() {
    int capacity, Q;
    scanf("%d %d", &capacity, &Q);

    struct Book shelf[capacity];
    int i;
    for (i = 0; i < capacity; i++) {
        shelf[i].id = -1;
        shelf[i].popularity = 0;
        shelf[i].lastUsed = 0;
    }

    char operation[10];
    int x, y;
    int time = 1;  // updated on each access or add

    for (i = 0; i < Q; i++) {

        scanf("%s", operation);

        if (strcmp(operation, "ADD") == 0) {
            scanf("%d %d", &x, &y);

            int pos = findBook(shelf, capacity, x);

            if (pos != -1) {
                shelf[pos].popularity = y;
                shelf[pos].lastUsed = time++;
            } 
            else {
                int empty = findEmptySlot(shelf, capacity);

                if (empty != -1) {
                    shelf[empty].id = x;
                    shelf[empty].popularity = y;
                    shelf[empty].lastUsed = time++;
                }
                else {
                    int removeIndex = findLRU(shelf, capacity);

                    shelf[removeIndex].id = x;
                    shelf[removeIndex].popularity = y;
                    shelf[removeIndex].lastUsed = time++;
                }
            }
        }

        else if (strcmp(operation, "ACCESS") == 0) {
            scanf("%d", &x);

            int pos = findBook(shelf, capacity, x);

            if (pos == -1) {
                printf("-1\n");
            } else {
                printf("%d\n", shelf[pos].popularity);
                shelf[pos].lastUsed = time++;
            }
        }
    }

    return 0;
}
