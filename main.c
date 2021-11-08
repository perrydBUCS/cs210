#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct person person;

double inner_product(const double *leftArray, const double *right_array, int length);

void large_and_small(const int *array, int length, int *largest, int *smallest);
void large_and_small2(const int *array, int length, int *largest, int *smallest);

bool compareArrays(int *left, int left_length, int *right, int right_length);

void structPtrs(void);

void structDMA(void);

int main() {

    //P2.1
    int array1[] = {72, 90, 100, 36, 21, 15, 76, -6, 63, 41, 99, 27, 3, 66, 19, 16, 27, 47, 0, 23};
    int array2[] = {-72, -90, -100, -36, -21, -15, -76, -6, 63, 41, 99, 27, 3, 66, 19, 16, 27, 47, 0, 23};
    int largest, smallest;

    large_and_small(array1, (sizeof array1 / sizeof(signed int)), &largest, &smallest);
    printf("Largest: %d\t Smallest: %d\n", largest, smallest);

    large_and_small(array2, (sizeof array2 / sizeof(signed int)), &largest, &smallest);
    printf("Largest: %d\t Smallest: %d\n", largest, smallest);

    //P2.2
    //    double left[] = {15.26, 28.20, 6.71, 72.22, 92.85, 15.50, 85.64, 57.41, 44.40, 72.91};
    //    double right[]= {9.17, 4.8, 10.9, 10.12, 17.18, 3.9, 6.19, 5.4, 3.13, 6.1};
    double left[] = {1.0, 2.0, 3.0};
    double right[] = {4.0, 5.0, 6.0};
    int length_left = sizeof left / sizeof(double);
    int length_right = sizeof right / sizeof(double);
    //Check that lengths are equal before running
    //
    if (length_right == length_left) {
        double result = inner_product(left, right, length_left);
        printf("Inner product: %f\n", result);
    } else {
        puts("Lengths were not equal");
    }

    //P2.3
    //
    signed int p3_left[] = {72, 90, 100, 36, 21, 15, 76, -6, 63, 41, 99, 27, 3, 66, 19, 16, 27, 47, 0, 23};
    signed int p3_right[] = {72, 90, 100, 36, 21, 15, 76, -6, 63, 41, 99, 27, 3, 66, 19, 16, 27, 47, 0, 22};
    length_left = sizeof p3_left / sizeof(signed int);
    length_right = sizeof p3_right / sizeof(signed int);
    bool identical = compareArrays(p3_left, length_left, p3_right, length_right);
    printf("The arrays are %s", identical ? "equal" : "not equal");

//    structPtrs();
    structDMA();

    int test_array[] = {-72,-90,-100,-36,-21,-15,-76,-6,63,41,99,27,3,66,19,16,27,47,0,23, 9999};
    int length = sizeof(test_array)/sizeof(int);
    int* largestp = test_array;
    int* smallestp = test_array;
    large_and_small2(test_array, length, largestp, smallestp);


    return 0;

}


//P2.1
void large_and_small(const int *array, int length, int *largest, int *smallest) {
    *largest = *smallest = *array;
    while (length--) {
        if (*array > *largest) { *largest = *array; }
        if (*array < *smallest) { *smallest = *array; }
        array++;
    }
}

//P2.2
//
double inner_product(const double *leftArray, const double *right_array, int length) {
    double result = 0.0; //initial value
    while (length--) {
        result += (*leftArray++ * *right_array++);
    }
    return result;
}

//P2.3
bool compareArrays(int *left, int left_length, int *right, int right_length) {
    if (left_length != right_length) { return false; }
    while (left_length--) {
        if (*left++ != *right++) { return false; }
    }
    return true;
}

//playing with structs

void structPtrs(void) {
    typedef struct {
        int age;
        char firstName[30];
    } person;

    person foo;
    person *foo_p = &foo;
    foo_p->age = 9;
    printf("Age: %d\n", foo_p->age);

}

void structDMA(void) {
#define NUMBER_ENTERED 5
    typedef struct {
        int age;
        char firstName[4];
    } person;

    person *people = malloc(NUMBER_ENTERED * sizeof(person));//This will be first element of array
    person *people_temp = people;
    person *person_p;
    int count = NUMBER_ENTERED;
    while (count--) {
        person_p = malloc(sizeof(person));
        person_p->age = count + 1; // just to keep track of them in memory
        *people_temp++ = *person_p;
    }
    printf("Person at [2] has age %d\n", (people + 2)->age);

    typedef struct {
        int part_number;
        double price;
        union {
            struct {
                int pages;
                int edition;
            } book;
            struct {
                float capacity;
                enum COLOR {BLUE, GREEN, WHITE};
            } mug;
        } item;
    } _items;

    _items item;
    item.item.book.pages = 123;


}