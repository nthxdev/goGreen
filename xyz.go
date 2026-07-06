package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

/**
 * Execution: Go compiles to single binary. Lightweight goroutines for concurrency.
 * Escape analysis determines Stack vs Heap allocation at compile time.
 */

// Function declarations

// Constants: Evaluated strictly at compile time. No dynamic assignment.
// Untyped constants (like Pi below) maintain arbitrary precision until assigned.
const Pi = 3.14159265358979323846
const TypedMaxUsers int = 100

// Entry point
func main() {
	fmt.Println("Hello World")

	/*
		================================
		1. BASICS OF VARIABLES: DEFINITION & CONSTANTS
		=================================
		Syntax options:
		1. var name type = value (Standard, explicit type)
		2. var name = value      (Type inference at compile time)
		3. name := value         (Short variable declaration - idiomatic for local scopes)
	*/
	var explicitVar int = 10
	var inferredVar = 20
	shortVar := 30

	fmt.Printf("Explicit variable: %d\n", explicitVar)
	fmt.Printf("Inferred variable: %d\n", inferredVar)
	fmt.Printf("Short variable: %d\n", shortVar)
	fmt.Printf("Const PiValue: %.5f\n", Pi)
	fmt.Printf("Const MaxBuffer: %d\n\n", TypedMaxUsers)
	// ==========================================
	// 2. BUILT-IN PRIMITIVES
	// ==========================================
	// Go maps types directly to hardware architectures without wrapper classes.
	// --- Integers ---
	// 'int' size is architecture-dependent (64-bit strictly on your Linux/WSL setup).
	var varInt int = 2147483647
	var varInt8 int8 = 127                   // 1 byte: -128 to 127
	var varInt16 int16 = 32767               // 2 bytes
	var varInt32 int32 = 2147483647          // 4 bytes
	var varInt64 int64 = 9223372036854775807 // 8 bytes

	// Unsigned integers (positive only ranges)
	var varUint8 uint8 = 255 // 'byte' is a built-in alias for uint8
	var varByte byte = 255   // Idiomatic for raw binary/ASCII data

	// --- Floating-Point (Decimals) ---
	// IEEE-754 standard. Go requires explicit bit sizes. No generic "float".
	var varFloat32 float32 = 3.1415927       // 4 bytes. ~7 decimal digits of precision
	var varFloat64 float64 = 3.1415926535897 // 8 bytes. ~15 decimal digits. Default choice.

	// --- Character (Rune/Rune for unicode) ---
	// Go does not have a 'char' primitive. It uses 'rune' (alias for int32).
	// Represents a Unicode code point to natively support multi-byte characters.
	var varRune rune = 'A' // Stores numeric 65. Requires single quotes.

	// --- Boolean ---
	var varBool bool = true

	fmt.Printf("int: %d\n", varInt)
	fmt.Printf("int8: %d\n", varInt8)
	fmt.Printf("int16: %d\n", varInt16)
	fmt.Printf("int32: %d\n", varInt32)
	fmt.Printf("int64: %d\n", varInt64)
	fmt.Printf("uint8: %d\n", varUint8)
	fmt.Printf("byte: %d\n", varByte)
	fmt.Printf("float32: %f\n", varFloat32)
	fmt.Printf("float64: %.15f\n", varFloat64)
	fmt.Printf("rune (char): %c (%d)\n", varRune, varRune)
	fmt.Printf("bool: %v\n\n", varBool)

	// ==========================================
	// 3. REFERENCE TYPES & MEMORY
	// ==========================================
	// Go determines Stack vs. Heap allocation via "Escape Analysis" at compile time.
	// If a variable's reference outlives its scope, it "escapes" to the Heap.

	// --- Pointers ---
	// Variables holding the raw memory address of another variable.
	var varInt_val int = 42
	var ptrInt *int = &varInt_val // '&' operator extracts the memory address
	fmt.Printf("Variable: %d\n", varInt_val)
	fmt.Printf("Pointer address: %p\n", ptrInt)
	fmt.Printf("Dereferenced pointer: %d\n", *ptrInt)

	// --- Strings ---
	// Primitive, immutable byte slices. Under the hood, they are a struct (StringHeader)
	// containing a pointer to a read-only backing array and an integer length.
	var varStr string = "Hello"
	fmt.Printf("String: %s\n", varStr)
	fmt.Printf("String length: %d\n", len(varStr))

	// --- Arrays ---
	// Fixed-size, statically allocated. In Go, Arrays are VALUES, not references.
	// Passing an array to a function copies the entire contiguous memory block.
	var varArrInt [4]int = [4]int{10, 20, 30, 40}
	fmt.Printf("Array: %v\n", varArrInt)
	fmt.Printf("Array[0]: %d\n", varArrInt[0])

	// --- Slices ---
	// Dynamic, reference-like arrays. Internally a struct (SliceHeader):
	// { Pointer to backing Array, Length, Capacity }.
	var varSlice []int = []int{10, 20, 30}
	varSlice = append(varSlice, 40, 50)
	fmt.Printf("Slice: %v (length: %d, capacity: %d)\n", varSlice, len(varSlice), cap(varSlice))
	emptySlice := make([]string, 3) // make() allocates memory & initializes the underlying array

	// --- Maps & Channels ---
	// Complex reference types. Must be initialized with make().
	varMap := make(map[string]int) // Hash table
	varChan := make(chan int)      // Concurrency synchronization primitive
	// Maps (hash tables)
	varMap["Alice"] = 30
	varMap["Bob"] = 25
	fmt.Printf("Map: %v\n", varMap)

	// --- Special Type: nil (zero-value for reference types) ---
	// Zero-value for pointers, interfaces, maps, slices, channels, and functions.
	var nilSlice []int = nil // Primitives (int, bool, float) CANNOT be nil.
	fmt.Printf("Nil slice: %v (is nil: %v)\n\n", nilSlice, nilSlice == nil)
	/* ==========================================================================
	   4. ALL OPERATORS
	   ==========================================================================
	*/
	// Relational: ==, !=, >, <, >=, <=
	a, b := 10, 3
	fmt.Printf("\nComparison: %d > %d is %v\n", a, b, a > b)
	fmt.Printf("Comparison: %d < %d is %v\n", a, b, a < b)
	fmt.Printf("Comparison: %d == %d is %v\n", a, b, a == b)

	// Logical: && (AND), || (OR), ! (NOT). Short-circuiting applies.
	fmt.Printf("\nLogical: true && false = %v\n", true && false)
	fmt.Printf("Logical: true || false = %v\n", true || false)
	fmt.Printf("Logical: !true = %v\n", !true)

	// Arithmetic: +, -, *, /, % (Modulo strictly for integers)
	fmt.Printf("Arithmetic: %d + %d = %d\n", a, b, a+b)
	fmt.Printf("Arithmetic: %d - %d = %d\n", a, b, a-b)
	fmt.Printf("Arithmetic: %d * %d = %d\n", a, b, a*b)
	fmt.Printf("Arithmetic: %d / %d = %d\n", a, b, a/b)
	fmt.Printf("Arithmetic: %d %% %d = %d\n", a, b, a%b)

	// Bitwise: & (AND), | (OR), ^ (XOR), << (Left Shift), >> (Right Shift), &^ (Bit Clear)
	// Assignment: =, +=, -=, *=, /=, %=, &=, |=, ^=

	// Unary: ++, --
	// CRITICAL: In Go, ++ and -- are STATEMENTS, not expressions.
	// in C , c++:  ++ is an expression, so it produces a value but in GO ++ is a statement, not an expression.
	// so in c - it says increase i and give me a value
	// but in go it says just increase i.Go doesn’t let i++ produce a value that can be assigned or used in larger expressions.
	// `val = i++` is illegal. There are no prefix variants (++i).
	counter := 5
	fmt.Printf("\nUnary: counter = %d\n", counter)
	counter++
	fmt.Printf("After counter++: %d\n\n", counter)

	/* ==========================================================================
	   5. ALL CONDITIONALS OF IF FAMILY
	   ==========================================================================
	*/
	// Parentheses around conditions are forbidden; braces are mandatory.
	if varBool {
		// Executes if condition is true
	} else if varInt > 10 {
		// Nested/Chained conditions
	} else {
		// Fallback
	}

	// Init statement in if
	// Idiomatic Go: Initialization Statement within If
	// `val` is scoped purely to this if-else chain. Ideal for error checking.
	if val := 10; val > 5 {
		fmt.Printf("Scoped value: %d\n\n", val)
	}

	// ==========================================
	// 6. SWITCH STATEMENT
	// ==========================================
	// --- Switch ---
	// Evaluates top-to-bottom. Stops at the first match.
	// CRITICAL: NO implicit fall-through (unlike C/Java). `break` is automatic.
	switchVar := 2
	switch switchVar {
	case 1:
		// Logic
	case 2, 3:
		// Comma separated acts as a logical OR.
		// If explicit fall-through is needed, use the `fallthrough` keyword.
	default:
		// Fallback
	}

	// Tagless Switch (Acts as a cleaner chained if-else)
	switch {
	case varInt > 100:
		// Logic
	case varBool == false:
		// Logic
	}

	// --- Ternary Operator ---
	// ARCHITECTURAL NOTE: Go DELIBERATELY omits the ternary operator (condition ? true : false).
	// The designers enforced explicit `if-else` blocks to maximize code readability and consistency.
	var ternaryStatus string
	ternaryAge := 20
	if ternaryAge >= 18 {
		ternaryStatus = "Adult"
	} else {
		ternaryStatus = "Minor"
	}

	/* ==========================================================================
	   7. ALL LOOPS
	   ==========================================================================
	   Go has ONLY ONE looping keyword: `for`.
	*/
	// 1. Standard Initializer; Condition; Post-statement
	for i := 0; i < 5; i++ {
		if i == 2 {
			continue // Skips current iteration
		}
		if i == 4 {
			break // Terminates loop immediately
		}
	}

	// 2. While-loop equivalent (Condition only)
	w := 0
	for w < 3 {
		w++
	}

	// 3. Infinite loop
	for {
		break // Exits immediately to prevent hang
	}

	// 4. For-Range (For-Each equivalent)
	// Iterates over slices, arrays, maps, strings, or channels.
	// Returns index/key and a COPY of the element.
	for index, value := range varArrInt {
		_ = index // Blank identifier `_` ignores unused variables (Go compiler requirement)
		_ = value
	}

	/* ==========================================================================
	   8 & 9. ALL INPUT OUTPUT & FORMATTING
	   ==========================================================================
	*/
	// Basic Output
	fmt.Println("Prints string appended with newline")
	fmt.Print("Prints string without newline")

	// Formatting (printf) verbs:
	// %v  (default value format)
	// %+v (structs with field names)
	// %#v (Go-syntax representation)
	// %T  (Type of the value)
	// %d  (Base 10 integer), %f (float), %s (string), %p (pointer address)
	fmt.Printf("\nFormatted Decimal (2 places): %.2f\n", varFloat64)
	fmt.Printf("Memory Address: %p | Type: %T\n", ptrInt, varInt)

	// Standard Input
	// Method 1: fmt.Scan (Reads space-separated tokens. Leaves '\n' in buffer)
	var inputAge int
	fmt.Print("Enter age: ")
	// fmt.Scan(&inputAge) // Requires pointer memory address to mutate variable

	// Method 2: bufio for full-line reading (Includes spaces)
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Enter full name: ")
	// nameInput, _ := reader.ReadString('\n')
	// _ -> dont care about the error
	// _, err := reader.ReadString('\n') // ignore string
	// (\n is included; use strings.TrimSpace(name) to remove it.)
	_ = reader
	// means "I'm intentionally not using reader yet." 
	// It prevents the Go compiler from reporting an "unused variable" error.


	// Input examples (commented, for manual testing)
	fmt.Println("\nInput example (commented - uncomment to test):")
	// reader := bufio.NewReader(os.Stdin)
	// fmt.Print("Enter your name: ")
	// name, _ := reader.ReadString('\n')
	// name = strings.TrimSpace(name)
	// fmt.Printf("Hello, %s!\n", name)

	// Demo without actual input
	demoName := "John"
	demoAge := 30
	fmt.Printf("Demo name: %s, age: %d\n\n", demoName, demoAge)

	// ==========================================
	// 9. PARSING & TYPE CONVERSION
	// ==========================================
	// --- Implicit/Explicit Casting ---
	// Go STRICTLY forbids implicit type coercion. You must explicitly cast.
	var rawInt int = 50
	var castFloat float64 = float64(rawInt)

	// --- Parsing Strings to Primitives ---
	strNum := "25"
	// strconv.Atoi (ASCII to Integer). Returns value and an error object.
	parsedAge, err := strconv.Atoi(strNum)
	if err == nil {
		_ = parsedAge
	}

	// String to int
	strNum = "25"
	parsedInt, err := strconv.Atoi(strNum)
	if err == nil {
		fmt.Printf("String '%s' to int: %d\n", strNum, parsedInt)
	}

	// String to float
	strFloat := "3.14"
	parsedFloat, _ := strconv.ParseFloat(strFloat, 64)
	fmt.Printf("String '%s' to float: %.2f\n", strFloat, parsedFloat)

	strFloat = "3.14"
	// 64 specifies IEEE 754 64-bit precision
	parsedFloat, _ = strconv.ParseFloat(strFloat, 64)

	// --- Converting Primitives to Strings ---
	score := 99
	// Method 1: Itoa (Integer to ASCII)
	strScore1 := strconv.Itoa(score)
	// Method 2: Sprintf (String Print Format - formats without outputting)
	strScore2 := fmt.Sprintf("%d", score)

	// ==========================================
	// 10 & 11. FUNCTIONS & PARAMETERS
	// ==========================================
	val1 := 10
	val2 := 10

	// ARCHITECTURAL CORE: In Go, EVERYTHING is pass-by-value.
	// When you pass a pointer, you are passing a COPY of the memory address.

	// Pass by value
	originalVal := 10
	fmt.Printf("\nBefore passByValue: %d\n", originalVal)
	demonstratePassByValue(originalVal) // Stack copy mutated. val1 remains 10.
	fmt.Printf("After passByValue: %d (unchanged)\n", originalVal)

	// Pass by pointer (Go's pass-by-reference)
	originalRef := 10
	fmt.Printf("\nBefore passByPointer: %d\n", originalRef)
	demonstratePassByPointer(&originalRef) // Address copied. Dereferencing mutates original. val2 becomes 99.
	fmt.Printf("After passByPointer: %d (changed!)\n", originalRef)

	// Slice pass (reference semantics)
	originalSlice := []int{1, 2, 3, 4, 5}
	fmt.Printf("\nBefore slicePass: %v\n", originalSlice)
	demonstrateSlicePass(originalSlice)
	fmt.Printf("After slicePass: %v\n", originalSlice)

	// Variadic function
	total := sumAll(1, 2, 3, 4, 5)
	fmt.Printf("\nsumAll(1,2,3,4,5) = %d\n", total)

	// Multiple return values
	result, err := divide(10, 2)
	if err == nil {
		fmt.Printf("divide(10, 2) = %d\n", result)
	}

	// _ = reader // Silence unused warning if not testing input
	_ = emptySlice
	_ = varChan
	_ = ternaryStatus
	_ = inputAge
	_ = rawInt
	_ = castFloat
	_ = strScore1
	_ = strScore2
	_ = val1
	_ = val2

	// Silencing strict compiler "unused variable" errors
	// _, _, _, _, _, _, _, _ = explicitVar, inferredVar, shortVar, varInt8, varInt16, varInt32, varInt64, varUint8
	// _, _, _, _, _, _, _, _ = varByte, varFloat32, varRune, varStr, varSlice, emptySlice, varMap, varChan
	// _, _, _, _, _, _ = nilPtr, ternaryStatus, inputAge, castFloat, parsedFloat, strScore1
	// _, _ = strScore2, err
}

// ==========================================
// FUNCTION IMPLEMENTATIONS
// ==========================================
// Syntax: func funcName(paramName paramType) returnType { ... }
// - Functions are defined at the package level.
// - Go supports Multiple Return Values, predominantly used for Error Handling.

// Example of multiple return values
func divide(a, b int) (int, error) {
	if b == 0 {
		return 0, fmt.Errorf("division by zero")
	}
	return a / b, nil
}

// Pass by Value
// `val` receives an isolated, independent copy of the primitive in this stack frame.
func demonstratePassByValue(val int) {
	val = 999
	fmt.Printf("Inside function (pass by value): %d\n", val)
}

// Pass by Pointer (Go's implementation of Pass by Reference)
// `ptr` receives a copied memory address. The `*` operator dereferences it,
// reaching across stack frames to mutate the original variable.
func demonstratePassByPointer(ptr *int) {
	*ptr = 999
	fmt.Printf("Inside function (pass by pointer): %d\n", *ptr)
}
func demonstrateSlicePass(slice []int) {
	if len(slice) > 0 {
		slice[0] = 999
		fmt.Printf("Inside function (slice modified): %v\n", slice)
	}
}

func addNumbers(a, b int) int {
	return a + b
}

func sumAll(numbers ...int) int {
	total := 0
	for _, num := range numbers {
		total += num
	}
	return total
}

// This line serves only to avoid unused import warning in this demo
var reader *bufio.Reader = bufio.NewReader(os.Stdin)
