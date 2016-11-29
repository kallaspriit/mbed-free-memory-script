#include "mbed.h"

#define FREEMEM_CELL 10

struct elem {
    struct elem *next;
    char dummy[FREEMEM_CELL-2];
};

// based on https://developer.mbed.org/questions/6994/How-to-print-Free-RAM-available-RAM-or-u/
int getFreeMemory(void) {
    int counter;
    struct elem *head, *current, *nextone;

    current = head = (struct elem*) malloc(sizeof(struct elem));

    if (head == NULL) {
        return 0;
	}

    counter = 0;

	//__disable_irq();

    do {
        counter++;
        current->next = (struct elem*) malloc(sizeof(struct elem));
        current = current->next;
    } while (current != NULL);

    current = head;

    do {
        nextone = current->next;
        free(current);
        current = nextone;
    } while (nextone != NULL);

	//__enable_irq();

    return counter * FREEMEM_CELL;
}

int main() {
	while (true) {
		int freeMemoryBytes = getFreeMemory();

		printf("> free memory: %d\n", freeMemoryBytes);

		wait(1.0f);
	}
}
