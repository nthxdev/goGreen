// Recommend reading xyz.c first

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <iomanip>
#include <cstdint> // For fixed-width integers
#include <initializer_list>
#include <cstdio>

using namespace std;

//  C++ Has optional garbage collection via smart pointers (RAII pattern).


// Global variable
int global_count = 0;

// ==================
// ===== class ======
// ==================
// Class definition
class Car {
private:
    string color;
    int year;

public:
    // Constructor
    Car(string c, int y) {
        color = c;
        year = y;
    }
    
    // Method
    void displayInfo() {
        cout << year << " " << color << " Car" << endl;
    }
    
    // Setter
    void setColor(string c) {
        color = c;
    }
    
    // Getter
    string getColor() {
        return color;
    }
};

// ==========================================
// 11. BASIC OF FUNCTIONS & WHERE TO DEFINE
// ==========================================
// In C++, functions must be declared before they are called.
// This is done via a "Forward Declaration" (Function Prototype) typically in a header (.h) file.
// The actual implementation (definition) goes in a source (.cpp) file.
// Forward declarations
// function prototype
int addNumbers(int a, int b);
void demonstratePassByValue(int val);
void demonstratePassByReference(int& ref);
void demonstratePassByPointer(int* ptr);
int sumVector(const vector<int>& nums);
void modifyValues(int val, int& ref, int* ptr);

// ===============================
// === some functions example: ===
// ================================
// Function with return value
int add(int a, int b) {
    return a + b;
}

// Function with no return
void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
}

// Function with default parameters
void print_message(string msg = "Default message") {
    cout << msg << endl;
}

// Function with multiple parameters
void swapValues(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Recursive function
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Function with variable arguments (varargs in C++11)
void printNumbers(initializer_list<int> nums) {
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

// function param and passing
// Pass by value - copy is made
void modify_value(int x) {
    x = 100;  // Only modifies copy
}

// Pass by reference - original is modified
void modify_reference(int& x) {
    x = 100;  // Modifies original
}

// Pass by const reference - read-only
void read_value(const int& x) {
    cout << "Value: " << x << endl;
    // x = 100;  // Compiler error - can't modify
}

// Pointer parameters
void modify_pointer(int* x) {
    *x = 100;  // Dereference to modify
}

// Entry point
int main() {
	// =======================
	// === implement class ===
	// ========================
    // Create object
    Car car1("Red", 2020);
    car1.displayInfo();
    car1.setColor("Blue");
    cout << "New color: " << car1.getColor() << endl;
    
    // Multiple objects
    Car car2("Green", 2022);
    car2.displayInfo();
    // =====================================
	// === calling the function examples ===
	// =====================================
	cout << "5 + 3 = " << add(5, 3) << endl;
    
    greet("Alice");
    
    print_message();                    // Uses default
    print_message("Custom message");
    
    int x = 5, y = 10;
    swapValues(x, y);
    cout << "After swap: x=" << x << ", y=" << y << endl;
    
    cout << "5! = " << factorial(5) << endl;
    
    printNumbers({1, 2, 3, 4, 5});
    
	int value = 5;
    
    modify_value(value);
    cout << "After pass by value: " << value << endl;  // Still 5
    
    modify_reference(value);
    cout << "After pass by reference: " << value << endl;  // Now 100
    
    int num = 42;
    read_value(num);
    
    modify_pointer(&num);
    cout << "After pointer modification: " << num << endl;
    
    // -----------------------------------------
    std::cout << "Hello World\n";
    // block_var not accessible here
    // ==========================================
    // 1. BASICS OF VARIABLES & CONSTANTS
    // ==========================================
    // Syntax: type identifier = value;
    // C++ is statically typed. Variables must be declared before use.
    int intVar = 10;
    
    // 'auto' keyword: The compiler deduces the exact type at compile-time based on the assigned value.
    auto deducedVar = 20.5; // Deduced as double
    // Deduced means figured out automatically from available information.

    // Constants:
    // const: Read-only variable. Evaluated at either runtime or compile-time.
    const double PI = 3.14159;
    // constexpr (C++11): Strictly evaluated at compile-time. Used for deep optimization.
    // compile-time constant: value is guaranteed known at compile time.
    constexpr int MAX_BUFFER = 1024;
    // Difference in const vs constexpr
    // const int a = x; OK  but the value is coming from x, which only know when program runs
	// constexpr int b = x; < -- ERROR 

    // ==========================================
    // 2. DATA TYPES BUILT-IN PRIMITIVES
    // ==========================================
    // Unlike Java, C++ primitive sizes are highly dependent on the compiler and OS architecture.
    // Modern C++ prefers <cstdint> (e.g., int32_t, uint64_t) for strict, guaranteed bit sizing.
    
    // Numbers (Whole Numbers)
    // char (often used as 1-byte int): 1 byte = 8 bits
    int8_t varByte = 127; 
    // short: minimum 2 bytes = 16 bits
    short varShort = 32767;
    // int: minimum 2 bytes, usually 4 bytes = 32 bits
    int varInt = 2147483647;
    // long: minimum 4 bytes (can be 4 or 8 depending on 32/64 bit OS)
    long varLong = 2147483647L;
    // long long: minimum 8 bytes = 64 bits
    long long varLongLong = 9223372036854775807LL;

    // Floating-Point (Decimals)
    // float: 4 bytes = 32 bits. Requires 'f' suffix. Precision: ~7 digits.
    float varFloat = 3.14f;
    // double: 8 bytes = 64 bits. Standard default for decimals. Precision: ~15 digits.
    double varDouble = 3.141592653589793;
    // long double: hardware dependent, typically 8, 12, or 16 bytes.
    long double varLongDouble = 3.141592653589793238L;

    // Character
    // char: 1 byte (ASCII). Must use single quotes.
    char varChar = 'A';
    // C++ also has wchar_t, char16_t, char32_t for wider Unicode handling.

    // Boolean
    // bool: 1 byte conceptually. Values strictly evaluate to true (1) or false (0).
    bool varBoolean = true;
    
    cout << "int8_t: " << (int)varByte << "\n";
    cout << "short: " << varShort << "\n";
    cout << "int: " << varInt << "\n";
    cout << "long: " << varLong << "\n";
    cout << "long long: " << varLongLong << "\n";
    cout << "float: " << fixed << setprecision(2) << varFloat << "\n";
    cout << "double: " << setprecision(15) << varDouble << "\n";
    cout << "char: " << varChar << "\n";
    cout << "bool: " << varBoolean << "\n\n";
    
    // Check sizes
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    
    // ==========================================
    // 3. REFERENCE TYPES & MEMORY ARCHITECTURE
    // ==========================================
    // C++ exposes direct memory manipulation. There is no background Garbage Collector.
    
	// --- POINTERS ---
    // Pointers vs References:
    int target = 42;
    int& refTarget = target; // Reference: An immutable alias to 'target'. Cannot be null or re-seated.
    int* ptrTarget = &target; // Pointer: A variable holding a memory address. Can be null and changed.
    cout << "Variable target: " << target << "\n";
    cout << "Reference refTarget: " << refTarget << "\n";
    cout << "Pointer ptrTarget: " << *ptrTarget << "\n";
    
    // Raw pointers with heap allocation
    int* heapInt = new int(100);
    cout << "Heap allocated int: " << *heapInt << "\n";
    delete heapInt;
    heapInt = nullptr;
    
    // Smart Pointers (Modern C++ <memory> - Safe Heap Allocation):
    // Emulates Garbage Collection via RAII. Automatically calls 'delete' when out of scope.
    unique_ptr<int> smartInt = make_unique<int>(200);
    cout << "Unique pointer: " << *smartInt << "\n"; // Exclusive ownership
    shared_ptr<int> sharedInt = make_shared<int>(300);
    cout << "Shared pointer: " << *sharedInt << "\n";  // Reference-counted shared ownership

    // --- ARRAYS ---
    // Legacy C-style array. Decays to a pointer. Unsafe.
    int cArray[4] = {10, 20, 30, 40};
    // C++11 fixed-size array on the Stack. Safe bounds.
    array<int, 4> cppArray = {10, 20, 30, 40};
    // Dynamic array on the Heap (C++ equivalent to ArrayList).
    vector<int> dynamicArray = {10, 20, 30, 40, 50};
    
    cout << "C-style array[0]: " << cArray[0] << "\n";
    cout << "std::array[0]: " << cppArray[0] << "\n";
    cout << "std::vector size: " << dynamicArray.size() << "\n";
    cout << "std::vector[2]: " << dynamicArray[2] << "\n\n";
    
    
	// --- STRINGS ---
    // String (C++ provides string class)
    string name = "Alice";
    string message = "Hello, World!";
    // Stack Allocation (Fast, local scope, automatically destroyed):
    // stack allocation
    std::string stackStr = "Hello"; 
    cout << "Stack string: " << stackStr << "\n";

    string str1 = "Hello";
    string str2 = "World";
    
    // String concatenation
    string combined = str1 + " " + str2;
    cout << combined << endl;           // Hello World
    
    // String operations
    cout << "Length: " << str1.length() << endl;
    cout << "First char: " << str1[0] << endl;
    cout << "Substring: " << str1.substr(1, 3) << endl;  // "ell"
    
    // String search
    size_t pos = str1.find("ll");
    cout << "Position of 'll': " << pos << endl;
    
    
	// --- HEAP ---
    // Heap Allocation (Manual Memory Management - Raw Pointers):
    // Uses 'new'. Lives dynamically in the Heap until explicitly destroyed with 'delete'.
    int* heapInt2 = new int(100); 
    delete heapInt2; // Failure to call delete results in a Memory Leak.

    // Null Concept:
    // C++11 introduced 'nullptr' to replace the unsafe legacy 'NULL' macro (which was just the integer 0).
    int* nullPtr = nullptr; 

	// --- VECTOR ---
    // Vector (dynamic array)
    vector<int> numbers;
    numbers.push_back(10);          // Add element
    numbers.push_back(20);
    numbers.push_back(30);
    
    // Access vector
    cout << "First: " << numbers[0] << endl;
    cout << "Size: " << numbers.size() << endl;
    
    // Iterate
    for (int num : numbers) {      // Range-based for loop
        cout << num << " ";
    }
    cout << endl;
    
    // Vector of strings
    vector<string> names = {"Alice", "Bob", "Charlie"};
    for (const auto& name : names) {
        cout << name << endl;
    }
       
    // Function with vector
    vector<int> nums = {10, 20, 30, 40, 50};
    int vecSum = sumVector(nums);
    cout << "\nsumVector([10,20,30,40,50]) = " << vecSum << "\n\n";

    cout << "--- Vector Operations ---\n";
    vector<int> myVector;
    myVector.push_back(100);
    myVector.push_back(200);
    myVector.push_back(300);
    
    cout << "Vector size: " << myVector.size() << "\n";
    cout << "Vector elements: ";
    for (const auto& elem : myVector) {
        cout << elem << " ";
    }
    
    // ==========================================
    // 4. OPERATORS
    // ==========================================
    int a = 10, b = 3;
    // Arithmetic: +, -, *, /, %
    cout << "Arithmetic: " << a << " + " << b << " = " << (a + b) << "\n";
    cout << "Arithmetic: " << a << " - " << b << " = " << (a - b) << "\n";
    cout << "Arithmetic: " << a << " * " << b << " = " << (a * b) << "\n";
    cout << "Arithmetic: " << a << " / " << b << " = " << (a / b) << "\n";
    cout << "Arithmetic: " << a << " % " << b << " = " << (a % b) << "\n";
    
    // Comparison: ==, !=, >, <, >=, <=
    cout << "\nComparison: " << a << " > " << b << " is " << (a > b) << "\n";
    cout << "Comparison: " << a << " < " << b << " is " << (a < b) << "\n";
    cout << "Comparison: " << a << " == " << b << " is " << (a == b) << "\n";
    
    // Logical: && (AND), || (OR), ! (NOT)
    cout << "\nLogical: true && false = " << (true && false) << "\n";
    cout << "Logical: true || false = " << (true || false) << "\n";
    cout << "Logical: !true = " << (!true) << "\n";
    

    // Bitwise (Direct CPU bit manipulation): & (AND), | (OR), ^ (XOR), ~ (NOT), << (Shift Left), >> (Shift Right)

    // Assignment: =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=

    // Unary: ++, --
    int counter = 5;
    cout << "\nUnary: counter = " << counter << "\n";
    cout << "Unary: counter++ = " << counter++ << " (then " << counter << ")\n";
    cout << "Unary: ++counter = " << ++counter << "\n\n";
    
    // Memory/Pointer Specific:
    //   & (Address-of operator)
    //   * (Dereference operator)
    //   -> (Member access through a pointer)
    //   sizeof (Returns size of a type in bytes)

    // ==========================================
    // 5. CONDITIONALS (If Family)
    // ==========================================
    bool condition = false, anotherCondition = true;
    
    if (condition) {
        // Execute if true
    } else if (anotherCondition) {
        if (true) { /* Nested */ } 
    } else {
        // Default
    }

    // C++17 Init-statement in if:
    // Allows initializing a variable whose scope is strictly bound to the if-else block.
    if (int scopedVal = 5; scopedVal > 0) {
        scopedVal++;
    }

    // ==========================================
    // 6. SWITCH 
    // ==========================================
    int switchVar = 1;
    // Allowed Types: C++ switch strictly requires an integral (int, char) or Enum type.
    // You CANNOT switch on std::string or floats.
    switch (switchVar) {
        case 1:
            // Code
            break; // Required to prevent falling into case 2
        case 2:
            // C++17 [[fallthrough]] explicitly tells the compiler the missing break is intentional.
            [[fallthrough]];
        default:
            break;
    }
	
	// =========================================
	// 7. TERNARY
	// =========================================
	
    // Ternary Operator
    // Syntax: condition ? true_val : false_val;
    int ternaryAge = 20;
    std::string ternaryStatus = (ternaryAge >= 18) ? "Adult" : "Minor";

    // Nested ternary
    int grade = 85;
    string letter = (grade >= 90) ? "A" :
                    (grade >= 80) ? "B" :
                    (grade >= 70) ? "C" : "F";
    cout << "Grade: " << letter << endl;
    
    
    // ==========================================
    // 7. LOOPS
    // ==========================================
    // While
    int count = 0;
    while (count < 3) {
    // DO something
    count++; 
    }

    // Do-While (Guaranteed execution at least once)
    do { 
    // DO something
    count--;
    } while (count > 0);

    // Standard For Loop
    for (int i = 0; i < 5; i++) { }

    // Range-based For Loop (C++11 For-Each):
    std::vector<std::string> loopNames = {"Alice", "Bob"};
    // Architectural Best Practice:
    // Use 'const auto&' to pass by read-only reference. This prevents deep copying of large objects.
    for (const auto& name : loopNames) { 
        // Read-only 
        cout << "  Name: " << name << "\n";
    }
    // Use 'auto&' if you need to mutate the elements in place.
    for (auto& name : loopNames) { 
        name += "!"; 
    }
    
    // Controls: break (exits immediately), continue (skips to next iteration)
    // Break and continue
    for (int i = 0; i < 10; i++) {
        if (i == 5) break;          // Exit loop
        if (i == 2) continue;       // Skip to next
        cout << i << " ";
    }
    cout << endl;
    
    // Nested loops
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << "(" << i << "," << j << ") ";
        }
        cout << endl;
    }
    
    
    // ==========================================
    // 8. INPUT / OUTPUT
    // ==========================================
    // Standard Output (std::cout) via the bitwise left-shift insertion operator (<<)
    // std::endl adds a newline AND explicitly flushes the output buffer. 
    // Architecturally, using '\n' is significantly faster because it defers flushing.
    std::cout << "Message Output\n";
    std::cerr << "Standard Error Output (Unbuffered)\n";

    // Standard Input (std::cin) via extraction operator (>>)
    // std::cin >> varInt; // Reads up to the first whitespace space. Leaves \n in buffer.

    // Full line input reading (Equivalent to Java's nextLine):
    std::string fullLine;
    // getline(cin, name);
    // std::getline(std::cin >> std::ws, fullLine); // std::ws clears leftover \n from buffer

    // ==========================================
    // 9. FORMATTING
    // ==========================================
    // C++ offers multiple ways to format strings natively:
    
    // 1. C++ I/O Manipulators (<iomanip>): Modifies the stream state
    double price = 19.9934;
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << "\n";
    // Padding: std::setw() handles width, std::left/right handles alignment.
    int population = 1500000;
    std::cout << "Population: " << std::setfill(' ') << std::setw(10) << population << "\n";
    std::cout << std::left << std::setw(10) << "Apple" << std::setw(5) << 5 << "\n";
    // Hexadecimal and octal
    cout << hex << num << endl;                // 2a (hexadecimal)
    cout << oct << num << endl;                // 52 (octal)
    cout << dec << num << endl;                // 42 (decimal)
    
    // 2. C-Style Formatting (<cstdio>): Identical to Java's printf. Still heavily used in C++ for performance.
    printf("char= %c, int=%d, float=%.2f\n", varChar, varInt, varFloat);

    // 3. C++20 <format> (Similar to Python's f-strings / C# interpolation):
    // std::cout << std::format("Price: ${:.2f}\n", price);

    // ==========================================
    // 10. PARSING & TYPE CONVERSION (Casting)
    // ==========================================
    // Implicit conversion
    int i = 42;
    double d = i; // int to double
    
	// Parsing Strings to Numbers:
    std::string ageInput = "25";
    int parsedAge = std::stoi(ageInput);     // String TO Integer
    double parsedDouble = std::stod("3.14"); // String TO Double

    // Converting Numbers to Strings:
    int score = 99;
    std::string textScore = std::to_string(score);

    // Casting (Type Conversion):
    // Avoid legacy C-style casting: (int)varDouble. It's unsafe.
    // C-style casting (avoid in modern C++)
    double decimal = 3.7;
    int whole = (int)decimal;      // 3

    // C++ style casting (preferred)
    // C++ provides 4 named casts for strict architectural safety:

    // 1. static_cast: Standard, safe conversions (e.g., float to int) checked at compile-time.
    double varDoubleForCast = 3.14;
    int cppCast = static_cast<int>(varDoubleForCast);  // 3

    // 2. dynamic_cast: Safe downcasting in OOP polymorphism (checked at runtime).
    class Base { public: virtual ~Base() {} };
    class Derived : public Base {};

    Base* basePtr = new Derived();
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr); // succeeds

    // 3. const_cast: Used exclusively to add or remove 'const' qualifiers.
    const int constX = 10;
    int* modifiablePtr = const_cast<int*>(&constX);

    // 4. reinterpret_cast: Dangerous low-level reinterpretation of raw bits.(e.g., pointer to int).
    int numForAddress = 65;
    int* ptrForAddress = &numForAddress;
    long long address = reinterpret_cast<long long>(ptrForAddress); // pointer -> integer


    // Function with return value
    int sum = addNumbers(5, 10);
    cout << "addNumbers(5, 10) = " << sum << "\n";
    
    // Pass by value
    int originalVal = 10;
    cout << "\nBefore passByValue: " << originalVal << "\n";
    demonstratePassByValue(originalVal);
    cout << "After passByValue: " << originalVal << " (unchanged)\n";
    
    // Pass by reference
    int originalRef = 10;
    cout << "\nBefore passByReference: " << originalRef << "\n";
    demonstratePassByReference(originalRef);
    cout << "After passByReference: " << originalRef << " (changed!)\n";
    
    // Pass by pointer
    int originalPtr = 10;
    cout << "\nBefore passByPointer: " << originalPtr << "\n";
    demonstratePassByPointer(&originalPtr);
    cout << "After passByPointer: " << originalPtr << " (changed!)\n";


    // Function Call Demonstration for Pass-by mechanics:
    int a2 = 10, b2 = 20, c2 = 30;
    modifyValues(a2, b2, &c2);
    // Result: 
    // 'a' remains 10.
    // 'b' is mutated to 99.
    // 'c' is mutated to 99.

    return 0; // Standard OS exit code (0 = success)
    
}

// ==========================================
// 12. PARAMETERS & PASS BY MECHANICS
// ==========================================

// Syntax: returnType methodName(type param1, type param2) { body }

int sumVector(const vector<int>& nums) {
    int total = 0;
    for (const auto& num : nums) {
        total += num;
    }
    return total;
}

int addNumbers(int a, int b) {
    return a + b;
}
// 1. Pass by Value (int val): 
// Copies the entire object. Mutations inside the method do NOT affect the original. Expensive for large objects.
void demonstratePassByValue(int val) {
    val = 999;
    cout << "Inside function (pass by value): " << val << "\n";
}

// 2. Pass by Reference (int& ref): 
//    Passes a direct alias to the original memory block. Mutations DO affect the original. Fast and safe
void demonstratePassByReference(int& ref) {
    ref = 999;
    cout << "Inside function (pass by reference): " << ref << "\n";
}

// 3. Pass by Pointer (int* ptr): 
//    Passes the memory address. Must be explicitly dereferenced (*) to mutate the original. Can be null.
void demonstratePassByPointer(int* ptr) {
    if (ptr != nullptr) {
        *ptr = 999;
        cout << "Inside function (pass by pointer): " << *ptr << "\n";
    }
}


void modifyValues(int val, int& ref, int* ptr) {
    val = 99;  // Modifies local stack copy. Caller is unaffected.
    
    ref = 99;  // Directly modifies the caller's variable.
    
    if (ptr != nullptr) {
        *ptr = 99; // Dereferences the pointer to modify the caller's variable in memory.
    }
}