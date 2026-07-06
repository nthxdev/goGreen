#include <stdio.h>     // Standard I/O operations (printf, scanf, fgets)
#include <stdlib.h>    // Standard library (malloc, free, strtol, atoi)
#include <stdbool.h>   // Boolean support (true, false)
#include <string.h>    // String manipulation (strcpy, strlen)


// ==========================================
// 13. FUNCTION DECLERATION (PROTOTYPES)
// ==========================================
// Functions must be declared before they are called.
// Syntax: return_type function_name(parameter_type param_name);


// Function declaration (prototype) - tells compiler about function before use
int add(int a, int b);

// Forward function declarations (prototypes)
void demonstratePassByValue(int val);
void demonstratePassByReference(int *ptr);
void demonstrateArrayPass(int arr[]);
int addNumbers(int a, int b);
int sumAll(int numbers[], int count);
void some_function(void);


// =========================================
// 14. Special Data Types - Structs
// =========================================
// Structure definition - groups related data
struct Person {
    char name[50];
    int age;
    float height;
};

// Typedef creates alias
typedef struct {
    int x;
    int y;
} Point;


// Global variable - visible everywhere
int global_var = 0;

// ==========================================
// 1. BASICS OF VARIABLES & CONSTANTS
// ==========================================
// Syntax: type variable_name = value;
// Preprocessor Macro: Handled before compilation. Text substitution. No memory address.
#define PI_MACRO 3.14159        // Preprocessor macro (text substitution, no memory address)

// Const Keyword: Stored in read-only memory segment (.rodata). Has a memory address.
const int MAX_USERS = 100;       // Const keyword (read-only segment .rodata, has address)


// Main entry point - where C programs start execution
int main(void) {
    printf("Hello World\n");

	// Local variable - exists only in this function
	// Local scope - only in main
    int local_var = 50;
    {
        // Block scope - only in this block
        int block_var = 25;
        printf("Block var: %d\n", block_var);
    }
    // block_var is not accessible here!
    printf("Local: %d, Global: %d\n", local_var, global_var);
    
    
    // ==========================================
    // 2.DATA TYPES - BUILT-IN PRIMITVES
    // ==========================================
    // C types map directly to hardware architectures. Sizes below assume your 
    // specific environment (64-bit Linux/Ubuntu on WSL).
    
    // --- Integer Types (Whole Numbers) ---
    // char: 1 byte (8 bits). Stores raw ASCII values. Range: -128 to 127
    char charVar = 'A'; 

    // short: 2 bytes (16 bits). Range: -32,768 to 32,767
    short shortVar = 32767;

    // int: 4 bytes (32 bits). Range: -2,147,483,648 to 2,147,483,647
    int intVar = 2147483647;

    // long: 8 bytes (64 bits on Linux/WSL, 4 bytes on Windows). 
    long longVar = 9223372036854775807L;

    // long long: Guaranteed 8 bytes (64 bits) across all platforms.
    long long longlongVar = 9223372036854775807LL;

    // Unsigned variants exist for all above (e.g., unsigned int) doubling positive range.
    unsigned int unsignedVar = 4294967295U;

    // --- Floating-Point Types (Decimals) ---
    // IEEE 754 standard.
    // float: 4 bytes (32 bits). Precision: ~6-7 decimal digits. 'f' suffix required.
    float floatVar = 3.14f;

    // double: 8 bytes (64 bits). Precision: ~15 decimal digits. Default decimal type.
    double doubleVar = 3.141592653589793;

    // --- Boolean ---
    // Requires <stdbool.h>. Under the hood, it's just an integer (0 = false, 1 = true).
    bool boolVar = true;

    printf("char: %c (ASCII: %d)\n", charVar, charVar);
    printf("short: %d\n", shortVar);
    printf("int: %d\n", intVar);
    printf("long: %ld\n", longVar);
    printf("unsigned int: %u\n", unsignedVar);
    printf("float: %.2f\n", floatVar);
    printf("double: %.10f\n", doubleVar);
    printf("bool: %d (true=1, false=0)\n\n", boolVar);

    // Void - no value
    some_function();

    // ==========================================
    // 3.REFERENCE TYPES (ARRAYS, STRING, HEAP)
    // ==========================================
	// --- Pointer ---
    // Pointer declaration: Holds the memory address
    int targetVar = 42;
    int *ptrInt = &targetVar;     // & gets memory address
    printf("Variable targetVar: %d\n", targetVar);
    printf("Pointer ptrInt holds address: %p\n", (void*)ptrInt);
    printf("Dereferencing *ptrInt: %d\n", *ptrInt);
    
	// --- Arrays ---
    // Arrays (contiguous memory)
    // Stored contiguously in memory. 
    int arrInt[4] = {10, 20, 30, 40}; //stack allocation
    printf("Array: [%d, %d, %d, %d]\n", arrInt[0], arrInt[1], arrInt[2], arrInt[3]);
    // Array name decays to a pointer to the first element.
    int *arrPtr = arrInt;  // arrPtr points to &arrInt[0]
    printf("%p\n", (void*)arrPtr);
    printf("Array pointer decay: arrInt[0] via pointer = %d\n", *(arrInt));
    
    int size = sizeof(arrInt) / sizeof(arrInt[0]);
    // size = size of whole array / size of element that it stores
    
    // --- Strings ---
    // C has no String class. Strings (null-terminated character arrays) ('\0').
    
    // Method A (Stack Array):
    char strArray[] = "Hello";    // Stack array, modifiable
    strArray[0] = 'h';
    printf("Modified string: %s\n", strArray);
    char str1[] = "Hello";           // Auto-sized
    char str2[50] = "World";         // Fixed size, max 49 chars + null terminator

    // string literals are shared (not copied every time)
    // Method B (String Literal Pointer): IMMUTABLE.
    char *strLiteral = "World"; 
    //  Points to read-only data segment of program memory, .rodata (read-only data segment)
    printf("String literal: %s\n", strLiteral);
    // strLiteral[0] = 'w'; // ERROR: Segmentation Fault!
    
    /*
    char *p = "Hello";     // unsafe to modify
    const char *p = "Hello"; // safe (read-only intent)
    char p[] = "Hello";    // copy, safe to modify
    */
    
    // Accessing array elements
    int first = arrInt[0];          // First element
    int last = arrInt[size - 1];    // Last element
    
    // String operations
    printf("Length of 'Hello': %lu\n", strlen(str1));
    
    // Concatenate strings (dangerous - need bounds checking)
    char combined[100];
    strcpy(combined, str1);          // Copy str1 to combined
    strcat(combined, " ");           // Add space
    strcat(combined, str2);          // Add str2
    printf("Combined: %s\n", combined);
    
    
	// --- HEAP ---
    // --- Dynamic Memory (The Heap) ---
    // Requires manual allocation and deallocation.
    // malloc requests contiguous bytes on the Heap.

    // Explanation of code below malloc returns void * (generic pointer)
    // int *heapArr - will hold address of int(s)
    // so type expected - (int *)
    int *heapArr = (int *)malloc(3 * sizeof(int));
    if (heapArr != NULL) { // NULL checks are mandatory in C
        heapArr[0] = 100;
        heapArr[1] = 200;
        heapArr[2] = 300;
        printf("Heap array: [%d, %d, %d]\n", heapArr[0], heapArr[1], heapArr[2]);
        free(heapArr); // MUST manually free memory to prevent leaks
        heapArr = NULL; // Best practice: nullify pointer after freeing (prevent dangling ptr)
    }

    // Special Type: NULL. Represents a pointer pointing to memory address 0.
    char *nullPtr = NULL;
    printf("NULL pointer: %p\n\n", (void*)nullPtr);





    // ==========================================
    // 4. OPERATORS
    // ==========================================
	int x = 10, y = 3;
    // Arithmetic: +, -, *, /, % (Modulo strictly for integers)
    printf("Arithmetic: %d + %d = %d\n", x, y, x + y);
    printf("Arithmetic: %d - %d = %d\n", x, y, x - y);
    printf("Arithmetic: %d * %d = %d\n", x, y, x * y);
    printf("Arithmetic: %d / %d = %d\n", x, y, x / y);
    printf("Arithmetic: %d %% %d = %d\n", x, y, x % y);
    // Relational (Comparsion): ==, !=, >, <, >=, <=
    printf("\nComparison: %d > %d is %d\n", x, y, x > y);
    printf("Comparison: %d < %d is %d\n", x, y, x < y);
    printf("Comparison: %d == %d is %d\n", x, y, x == y);
    // Logical: && (AND), || (OR), ! (NOT). Short-circuiting applies.
    printf("\nLogical: true && false = %d\n", true && false);
    printf("Logical: true || false = %d\n", true || false);
    printf("Logical: !true = %d\n", !true);
    // Bitwise (Low-level memory manipulation): & (AND), | (OR), ^ (XOR), ~ (NOT), << (Left Shift), >> (Right Shift)
    printf("\nBitwise: 5 & 3 = %d\n", 5 & 3);
    printf("Bitwise: 5 | 3 = %d\n", 5 | 3);
    printf("Bitwise: 5 << 1 = %d\n", 5 << 1);
    // Assignment: =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=
    // Unary: ++, -- (prefix/postfix), +, -, & (address-of), * (dereference)
    int counter = 5;
    printf("\nUnary: counter = %d\n", counter);
    printf("Unary: counter++ = %d ", counter);
    counter++;
    printf("(then counter = %d)\n", counter);
    printf("Unary: ++counter = %d\n", ++counter);
    // sizeof: Determines byte size of a type or variable at compile-time.
    printf("\nsizeof(int) = %zu bytes\n", sizeof(intVar));
    printf("sizeof(double) = %zu bytes\n\n", sizeof(doubleVar));

    // ==========================================
    // 5. CONDITIONALS (IF-ELSE FAMILY)
    // ==========================================
    // C evaluates 0 as false, and ANY non-zero value as true.

    if (intVar > 0 && boolVar) {
        // executes if condition is true
    } else if (!boolVar) {
        // Nested logic
        if (arrInt[0] == 10) {
            // deep scope
        }
    } else {
        // fallback
    }


    // ==========================================
    // 6. SWITCH STATEMENT
    // ==========================================
    int switchVar = 2;
    // switch ONLY evaluates integral types (char, short, int, long, enum). No strings/floats.
    switch (switchVar) {
        case 1:
            // logic
            break;
        case 2:
        case 3: // Fall-through behavior: executes for 2 AND 3 because 2 lacks a break.
            // logic
            break;
        default:
            // fallback
            break;
    }

    // ==========================================
    // 7. Ternary
    // ==========================================

    // Ternary Operator: (condition) ? true_val : false_val
    int age = 20;
    // Cannot assign string literals directly in C ternary unless using char*
    char *status = (age >= 18) ? "Adult" : "Minor";

    // Nested ternary
    int score = 85;
    char* grade = (score >= 90) ? "A" : 
                  (score >= 80) ? "B" : 
                  (score >= 70) ? "C" : "F";
    printf("Grade: %s\n", grade);

    // ==========================================
    // 8. LOOPS
    // ==========================================

    // While loop
    int w = 0;
    while (w < 3) {
	    // do something
        w++;
    }

    // Do-while (Guaranteed one execution)
    int dw = 0;
    do {
	    // do something
        dw++;
    } while (dw < 0);

    // For loop
    for (int i = 0; i < 5; i++) {
	    // do something
        if (i == 2) continue; // Skip iteration
        if (i == 4) break;    // Exit loop entirely
    }

    // Nested loops
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("(%d,%d) ", i, j);
        }
        printf("\n");
    }
    
    // ==========================================
    // 9. INPUT / OUTPUT & FORMATTING
    // ==========================================
    // Output Formatting with printf()
    // %d (int), %ld (long), %f (float/double), %c (char), %s (string), %p (pointer address)
    // %zu (size_t for sizeof)
    // Output with printf (formatted)
    // Output to console (stdout)
    // %s = string, %.1f = float with 1 decimal decimal
    printf("Basic printf: %s\n", "Hello World");
    printf("Formatted double: %.2f\n", doubleVar); // .2 restricts to 2 decimal places
    printf("Decimal integer:  %d\n", 42); 
    printf("Pointer address: %p\n", (void*)&intVar);

    // Padding and alignment
    printf("\nAlignment and padding:\n");
    printf("Right-aligned number: %10d\n", 42); // "        42"
    printf("Left-aligned text:  %-10s|\n", "Apple"); // "42        |"
    printf("Padded with zeros:  %05d\n", 42);
    
    // Character output
    printf("\nCharacter output: %c %c %c\n", 'H', 'i', '!');
    
    // Input with scanf (uncomment to test)
    int inputAge;
    char name[50];
    // Input from console (stdin)
    // name is already an address (array decays to pointer), so no `&`.
    // scanf("%s", name);              // Read string (up to whitespace)
    // %49s prevents the user from entering more text than the buffer can hold 
    // scanf("%49s", name);
    
    // printf("Enter an integer: ");
    // scanf("%d", &inputAge);
    // printf("You entered: %d\n", inputAge);
    // scanf reads formatted input. MUST pass the memory address using '&'
    // Returns number of items successfully matched.
    // if (scanf("%d", &inputAge) == 1) {
    //     printf("You entered: %d\n", inputAge);
    // }
    
    // Buffer Clearing (CRITICAL C MECHANIC)
    // scanf leaves the '\n' (Enter key) in the input buffer. 
    // We must manually flush it before reading strings.
    // int ch;
    // while ((ch = getchar()) != '\n' && ch != EOF); 
    // loop does nothing inside body , so it's a pure cleanup loop.
    
    // Reading entire line including spaces
    // char line[100];
    // printf("Enter a line: ");
    // fgets(line, sizeof(line), stdin);  // Read up to 99 chars or newline
    // printf("You entered: %s", line);


    // ==========================================
    // 10. PARSING & TYPE CONVERSION
    // ==========================================
    // Implicit Type Conversion (Coercion)
    double doubleResult = intVar; // int to double

    // Explicit Type Casting (Narrowing)
    int castInt = (int)3.99; // Truncates decimal, becomes 3

    // Parsing Strings to Numbers
    // Method 1: atoi() / atof() - Fast but unsafe (cannot distinguish '0' from error)
    char *numStr = "404";
    char str_num[] = "42";
    char invalid_str[] = "apple";
    int parsedInt = atoi(numStr); 
    printf("String '%s' parsed to int: %d\n", numStr, parsedInt);

    char *hexStr = "0xFF";
    // 1. Quick but risky parsing 
    int num = atoi(str_num);
    char *endPtr;
    // Method 2: strtol() / strtod() - Robust, standard industry practice
    // 2. Safe parsing with error checking using strtol
    // long safe_num = strtol(invalid_str, &endptr, 10);
    // If endptr points to the start of the string, no conversion happened 
    // if (endptr == invalid_str) { printf("C Error: No valid digits found to parse.\n"); }
    
    
    // Base 16 parsing, with error checking via endPtr
    long parsedHex = strtol(hexStr, &endPtr, 16); 
    printf("String '%s' parsed to hex: %ld\n", hexStr, parsedHex);
    
    // Converting Numbers to Strings
    // Use snprintf() to print formatted data into a character buffer.
    char stringifiedNum[20];
    snprintf(stringifiedNum, sizeof(stringifiedNum), "%d", 99);
    printf("Number 99 converted to string: \"%s\"\n", stringifiedNum);


    // ==========================================
    // 11. CALLING FUNCTIONS & PASS BY VALUE/REFERENCE
    // ==========================================
    // Function returning a value
    int sum = add(5, 10);
    printf("add(5, 10) = %d\n", sum);
    int val1 = 10, val2 = 10;
    
    // Pass by Value: Copies the data. Original is unaffected.
    // Pass by value (primitives)
    int originalVal = 10;
    printf("\nBefore passByValue: %d\n", originalVal);
    demonstratePassByValue(originalVal); 
    printf("After passByValue: %d (unchanged)\n", originalVal); // remains 10
    
    // Pass by Reference (Simulated): Passes the memory address. Original is mutated.
    // Pass by reference (pointers)
    int originalRef = 10;
    printf("\nBefore passByReference: %d\n", originalRef);
    demonstratePassByReference(&originalRef);
    printf("After passByReference: %d (changed!)\n", originalRef); // becomes 999


    // Array pass (decays to pointer)
    int numArray[] = {1, 2, 3, 4, 5};
    printf("\nArray before: [%d, %d, %d, %d, %d]\n", 
           numArray[0], numArray[1], numArray[2], numArray[3], numArray[4]);
    demonstrateArrayPass(numArray);
    printf("Array after: [%d, %d, %d, %d, %d]\n\n", 
           numArray[0], numArray[1], numArray[2], numArray[3], numArray[4]);
    
    // Variable length function
    int nums[] = {10, 20, 30, 40, 50};
    int total = sumAll(nums, 5);
    printf("sumAll([10,20,30,40,50]) = %d\n\n", total);

    return 0; // OS exit code 0 indicates successful execution
}


// ==========================================
// 12. FUNCTION DEFINITIONS
// ==========================================

void some_function(void) {
    // returns nothing
}


// Function definition - actual implementation
int add(int a, int b) {
    // Variables declared inside function are local
    int sum = a + b;
    return sum;
}

// Pass by Value
// 'val' is a local copy created on this function's stack frame.
void demonstratePassByValue(int val) {
    val = 999; // Only modifies the local copy of val
    printf("Inside function (pass by value): %d\n", val);
}

// Pass by Reference (Via Pointers)
// 'ptr' is a local pointer, but it points to the original variable's memory address.
void demonstratePassByReference(int *ptr) {
    *ptr = 999; // Dereferencing '*' modifies the actual value at the memory address
    printf("Inside function (pass by reference): %d\n", *ptr);
}

// Array parameter (decays to pointer, can modify original)
void demonstrateArrayPass(int arr[]) {
    arr[0] = 999;  // Modifies original array
    printf("Inside function (array modified): [%d, ...]\n", arr[0]);
}

// Function with variable length array parameter
int sumAll(int numbers[], int count) {
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += numbers[i];
    }
    return total;
}
