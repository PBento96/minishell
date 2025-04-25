## Naming
- Naming scheme used is `snake_case` and can only contain `standard ASCII` lowercase characters and digits, unless inside literal strings and chars.
- Pointer asterisks must be stuck to variable names
- Macro names must all be uppercase.
- All identifiers (functions, types, variables, etc.) names should be explicit, or a
	mnemonic, should be readable in English, with each word separated by an underscore.
	This applies to macros, filenames and directories as well.

## Prefixes:
- `s_` *Structure*, `t_` *Typedef*, `u_` *Union*, `e_` *Enum*, `g_` *Global*

## Limits
- Each line must be at most ``80 columns wide`` (comments included).
- A function must not exceed `25 lines` (function braces excluded).
- A function can have up to `4 named parameters` and `5 variable declarations`.
- You cannot have more than ``5 function implementations`` in a file.

## Declarations
- Declarations must be at the beginning of a function.
- One single variable declaration per line.
- Declaration and initialisation cannot be on the same line, except for global
	variables (when allowed), static variables, and constants.

## Line Formatting
- An empty line must be empty: no spaces or tabulations.
- A line can never end with spaces or tabulations.
- You can never have two consecutive empty lines or spaces.
- Functions must be separated by an empty line.
- In a function, you must place an empty line between variable declarations and the remainder of the function. No other empty lines are allowed in a function.
- An instruction or control structure can be split into multiple lines when needed.
	The following lines created must be indented compared to the first line, natural
	spaces will be used to cut the line, and if applies, operators will be at the beginning
	of the new line and not at the end of the previous one.

## Tabulation and Spacing
- You must indent your code with tabulations (ASCII `'\t'`, not spaces)
- Blocks within braces must be indented.
- All variable names (including names for structs, typedefs, enums and unions)
	must be indented on the same column in their scope.
- You must indent struct constructor names on the same column for their scope.
- Each function must have a single tabulation between its return type and its name.
- You must indent preprocessor directives inside #if, #ifdef or #ifndef blocks.
- Unless it’s the end of a line, each comma or semi-colon must be followed by a space.
- Each operator or operand must be separated by exactly one space.
- Each C keyword (like structs, typedefs, enum and unions) must be followed by a space,
	except for keywords for types (such as int, char, float, etc.), as well as sizeof.

## Braces
- Control structures (if, while..) must use braces, unless they contain a
	single instruction on a single line.
- Braces are alone on their own line, except in declaration of struct, enum, union.
- Only one instruction or control structure per line is allowed. Eg.: Assignment in
	a control structure is forbidden, two or multiple assignments on the same line is
	forbidden, a newline is needed at the end of a control structure, ....

## Functions and Macros
- A function that doesn’t take arguments must be prototyped with a void argument.
- Parameters in function prototypes must be named.
- Return of a function has to be between parenthesis, unless the function returns nothing.
- Preprocessor constants (or #define) you create must be used only for literal and constant values.
- You can use macros available in standard libraries, only if those ones are allowed
	in the scope of the given project.
- All #define created to bypass or obfuscate the norm are forbidden.

## Header Files
- Allowed elements of a header file: `includes`, `declarations`, `defines`, `prototypes` and `macros`.
- All includes must be at the beginning of the file.
- You cannot include a .c file in a .h file or another .c file.
- Header files must be protected from double inclusions (ifndef FT_FOO_H)
- Inclusion of unused headers is forbidden.

## Restrictions
- `for`, `do` `while`, `switch`, `case`, `goto` and `ternary` operators are forbidden.
- Using `global variables` that are not marked const or static is forbidden.
- `Multiline macros` are forbidden.
- `Variable Length Arrays` (VLAs) and implicit types in variable declarations are forbidden.
- Preprocessor instructions are forbidden outside of global scope.
- You cannot declare a structure in a .c file.
- Comments cannot be inside function bodies.

## Makefile
- The `$(NAME)` , `clean` , `fclean` , `re` and `all` rules are mandatory. The all rule must be
	the default one and executed when typing just make.
- If the makefile relinks when not necessary, the project will be considered non functional.
- In the case of a multibinary project, in addition to the above rules, you must have
	a rule for each binary (eg: `$(NAME_1)`, `$(NAME_2)`, ...). The “all” rule will
	compile all the binaries, using each binary rule.
- In the case of a project that calls a function from a non-system library (e.g.:libft)
	that exists along your source code, your makefile must compile this library automatically.
- All source files needed to compile your project must be explicitly named in your
	Makefile. `No wildcards`.
