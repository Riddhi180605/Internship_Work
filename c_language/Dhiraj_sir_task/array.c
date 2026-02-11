/*
    Author : Patel Riddhi
    Doc : 20-1-2026
    Objective : To perform various operations on two arrays such as
                arithmetic operations, sorting, and searching
                using menu driven programming in C.
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

/* ---------- Function Declaration ---------- */
void bubbleSort(int a[]);
void selectionSort(int a[]);
void insertionSort(int a[]);
void mergeSort(int a[], int l, int r);
void quickSort(int a[], int low, int high);
void merge(int a[], int l, int m, int r);
int partition(int a[], int low, int high);
void printArray(int a[]);

/* ---------- Main Function ---------- */
int main() {

    int a[SIZE], b[SIZE], c[SIZE];
    int i, choice, choice1, key;
    int flag, low, high, mid;

    printf("\nEnter %d values in array A:\n", SIZE);
    for (i = 0; i < SIZE; i++) {
        printf("a[%d] : ", i);
        scanf("%d", &a[i]);
    }

    printf("\nEnter %d values in array B:\n", SIZE);
    for (i = 0; i < SIZE; i++) {
        printf("b[%d] : ", i);
        scanf("%d", &b[i]);
    }

    while (1) {
        printf("\n----------------------------------------");
        printf("\n1. Addition");
        printf("\n2. Subtraction");
        printf("\n3. Multiplication");
        printf("\n4. Division");
        printf("\n5. Sorting");
        printf("\n6. Searching");
        printf("\n7. Exit");
        printf("\n----------------------------------------");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            for (i = 0; i < SIZE; i++) {
                c[i] = a[i] + b[i];
                printf("%d + %d = %d\n", a[i], b[i], c[i]);
            }
            break;

        case 2:
            for (i = 0; i < SIZE; i++) {
                c[i] = a[i] - b[i];
                printf("%d - %d = %d\n", a[i], b[i], c[i]);
            }
            break;

        case 3:
            for (i = 0; i < SIZE; i++) {
                c[i] = a[i] * b[i];
                printf("%d * %d = %d\n", a[i], b[i], c[i]);
            }
            break;

        case 4:
            for (i = 0; i < SIZE; i++) {
                if (b[i] != 0) {
                    c[i] = a[i] / b[i];
                    printf("%d / %d = %d\n", a[i], b[i], c[i]);
                } else {
                    printf("Division by zero at index %d\n", i);
                }
            }
            break;

        case 5:
            printf("\n1. Bubble Sort");
            printf("\n2. Selection Sort");
            printf("\n3. Insertion Sort");
            printf("\n4. Merge Sort");
            printf("\n5. Quick Sort");
            printf("\nEnter sorting choice : ");
            scanf("%d", &choice1);

            switch (choice1) {
            case 1:
                bubbleSort(a);
                break;
            case 2:
                selectionSort(a);
                break;
            case 3:
                insertionSort(a);
                break;
            case 4:
                mergeSort(a, 0, SIZE - 1);
                break;
            case 5:
                quickSort(a, 0, SIZE - 1);
                break;
            default:
                printf("Invalid sorting choice\n");
            }

            printf("\nSorted Array : ");
            printArray(a);
            break;

        case 6:
            printf("\n1. Linear Search");
            printf("\n2. Binary Search");
            printf("\nEnter searching choice : ");
            scanf("%d", &choice1);

            
            if (choice1 == 1) {
                flag = -1;
                int x = 0;
                printf("Enter value to search : ");
                scanf("%d", &key);

                for (i = 0; i < SIZE; i++) {
                    if (a[i] == key) {
                        flag = i;
                        break;
                    }
                }
                if (flag >= 0)
                    printf("Value found at position %d\n", flag);
                else
                    printf("Value not found\n");
            }
            else if (choice1 == 2) {
                bubbleSort(a);  // must be sorted
                low = 0;
                high = SIZE - 1;
                flag = -1;
                printf("Enter value to search : ");
                scanf("%d", &key);

                while (low <= high) {
                    mid = (low + high) / 2;
                    if (a[mid] == key) {
                        flag = mid;
                        break;
                    }
                    else if (key > a[mid])
                        low = mid + 1;
                    else
                        high = mid - 1;
                }

                if (flag >= 0)
                    printf("Value found at position %d\n", flag);
                else
                    printf("Value not found\n");
            }
            else{
                printf("Enter valid number.");
            }
            break;

        case 7:
            exit(0);

        default:
            printf("Invalid choice\n");
        }
    }
}

/* ---------- Sorting Functions ---------- */

/* ---------- Bubble Sort ---------- */
void bubbleSort(int a[]) {
    int i, j, temp, exc;
    for (i = 0; i < SIZE - 1; i++) {
        exc = 0;
        for (j = 0; j < SIZE - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                exc = 1;
            }
        }
        if (exc == 0) break;
    }
}

/* ---------- Selection Sort ---------- */
void selectionSort(int a[]) {
    int i, j, min, temp;
    for (i = 0; i < SIZE - 1; i++) {
        min = i;
        for (j = i + 1; j < SIZE; j++) {
            if (a[j] < a[min])
                min = j;
        }
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

/* ---------- Insertion Sort ---------- */
void insertionSort(int a[]) {
    int i, key, j;
    for (i = 1; i < SIZE; i++) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

/* ---------- Merge Sort ---------- */
void merge(int a[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++) L[i] = a[l + i];
    for (j = 0; j < n2; j++) R[j] = a[m + 1 + j];

    i = j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

/* ---------- Quick Sort ---------- */
int partition(int a[], int low, int high) {
    int pivot = a[high], i = low - 1, j, temp;
    for (j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            temp = a[i]; a[i] = a[j]; a[j] = temp;
        }
    }
    temp = a[i + 1]; a[i + 1] = a[high]; a[high] = temp;
    return i + 1;
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

void printArray(int a[]) {
    int i;
    for (i = 0; i < SIZE; i++)
        printf("%d ", a[i]);
}
