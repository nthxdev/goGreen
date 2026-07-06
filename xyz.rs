use std::io::{self, Write};


// Function declarations
fn demonstrate_move(s: String);
fn demonstrate_borrow(s: &String);
fn demonstrate_borrow_mut(s: &mut String);
fn add_numbers(a: i32, b: i32) -> i32;
fn sum_all(numbers: &[i32]) -> i32;

const PI: f64 = 3.14159265358979323846;
const MAX_BUFFER: u32 = 1024;

fn main() {
    println!("Hello World");

    // ==========================================
    // 1. BASIC VARIABLES & CONSTANTS
    // ==========================================
    /*
    Variables in Rust are IMMUTABLE by default for thread safety and memory safety.
    Declared using `let`. 
    */
    let x = 5; // Immutable variable
    // x = 6; // ERROR: cannot assign twice to immutable variable

    let mut y = 10; // MUTABLE variable (explicitly opted-in using `mut`)
    y = 15; 

    /*
    Shadowing:
    You can redeclare a variable with the same name. This destroys the previous 
    variable and creates a new one, allowing type changes without needing `mut`.
    */
    // Shadowing (rebind with potentially different type)
    let shadowed = "text";
    let shadowed = shadowed.len(); // Changed from &str to usize

    /*
    Constants and Stastics:
    `const`: Always immutable. Evaluated at compile time. Inlined where used. Must have explicit type.
    `static`: Similar to const, but has a fixed memory address (lives for the entire program).
    */
    const MAX_SPEED: u32 = 100_000;
    static GLOBAL_COUNTER: i32 = 0;


    // ==========================================
    // 2. PRIMITIVES (Scalar & Compound)
    // ==========================================
    /*
    Primitives in Rust have fixed, known sizes at compile time and are pushed onto the Stack.
    
    Integers:
    Signed (i)   : i8, i16, i32 (default), i64, i128, isize (arch-dependent pointer size)
    Unsigned (u) : u8, u16, u32, u64, u128, usize (used for indexing)
    */
    let var_u8: u8 = 255; 
    let var_i32: i32 = 2_147_483_647; // Underscores for readability
    
    /*
    Floating-Point:
    f32 (single precision), f64 (double precision - default)
    IEEE-754 standard.
    */
    let var_f32: f32 = 3.14f32; // Explicit suffix
    let var_f64 = 3.141592653589793; // Inferred as f64

    /*
    Boolean: 1 byte
    */
    let var_bool: bool = true;

    /*
    Character: 4 bytes
    Represents a Unicode Scalar Value (supports emojis, CJK, etc., not just ASCII). Use single quotes.
    */
    let var_char: char = '🦀';

    /*
    Compound Types: Tuples and Arrays (Stack allocated)
    */
    // Tuple: Fixed length, mixed types.
    let var_tuple: (i32, f64, char) = (500, 6.4, 'A');
    let tuple_val = var_tuple.1; // Access via dot notation

    // Array: Fixed length, single type.
    let var_arr: [i32; 4] = [10, 20, 30, 40];
    let arr_init = [0; 100]; // Array of 100 zeros

    println!("Primitives - u8: {}, i32: {}, f32: {}, f64: {}, bool: {}, char: {}", var_u8, var_i32, var_f32, var_f64, var_bool, var_char);
    println!("Tuple: {:?}, value at index 1: {}", var_tuple, tuple_val);
    println!("Array: {:?}, initialized array length: {}\n", var_arr, arr_init.len());


    /*
    Rust's memory model
    - Ownership: Every value has one owner; memory is freed automatically when the owner goes out of scope.
    - Stack: Fast storage for fixed-size values.
    - Heap: Dynamic storage for values whose size isn't known at compile time (e.g. String, Vec).
    - References (&, &mut): Borrow data without taking ownership.
    */
    // ==========================================
    // 3. REFERENCE TYPES & HEAP ALLOCATION
    // ==========================================

    // stack variable
    // String is Heap-allocated, dynamic, UTF-8 encoded.
    // The Stack holds the pointer, length, and capacity. The Heap holds the characters.
    let mut heap_string = String::from("Hello"); 
    println!("Stack int: {}", x);

    // `&str` (String Slice) is a reference to string data. It is an immutable view.
    // This points to a hardcoded string literal embedded in the binary (static memory).
    let stack_str: &str = "World"; 
    println!("String slice: {}", stack_str);

    // Borrowing  (immutable reference)
    let ref_to_string: &String = &heap_string; // Immutable borrow (&)
    println!("Borrowed reference: {}", ref_to_string);
    let ref_mut_string: &mut String = &mut heap_string; // Mutable borrow (&mut)
    ref_mut_string.push_str(" Rust");  
    println!("After mutable borrow: {}\n", heap_string);

    // Vectors (Dynamic arrays on the Heap)
    let mut var_vec: Vec<i32> = vec![1, 2, 3];
    var_vec.push(4);

    // Box (heap allocation)
    // Smart Pointers (Box allocates directly on the Heap)
    let boxed_int: Box<i32> = Box::new(5);
    println!("Boxed int: {}\n", boxed_int);

    // Null does NOT exist in Rust. It uses the `Option` enum to handle absence of value safely.
    // Option (safe null handling)
    let some_value: Option<i32> = Some(5);
    let no_value: Option<i32> = None;
    println!("Some value: {:?}", some_value);
    println!("No value: {:?}\n", no_value);

    // ==========================================
    // 4. OPERATORS
    // ==========================================
    /*
    Comparison: ==, !=, >, <, >=, <=
    Logical: &&, ||, !
    Arithmetic: +, -, *, /, %
    Assignment: =, +=, -=, *=, /=, %=
    Bitwise: &, |, ^, <<, >>
    
    NOTE: Rust does NOT have increment/decrement (++, --). Use += 1 or -= 1.
    */

    // ==========================================
    // 5. CONDITIONALS (If Family)
    // ==========================================
    /*
    `if` conditions MUST evaluate to a strict `bool` (no implicit truthy/falsy).
    `if` is an EXPRESSION in Rust, meaning it returns a value.
    */
    let condition = true;
    if condition {
        // execute
    } else if 10 > 5 {
        // execute
    } else {
        // execute
    }

    // `if let` (Pattern matching shortcut for one condition)
    let optional_name = Some("Alice");
    if let Some(name) = optional_name {
        println!("Optional name: {}", name);
    }



    // ==========================================
    // 6. MATCH & TERNARY
    // ==========================================

    /*
    Switch equivalent: `match`
    Powerful pattern matching. It MUST be exhaustive (cover all possible values).
    */
    let match_var = 2;
    let match_result = match match_var {
        1 => "One",
        2 | 3 => "Two or Three", // Multiple patterns
        4..=10 => "Four to Ten", // Inclusive range
        _ => "Anything else",    // Default/catch-all (required for exhaustiveness)
    };
    println!("Match result for {}: {}", match_var, match_result);

    /*
    Ternary: Rust has no `? :` operator. Since `if` is an expression, use it directly.
    The return types of all branches must match exactly.
    */
    let ternary_age = 20;
    let ternary_status = if ternary_age >= 18 { "Adult" } else { "Minor" };
    println!("Age {} is: {}\n", ternary_age, ternary_status);

    // ==========================================
    // 7. LOOPS
    // ==========================================
    /*
    loop: Infinite loop. Can return a value.
    */
    let mut counter = 0;
    let loop_result = loop {
        counter += 1;
        if counter == 10 {
            break counter * 2; // Returns 20 from the loop
        }
    };
    println!("Loop result: {}", loop_result);

    /*
    while: Standard condition loop.
    */
    counter = 10;
    while counter > 0 {
        counter -= 1;
    }

    /*
    for: Iterator loop. The standard way to iterate in Rust.
    */
    for i in 0..5 { // Exclusive range: 0, 1, 2, 3, 4
        // execute
    }
    for i in 0..=5 { // Inclusive range: 0 to 5
        // execute
    }
    
    // For-each on collections. iter() borrows, into_iter() moves/consumes.
    for element in var_arr.iter() {
        // execute
    }

    // Loop Labels (break/continue specific outer loops)
    'outer: for x in 0..5 {
        'inner: for y in 0..5 {
            if x * y > 10 {
                break 'outer; // Exits the outermost loop immediately
            }
        }
    }
    // Labeled loop break
    println!("Labeled loop:");
    'outer: for x in 0..5 {
        for y in 0..5 {
            if x * y > 6 {
                println!("Breaking outer at x={}, y={}", x, y);
                break 'outer;
            }
        }
    }
    println!();


    // ==========================================
    // 8. INPUT / OUTPUT
    // ==========================================
    /*
    Standard Output: Handled via macros (`println!`, `print!`)
    */
    println!("println! with newline");
    print!("print! ");
    println!("without leading newline");

    /*
    Standard Input: `std::io::stdin()`
    Reads input as a String. Returns a `Result` type which must be handled (e.g., using `.expect()`).
    */
    let mut input = String::new();
    // io::stdin().read_line(&mut input).expect("Failed to read line");


    // ==========================================
    // 9. FORMATTING
    // ==========================================
    /*
    Macros: `println!` (print to stdout), `format!` (returns a String).
    Requires the type to implement specific Traits:
    `Display` trait ({}): User-facing, pretty print.
    `Debug` trait ({:?}): Developer-facing, shows internal structure. Pretty debug: {:#?}
    */
    // Formatting with format specifiers
    let price = 19.9934;
    let population = 1500000;
    let f_price = 19.9934;
    println!("Population: {}", population);
    println!("Multiple: {} and {}", 42, "text");
    println!("Price: {:.2}", f_price); // 2 decimal places
    println!("Price variable: {:.2}", price);

    let f_num = 5;
    println!("{:<10} {:>5}", "Apple", f_num); // Left-align 10 chars, Right-align 5 chars
    
    println!("Positional: {1}, {0}, {1}", "Zero", "One"); // One, Zero, One
    println!("Named: {first} {second}", first="A", second="B");

    // Debug formatting
    let numbers = vec![1, 2, 3, 4, 5];
    println!("Debug format: {:?}", numbers);
    println!("Pretty debug:\n{:#?}\n", numbers);

    // Manual input example (commented)
    println!("(Input example commented - uncomment to test)");
    // let mut input = String::new();
    // io::stdin().read_line(&mut input).expect("Failed to read line");
    // println!("You entered: {}", input.trim());


    // ==========================================
    // 10. PARSING & TYPE CONVERSION
    // ==========================================
    /*
    Explicit casting (Narrowing/Widening primitives) using `as`.
    */
    let int_val = 10_i32;
    let float_val = int_val as f64;
    println!("Cast i32 to f64: {} -> {}", int_val, float_val);

    /*
    Parsing Strings to Types using `.parse::<T>()`.
    Requires the target type to implement the `FromStr` trait.
    Returns a `Result<T, Error>` because parsing can fail.
    */
    let str_num = "42";
    let parsed_int: u32 = str_num.parse().expect("Not a number!");
    println!("Parse '{}' to u32: {}", str_num, parsed_int);
    // OR using turbofish syntax: string_num.parse::<u32>().unwrap();

    /*
    Converting Types to Strings
    Types that implement `Display` automatically implement `.to_string()`.
    */
    let num_to_string: String = 99.to_string();
    println!("99 to string: \"{}\"", num_to_string);
    let num_to_string_fmt: String = format!("{}", 99);
    println!("Using format!: \"{}\"\n", num_to_string_fmt);


    // ==========================================
    // 11 & 12. FUNCTIONS, PARAMETERS, PASSING
    // ==========================================
    /*
    Functions define parameters with strict types. Return types follow `->`.
    Rust relies on "Expressions vs Statements".
    - Statement: Ends in `;`, performs an action, returns `()` (unit type).
    - Expression: Evaluates to a value. The last expression in a block (without `;`) is automatically returned.
    */

    let sum = add_numbers(5, 10);
    println!("add_numbers(5, 10) = {}", sum);

    // Ownership transfer (move)
    let original_string = String::from("Hello");
    println!("\nBefore demonstrateMove: {}", original_string);
    demonstrate_move(original_string);
    // println!("After demonstrateMove: {}", original_string); // ERROR: original_string was moved!

    // Borrowing (immutable reference)
    let borrowed_string = String::from("World");
    println!("\nBefore demonstrateBorrow: {}", borrowed_string);
    demonstrate_borrow(&borrowed_string);
    println!("After demonstrateBorrow: {} (still available)", borrowed_string);

    // Mutable borrowing
    let mut mutable_string = String::from("Rust");
    println!("\nBefore demonstrateBorrowMut: {}", mutable_string);
    demonstrate_borrow_mut(&mut mutable_string);
    println!("After demonstrateBorrowMut: {}", mutable_string);

    // Slice parameter
    let numbers = vec![10, 20, 30, 40, 50];
    let array_sum = sum_all(&numbers);
    println!("\nsum_all([10,20,30,40,50]) = {}\n", array_sum);


    // Pass by Value (Move or Copy semantics)
    // - Primitives implement the `Copy` trait (bit-for-bit duplication on stack).
    // - Complex types (String, Vec) implement `Move` (ownership is transferred, original variable invalidated).
    fn takes_ownership(s: String) -> String {
        s // Implicit return (no semicolon)
    }

    // Pass by Reference (Borrowing)
    // - `&T`: Immutable reference. Function can read but not alter original data.
    // - `&mut T`: Mutable reference. Function can alter original data in place.
    fn modify_in_place(num: &mut i32, _read_only_str: &str) {
        *num += 10; // Dereference pointer to modify actual value
        // read_only_str cannot be modified here.
    }

    let mut mutable_num = 5;
    modify_in_place(&mut mutable_num, stack_str);
    println!("After modify_in_place: {}", mutable_num);

    // Use all constants and variables
    println!("\nConstants - PI: {}, MAX_BUFFER: {}, MAX_SPEED: {}, GLOBAL_COUNTER: {}", PI, MAX_BUFFER, MAX_SPEED, GLOBAL_COUNTER);
    println!("Shadowed variable final value: {}", shadowed);
    println!("y value: {}", y);
    println!("Input buffer: \"{}\"", input);
    let _ = takes_ownership(String::from("test"));
}


// ==========================================
// FUNCTION IMPLEMENTATIONS
// ==========================================

fn add_numbers(a: i32, b: i32) -> i32 {
    a + b  // Implicit return (no semicolon)
}

// Demonstrates ownership/move semantics
// s is moved into this function, original binding becomes invalid
fn demonstrate_move(s: String) {
    println!("Inside demonstrateMove: {}", s);
    // s is dropped here, memory freed
}

// Demonstrates immutable borrowing
// s is borrowed (referenced), original remains valid
fn demonstrate_borrow(s: &String) {
    println!("Inside demonstrateBorrow: {}", s);
    // s is reference, nothing is dropped
}

// Demonstrates mutable borrowing
// s is mutably borrowed, can modify original
fn demonstrate_borrow_mut(s: &mut String) {
    s.push_str("!");
    println!("Inside demonstrateBorrowMut: {}", s);
}

// Function with slice parameter
// Borrows the data, doesn't take ownership
fn sum_all(numbers: &[i32]) -> i32 {
    let mut total = 0;
    for &num in numbers {
        total += num;
    }
    total
}
