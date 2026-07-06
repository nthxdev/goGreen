export {};
// Namespace import: Imports the entire module as an object
// import * as process from 'node:process';
// import * as readline from 'node:readline';

// Default import
declare const require: any;
const readline = require('node:readline');
const process = require('node:process');

// SYNTAX
// Comments
/*
Multi-line
comment 
*/

// Import modules
// const fs = require('fs');   // CommonJS
// import { someFunc } from './file.js'; // ES6 modules

// Global variable
let globalCount = 0;

// Function
function addBasic(a, b) {
    return a + b;
}

// Arrow function
const multiplyBasic = (a, b) => a * b;

// Class
class CalculatorBasic {
    multiply(a, b) {
        return a * b;
    }
}
/*
Entry point (Node.js)
if (require.main === module) {
    console.log(add(5, 3));
}
*/

// ==========================================
// 1. BASIC VARIABLES & CONSTANTS
// ==========================================
/*
- JS/TS Variable Declarations & Scope Mechanics:
- `let`: Block-scoped. Subject to Temporal Dead Zone (TDZ). Reassignable.
- `const`: Block-scoped. Immutable binding (the variable identifier cannot be reassigned), 
- but the contents of objects/arrays it points to ARE mutable.
- `var`: Function-scoped or globally scoped. Hoisted to the top of its execution context 
- with `undefined`. Avoid using `var` in modern TS/JS to prevent scope leakage.
*/
let myLet: string = "Block scoped";
const MY_CONST: number = 100; // Cannot do MY_CONST = 101;
var legacyVar: boolean = false; // Hoisted, avoid.

// Type inference
let inferred = 42;                  // Inferred as number


// ==========================================
// 2. BUILT-IN PRIMITIVES
// ==========================================
// Primitives are immutable, passed by value, and stored on the Stack (usually, depending on engine implementation like V8). JS/TS has 7 primitive types.
// Number (IEEE 754 64-bit float, no separate int/float)
// 1. Number: IEEE 754 double-precision 64-bit floating point. (No separate int/float).
let numInt: number = 42;
let numFloat: number = 3.14159;
let numHex: number = 0xff; // Hexadecimal
let numBinary: number = 0b1010; // Binary

// String (UTF-16)
// 2. String: UTF-16 code units.
let strSingle: string = 'A';
let strDouble: string = "Hello";
const str = "Hello, World!";
console.log(str.length);            // 13
console.log(str[0]);                // 'H'
console.log(str.substring(0, 5));   // 'Hello'
console.log(str.includes("World"));  // true
console.log(str.indexOf("World"));   // 7
console.log(str.replace("World", "JavaScript"));  // 'Hello, JavaScript!'
console.log(str.toUpperCase());     // 'HELLO, WORLD!'


// 3. Boolean: true or false (1 byte conceptually).
let isTrue: boolean = true;

// Undefined (uninitialized)
// 4. Undefined: Uninitialized variable. The default value of declared but unassigned variables.
let uninitVar: undefined = undefined;

// Null (intentional absence)
// 5. Null: Intentional absence of any object value.
let nullVar: null = null;

// BigInt (arbitrary precision)
// 6. BigInt: Arbitrary precision integers (for numbers larger than Number.MAX_SAFE_INTEGER: 2^53 - 1).
let bigIntVal: bigint = 9007199254740991n; // 'n' suffix

// Symbol (unique identifier)
// 7. Symbol: Unique, immutable identifier (often used for hidden object properties).
let sym: symbol = Symbol("uniqueKey");

// TS-Specific Types (Conceptual Primitives in TS):
let anyVar: any = "Can be anything"; // Bypasses type checking (Avoid).
let unknownVar: unknown = 42; // Type-safe counterpart to `any`. Requires type checking before use.
let neverVar: never; // Represents values that never occur (e.g., function that always throws).

console.log(`number: ${numInt}`);
console.log(`float: ${numFloat}`);
console.log(`hex: ${numHex}`);
console.log(`string: ${strDouble}`);
console.log(`boolean: ${isTrue}`);
console.log(`undefined: ${uninitVar}`);
console.log(`null: ${nullVar}`);
console.log(`bigint: ${bigIntVal}`);
console.log(`symbol: ${sym.toString()}\n`);

// Destructuring assignment
const [x, y] = [10, 20];
const { name, age } = { name: "Alice", age: 25 };

// Union types
let id: string | number;
id = "ABC123";                      // OK
id = 123;                           // OK

// Type alias
type Status = "active" | "inactive";
let status: Status = "active";

// ==========================================
// 3. REFERENCE TYPES
// ==========================================
/*
Reference Types (Objects) are dynamically allocated on the Heap.
The Stack holds the variable (the reference/pointer), which points to the memory address on the Heap.
*/


// Interface for type safety
interface User {
    name: string;
    age: number;
}

// 1. Objects (Key-Value pairs)
// TS Interface defines the shape of an objects
const userObj: User = { name: "Alice", age: 30 };
console.log(`Object: ${JSON.stringify(userObj)}`);
 // 'userObj' reference is constant, but `userObj.age` is mutable.
// object operation



// 2. Arrays
const arr = [1, 2, 3, 4, 5];
let arrNum: number[] = [10, 20, 30];
let arrStr: Array<string> = ["A", "B", "C"];
console.log(`Array<number>: ${arrNum}`);
console.log(`Array<string>: ${arrStr}`);
// Generic syntax
// Array Methods
let arr1 = [1, 2, 3, 4, 5];
console.log(`Original: ${arr1}`);

// Arrays
arr1.push(6);                        // Add to end -> [1,2,3,4,5,6]
arr1.pop();                          // Remove last -> 6
arr1.shift();                        // Remove first -> 1
arr1.unshift(0);                     // Add to beginning -> [0,2,3,4,5]

// Array iteration
arr1.forEach((num) => {
    console.log(num);
});

// Map (transform each element)
const squared = arr1.map(x => x ** 2);
// Filter
const evens = arr1.filter(x => x % 2 === 0);
// Find
const first_even = arr1.find(x => x % 2 === 0);
// Slice (get subset)
const subset = arr1.slice(1, 4);     // [2, 3, 4]
// Spread operator
const arr2 = [...arr1, 6, 7];        // Combine arrays

// Typed strings and arrays
const str2: string = "Hello";
const numbers1: number[] = [1, 2, 3];

// Array methods return typed values
const doubled: number[] = numbers1.map(x => x * 2);
const evens2: number[] = numbers1.filter(x => x % 2 === 0);

// Type-safe find
const found: number | undefined = numbers1.find(x => x > 2);



// 3. Tuples (TS specific): Fixed-length array with predefined types at each index.
let myTuple: [string, number, boolean] = ["Bob", 25, true];
console.log(`Tuple: ${JSON.stringify(myTuple)}`);

// 4. Enums (TS specific): Named constants. Compiles to JS objects (or IIFEs).
enum Direction {
    Up = 1, // Auto-increments from here
    Down,
    Left,
    Right,
}
let dir: Direction = Direction.Up;
console.log(`Enum: ${dir}\n`);

// ==========================================
// 4. OPERATORS
// ==========================================
/*
Arithmetic: +, -, *, /, % (modulo), ** (exponentiation)
Assignment: =, +=, -=, *=, /=, %=, **=
Unary: ++, --, +, -, ~, !

Comparison (Crucial JS/TS distinction):
- Loose Equality (==, !=): Performs implicit type coercion. (e.g., 5 == "5" is true). AVOID.
- Strict Equality (===, !==): Compares VALUE and TYPE. (e.g., 5 === "5" is false). ALWAYS USE.
*/
// Comparison (use === and !==, not == and !=)
const a: number = 10, b: number = 5;
console.log(`\nComparison: ${a} > ${b} is ${a > b}`);
console.log(`Comparison: ${a} == ${b} is ${a == b}`);
console.log(`Strict: ${a} === ${b} is ${a === b}`);

// - Relational: >, <, >=, <=

// Logical:
// - && (AND), || (OR), ! (NOT)
console.log(`\nLogical: true && false = ${true && false}`);
console.log(`Logical: true || false = ${true || false}`);
console.log(`Logical: !true = ${!true}`);


// ==========================================
// 5. CONDITIONALS (IF FAMILY)
// ==========================================
/*
JS/TS evaluates conditions based on "Truthy" and "Falsy" values.
Falsy values (exactly 6): false, 0 (and -0, 0n), "", null, undefined, NaN.
Everything else is Truthy (including empty arrays [] and empty objects {}).
*/
let condVal: any = "Non-empty string is truthy";

if (condVal) {
    // Executes because string is truthy
} else if (condVal === "Specific") {
    // Nested if logic
    if (true) { }
} else {
    // Fallback
}

// ==========================================
// 6. REST CONDITIONALS (SWITCH, TERNARY)
// ==========================================
/*
Switch uses STRICT equality (===) under the hood.
Omitted `break` causes "fall-through" to the next case (often a bug, sometimes intentional).
*/
let switchVar: string = "B";
switch (switchVar) {
    case "A":
        // Logic for A
        break;
    case "B":
    case "C": // Fall-through: executes for B or C
        // Logic for B and C
        break;
    default:
        // Default logic
}

/*
Ternary Operator: condition ? exprIfTrue : exprIfFalse
Expression, so it evaluates to a value.
*/
let ternaryAge: number = 20;
let status1: string = ternaryAge >= 18 ? "Adult" : "Minor";
console.log(`Ternary status: ${status1}\n`);


// - ?? (Nullish Coalescing): Returns right-hand side ONLY if left is `null` or `undefined`.
let nullValue: string | null = null;
let result = nullValue ?? "Default";
console.log(`Nullish coalescing: null ?? "Default" = ${result}`);

// - ?. (Optional Chaining): Safely accesses deeply nested properties.
let optChain1 = userObj?.name;
console.log(`Optional chaining: userObj?.name = ${optChain1}\n`);

let mathRes: number = (10 ** 2) % 3; // 100 % 3 = 1
let strictCheck: boolean = (10 === 10);
let nullishRes = nullVar ?? "Default Value"; // Evaluates to "Default Value"
let optChain = userObj?.name; // Evaluates to "Alice" without throwing if userObj is undefined.


// ==========================================
// 7. LOOPS
// ==========================================
let counter: number = 0;

// While loop
while (counter < 3) {
    counter++;
}

// Do-While loop (executes at least once)
do {
    counter--;
} while (counter > 0);

// Standard For loop
for (let i = 0; i < 3; i++) {
    if (i === 1) continue; // Skip to next iteration
    if (i === 2) break;    // Exit loop entirely
}

// For-Of (iterates over values) 
// (Iterates over iterables: Arrays, Strings, Maps, Sets. Yields VALUES)
for (const val of arrNum) {
    // val is 10, then 20, then 30
}

// For-In (iterates over keys/indexes) 
// (Iterates over enumerable properties of objects. Yields KEYS/INDEXES)
// Note: Usually avoided for Arrays because it yields string indices ("0", "1").
for (const key in userObj) {
    // key is "name", then "age"
}

// ==========================================
// 8. INPUT OUTPUT
// ==========================================
/*
Standard Output (Node.js Environment)
*/
console.log("Prints message with a newline");
console.error("Prints to stderr");
process.stdout.write("Prints WITHOUT a newline. ");

/*
Standard Input (Node.js Environment via 'readline')
(Requires importing the built-in 'node:readline' module)
*/
/*
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question('Enter age: ', (answer) => {
    console.log(answer);
    rl.close();
});
*/

// ==========================================
// 9. FORMATTING
// ==========================================
// 1. Template Literals (Backticks). Replaces printf. Supports multiline and interpolation.
let formattedStr: string = `User ${userObj.name} is ${userObj.age} years old.`;

// 2. Number Formatting (Decimal places) -> Returns a string!
let price: number = 19.9934;
let formattedPrice: string = price.toFixed(2); // "19.99"
console.log(`toFixed(2): ${price.toFixed(2)}`);

// 3. Internationalization API (Commas, Currency)
let population: number = 1500000;
let localePop: string = new Intl.NumberFormat('en-US').format(population); // "1,500,000"
console.log(`Locale formatting: ${localePop}`);

// 4. String Padding
let padded: string = "5".padStart(3, '0'); // "005"
console.log(`Padded: ${padded}\n`);

// ==========================================
// 10. PARSING & TYPE CONVERSION
// ==========================================
let strNum: string = "42.5px";

// String to Number (Explicit)
let parsedInt: number = parseInt(strNum, 10); // 42 (stops at non-numeric characters. '10' is the radix/base)
let parsedFloat: number = parseFloat(strNum); // 42.5
let castNumber: number = Number("42.5");      // 42.5 (Strict: Returns NaN if contains letters)
let unaryCast: number = +"42.5";              // 42.5 (Shorthand for Number())

// Number to String
let numToStr1: string = parsedInt.toString();
let numToStr2: string = String(parsedInt);
let numToStr3: string = `${parsedInt}`; // Template literal coercion

// Type assertions (compile-time only)
// TypeScript Type Assertions (Casting at compile time only, no runtime effect):
let unknownData: unknown = "Hello TS";
let lengthOfData: number = (unknownData as string).length;
let lengthAlt: number = (<string>unknownData).length; // Alternate syntax (clashes with React JSX)

// ==========================================
//11. FUNCTION DEFINITIONS (Definitions & Context)
// ==========================================

// 1. Function Declaration: Hoisted (can be called before defined in code).
function addExample(a: number, b: number): number {
    return a + b;
}
console.log(`add(5, 10) = ${addExample(5, 10)}`);


// 2. Function Expression: Assigned to a variable. Not hoisted.
const multiplyExample = function(a: number, b: number): number {
    return a * b;
};
console.log(`multiply(5, 10) = ${multiplyExample(5, 10)}`);


/*
3. Arrow Functions: ES6 shorthand. 
Crucial Engine Detail: Arrow functions do NOT have their own `this` binding. 
They lexically capture `this` from the surrounding outer scope.
*/
const subtract = (a: number, b: number): number => a - b; // Implicit return
console.log(`subtract(10, 3) = ${subtract(10, 3)}`);

// Optional parameters
function greet(name: string, greeting?: string): string {
    return `${greeting || "Hello"}, ${name}!`;
}

console.log(`greet('Alice'): ${greet("Alice")}`);
console.log(`greet('Bob', 'Hi'): ${greet("Bob", "Hi")}`);


// Default parameters
function power(base: number, exponent: number = 2): number {
    return Math.pow(base, exponent);
}
console.log(`power(5): ${power(5)}`);
console.log(`power(5, 3): ${power(5, 3)}`);


// Rest parameters
function sumAll(...numbers: number[]): number {
    return numbers.reduce((a, b) => a + b, 0);
}
console.log(`sumAll(1,2,3,4,5) = ${sumAll(1, 2, 3, 4, 5)}\n`);

/*
Parameters:
- Optional Parameters (`?`): Must come after required parameters.
- Default Parameters (`= value`)
- Rest Parameters (`...args`): Collects remaining arguments into an array.
*/
function buildProfile(name: string, age?: number, role: string = "User", ...skills: string[]): string {
    return `${name} (${role}) knows ${skills.join(', ')}`;
}
// buildProfile("Alice", undefined, "Admin", "JS", "TS", "Go");

/*
Pass By "Call-by-Sharing" (A subset of Pass by Value):
- Primitives: Passed by exact value copy. Changing it inside does not affect the outside.
- Objects/Arrays: The *reference itself* is passed by value (a copy of the memory address).
  -> Mutating the object's properties inside the function mutates the original object on the Heap.
  -> Reassigning the parameter to a NEW object inside the function does NOT affect the outside variable.
*/
function modifyData(primVal: number, refObj: User): void { // void return type
    // Primitive: Local copy changed. Outside `primVal` is untouched.
    primVal = 999; 
    
    // Reference: Mutating the shared heap object. Outside `userObj` IS affected.
    refObj.age = 99; 
    
    // Reference: Reassigning the pointer. Outside `userObj` is NOT affected by this line.
    refObj = { name: "Bob", age: 10 }; 
}

// Primitives: pass by value
let primitiveVal = 10;
function modifyPrimitive(val: number): void {
    val = 999;
    console.log(`  Inside function: ${val}`);
}

console.log(`Before: ${primitiveVal}`);
modifyPrimitive(primitiveVal);
console.log(`After: ${primitiveVal} (unchanged)\n`);

// Objects: pass by call-by-sharing
interface DataObj {
    value: number;
}

let objVal: DataObj = { value: 10 };
function modifyObject(obj: DataObj): void {
    obj.value = 999;
    console.log(`  Inside function: ${obj.value}`);
}

console.log(`Before: ${objVal.value}`);
modifyObject(objVal);
console.log(`After: ${objVal.value} (changed!)\n`);


let outsideNum = 1;
const outsideObj: User = { name: "Eve", age: 20 };

modifyData(outsideNum, outsideObj);
// outsideNum is still 1.
// outsideObj is now { name: "Eve", age: 99 }.

// Pass by value (primitives)
function modify_value(x) {
    x = 100;                        // Only changes local copy
}
let value = 5;
modify_value(value);
console.log(value);                 // Still 5

// Pass by reference (objects/arrays)
function modify_array(arr) {
    arr.push(4);                    // Modifies original
}
let numbers = [1, 2, 3];
modify_array(numbers);
console.log(numbers);               // [1, 2, 3, 4]

// Destructuring parameters
function display({ name, age }) {
    console.log(`${name} is ${age}`);
}
display({ name: "Alice", age: 25 });

// Spread operator for calling
const nums = [1, 2, 3];
console.log(Math.max(...nums));     


// Recursive function
function factorial(n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Closure
function counterClosure() {
    let count = 0;
    return function() {
        return ++count;
    };
}
const inc = counterClosure();
console.log(inc());                 // 1
console.log(inc());                 // 2

// Typed function
function addTyped2(a: number, b: number): number {
    return a + b;
}

// Typed arrow function
const multiplyTyped2 = (a: number, b: number): number => a * b;

// Optional and default parameters
function displayTyped(name: string, age?: number, city: string = "Unknown"): void {
    console.log(`${name}, ${age}, ${city}`);
}

// Overloading
function processInput(value: string): string;
function processInput(value: number): number;
function processInput(value: string | number): string | number {
    if (typeof value === 'string') {
        return value.toUpperCase();
    }
    return value * 2;
}

// ====== Typescript concepts =====

const intlValue: number = 42;
// Intl API (internationalization)
const formatted = new Intl.NumberFormat('en-US', {
    minimumFractionDigits: 2,
    maximumFractionDigits: 2
}).format(intlValue);
console.log(formatted);                    // "42.00"

// Type assertions (tell TypeScript what type it is)
let valueAny: any = "123";
let num: number = parseInt(valueAny);

// Type assertion syntax
const strAny: any = "hello";
let length: number = (strAny as string).length;

// or using angle brackets
let length2: number = (<string>strAny).length;

// Safely check types
function processValue(value: unknown): number {
    if (typeof value === 'number') {
        return value;
    }
    if (typeof value === 'string') {
        return parseInt(value);
    }
    throw new Error('Invalid type');
}


// Object & classes
// Object literal
const person = {
    name: "Alice",
    age: 25,
    greet: function() {
        return `Hello, I'm ${this.name}`;
    }
};

// Constructor function (old way)
function PersonOld(name, age) {
    this.name = name;
    this.age = age;
}

// Class (modern)
class Student {
    name: string;
    age: number;
    studentId: string;

    constructor(name: string, age: number, studentId: string) {
        this.name = name;
        this.age = age;
        this.studentId = studentId;
    }
    
    study() {
        return `${this.name} is studying`;
    }
    
    getInfo() {
        return `${this.name} (${this.age})`;
    }
}

const student = new Student("Bob", 20, "S123");
console.log(student.study());       // Bob is studying
console.log(student.getInfo());     // Bob (20)

// Inheritance
class GraduateStudent extends Student {
    major: string;

    constructor(name: string, age: number, studentId: string, major: string) {
        super(name, age, studentId);
        this.major = major;
    }
    
    research() {
        return `${this.name} researches ${this.major}`;
    }
}

// Interface
// Interface
interface PersonInterface {
    name: string;
    age: number;
    greet(): string;
}

// Implementing interface
class Person implements PersonInterface {
    name: string;
    age: number;
    
    constructor(name: string, age: number) {
        this.name = name;
        this.age = age;
    }
    
    greet(): string {
        return `Hello, I'm ${this.name}`;
    }
}

// Abstract class
abstract class Animal {
    abstract makeSound(): void;
    
    move(): void {
        console.log("Moving");
    }
}

class Dog extends Animal {
    makeSound(): void {
        console.log("Woof!");
    }
}

