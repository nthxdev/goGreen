# built-in Python module that provides access to the Python interpreter and system-level information.
import sys 
def main():
    print("Hello World")
    
    # ==========================================
    # 1. BASICS OF VARIABLES & CONSTANTS
    # ==========================================
    # Syntax: variable_name = value
    # Python is dynamically typed; types are inferred at runtime, not declared.
    # Variables act as labels/tags bound to objects in memory, not literal memory buckets.
    
    dynamic_var = 10        # Binds label 'dynamic_var' to integer object 10
    dynamic_var = "String"  # Rebinds label to a string object (perfectly valid)

    # Constants:
    # Python does not have a strict 'const' keyword enforcing immutability.
    # By convention, ALL_CAPS denotes a variable that should not be changed.
    PI = 3.14159
    MAX_CONNECTIONS = 100

    # ==========================================
    # 2. BUILT-IN PRIMITIVES (Strictly speaking, all are Objects in Python)
    # ==========================================
    # Python's "primitives" are immutable objects allocated on the private heap.
    
    # Numbers (Integers)
    # int: Arbitrary-precision integers. Python dynamically allocates more memory (bytes) as the number grows. No risk of overflow
    var_int = 2147483647
    var_large_int = 9223372036854775807123456789  

    # Floating-Point (Decimals)
    # float: Implemented using C doubles (IEEE 754 double precision). ~15 decimal digits. No 'f' or 'd' suffix needed.
    var_float = 3.141592653589793

    # Complex Numbers (Python specific built-in)
    var_complex = 3 + 4j # Real part 3.0, Imaginary part 4.0

    # Character / String (str)
    # Python has NO separate 'char' type. A character is just a string of length 1.
    # UTF-8 encoded Unicode objects. Single '' or double "" quotes are identical.
    var_char = 'A'

    # Boolean (bool)
    # Subclass of int. True behaves like 1, False behaves like 0.
    # Capitalized in Python.
    var_boolean = True 


    # ==========================================
    # 3. REFERENCE TYPES & MEMORY ARCHITECTURE
    # ==========================================
    # Python Memory Model: All objects live on the Heap. Variables live in frames on the Stack 
    # and hold C-style pointers (references) to the Heap objects.
    
    # Immutable Reference Types (Cannot be changed after creation):
    # Strings, Tuples, Ints, Floats. Reassigning creates a *new* object.
    text = "Hello World"
    print(f"Original: {text}")
    print(f"Upper: {text.upper()}")
    print(f"Lower: {text.lower()}")
    print(f"Length: {len(text)}")
    print(f"Split: {text.split()}")
    var_tuple = (10, 20, 30) # Immutable equivalent of a fixed array

    # Mutable Reference Types (Can be changed in-place):
    # Lists, Dictionaries, Sets.
    var_list = [10, 20, 30, 40] # Dynamic array (similar to ArrayList in Java, heavily optimized C-array of pointers under the hood)
    my_list = [10, 20, 30]
    my_list.append(40)
    my_list.extend([50, 60])
    print(f"List after append/extend: {my_list}")
    print(f"List length: {len(my_list)}")
    print(f"List[2]: {my_list[2]}")

    # Dictionaries
    my_dict = {"name": "Alice", "age": 30}
    my_dict["city"] = "NYC"
    print(f"Dictionary: {my_dict}")
    print(f"Keys: {list(my_dict.keys())}")
    print(f"Values: {list(my_dict.values())}")
    # Special Types: None (Equivalent to Java's null)
    # Represents the intentional absence of a value. It is a singleton object of type NoneType.
    var_null = None


    # ==========================================
    # 4. OPERATORS
    # ==========================================
    # Arithmetic:
    # +, -, *, / (Always returns float), % (Modulo)
    # // (Floor Division - truncates decimal), ** (Exponentiation)
    calc = (10 // 3) + (2 ** 3) # Evaluates to 3 + 8 = 11

    # Comparison (Relational):
    # == (Value equality), !=, >, <, >=, <=

    # Logical:
    # Uses English words, NOT symbols (&&, ||, !).
    # 'and', 'or', 'not'
    logic_res = (True and False) or not False

    # Assignment:
    # =, +=, -=, *=, /=, //=, %=, **=
    # NOTE: Python does NOT have ++ or -- (unary increment/decrement). Use += 1 or -= 1.

    # Identity vs Equality & Membership (Python Specific):
    # 'is' checks MEMORY ADDRESS (identity), '==' checks VALUE equality.
    # 'in' checks if an element exists in an iterable.
    list_a = [1, 2]
    list_b = [1, 2]
    print(list_a == list_b) # True (Same value)
    print(list_a is list_b) # False (Different objects in heap)
    print(1 in list_a)      # True


    # ==========================================
    # 5. CONDITIONALS (If Family)
    # ==========================================
    # Uses indentation (whitespace) instead of curly braces {} to define scope blocks.
    # 'else if' is contracted to 'elif'.
    
    condition, another_condition = False, True
    if condition:
        pass # 'pass' is a null operation placeholder
    elif another_condition:
        # Nested block
        if 10 > 5:
            pass
        else:
            pass
    else:
        pass


    # ==========================================
    # 6. Match/Switch
    # ==========================================
    # Structural Pattern Matching (Python 3.10+):
    # Replaces Java's switch. Much more powerful, allows matching object structures, types, and unpacking.
    # No 'break' statement is needed; cases do not fall through.
    status_code = 200
    match status_code:
        case 200 | 201: # OR operator in match
            response = "Success"
        case 400:
            response = "Bad Request"
        case _: # Underscore is the default/wildcard (equivalent to default:)
            response = "Unknown"

    # ============================================
    # 7. Ternary
    # =============================================
    # Ternary Operator:
    # Syntax: [value_if_true] if [condition] else [value_if_false]
    ternary_age = 20
    ternary_status = "Adult" if ternary_age >= 18 else "Minor"


    # ==========================================
    # 7. LOOPS
    # ==========================================
    # While Loop:
    count = 0
    while count < 3:
        count += 1

    # Python does NOT have a do-while loop natively.
    # Simulated do-while:
    while True:
        # Do something
        break # Exit condition checked at the end

    # For Loop (Always a For-Each loop in Python):
    # Python loops over iterables directly. 
    collection = ["A", "B", "C"]
    for element in collection:
        pass

    # For a traditional index-based loop, use range(start, stop_exclusive, step)
    for i in range(0, 5, 1): 
        pass

    # Loop Control: 'break', 'continue', and 'else'
    # Python loops can have an 'else' block which executes ONLY if the loop finishes naturally (no break).
    for num in range(3):
        if num == 5:
            break
    else:
        print("Loop completed without hitting a break statement.")


    # ==========================================
    # 8. INPUT & OUTPUT
    # ==========================================
    # Standard Output
    # print() automatically appends a newline by default.
    print("message")
    
    # To print without a newline, modify the 'end' parameter.
    print("No-Newline!", end="") 
    
    # To print multiple items with a custom separator:
    print("\nItem1", "Item2", sep=" | ")

    # Standard Input
    # input() reads an entire line of text as a String. Standard input buffer handles the \n.
    # (Uncomment below to test input)
    # user_input = input("Enter your name: ") 


    # ==========================================
    # 9. FORMATTING
    # ==========================================
    # 1. f-Strings (Formatted String Literals - Python 3.6+) - Most modern, readable approach.
    price = 19.9934
    population = 1500000
    
    # Evaluates expressions directly inside {}. 
    # :.2f (2 decimal places), :, (comma separator)
    print(f"Price: ${price:.2f}")               # Output: Price: $19.99
    print(f"Population: {population:,}")        # Output: Population: 1,500,000
    
    # Padding and alignment: < (left), > (right), ^ (center)
    print(f"{'Apple':<10} {5:>5}")              # Left-align text 10 chars, right-align num 5 chars

    # 2. .format() method (Older, but still heavily used)
    print("char= {}, int={}, float={:.2f}".format(var_char, var_int, var_float))

    # 3. % formatting (Legacy C-style, identical to Java's printf)
    print("char= %c, int=%d, float=%.2f" % (var_char, var_int, var_float))


    # ==========================================
    # 10. PARSING & TYPE CONVERSION (Casting)
    # ==========================================
    # Python relies on built-in constructor functions to cast/convert between types.
    
    # String to Number (Parsing)
    age_input = "25"
    parsed_age = int(age_input)       # Equivalent to Integer.parseInt()
    price_input = "99.99"
    parsed_float = float("3.14")      # Equivalent to Double.parseDouble()
    print(f"String '{price_input}' to float: {parsed_float}")

    # Number to String
    score_val = 99
    score_str = str(score_val) # Equivalent to String.valueOf()
    print(f"Int {score_val} to string: '{score_str}'")
    
    # Type checking with isinstance()
    print(f"\nType checking:")
    print(f"isinstance(25, int): {isinstance(25, int)}")
    print(f"isinstance('text', str): {isinstance('text', str)}")
    print(f"isinstance([1,2], list): {isinstance([1,2], list)}\n")

    # Type coercion is explicit in Python (except int to float operations).
    # You cannot concatenate str + int without casting the int to str first.
    # e.g., "Age: " + str(25)


# ==========================================
# 11 & 12. FUNCTIONS (Methods)
# ==========================================
# Basics & Where to define:
# Defined using the 'def' keyword. They must be defined BEFORE they are called in the script.
# Python functions are first-class objects (they can be assigned to variables, passed as arguments).

# Defining, Parameters, and Type Hinting (Python 3.5+):
# Syntax: def function_name(param: type) -> return_type:
def modify_data(num: int, arr: list) -> list:
    """
    Pass By Object Reference (Call-by-sharing):
    - Variables point to objects. The function receives a copy of the POINTER, not the object.
    - If the object is Immutable (e.g., int, str, tuple), modifying it rebinds the local 
      pointer to a new object. The original variable outside remains unchanged.
    - If the object is Mutable (e.g., list, dict), modifying it in-place affects the 
      underlying heap object. The original variable outside sees the change.
    """
    # 'num' is an int (immutable). This assignment points the local 'num' to a new int object.
    # Original integer remains completely unaffected.
    num = 999 
    
    # 'arr' is a list (mutable). .append() modifies the object dynamically on the heap.
    # The caller will see this mutation.
    arr.append(4) 
    
    return arr

    # Function with return value
    def add_numbers(a: int, b: int) -> int:
        """Simple function with type hints."""
        return a + b
    
    result = add_numbers(5, 10)
    print(f"add_numbers(5, 10) = {result}")
    
    # Pass by object reference demonstration
    def modify_primitive(num: int) -> None:
        num = 999
        print(f"  Inside function (primitive): {num}")
    
    def modify_list(lst: list) -> None:
        lst.append(999)
        print(f"  Inside function (list): {lst}")
    
    # Primitive (immutable)
    original_int = 10
    print(f"\nBefore modify_primitive: {original_int}")
    modify_primitive(original_int)
    print(f"After modify_primitive: {original_int} (unchanged)")
    
    # List (mutable)
    original_list = [1, 2, 3]
    print(f"\nBefore modify_list: {original_list}")
    modify_list(original_list)
    print(f"After modify_list: {original_list} (modified!)")
    
    # Default parameters
    def greet(name: str, greeting: str = "Hello") -> str:
        return f"{greeting}, {name}!"
    
    print(f"\ngreet('Alice'): {greet('Alice')}")
    print(f"greet('Bob', 'Hi'): {greet('Bob', 'Hi')}")
    
    # Variable length arguments
    def sum_all(*numbers: int) -> int:
        return sum(numbers)

    
# Execution Flow entry point mapping (Similar to public static void main)
# 'sys.argv' contains command line arguments.
if __name__ == "__main__":
    main()
    
    # Demonstrating Pass by Object Reference behavior:
    original_int = 10
    original_list = [1, 2, 3]
    
    modify_data(original_int, original_list)
    # original_int is still 10. original_list is now [1, 2, 3, 4]