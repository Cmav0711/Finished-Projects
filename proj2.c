#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Calculates the average of the grades and prints each grade relative to the average.
 *
 * @param grades Pointer to the array of grades.
 * @param count The number of grades.
 */
void calculate_and_print_average(double *grades, size_t count);
/**
 * The main function reads grades from user input, stores them dynamically on the heap,
 * reallocates memory as needed, calculates and prints the average grade, and then
 * classifies each grade relative to the average.
 *
 * Inputs: None (reads from standard input)
 * Outputs: Prints information to standard output
 * Assumptions: User inputs valid numeric grades separated by newlines, ending with a negative value.
 */
int main() {
    double *grades = NULL;            // Pointer to dynamically allocated array of grades
    size_t grade_count = 0;           // Number of grades entered
    size_t capacity = 40 / sizeof(double); // Current capacity of the grades array (40 bytes initially)
    double input_grade;               // Variable to store user input
    size_t allocation_count = 0;      // Number of times memory was allocated
    size_t free_count = 0;            // Number of times memory was freed
    size_t total_allocated_bytes = 0; // Total bytes allocated on the heap

    // Prompt user for input
    printf("Enter a list of grades below where each grade is separated by a newline character.\n");
    printf("After the last grade is entered, enter a negative value to end the list.\n");

    // Read grades from input until a negative value is entered
    while (1) {
        if (scanf("%lf", &input_grade) != 1) {
            printf("Invalid input\n");
            if (grades != NULL) {
                free(grades);
                free_count++;
            }
            return 1;
        }

        // Sentinel value to end input
        if (input_grade < 0) {
            break;
        }

        // Allocate memory when the first positive grade is entered
        if (grades == NULL) {
            grades = (double *)malloc(capacity * sizeof(double));
            if (grades == NULL) {
                printf("Memory allocation failed\n");
                return 1;
            }
            allocation_count++;
            total_allocated_bytes += capacity * sizeof(double);
            printf("Allocated %zu bytes to the heap at %p.\n", capacity * sizeof(double), (void *)grades);
        }

        // Store grade in the heap
        *(grades + grade_count) = input_grade;
        printf("Stored %.6lf in the heap at %p.\n", *(grades + grade_count), (void *)(grades + grade_count));
        grade_count++;

        // Reallocate memory if necessary
        if (grade_count == capacity) {
            printf("Stored %zu grades (%zu bytes) to the heap at %p.\n", capacity, capacity * sizeof(double), (void *)grades);
            printf("Heap at %p is full.\n", (void *)grades);

            size_t new_capacity = capacity + (40 / sizeof(double));
            double *new_grades = (double *)malloc(new_capacity * sizeof(double));
            if (new_grades == NULL) {
                printf("Memory allocation failed\n");
                free(grades);
                free_count++;
                return 1;
            }
            allocation_count++;
            total_allocated_bytes += new_capacity * sizeof(double);
            printf("Allocated %zu bytes to the heap at %p.\n", new_capacity * sizeof(double), (void *)new_grades);

            // Copy grades to new memory
            for (size_t i = 0; i < grade_count; i++) {
                *(new_grades + i) = *(grades + i);
            }
            printf("Copied %zu grades from %p to %p.\n", grade_count, (void *)grades, (void *)new_grades);

            // Free old memory
            free(grades);
            free_count++;
            printf("Freed %zu bytes from the heap at %p.\n", capacity * sizeof(double), (void *)grades);

            grades = new_grades;
            capacity = new_capacity;
        }
    }

    // Calculate and print the average, and classify grades
    if (grade_count > 0) {
        calculate_and_print_average(grades, grade_count);
    } else {
        printf("The average of 0 grades is 0.000000.\n");
    }

    // Free the allocated memory
    if (grades != NULL) {
        free(grades);
        free_count++;
        printf("Freed %zu bytes from the heap at %p.\n", capacity * sizeof(double), (void *)grades);
    }

    printf("total heap usage: %zu allocs, %zu frees, %zu bytes allocated\n", allocation_count, free_count, total_allocated_bytes);

    return 0;
}

/**
 * Calculates the average of the grades and prints each grade relative to the average.
 *
 * @param grades Pointer to the array of grades.
 * @param count The number of grades.
 */
void calculate_and_print_average(double *grades, size_t count) {
    double sum = 0.0;

    // Calculate the sum of all grades
    for (size_t i = 0; i < count; i++) {
        sum += *(grades + i);
    }

    double average = sum / count;
    printf("The average of %zu grades is %.6lf.\n", count, average);

    // Print each grade relative to the average
    for (size_t i = 0; i < count; i++) {
        printf("%zu. The grade of %.6lf is %s the average.\n", i + 1, *(grades + i), (*(grades + i) >= average) ? ">=" : "<");
    }
} 
