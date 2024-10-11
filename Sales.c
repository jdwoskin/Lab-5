#include <stdio.h>
#include <stdlib.h>

#define MONTHS 12

// Function prototypes
void printSalesReport(float sales[], const char *months[]);
float findMin(float sales[], int *minMonth);
float findMax(float sales[], int *maxMonth);
float calculateAverage(float sales[]);
void printSixMonthMovingAvg(float sales[], const char *months[]);

int main() {
    // Monthly sales data
    float sales[MONTHS];
    // Corresponding month names
    const char *months[MONTHS] = {"January", "February", "March", "April", "May", "June",
                                  "July", "August", "September", "October", "November", "December"};
    
    // Open the input file
    FILE *file = fopen("sales.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file 'sales.txt'.\n");
        return 1;
    }

    // Read sales data from file
    for (int i = 0; i < MONTHS; i++) {
        if (fscanf(file, "%f", &sales[i]) != 1) {
            printf("Error: Invalid data in file.\n");
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    // Print the monthly sales report
    printSalesReport(sales, months);
    
    // Calculate minimum, maximum, and average sales
    int minMonth, maxMonth;
    float minSales = findMin(sales, &minMonth);
    float maxSales = findMax(sales, &maxMonth);
    float avgSales = calculateAverage(sales);

    printf("\nSales summary report:\n");
    printf("Minimum sales: %.2f (%s)\n", minSales, months[minMonth]);
    printf("Maximum sales: %.2f (%s)\n", maxSales, months[maxMonth]);
    printf("Average sales: %.2f\n", avgSales);

    // Print the six-month moving average
    printf("\nSix-Month moving average report:\n");
    printSixMonthMovingAvg(sales, months);

    // Print sales sorted from highest to lowest
    printf("\nSales report (highest to lowest):\n");
    for (int i = 11; i >= 0; i--) {
        printf("%-10s $%.2f\n", months[i], sales[i]);
    }

    return 0;
}

// Function to print sales report
void printSalesReport(float sales[], const char *months[]) {
    printf("Monthly Sales Report for 2024\n");
    printf("%-10s Sales\n", "Month");
    for (int i = 0; i < MONTHS; i++) {
        printf("%-10s %.2f\n", months[i], sales[i]);
    }
}

// Function to find the minimum sales
float findMin(float sales[], int *minMonth) {
    float min = sales[0];
    *minMonth = 0;
    for (int i = 1; i < MONTHS; i++) {
        if (sales[i] < min) {
            min = sales[i];
            *minMonth = i;
        }
    }
    return min;
}

// Function to find the maximum sales
float findMax(float sales[], int *maxMonth) {
    float max = sales[0];
    *maxMonth = 0;
    for (int i = 1; i < MONTHS; i++) {
        if (sales[i] > max) {
            max = sales[i];
            *maxMonth = i;
        }
    }
    return max;
}

// Function to calculate average sales
float calculateAverage(float sales[]) {
    float sum = 0.0;
    for (int i = 0; i < MONTHS; i++) {
        sum += sales[i];
    }
    return sum / MONTHS;
}

// Function to print six-month moving average
void printSixMonthMovingAvg(float sales[], const char *months[]) {
    for (int i = 0; i <= 6; i++) {
        float sum = 0.0;
        for (int j = i; j < i + 6; j++) {
            sum += sales[j];
        }
        float avg = sum / 6.0;
        printf("%s-%s %.2f\n", months[i], months[i + 5], avg);
    }
}

