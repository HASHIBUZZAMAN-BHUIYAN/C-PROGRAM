#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT_NAME_LEN 100

// Structure to store installment payment details
typedef struct Installment {
    int month;            // Payment month
    double balance;       // Remaining balance
    double principal;     // Principal amount
    double fee;           // Interest fee
    double monthly_payment; // Monthly payment amount
    struct Installment* next; // Next installment in the queue
} Installment;

// Structure to store credit card purchase details
typedef struct CreditCardPurchase {
    char product_name[MAX_PRODUCT_NAME_LEN]; // Name of the product
    double principal_amount;                 // Original purchase amount
    int months;                              // Number of months for installment
    double interest_rate;                    // Interest rate for the installment
    Installment* installment_list;           // List of installments
} CreditCardPurchase;

// Function to calculate the monthly payment for the installment
double calculateMonthlyPayment(double principal, int months, double interest_rate) {
    double monthly_rate = interest_rate / 100 / 12;
    return (principal * monthly_rate) / (1 - pow(1 + monthly_rate, -months));
}

// Function to calculate the installment details
void calculateInstallments(CreditCardPurchase* purchase) {
    double monthly_payment = calculateMonthlyPayment(purchase->principal_amount, purchase->months, purchase->interest_rate);
    double remaining_balance = purchase->principal_amount;
    double principal_per_month = purchase->principal_amount / purchase->months;
    
    Installment* previous_installment = NULL;

    for (int i = 1; i <= purchase->months; i++) {
        Installment* new_installment = (Installment*)malloc(sizeof(Installment));
        new_installment->month = i;
        new_installment->balance = remaining_balance;
        new_installment->principal = principal_per_month;
        new_installment->fee = (remaining_balance * purchase->interest_rate / 100) / 12;
        new_installment->monthly_payment = principal_per_month + new_installment->fee;
        new_installment->next = NULL;

        remaining_balance -= principal_per_month;

        if (previous_installment != NULL) {
            previous_installment->next = new_installment;
        } else {
            purchase->installment_list = new_installment;
        }

        previous_installment = new_installment;
    }
}

// Function to print the installment details
void printInstallments(CreditCardPurchase* purchase) {
    Installment* current = purchase->installment_list;
    while (current != NULL) {
        printf("Month %d: Remaining Balance: %.2f, Principal: %.2f, Fee: %.2f, Monthly Payment: %.2f\n",
               current->month, current->balance, current->principal, current->fee, current->monthly_payment);
        current = current->next;
    }
}

// Function to make a payment
void makePayment(CreditCardPurchase* purchase) {
    if (purchase->installment_list == NULL) {
        printf("No installments to pay.\n");
        return;
    }

    Installment* current = purchase->installment_list;
    printf("Paying for month %d:\n", current->month);
    printf("Remaining Balance: %.2f, Principal: %.2f, Fee: %.2f, Monthly Payment: %.2f\n", 
           current->balance, current->principal, current->fee, current->monthly_payment);

    purchase->installment_list = current->next;
    free(current);

    if (purchase->installment_list != NULL) {
        printf("Next payment due.\n");
    } else {
        printf("All payments completed.\n");
    }
}

// Function to simulate the installment payment process
void studyMoney() {
    CreditCardPurchase purchase;
    printf("Enter the product name: ");
    fgets(purchase.product_name, MAX_PRODUCT_NAME_LEN, stdin);
    purchase.product_name[strcspn(purchase.product_name, "\n")] = 0; // Remove the newline

    printf("Enter the principal amount (product price): ");
    scanf("%lf", &purchase.principal_amount);

    printf("Enter the number of months for installment: ");
    scanf("%d", &purchase.months);

    printf("Enter the interest rate (annual percentage rate): ");
    scanf("%lf", &purchase.interest_rate);

    // Calculate the installment hb details
    purchase.installment_list = NULL;
    calculateInstallments(&purchase);

    printf("\nInstallment details for %s:\n", purchase.product_name);
    printInstallments(&purchase);

    int payment_choice;
    while (1) {
        printf("\n1. Make a payment\n2. Exit\nEnter your choice: ");
        scanf("%d", &payment_choice);

        if (payment_choice == 1) {
            makePayment(&purchase);
            printInstallments(&purchase); // Print remaining installments
        } else if (payment_choice == 2) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice, try again.\n");
        }
    }
}

// Main function
int main() {
    studyMoney();
    return 0;
}
