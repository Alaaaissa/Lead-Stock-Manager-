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

// Function declarations
void saveToFile(part* head);
void display(part* head);
void addPart(part** head);
void removePart(part** head);
void modifyPart(part** head);
part* loadFromFile();

// Function to load stock from file
part* loadFromFile() {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Failed to open file for reading. Starting with an empty stock.\n");
        return NULL; // Return empty list
    }

    part* head = NULL;
    part* newPart = NULL;

    while (1) {
        newPart = (part*)malloc(sizeof(part)); // Allocate memory
        if (newPart == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return head; // Return the loaded parts so far
        }

        if (fscanf(file, "%s %s %d %d %d", 
                   newPart->reference, 
                   newPart->name, 
                   &newPart->quantity, 
                   &newPart->sellingprice, 
                   &newPart->purchaseprice) != 5) {
            free(newPart); // Free memory if fscanf fails
            break;
        }

        newPart->next = head; // Add to the linked list
        head = newPart;
    }

    fclose(file); // Close the file
    printf("Stock loaded from file successfully.\n");
    return head;
}

// Function to display the stock
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

// Function to add a part to the stock
void addPart(part** head) {
    part* newPart = (part*)malloc(sizeof(part));
    if (newPart == NULL) {
        printf("Memory allocation failed.\n");
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

    printf("Part added successfully.\n");
    saveToFile(*head);
}

// Function to remove a part from the stock
void removePart(part** head) {
    if (*head == NULL) {
        printf("Stock is empty. Nothing to remove.\n");
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
        printf("Part not found.\n");
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Part removed.\n");
    saveToFile(*head);
}

// Function to modify a part's details
void modifyPart(part** head) {
    if (*head == NULL) {
        printf("Stock is empty. Nothing to modify.\n");
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
    saveToFile(*head);
}

// Function to save stock to file
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
    printf("Stock saved to file successfully.\n");
}

// Main function
int main(void) {
    int choice;
    part* head = loadFromFile(); // Load stock at the start of the program
    
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
                printf("Exiting program.\n");
                saveToFile(head);
                break;
            default:
                printf("Enter a valid number.\n");
                break;
        }
    } while (choice != 5);
    
    // Free memory
    part* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}