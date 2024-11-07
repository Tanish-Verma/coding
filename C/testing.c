#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addExpense();
void viewExpenses();
void resetExpenses();

int main() {
    int option;
    addExpense();
    while (1) {
        printf("\nExpense Manager\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Reset Expense List\n");
        printf("4. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);
        getchar();  // Consume newline left in input buffer
        switch (option) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                resetExpenses();
                break;
            case 4:
                return 0;
        }
        
    }
    return 0;
}

void addExpense() {
    FILE *file = fopen("expenses.txt", "a");
    //write your logic here
    printf("Expense added successfully!\n");
    fclose(file);
}

void viewExpenses() {
    FILE *file = fopen("expenses.txt", "r");
    //write your logic here    
    // printf("Total Expenses: %.2f\n", total);
  
}

void resetExpenses() {
    //write your logic here
    printf("Expense list has been reset.\n");
}