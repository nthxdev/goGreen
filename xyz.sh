
# Commentts
: <<'write_anything_any_case'
this is a multiline commnet
the : is the null command in Bash — it does nothing and always succeeds.
The here-document is fed to :, but since : ignores all input and does nothing, 
the block effectively becomes a comment.
write_anything_any_case

echo "Hello World"

# ==========================================
# 1. BASICS OF VARIABLES & CONSTANTS
# ==========================================
# Syntax: variableName=value
# NO SPACES around the equals sign! If you add a space, Bash evaluates 'variableName' 
# as a command to execute, and '=' as its argument.

var_string="Hello"  # Assigned in the current shell environment

echo -e "\n--- String Operations ---"
text="Hello World"
echo "Original: $text"
echo "Length: ${#text}"
echo "Substring (0-4): ${text:0:5}"
echo "Replace 'World' with 'Bash': ${text/World/Bash}"


# Constants:
# Variables can be made read-only. The interpreter will throw an error if reassigned.
readonly PI="3.14159"
declare -r MAX_RETRIES=5

# ==========================================
# 2. BUILT-IN PRIMITIVES
# ==========================================
# Under the hood, Bash has no true primitive data types. EVERYTHING is a string.
# However, you can use `declare` to assign attributes to variables, giving them 
# primitive-like validation in specific contexts.

# Numbers (Integers):
# The `-i` attribute tells Bash to treat the variable as an integer.
# If you assign text to it, it evaluates to 0. 
declare -i var_int=2147483647
var_int="10 + 20" # Bash natively evaluates this arithmetic string to 30!

# Floating-Point (Decimals):
# BASH DOES NOT SUPPORT FLOATING POINT ARITHMETIC NATIVELY.
# It only understands integer arithmetic. For decimals, you must pipe strings to 
# external C-binaries like `bc` (Basic Calculator) or `awk`.
var_float="3.14" # Conceptually just a string
# calc_float=$(echo "$var_float + 2.5" | bc)

# Character:
# No char type. It's strictly a string of length 1.
var_char='A'

# Boolean:
# Bash has no literal boolean data type. 
# Concept 1: String checking ("true" vs "false").
var_bool_str="true"
# Concept 2: EXIT CODES (The Architectural Standard).
# 0 represents SUCCESS (True).
# 1-255 represents FAILURE (False).
# `true` and `false` are actual built-in commands that return exit codes 0 and 1.

# ==========================================
# 3. REFERENCE TYPES (Arrays & Pointers)
# ==========================================
# Arrays are the closest thing Bash has to objects. They are stored
# contiguously in the shell's memory space.

# Indexed Arrays (Like Java's int[] or String[]):
declare -a var_arr=(10 20 30 40)
# Accessing element: ${var_arr[0]}
# Accessing all elements: ${var_arr[@]}

# Associative Arrays (Hash Maps/Dictionaries - Bash 4.0+):
# Keys are strings instead of integer indexes.
declare -A user_map
user_map=( ["name"]="Alice" ["age"]="30" )


fruits=("Apple" "Banana" "Cherry")
echo "Array: ${fruits[@]}"
echo "Length: ${#fruits[@]}"
echo "fruits[0]: ${fruits[0]}"
echo -e "\nArray iteration:"
for fruit in "${fruits[@]}"; do
    echo "  $fruit"
done


# Special Types / Null:
# Bash doesn't have a strict 'null' object. An unset or empty variable evaluates 
# to a zero-length string.
empty_var=""
unset removed_var # Completely removes the variable from the process environment.

# ==========================================
# 4. OPERATORS
# ==========================================
# Bash has no data types at runtime—everything is treated as text.
# The meaning of a value depends on the context:
#   $(( )) → arithmetic context
#   [[ ]]  → conditional/string context

# Arithmetic Operators (Inside $(( ... )) or let):
# +, -, *, /, % (Modulo), ** (Exponentiation)
(( math_result = 5 + 5 )) 

# Integer Comparison Operators (Used inside [[ ]]):
# -eq (==), -ne (!=), -gt (>), -lt (<), -ge (>=), -le (<=)

# String Comparison Operators:
# == (Equal), != (Not Equal), < (Alphabetical sort before), > (Alphabetical sort after)
# -z (String is empty/null), -n (String is NOT empty)
# Important: In [ ... ], < and > are treated as shell redirection operators unless escaped: \< , \>
# that's is why we use [[ ... ]] to avoids this problem:

# Logical Operators:
# && (AND), || (OR), ! (NOT)

# ==========================================
# 5. CONDITIONALS (If Family)
# ==========================================
# The `if` statement strictly evaluates the EXIT CODE of a command. 
# The `[[ ]]` construct is a bash keyword that performs tests and returns 0 or 1.

condition=0 # 0 means true in process execution, but in integer comparison, we test explicitly.

if [[ $condition -eq 0 ]]; then
    # Executes if the condition evaluation returns exit code 0
    : # ':' is a null utility, similar to 'pass' in Python
elif [[ -n "$var_string" ]]; then
    # Nested conditionals
    if [[ "A" == "A" ]]; then
        :
    else
        :
    fi
else
    :
fi

# ==========================================
# 6. REST CONDITIONALS (Switch & Ternary)
# ==========================================
# Switch Statement -> Case Statement
# Evaluates strings using glob pattern matching (not regex, though similar).

switch_var="start"

# The | acts as logical OR
# Executed if switch_var matches 'start' or 'begin'
case "$switch_var" in
    "start" | "begin") 
        ;; # The double semicolon acts like Java's 'break' statement
    "stop")
        ;;
    *[0-9]*) # Matches any string containing a number
        ;;
    *) # The wildcard * acts as the 'default' case
        ;;
esac

# Ternary Operator:
# Bash has no literal `? :` syntax. Instead, we use short-circuit boolean evaluation.
# Syntax: [[ condition ]] && true_command || false_command
# WARNING: If true_command fails (returns non-zero), false_command will execute!
ternary_age=20
[[ $ternary_age -ge 18 ]] && ternary_status="Adult" || ternary_status="Minor"
# just know this:
# `cmd1 && cmd2` means execute `cmd2` only if `cmd1` succeeds (returns exit status 0).
# `cmd1 || cmd2` means **execute `cmd2` only if `cmd1` fails (returns a non-zero exit status).
# bash evalutes ternanry like this - (condition && on_true) || on_false


# ==========================================
# 7. LOOPS
# ==========================================
# While loop: runs as long as the evaluation returns 0 (true).
count=0
while [[ $count -lt 3 ]]; do
    ((count++))
done

# Until loop: runs as long as the evaluation returns non-zero (false).
until [[ $count -eq 0 ]]; do
    ((count--))
done

# For loop (For-Each style iterating over a word list):
for element in "Apple" "Banana" "Cherry"; do
    :
done

# C-Style For loop (Native arithmetic evaluation):
for (( i=0; i<5; i++ )); do
    :
done

# Loop Control:
# break (exits loop immediately), continue (skips to next iteration)

# ==========================================
# 8. INPUT / OUTPUT
# ==========================================
# Standard Output:
# `echo` prints arguments separated by spaces, adding a newline automatically.
echo "Standard Output"
# `echo -n` prevents the trailing newline. `echo -e` parses backslash escapes (\n, \t).
echo -n "No-Newline! "

# Standard Input:
# `read` pulls a line from stdin (the buffer) and assigns words to variables.
# -p specifies a prompt. -r prevents backslashes from being interpreted as escape it's an old Unix design choice
# historically \ use was deafult in read. Instead of pressing Enter and ending input after the first line.
# characters (Architectural best practice: Always use -r).
# read -r -p "Enter name: " user_name

# ==========================================
# 9. FORMATTING
# ==========================================
# $'...' - called ANSI-C quoting in Bash.
# eg- read -r -p $'some stirng \n' <------ \n will work here but not if used "..."
# string interpolation uses double quotes ("...").
# ordinary double quotes do not interpret \n.
# so either use echo -e , $'...' or printf "..."
# `printf` in Bash works almost identically to C and Java's System.out.printf.
# It does NOT automatically append a newline; you must provide \n.
: <<'printf specifiers'
%s  string
%d  integer
%f  float
%x  hexadecimal
%c  character
\n  newline
\t  tab
printf specifiers

var_double="19.9934" # Stored as string, but printf casts it to format as a float
printf "Formatted number: %.2f\n" "$var_double"
printf "char= %c, int=%d, float=%.2f\n" "$var_char" "$var_int" "$var_double"

# Padding and alignment (Positive=Right align, Negative=Left align):
printf "%-10s %5d\n" "Apple" 5  
printf "%-10s %5d\n" "Banana" 12

# Bash supports variable interpolation, but not true f-strings or template literals.
:<<'interpolation'
${name}          # variable value
${#name}         # length
${name^^}        # uppercase
${name,,}        # lowercase
${name:0:3}      # substring
${name:-default} # default value
interpolation

hello="HeLLo WoRLD"
# Lowercase all
echo "${hello,,}"
# Uppercase all
echo "${hello^^}"
# First character lowercase
echo "${hello,}"
# First character uppercase
echo "${hello^}"

# for e.g:-
# echo "${var1} + ${var2}: $((var1 + var2))"
# note we used $ here with ((arithmetic))
:<<'substituted'
The $ means expand this into its value
$name
$(command)
$((expression))
All three use $ because they produce a value that gets substituted into the surrounding text.
substituted

# ==========================================
# 10. PARSING & TYPE CONVERSION (Casting)
# ==========================================
# Because everything is fundamentally a string, "casting" is just treating the string 
# differently based on the context (arithmetic context vs string context).

age_input="25"
# "Parsing" string to int happens implicitly in an arithmetic context:
(( age_next_year = age_input + 1 )) 

# Converting Numbers to Strings:
# N/A in Bash. Numbers are already strings under the hood.
string_score="$age_next_year"

# String parsing via Parameter Expansion (Pattern Replacement):
# Syntax: ${var//pattern/replacement}
raw_price="\$19.99"
parsed_price="${raw_price//$/}" # Replaces '$' with nothing, parsing out "19.99"

# ==========================================
# 11 & 12. FUNCTIONS (Methods) & PARAMETERS
# ==========================================
# Functions MUST be defined BEFORE they are called.
# They execute in the current shell environment (unless explicitly sub-shelled ()).



# Defining:
function_name() {
    # Method body
    
    # PARAMETERS:
    # Think of Bash functions as mini scripts.
    # Bash functions do NOT declare named parameters in the signature.
    # They use positional parameters (architecturally identical to script arguments).
    # $1 is the 1st argument, $2 is the 2nd, $# is the count of args, $@ is all of them.
    
    # SCOPE: Variables are GLOBAL by default. Always use `local` to restrict scope 
    # to the current execution stack frame.
    local param1="$1"
    local param2="$2"
    
    # RETURN VALUES:
    # Functions CANNOT return data types. They can only return an EXIT CODE (0-255) using `return`.
    # To "return" data (strings/numbers), the function must `echo` the data to stdout, 
    # and the caller captures it using Command Substitution: $(func_name).
    echo "Result of $param1 and $param2"
    return 0 # 0 indicates success
    # if we did return 10 
    # 10 is not data. It's an exit code. to return actual data use echo
}

# PASS BY VALUE vs PASS BY REFERENCE:

# Pass by Value (Default Behavior):
# The function gets copy of value of var changing the copy doesn't affect the original
# You pass strings. Modifying them inside the function doesn't affect the caller's environment.
pass_by_value() {
    local val="$1"
    val="Changed"
}
my_var="Original"
pass_by_value "$my_var" # Passes the literal string "Original". my_var remains unchanged.


# Pass by Reference (Bash 4.3+ via Namerefs):
# The `declare -n` creates a pointer. Modifying the local nameref mutates the underlying 
# global object memory address it points to.
pass_by_reference() {
    # Expects the literal NAME of a variable, not its value.
    declare -n ref="$1" # 'ref' now acts as an alias to the memory location of the passed variable name
:<<'visual'
data_var -----> "Original state"
     ^
     |
    ref
ref is pointing to data_var. ref is another name for data_var
visual
    ref="Modified by reference"
}
data_var="Original State"
pass_by_reference data_var # IMPORTANT: Pass the variable NAME, do not use "$data_var"
# If we use $variable_name, the variable is substituted with its value.
# echo "$data_var" -> Outputs: "Modified by reference"

# Variadic function (variable arguments)
sum_all() {
    local total=0
    for num in "$@"; do
        ((total += num))
    done
    echo "$total"
}

echo -e "\nsum_all(1, 2, 3, 4, 5) = $(sum_all 1 2 3 4 5)"
echo
