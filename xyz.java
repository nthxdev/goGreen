import java.util.Scanner;
import java.util.ArrayList;

/**
 * Execution: Java executes top-down with JVM bytecode compilation.
 * All primitives are stored on Stack; all Objects reference Heap memory.
 */
public class xyz {

    public static void main(String[] args) {
        System.out.println("Hello World");

        // ==========================================
        // 1. BASICS OF VARIABLES & CONSTANTS
        // ==========================================
        // Syntax: type variableName = value;
        // Java is statically typed. Variables must be declared before use.
        
        int standardVar = 10;
        
        // Constants: declared with final keyword
        final double PI = 3.14159;
        final int MAX_USERS = 100;
        
        System.out.println("Variable: " + standardVar);
        System.out.println("Constant PI: " + PI);


        // ==========================================
        // 2. BUILT-IN PRIMITIVES
        // ==========================================
        
        // Numbers (Whole Numbers)
        // byte: 1 byte (8 bits), range -128 to 127
        byte varByte = 127;
        
        // short: 2 bytes (16 bits), range -32,768 to 32,767
        short varShort = 32767;
        
        // int: 4 bytes (32 bits), range -2,147,483,648 to 2,147,483,647
        int varInt = 2147483647;
        
        // long: 8 bytes (64 bits), requires 'L' suffix
        long varLong = 9223372036854775807L;
        
        // Floating-Point (Decimals)
        // float: 4 bytes (32 bits), precision ~6-7 decimal digits, requires 'f' suffix
        float varFloat = 3.14f;
        
        // double: 8 bytes (64 bits), precision ~15 decimal digits, default for decimals
        double varDouble = 3.141592653589793;
        
        // Character: 2 bytes (16 bits), single Unicode character, single quotes mandatory
        char varChar = 'A';
        
        // Boolean: 1 byte (conceptually), stores true or false
        boolean varBoolean = true;
        
        System.out.println("\n--- Primitives ---");
        System.out.println("byte: " + varByte);
        System.out.println("short: " + varShort);
        System.out.println("int: " + varInt);
        System.out.println("long: " + varLong);
        System.out.println("float: " + varFloat);
        System.out.println("double: " + varDouble);
        System.out.println("char: " + varChar);
        System.out.println("boolean: " + varBoolean);


        // ==========================================
        // 3. REFERENCE TYPES (OBJECTS)
        // ==========================================
        // Reference types store memory address pointing to Heap objects.
        // Stack holds the reference variable; Heap holds the actual object.
        
        // Strings: immutable objects
        String varStr = "Hello";
        String anotherStr = "World";
        
        // Arrays: ordered collections of same type
        int[] varArrInt = {10, 20, 30, 40};
        String[] varArrStr = new String[3];
        varArrStr[0] = "Alice";
        varArrStr[1] = "Bob";
        varArrStr[2] = "Charlie";
        
        // ArrayList: dynamic array (equivalent to C++ std::vector)
        ArrayList<String> namesList = new ArrayList<>();
        namesList.add("Alice");
        namesList.add("Bob");
        namesList.add("Charlie");
        
        // null: represents absence of value (only for reference types, NOT primitives)
        String nullValue = null;
        
        System.out.println("\n--- Reference Types ---");
        System.out.println("String: " + varStr);
        System.out.println("Array[0]: " + varArrInt[0]);
        System.out.println("ArrayList: " + namesList);
        System.out.println("null value: " + nullValue);


        // ==========================================
        // 4. OPERATORS
        // ==========================================
        
        // Arithmetic operators: +, -, *, /, %
        int a = 10, b = 3;
        System.out.println("\n--- Arithmetic Operators ---");
        System.out.println(a + " + " + b + " = " + (a + b));
        System.out.println(a + " - " + b + " = " + (a - b));
        System.out.println(a + " * " + b + " = " + (a * b));
        System.out.println(a + " / " + b + " = " + (a / b));
        System.out.println(a + " % " + b + " = " + (a % b));
        
        // Comparison operators: ==, !=, >, <, >=, <=
        System.out.println("\n--- Comparison Operators ---");
        System.out.println(a + " > " + b + " is " + (a > b));
        System.out.println(a + " < " + b + " is " + (a < b));
        System.out.println(a + " == " + b + " is " + (a == b));
        
        // Logical operators: && (AND), || (OR), ! (NOT)
        System.out.println("\n--- Logical Operators ---");
        System.out.println("true && false = " + (true && false));
        System.out.println("true || false = " + (true || false));
        System.out.println("!true = " + (!true));
        
        // Assignment operators: =, +=, -=, *=, /=, %=
        int num = 20;
        num += 5;  // num = num + 5
        System.out.println("\nAfter num += 5: " + num);
        
        // Unary operators: ++, --, +, -
        int counter = 0;
        System.out.println("counter: " + counter);
        System.out.println("counter++: " + counter++);  // Post-increment
        System.out.println("++counter: " + (++counter));  // Pre-increment


        // ==========================================
        // 5. CONDITIONALS (If Family)
        // ==========================================
        // if statement evaluates boolean condition
        
        System.out.println("\n--- If Conditionals ---");
        int age = 25;
        
        if (age < 18) {
            System.out.println("You are a minor");
        } else if (age >= 18 && age < 65) {
            System.out.println("You are an adult");
        } else {
            System.out.println("You are a senior");
        }
        
        // Nested conditionals
        int score = 85;
        if (score >= 80) {
            if (score >= 90) {
                System.out.println("Grade: A");
            } else {
                System.out.println("Grade: B");
            }
        } else {
            System.out.println("Grade: C or below");
        }


        // ==========================================
        // 6. SWITCH & TERNARY OPERATORS
        // ==========================================
        
        System.out.println("\n--- Switch Statement ---");
        // switch only works with: byte, short, char, int, String, Enum
        int dayNum = 3;
        String dayName;
        
        switch (dayNum) {
            case 1:
                dayName = "Monday";
                break;
            case 2:
                dayName = "Tuesday";
                break;
            case 3:
                dayName = "Wednesday";
                break;
            default:
                dayName = "Unknown";
        }
        System.out.println("Day " + dayNum + ": " + dayName);
        
        // Ternary operator: (condition) ? valueIfTrue : valueIfFalse
        System.out.println("\n--- Ternary Operator ---");
        int userAge = 20;
        String status = (userAge >= 18) ? "Adult" : "Minor";
        System.out.println("Status: " + status);
        
        // Enhanced Switch (Java 14+)
        System.out.println("\n--- Enhanced Switch Expression ---");
        String month = "March";
        int days = switch (month) {
            case "January", "March", "May", "July", "August", "December" -> 31;
            case "April", "June", "September", "November" -> 30;
            case "February" -> 28;
            default -> 0;
        };
        System.out.println("Days in " + month + ": " + days);


        // ==========================================
        // 7. LOOPS
        // ==========================================
        
        System.out.println("\n--- While Loop ---");
        int count = 0;
        while (count < 3) {
            System.out.println("While iteration: " + count);
            count++;
        }
        
        // Do-while (executes at least once)
        System.out.println("\n--- Do-While Loop ---");
        count = 0;
        do {
            System.out.println("Do-while iteration: " + count);
            count++;
        } while (count < 2);
        
        // Standard for loop
        System.out.println("\n--- For Loop ---");
        for (int i = 0; i < 3; i++) {
            System.out.println("For iteration: " + i);
            if (i == 1) {
                System.out.println("  (Skipping next iteration)");
                continue;
            }
        }
        
        // Enhanced for-each loop (for iterables)
        System.out.println("\n--- For-Each Loop ---");
        int[] numbers = {10, 20, 30, 40};
        for (int num_val : numbers) {
            System.out.println("Array element: " + num_val);
        }
        
        // Loop with break
        System.out.println("\n--- Loop with Break ---");
        for (int i = 0; i < 5; i++) {
            if (i == 3) {
                System.out.println("Breaking at i=" + i);
                break;
            }
            System.out.println("i=" + i);
        }


        // ==========================================
        // 8. INPUT & OUTPUT
        // ==========================================
        
        System.out.println("\n--- Output ---");
        System.out.println("println adds newline");
        System.out.print("print ");
        System.out.print("without newline");
        System.out.println();
        
        // Formatted output with printf
        System.out.println("\n--- Formatted Output (printf) ---");
        int age_out = 25;
        double salary = 50000.50;
        char grade = 'A';
        
        System.out.printf("Age: %d%n", age_out);
        System.out.printf("Salary: $%.2f%n", salary);
        System.out.printf("Grade: %c%n", grade);
        System.out.printf("%-15s %8d%n", "Apple", 25);  // Left-align text, right-align number
        
        // Input with Scanner
        System.out.println("\n--- Scanner Input ---");
        Scanner sc = new Scanner(System.in);
        // Uncomment to test input:
        // System.out.print("Enter your name: ");
        // String inputName = sc.nextLine();
        // System.out.println("Hello, " + inputName);
        
        // Alternative: demonstrate without actual input
        String demoName = "John";
        int demoAge = 30;
        System.out.println("Entered name: " + demoName);
        System.out.println("Entered age: " + demoAge);


        // ==========================================
        // 9. STRING FORMATTING
        // ==========================================
        
        System.out.println("\n--- String Formatting ---");
        double price = 19.9934;
        int population = 1500000;
        
        // String.format() returns formatted string
        String formatted1 = String.format("Price: $%.2f", price);
        System.out.println(formatted1);
        
        // printf directly to console
        System.out.printf("Population: %,d%n", population);
        
        // String concatenation
        String message = "Price: $" + String.format("%.2f", price);
        System.out.println(message);


        // ==========================================
        // 10. PARSING & TYPE CONVERSION
        // ==========================================
        
        System.out.println("\n--- Type Conversion ---");
        
        // String to Integer
        String ageInput = "25";
        int parsedAge = Integer.parseInt(ageInput);
        System.out.println("Parsed int: " + parsedAge);
        
        // String to Double
        String priceInput = "99.99";
        double parsedPrice = Double.parseDouble(priceInput);
        System.out.println("Parsed double: " + parsedPrice);
        
        // Integer to String
        int score_val = 99;
        String scoreString1 = String.valueOf(score_val);  // Recommended
        String scoreString2 = Integer.toString(score_val);
        System.out.println("Number to String: " + scoreString1);
        
        // Explicit casting (narrowing)
        double decimalValue = 10.7;
        int castToInt = (int) decimalValue;  // Truncates to 10
        System.out.println("Cast 10.7 to int: " + castToInt);


        // ==========================================
        // 11 & 12. FUNCTIONS/METHODS & PARAMETERS
        // ==========================================
        
        System.out.println("\n--- Methods/Functions ---");
        
        // Call method that returns a value
        int sum = addNumbers(5, 10);
        System.out.println("5 + 10 = " + sum);
        
        // Pass by value (primitives)
        int originalValue = 10;
        System.out.println("Before passByValue: " + originalValue);
        passByValue(originalValue);
        System.out.println("After passByValue: " + originalValue);  // Still 10
        
        // Pass by reference (objects)
        int[] originalArray = {100};
        System.out.println("Before passByReference: " + originalArray[0]);
        passByReference(originalArray);
        System.out.println("After passByReference: " + originalArray[0]);  // Changed to 999
        
        // Variable arguments (varargs)
        int sumVarargs = sumMultiple(1, 2, 3, 4, 5);
        System.out.println("Sum of 1,2,3,4,5: " + sumVarargs);
        
        // Default parameter behavior (Java doesn't have default params, but overloading)
        printMessage("Hello");  // Uses overloaded version
        printMessage("Hello", "World");
  
        sc.close();  // Close Scanner resource
        System.out.println("\n--- Program Complete ---");
    }


    // ==========================================
    // METHOD DEFINITIONS
    // ==========================================
    
    // Simple method with return value
    public static int addNumbers(int a, int b) {
        return a + b;
    }
    
    // Demonstrate pass by value (primitives)
    // Changes inside method don't affect original
    public static void passByValue(int val) {
        val = 999;
        System.out.println("Inside method (pass by value): " + val);
    }
    
    // Demonstrate pass by reference (objects)
    // Changes to object content affect original
    public static void passByReference(int[] arr) {
        arr[0] = 999;  // Modifies the actual array
        System.out.println("Inside method (pass by reference): " + arr[0]);
    }
    
    // Method with variable number of arguments (varargs)
    public static int sumMultiple(int... numbers) {
        int total = 0;
        for (int num : numbers) {
            total += num;
        }
        return total;
    }
    
    // Method overloading (different parameter lists, same method name)
    public static void printMessage(String msg) {
        System.out.println("Message: " + msg);
    }
    
    public static void printMessage(String msg1, String msg2) {
        System.out.println("Message: " + msg1 + " " + msg2);
    }
}
