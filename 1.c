#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct part {
    char reference[20];
    char name[20];
    int quantity;
    int sellingprice;
    int purchaseprice;
    struct part* next;
} part;

#define FILE_NAME "stock.txt"
void display(part* head);
part* addPart(part* head);
part* removePart(part* head);
void modifyPart(part* head);
void saveToFile(part* head);
part* loadFromFile();


void display(part* head) {
    if (head == NULL) {
        printf("Stock is empty.\n");
        return;
    }
    part* p = head;
    while (p != NULL) {
        printf("Reference: %s\n", p->reference);
        printf("Name: %s\n", p->name);
        printf("Quantity: %d\n", p->quantity);
        printf("Selling Price: %d\n", p->sellingprice);
        printf("Purchase Price: %d\n", p->purchaseprice);
        printf("----------------------\n");
        p = p->next;
    }
}

part* addPart(part* head) {
    part* newPart = (part*)malloc(sizeof(part));
    if (newPart == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }
    printf("Enter reference: ");
    scanf("%s", newPart->reference);
    printf("Enter name: ");
    scanf("%s", newPart->name);
    printf("Enter quantity: ");
    scanf("%d", &newPart->quantity);
    printf("Enter selling price: ");
    scanf("%d", &newPart->sellingprice);
    printf("Enter purchase price: ");
    scanf("%d", &newPart->purchaseprice);
    newPart->next = head;
    head = newPart;
    printf("Part added successfully.\n");
    saveToFile(head);
    return head;
}

part* removePart(part* head) {
    if (head == NULL) {
        printf("Stock is empty. Nothing to remove.\n");
        return head;
    }
    char ref[20];
    printf("Enter reference of the part to remove: ");
    scanf("%s", ref);

    part *current = head, *previous = NULL;
    while (current != NULL && strcmp(current->reference, ref) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Part not found.\n");
        return head;
    }

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
    printf("Part removed successfully.\n");
    saveToFile(head);
    return head;
}

void modifyPart(part* head) {
    if (head == NULL) {
        printf("Stock is empty. Nothing to modify.\n");
        return;
    }
    char ref[20];
    printf("Enter reference of the part to modify: ");
    scanf("%s", ref);

    part* current = head;
    while (current != NULL && strcmp(current->reference, ref) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Part not found.\n");
        return;
    }

    printf("Enter new quantity: ");
    scanf("%d", &current->quantity);
    printf("Enter new selling price: ");
    scanf("%d", &current->sellingprice);
    printf("Enter new purchase price: ");
    scanf("%d", &current->purchaseprice);
    printf("Part modified successfully.\n");
    saveToFile(head);
}

void saveToFile(part* head) {
    FILE* file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Failed to open file for saving.\n");
        return;
    }
    part* current = head;
    while (current != NULL) {
        fprintf(file, "%s %s %d %d %d\n", current->reference, current->name, current->quantity, current->sellingprice, current->purchaseprice);
        current = current->next;
    }
    fclose(file);
    printf("Stock saved to file.\n");
}

part* loadFromFile() {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No existing stock file found. Starting fresh.\n");
        return NULL;
    }

    part* head = NULL;
    part* newPart = NULL;
    while (!feof(file)) {
        newPart = (part*)malloc(sizeof(part));
        if (fscanf(file, "%s %s %d %d %d", newPart->reference, newPart->name, &newPart->quantity, &newPart->sellingprice, &newPart->purchaseprice) == 5) {
            newPart->next = head;
            head = newPart;
        } else {
            free(newPart);
            break;
        }
    }
    fclose(file);
    printf("Stock loaded from file.\n");
    return head;
}

int main(void) {
    int choice;
    part* head = loadFromFile();

    do {
        printf("\n---------- STOCK MANAGER ----------\n");
        printf("1. Add a part to the stock.\n");
        printf("2. Remove a part from the stock.\n");
        printf("3. Modify a part.\n");
        printf("4. Display the stock.\n");
        printf("5. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                head = addPart(head);
                break;
            case 2:
                head = removePart(head);
                break;
            case 3:
                modifyPart(head);
                break;
            case 4:
                display(head);
                break;
            case 5:
                printf("Exiting program.\n");
                saveToFile(head);
                break;
            default:
                printf("Enter a valid number.\n");
                break;
        }
    } while (choice != 5);
    part* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}