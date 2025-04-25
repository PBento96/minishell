# Code instructions

- Always strictly follow the project requirements and limitations as set in `docs/en.subject.pdf`.
- Adhere to the coding standards defined in the 42 norm at all times.
- The norm is detailed in `docs/en.norm.pdf` and summarized in `docs/norm_summary.md` and `docs/quick_reference.md`. When in doubt, defer to these documents.
- If a rule is covered by the norm or subject, do not contradict it; these take precedence over any other guideline.
- Use naming conventions, function signatures, and file organization consistent with the rest of the project.
- Always handle errors gracefully and check the return value of every system call and memory allocation.
- Ensure all allocated memory is freed appropriately; avoid memory leaks, double frees, and dangling pointers.
- Add clear, concise comments above each function and for complex logic, but never place comments inside function bodies.
- Place all `#include` directives at the beginning of the file. Header files must use include guards and must not include `.c` files.
- When suggesting test code, follow the project's conventions for test and log file locations.
- Always match the indentation, spacing, and brace style used in the rest of the project.
- If you suggest new functions or files, also suggest updates to relevant documentation (README, docstrings, etc.).
- Avoid unsafe functions and practices (e.g., unchecked buffer sizes, use of `gets`, etc.).
- Ensure code is portable and does not rely on platform-specific behavior unless required by the project.
- Do not use forbidden constructs as defined by the 42 norm (e.g., `for`, `do`, `while`, `switch`, `case`, `goto`, ternary operators, variable-length arrays).
- Functions should not exceed 25 lines (excluding braces), and each file should contain no more than 5 function implementations, as per the 42 norm.
- No function should have more than 4 named parameters or 5 variable declarations.
- All lines must be at most 80 columns wide, including comments.
