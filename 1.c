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

void saveToFile(part* head);
void display(part* head);
void addPart(part** head);
void removePart(part** head);
void modifyPart(part** head);
part* loadFromFile();

part* loadFromFile() {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("\033[31mFailed to open file for reading. Starting with an empty stock.\033[0m\n");
        return NULL;
    }

    part* head = NULL;
    part* newPart = NULL;

    while (1) {
        newPart = (part*)malloc(sizeof(part));
        if (newPart == NULL) {
            printf("\033[31mMemory allocation failed.\033[0m\n");
            fclose(file);
            return head;
        }

        if (fscanf(file, "%s %s %d %d %d", 
                   newPart->reference, 
                   newPart->name, 
                   &newPart->quantity, 
                   &newPart->sellingprice, 
                   &newPart->purchaseprice) != 5) {
            free(newPart);
            break;
        }
        newPart->next = head;
        head = newPart;
    }

    fclose(file);
    printf("\033[32mStock loaded from file successfully.\033[0m\n");
    return head;
}

void display(part* head) {
    if (head == NULL) {
        printf("\033[33mStock is empty.\033[0m\n");
        return;
    }
    printf("\033[36m+------------------+------------------+----------+--------------+---------------+\n");
    printf("| Reference        | Name             | Quantity | Selling Price| Purchase Price|\n");
    printf("+------------------+------------------+----------+--------------+---------------+\033[0m\n");

    part* p = head;
    while (p != NULL) {
        printf("| \033[35m%-16s\033[0m | \033[35m%-16s\033[0m | \033[35m%-8d\033[0m | \033[35m%-12d\033[0m | \033[35m%-13d\033[0m |\n", 
               p->reference, p->name, p->quantity, p->sellingprice, p->purchaseprice);
        p = p->next;
    }

    printf("\033[36m+------------------+------------------+----------+--------------+---------------+\033[0m\n");
}

void addPart(part** head) {
    part* newPart = (part*)malloc(sizeof(part));
    if (newPart == NULL) {
        printf("\033[31mMemory allocation failed.\033[0m\n");
        return;
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

    newPart->next = *head;
    *head = newPart;

    printf("\033[32mPart added successfully.\033[0m\n");
    saveToFile(*head);
}

void removePart(part** head) {
    if (*head == NULL) {
        printf("\033[33mStock is empty. Nothing to remove.\033[0m\n");
        return;
    }

    char ref[20];
    printf("Enter reference of the part to remove: ");
    scanf("%s", ref);

    part *current = *head, *previous = NULL;
    while (current != NULL && strcmp(current->reference, ref) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("\033[31mPart not found.\033[0m\n");
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("\033[32mPart removed successfully.\033[0m\n");
    saveToFile(*head);
}

void modifyPart(part** head) {
    if (*head == NULL) {
        printf("\033[33mStock is empty. Nothing to modify.\033[0m\n");
        return;
    }

    char ref[20];
    printf("Enter reference of the part to modify: ");
    scanf("%s", ref);

    part* current = *head;
    while (current != NULL && strcmp(current->reference, ref) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("\033[31mPart not found.\033[0m\n");
        return;
    }

    printf("Enter new quantity: ");
    scanf("%d", &current->quantity);
    printf("Enter new selling price: ");
    scanf("%d", &current->sellingprice);
    printf("Enter new purchase price: ");
    scanf("%d", &current->purchaseprice);

    printf("\033[32mPart modified successfully.\033[0m\n");
    saveToFile(*head);
}

void saveToFile(part* head) {
    FILE* file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("\033[31mFailed to open file for saving.\033[0m\n");
        return;
    }

    part* current = head;
    while (current != NULL) {
        fprintf(file, "%s %s %d %d %d\n", current->reference, current->name, current->quantity, current->sellingprice, current->purchaseprice);
        current = current->next;
    }

    fclose(file);
    printf("\033[32mStock saved to file successfully.\033[0m\n");
}

int main(void) {
    int choice;
    part* head = loadFromFile();

    do {
        printf("\n\033[34m---------- STOCK MANAGER ----------\033[0m\n");
        printf("1. \033[33mAdd a part to the stock.\033[0m\n");
        printf("2. \033[33mRemove a part from the stock.\033[0m\n");
        printf("3. \033[33mModify a part.\033[0m\n");
        printf("4. \033[33mDisplay the stock.\033[0m\n");
        printf("5. \033[31mExit.\033[0m\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPart(&head);
                break;
            case 2:
                removePart(&head);
                break;
            case 3:
                modifyPart(&head);
                break;
            case 4:
                display(head);
                break;
            case 5:
                printf("\033[31mExiting program.\033[0m\n");
                saveToFile(head);
                break;
            default:
                printf("\033[31mEnter a valid number.\033[0m\n");
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