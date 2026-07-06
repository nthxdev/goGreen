# Nix language basics file
# Run examples:
# nix-instantiate --eval nix_basics.nix
# nix eval --file nix_basics.nix

# Nix Language Fundamentals
# ==========================================
# Overview:
# Nix is a purely functional, lazily-evaluated programming language designed primarily
# for declarative package management and system configuration. Unlike imperative languages,
# Nix is immutable-first, side-effect-free, and emphasizes reproducibility.
# All values are immutable. You cannot modify data; you create new data structures.
# ==========================================

# ==========================================
# 1. BASICS OF VARIABLES & CONSTANTS
# ==========================================
# Syntax: let <name> = <value>; in <expression>
# Variables are bound using 'let' expressions. There is no mutable state reassignment.
# Every "variable" is a binding of a name to an immutable value.

let
  # Nix variables are immutable bindings.
  # Syntax: name = value;
  # Bindings are usually defined inside let ... in ... blocks or attribute sets.

  name = "Alice";
  age = 25;
  pi = 3.14159;
  isActive = true;
  
  # Basic binding
  name = "Nix Language";           # Binds identifier 'name' to immutable string value
  version = 2.0;                   # Binds identifier 'version' to immutable number

  # Constants (semantically enforced by immutability):
  # Nix has no 'const' keyword; all bindings are immutable by default.
  # By convention, ALL_CAPS denotes values that should not be "changed" (though Nix enforces this).
  PI = 3.14159;
  MAX_CONNECTIONS = 100;

in
  # The rest of the program has access to these bindings within this scope
  name

# ==========================================
# 2. BUILT-IN PRIMITIVES (Basic Value Types)
# ==========================================
# Nix has a minimal set of primitive types. All values are first-class objects.

let
  # Null:
  # Represents the absence of a value. Singleton type.
  null_value = null;

  # Booleans:
  # true and false are the only boolean values. Capitalized.
  bool_true = true;
  bool_false = false;

  # Numbers (Integers):
  # Arbitrary-precision integers (similar to Python).
  # Nix handles large integers efficiently; no overflow risk.
  var_int = 2147483647;
  var_large_int = 9223372036854775807;

  # Floating-Point (Decimals):
  # Represented as IEEE 754 double precision, similar to C doubles.
  # Approximately 15 decimal digits of precision.
  var_float = 3.141592653589793;

  # Strings:
  # UTF-8 encoded text. Enclosed in double quotes.
  # Single quotes are NOT used for strings in Nix (they have special meaning for multi-line strings).
  var_string = "Hello, Nix!";

  # Multi-line Strings (Indented Strings):
  # Syntax: '' ... '' (two single quotes).
  # Useful for preserving formatting without escape sequences.
  multiline_text = ''
    This is a multi-line string in Nix.
    It preserves indentation and newlines.
    Leading whitespace is stripped intelligently.
  '';

  # Paths:
  # Nix can represent file system paths as first-class values.
  # Paths are either absolute (/home/user/file) or relative (./config.nix).
  # Paths are not evaluated as strings; they are distinct from strings.
  config_path = ./config.nix;
  abs_path = /etc/nixos/configuration.nix;

  # Lists:
  # Ordered collections of heterogeneous values.
  # Unlike tuples in other languages, lists can contain different types.
  # Syntax: [ value1 value2 ... ]
  var_list = [ 10 20 30 "string" true ];
  empty_list = [ ];
  string_list = [ "Apple" "Banana" "Cherry" ];

  # Sets (Attribute Sets / Dictionaries / Objects):
  # Unordered collections of key-value pairs.
  # Keys are always strings (though attribute names without special chars don't need quotes).
  # Syntax: { key = value; ... }
  person = {
    name = "Alice";
    age = 30;
    city = "New York";
  };

  # Sets with quoted keys (for keys with special characters):
  config = {
    "http-port" = 8080;
    "debug-mode" = true;
  };

  # Nested structures:
  nested = {
    user = {
      name = "Bob";
      settings = {
        theme = "dark";
        notifications = true;
      };
    };
  };

in
  null_value

# ==========================================
# 3. REFERENCE TYPES & IMMUTABILITY MODEL
# ==========================================
# All data in Nix is immutable. There is no concept of mutable references or pointers
# in the traditional sense. Instead, Nix uses structural sharing and lazy evaluation.

let
  # Lists are immutable. To "modify" a list, you create a new list.
  original_list = [ 1 2 3 ];

  # Using the ++ operator to concatenate lists (creates a new list):
  extended_list = original_list ++ [ 4 5 ];  # Result: [1 2 3 4 5]

  # Sets are immutable. To "modify" a set, you create a new set via merging/overriding.
  original_set = { x = 10; y = 20; };

  # The '//' operator performs recursive merge (right side overrides left):
  merged_set = original_set // { y = 25; z = 30; };
  # Result: { x = 10; y = 25; z = 30; }

  # Functions create closures (captured environments).
  # They reference values from their defining scope.
  create_adder = x: y: x + y;
  # When 'create_adder' is called, it captures the scope in which it was defined.

  # Lazy Evaluation:
  # Nix delays computation until a value is actually needed.
  # This allows for infinite data structures and efficient resource usage.
  infinite_sequence = x: [ x ] ++ (infinite_sequence (x + 1));
  # This would create an infinite list, but it's never fully evaluated until accessed.

in
  merged_set

# ==========================================
# 4. OPERATORS
# ==========================================
# Nix supports standard operators, but with functional paradigms in mind.

let
  # Arithmetic Operators:
  # +, -, *, /, %
  addition = 10 + 5;         # 15
  subtraction = 10 - 3;      # 7
  multiplication = 4 * 5;    # 20
  division = 20 / 4;         # 5 (integer division)
  modulo = 17 % 5;           # 2

  # Note: Division of integers returns a float in Nix
  int_div = 10 / 3;          # 3.333... (float result)

  # String Concatenation:
  # The + operator also concatenates strings.
  str_concat = "Hello" + " " + "Nix";  # "Hello Nix"

  # Comparison Operators:
  # ==, !=, <, >, <=, >=
  # Returns boolean values.
  eq = 5 == 5;               # true
  ne = 5 != 3;               # true
  lt = 3 < 5;                # true
  gt = 10 > 7;               # true
  le = 5 <= 5;               # true
  ge = 10 >= 8;              # true

  # Logical Operators:
  # &&, ||, !
  and_result = true && false;        # false
  or_result = true || false;         # true
  not_result = !true;                # false

  # Set/Attribute Operators:
  # '.' (dot operator): Access set attributes.
  person = { name = "Alice"; age = 30; };
  person_name = person.name;         # "Alice"

  # 'or' operator: Provide default value if attribute doesn't exist.
  # Syntax: set.attr or default_value
  greeting = person.greeting or "Hello";  # "Hello" (greeting doesn't exist)

  # List/Set Membership:
  # The 'in' operator checks membership (for sets and attribute names).
  has_name = "name" in person;       # true
  has_age = "age" in person;         # true
  has_email = "email" in person;     # false

  # Update/Merge Operator:
  # '//' merges two sets (right side overrides left).
  defaults = { color = "blue"; size = "large"; };
  overrides = { color = "red"; };
  final = defaults // overrides;     # { color = "red"; size = "large"; }

in
  and_result

# ==========================================
# 5. CONDITIONALS (If/Then/Else)
# ==========================================
# Nix uses 'if-then-else' expressions (not statements).
# All branches return a value. Nix requires explicit 'else' in most contexts.

let
  age = 25;
  status = if age >= 18 then "Adult" else "Minor";
  # 'if' evaluates a boolean condition and returns different values for true/false.

  # Nested conditionals:
  nested_cond =
    if age < 13 then
      "Child"
    else if age < 18 then
      "Teenager"
    else
      "Adult";

  # Set attributes based on conditionals:
  config = {
    debug_mode = true;
    log_level = if config.debug_mode then "verbose" else "error";
  };

  # Conditionals in list comprehensions:
  numbers = [ 1 2 3 4 5 ];
  # Filter even numbers (using conditionals implicitly via map):
  even_numbers = builtins.filter (x: x % 2 == 0) numbers;

in
  status

# ==========================================
# 6. PATTERN MATCHING / DESTRUCTURING
# ==========================================
# Nix doesn't have traditional switch statements.
# Instead, it uses 'assert' for assertions and pattern matching in function arguments.

let
  # Assert statements: evaluate a condition and fail the build if false.
  x = 10;
  assertion = assert x > 0; "x is positive";
  # If x <= 0, the build fails with an error. Otherwise, "x is positive" is returned.

  # Pattern matching in function parameters:
  greet = { name, age }: "Hello ${name}, age ${toString age}";
  # Function expects a set with 'name' and 'age' attributes.

  person = { name = "Alice"; age = 30; };
  greeting = greet person;  # "Hello Alice, age 30"

  # Destructuring lists:
  first_element = { x }: x;
  list_match = first_element (builtins.head [ 1 2 3 ]);  # 1

  # Multiple assertions:
  validate = x:
    assert x != null;
    assert x > 0;
    "valid";
  # Both conditions must be true for the function to succeed.

in
  greeting

# ==========================================
# 7. TERNARY OPERATOR (Conditional Expression)
# ==========================================
# Nix's 'if-then-else' IS the ternary operator.
# Syntax: if condition then value_true else value_false

let
  age = 20;
  # Direct ternary-like usage:
  status = if age >= 18 then "can vote" else "cannot vote";

  # Nested ternary:
  classification =
    if age < 13 then
      "child"
    else if age < 20 then
      "teenager"
    else
      "adult";

in
  status

# ==========================================
# 8. LOOPS (Recursion & Higher-Order Functions)
# ==========================================
# Nix has no traditional 'while' or 'for' loops.
# Instead, it uses recursion and higher-order functions like map, filter, fold.
# This is inherent to functional programming paradigm.

let
  # Recursion: Manually implement looping logic.
  # Example: Sum numbers from 1 to n.
  sum_to = n:
    if n <= 0 then
      0
    else
      n + (sum_to (n - 1));
  # Result: sum_to 5 = 5 + 4 + 3 + 2 + 1 = 15

  # map: Apply a function to each element in a list.
  numbers = [ 1 2 3 4 5 ];
  doubled = builtins.map (x: x * 2) numbers;
  # Result: [ 2 4 6 8 10 ]

  # filter: Keep elements that satisfy a predicate.
  evens = builtins.filter (x: x % 2 == 0) numbers;
  # Result: [ 2 4 ]

  # fold: Accumulate a value by iterating over a list.
  # Syntax: builtins.foldl' (accumulator: value: new_accumulator) initial_value list
  sum = builtins.foldl' (acc: x: acc + x) 0 numbers;
  # Result: 15

  # foldr: Right fold (processes list from right to left).
  concat = builtins.foldr (x: acc: acc + x) "" (builtins.map toString numbers);
  # Result: "54321"

  # Tail recursion (preferred for efficiency):
  sum_tail = n: sum_helper n 0
    where sum_helper = n: acc:
      if n <= 0 then
        acc
      else
        sum_helper (n - 1) (acc + n);

  # forEach (alternative to map for side effects, though Nix discourages side effects):
  # builtins.forEach list function

in
  doubled

# ==========================================
# 9. INPUT / OUTPUT
# ==========================================
# Nix is a build/configuration language, not a general-purpose scripting language.
# It has limited I/O capabilities. No stdin interaction (not designed for it).
# Output is primarily through 'builtins.trace' for debugging during evaluation.

let
  # trace: Outputs a message to stderr during evaluation (for debugging only).
  debug_msg = builtins.trace "Debug: Starting configuration" 42;
  # Output: "Debug: Starting configuration" printed to stderr.
  # The expression evaluates to 42.

  # builtins.error: Fail the build with an error message.
  validate = x:
    if x < 0 then
      builtins.error "Value must be non-negative"
    else
      x;

  # Nix cannot read from stdin like traditional scripts.
  # All inputs come from:
  # - Command-line arguments
  # - Environment variables (via builtins.getEnv)
  # - External files (via import or builtins.readFile)

  # Reading environment variables:
  home = builtins.getEnv "HOME";  # Retrieves the HOME environment variable

  # Reading files:
  file_content = builtins.readFile ./example.txt;
  # Reads the content of example.txt as a string.

  # Import Nix files:
  # Syntax: import <file-path> [optional-arguments]
  # config = import ./config.nix;

in
  debug_msg

# ==========================================
# 10. FORMATTING / STRING INTERPOLATION
# ==========================================
# Nix provides powerful string interpolation via ${ ... } syntax.

let
  name = "Alice";
  age = 30;
  active = true;

  # String interpolation with ${ }:
  message = "Hello ${name}, age ${age}";
  # Result: "Hello Alice, age 30"

  # toString: Convert non-string values to strings.
  age_str = toString age;
  # builtins.toString can also be used.

  # Conditional formatting:
  status = "User is " + (if active then "active" else "inactive");

  # Multi-line string with interpolation:
  formatted = ''
    Name: ${name}
    Age: ${toString age}
    Status: ${status}
  '';

  # Escaping ${ } in strings (if you want literal ${...}):
  escaped = "Literal dollar: $${variable}";  # Output: "Literal dollar: ${variable}"

  # Using + for string concatenation (alternative to interpolation):
  concat = "Hello " + name + ", age " + toString age;

  # Format numbers (builtins.toJSON for structured output):
  json_output = builtins.toJSON { name = name; age = age; };
  # Result: '{"name":"Alice","age":30}'

  # String functions from builtins:
  lowercase = builtins.toLower "HELLO";       # "hello"
  uppercase = builtins.toUpper "hello";       # "HELLO"
  substring = builtins.substring 0 5 "Hello World";  # "Hello"
  
  # Split strings:
  split_result = builtins.split "," "apple,banana,cherry";
  # Result: [ "apple" "banana" "cherry" ]

in
  message

# ==========================================
# 11 & 12. FUNCTIONS (Definitions & Parameters)
# ==========================================
# Functions are first-class values in Nix.
# They are defined using the syntax: param: body or (param1: param2: body)
# All functions are curried (can be partially applied).

let
  # Simple function (single parameter):
  double = x: x * 2;
  result1 = double 5;  # 10

  # Multi-parameter function (curried):
  add = x: y: x + y;
  result2 = add 5 10;  # 15

  # Partial application (currying in action):
  add_five = add 5;    # Returns a function waiting for the second argument
  result3 = add_five 10;  # 15

  # Function with set parameter (destructuring):
  greet = { name, age, city ? "Unknown" }:
    "Hello ${name}, age ${toString age} from ${city}";
  # { name, age, city ? "Unknown" } destructures a set parameter.
  # city has a default value of "Unknown".

  person = { name = "Bob"; age = 25; city = "NYC"; };
  greeting = greet person;  # "Hello Bob, age 25 from NYC"

  greeting2 = greet { name = "Charlie"; age = 28; };
  # "Hello Charlie, age 28 from Unknown" (city uses default)

  # Variadic functions (variable arguments):
  # Nix doesn't have traditional varargs. Instead, use lists or sets.
  sum_list = xs: builtins.foldl' (acc: x: acc + x) 0 xs;
  total = sum_list [ 1 2 3 4 5 ];  # 15

  # Function with type assertions (using assert):
  divide = x: y:
    assert y != 0;
    x / y;

  # Recursive functions:
  factorial = n:
    if n <= 1 then
      1
    else
      n * (factorial (n - 1));
  fact_5 = factorial 5;  # 120

  # Functions with multiple sets of parameters:
  configure = { name, version }:
    { config_dir, output_dir }:
    {
      inherit name version config_dir output_dir;
      full_config = "${name}-${version} in ${config_dir}";
    };
  # Calling: configure { name = "app"; version = "1.0"; } { config_dir = "/etc"; output_dir = "/out"; }

  # Lambda (anonymous) functions:
  square = (x: x * x);
  apply_twice = f: x: f (f x);
  result4 = apply_twice (x: x + 1) 10;  # (10 + 1) + 1 = 12

  # Higher-order functions:
  map_add = f: xs: builtins.map f xs;
  incremented = map_add (x: x + 1) [ 1 2 3 ];  # [ 2 3 4 ]

  # Scope & Closures:
  # Functions capture variables from their defining scope (closure).
  multiplier = 5;
  make_multiplier = scale: x: x * scale;
  times_five = make_multiplier multiplier;
  result5 = times_five 10;  # 50

  # Function composition:
  compose = f: g: x: f (g x);
  add_one = x: x + 1;
  double_val = x: x * 2;
  add_then_double = compose double_val add_one;
  result6 = add_then_double 5;  # (5 + 1) * 2 = 12

in
  result1

# ==========================================
# ADDITIONAL NIX-SPECIFIC CONCEPTS
# ==========================================

let
  # 'with' expression: Brings set attributes into scope.
  person = { name = "Alice"; age = 30; city = "NYC"; };
  
  message = with person; "Hello ${name}, age ${toString age}";
  # Equivalent to: "Hello " + person.name + ", age " + toString person.age
  # 'with' temporarily adds all attributes of 'person' to the local scope.

  # 'inherit' keyword: Shorthand for { name = name; age = age; }
  name = "Bob";
  age = 25;
  person2 = { inherit name age; city = "LA"; };
  # Result: { name = "Bob"; age = 25; city = "LA"; }

  # Recursive set (rec): Allows attributes to reference other attributes in the same set.
  recursive_set = rec {
    x = 10;
    y = 20;
    sum = x + y;  # Can reference x and y within the same set
  };

  # Library functions from builtins:
  # builtins.map, builtins.filter, builtins.foldl', etc.
  # These are essential for functional programming in Nix.

  # Type checking functions:
  is_string = builtins.isString "hello";      # true
  is_int = builtins.isInt 42;                 # true
  is_list = builtins.isList [ 1 2 3 ];        # true
  is_bool = builtins.isBool true;             # true
  is_function = builtins.isFunction (x: x);   # true

  # List operations:
  list_length = builtins.length [ 1 2 3 ];    # 3
  list_head = builtins.head [ 1 2 3 ];        # 1
  list_tail = builtins.tail [ 1 2 3 ];        # [ 2 3 ]
  list_reverse = builtins.reverse [ 1 2 3 ];  # [ 3 2 1 ]

  # Set operations:
  set_keys = builtins.attrNames { a = 1; b = 2; };  # [ "a" "b" ]
  set_values = builtins.attrValues { a = 1; b = 2; };  # [ 1 2 ]

in
  message
