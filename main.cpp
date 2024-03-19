#include <cstring>
#include <future>
#include <iostream>
#include <valarray>

constexpr int MAX_ARRAY_SIZE = 1024;

void check_cin_int() {
    if (std::cin.good())
        return;
    std::cin.clear();
    std::string ignore;
    std::cin >> ignore;
}

int readInt(const char *prompt) {
    int result = 0;
    while (true) {
        printf(prompt);
        std::cin >> result;
        check_cin_int();
        if (result >= 1)
            break;
        printf("     Number must be greater than 1!\n");
    }

    return result;
}

void printArr(const int arr[], const int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("]\n");
}

void printMat(int (*arr)[MAX_ARRAY_SIZE], const int rows, const int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%6d ", arr[i][j]);
        }
        printf("\n");
    }
}

double task_1_f(double a, double b, double c) {
    return (2 * a - b - std::sin(c)) / (5 + fabs(c));
}

void task_1() {
    int s = readInt("1. Enter int (s): ");
    int t = readInt("   Enter int (t): ");
    double result = task_1_f(t, -2 * s, 1.17) - task_1_f(2.2, t, s - t);
    printf("   Result: %.2f\n", result);
}

void task_2_fill_array(int arr[], int size) {
    for(int i = 0; i < size; i++)
        arr[i] = rand() % 65534 - 32767;
}

void task_2_array_sort(int arr[], const int size) {
    for(int i = 0; i < size; i += 2) {
        for(int j = i; j < size; j += 2) {
            if (arr[i] > arr[j]) {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}

void task_2_array() {
    int arr[MAX_ARRAY_SIZE];

    int n = readInt("2. Enter array size: ");
    task_2_fill_array(arr, n);

    printf("   Array: ");
    printArr(arr, n);

    task_2_array_sort(arr, n);

    printf("   Array: ");
    printArr(arr, n);
}

void task_2_fill_matrix(int (*mat)[MAX_ARRAY_SIZE], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mat[i][j] = rand() % 65534 - 32767;
}

void task_2_process_matrix(int (*mat)[MAX_ARRAY_SIZE], int size) {
    for(int i = 0; i < size; i += 2) {
        for (int j = 0; j < size / 2; j++) {
            int tmp = mat[i][j];
            mat[i][j] = mat[i][size - j - 1];
            mat[i][size - j - 1] = tmp;
        }
    }
}

void task_2_matrix() {
    int mat[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];

    int n = readInt("   Enter matrix size: ");
    task_2_fill_matrix(mat, n);

    printf("     Matrix: \n");
    printMat(mat, n, n);

    task_2_process_matrix(mat, n);

    printf("     Matrix: \n");
    printMat(mat, n, n);
}

struct Person {
    char* name;
    char* address;
    int age;
};

Person task_3_make_person() {
    char name [128];
    char address [128];
    int age;

    printf("   Name: ");
    std::cin >> name;
    printf("   Address: ");
    std::cin >> address;
    age = readInt("   Age: ");

    Person person;
    person.name = new char[strlen(name)+1];
    strcpy(person.name, name);
    person.address = new char[strlen(address)+1];
    strcpy(person.address, address);
    person.age = age;

    return person;
}

void task_3_struct_fill_arr(Person arr[], const int size) {
    for(int i = 0; i < size; i++)
        arr[i] = task_3_make_person();
}

void task_3_print_person(Person p) {
    printf("   Person:\n    Name: %s\n    Address: %s\n    Age: %d\n", p.name, p.address, p.age);
}

void task_3_search(Person arr[], const int size) {
    bool found = false;
    for(int i = 0; i < size; i++) {
        if(arr[i].name[0] == 'A') {
            task_3_print_person(arr[i]);
            found = true;
        }
    }

    if(!found)
        printf("   No person with name starting with 'A' found!\n");
}

void task_3_struct() {
    int n = readInt("3. Enter struct array size: ");
    auto *arr = new Person[n];

    task_3_struct_fill_arr(arr, n);
    task_3_search(arr, n);

    delete[] arr;
}

void task_3_string_fill_arr(std::string arr[], const int size) {
    std::cin.ignore();
    for(int i = 0; i < size; i++) {
        printf("   Enter string: ");
        std::getline(std::cin, arr[i]);
    }
}

void task_3_string_print_arr(std::string arr[], const int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%s", arr[i].c_str());
        if (i < size - 1)
            printf(", ");
    }
    printf("]\n");
}

void task_3_string_insert(std::string arr[], int &size) {
    int idx = readInt("   Enter new string index: ");
    printf("   Enter string: ");
    for(int i = size; i >= idx; i--)
        arr[i] = arr[i-1];

    std::cin.ignore();
    std::getline(std::cin, arr[idx]);
    size++;
}

void task_3_string() {
    int n = readInt("   Enter array size: ");
    auto *arr = new std::string[n+1];

    task_3_string_fill_arr(arr, n);
    printf("    Array: ");
    task_3_string_print_arr(arr, n);

    task_3_string_insert(arr, n);
    printf("    Array (after insert): ");
    task_3_string_print_arr(arr, n);

    delete[] arr;
}

int main() {
    task_1();
    task_2_array();
    task_2_matrix();
    task_3_struct();
    task_3_string();

    return 0;
}
