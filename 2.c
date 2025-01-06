#include<stdio.h>
#include<stdlib.h>

typedef struct part {
    char reference[20];
    char name[20];
    int quantity;
    int sellingprice;
    int purchaseprice;
    struct part* next;
} part;

#define FILE_NAME"stock.text"

void display(part*head){
    if(head==NULL){
        printf("empty\n");
    }
    part*p=head;
    while(p!=NULL){
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






int main(void){





    return 0;
}