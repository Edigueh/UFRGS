### **1. Naming Conventions:**

- **Variables and Functions:**
    - **Camel Case:** Common in some projects. Example: `calculateSum()`, `totalItems`.
    - **Snake Case (preferred in C projects):** More common in traditional C programs. Example: `calculate_sum()`, `total_items`.
- **Constants:**
    - Use **UPPERCASE_SNAKE_CASE** for constants. Example: `MAX_BUFFER_SIZE`.
- **Struct and Typedef Names:**
    - Use `PascalCase` for structs and typedefs: `typedef struct Student { ... } Student;`

---

### **2. Function Guidelines:**

- **Small and Focused Functions:** Keep functions short and do one thing well.
    - Example:
        
        ```c
        c
        CopierModifier
        int calculate_sum(int a, int b) {
            return a + b;
        }
        
        ```
        
- **Descriptive Function Names:** Avoid vague names like `doStuff()`. Use descriptive verbs like `initialize_array()`.
- **Function Declaration Style:**
    - Always include parameter types:
        
        ```c
        c
        CopierModifier
        int calculate_sum(int a, int b);
        
        ```
        

---

### **3. Indentation and Bracing:**

- **Consistent Indentation (4 spaces or 2 spaces, avoid tabs):**
    - Example with 4 spaces:
        
        ```c
        c
        CopierModifier
        int main() {
            printf("Hello, World!\n");
            return 0;
        }
        
        ```
        
- **Braces on New Line (K&R Style):** (used in Linux kernel and many C projects)
    - Example:
        
        ```c
        c
        CopierModifier
        if (x > 0) {
            printf("Positive\n");
        }
        
        ```
        
    - Alternatively, you can use **Allman style** (braces on a new line):
        
        ```c
        c
        CopierModifier
        if (x > 0)
        {
            printf("Positive\n");
        }
        
        ```
        

---

### **4. Comments:**

- Use **inline comments** sparingly and only when necessary.
    
    ```c
    c
    CopierModifier
    // Calculate the average of two numbers.
    float average = (x + y) / 2.0;
    
    ```
    
- Use **block comments** for more complex explanations:
    
    ```c
    c
    CopierModifier
    /*
     * This function initializes the buffer
     * and checks for memory allocation errors.
     */
    void init_buffer() {
        ...
    }
    
    ```
    

---

### **5. Constants and Macros:**

- Use `#define` for macros and constants.
    
    ```c
    c
    CopierModifier
    #define PI 3.14159
    #define MAX_BUFFER_SIZE 1024
    
    ```
    
- Prefer `const` variables over `#define` where applicable:
    
    ```c
    c
    CopierModifier
    const double PI = 3.14159;
    
    ```
    

---

### **6. Error Handling:**

- Always handle errors gracefully and check return values:
    
    ```c
    c
    CopierModifier
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    
    ```
    

---

### **7. Code Organization:**

- **Header Files:**
    - Declare function prototypes, macros, and struct definitions in `.h` files.
        
        ```c
        c
        CopierModifier
        // utils.h
        void print_message(const char *message);
        
        ```
        
    - Define actual functions in `.c` files:
        
        ```c
        c
        CopierModifier
        // utils.c
        #include "utils.h"
        
        void print_message(const char *message) {
            printf("%s\n", message);
        }
        
        ```
        
- **Include Guards:** Prevent multiple inclusions of the same header file.
    
    ```c
    c
    CopierModifier
    #ifndef UTILS_H
    #define UTILS_H
    
    // Declarations
    
    #endif // UTILS_H
    
    ```
    

---

### **8. Use of Pointers:**

- Always check for `NULL` when dealing with pointers:
    
    ```c
    c
    CopierModifier
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    ```
    
- Avoid pointer arithmetic when possible and document carefully if used.

---

### **9. Avoid Magic Numbers:**

- Use named constants instead of "magic numbers":
    
    ```c
    c
    CopierModifier
    #define MAX_RETRIES 5
    
    for (int i = 0; i < MAX_RETRIES; i++) {
        retry_connection();
    }
    
    ```
    

---

### **10. Follow Community Standards:**

- **Linux Kernel Style Guide:**
    
    Linux Kernel Coding Style
    
    - Common in low-level C programming.
- **Google C++ Style Guide (adaptable to C):**
    
    Google C++ Style Guide
    
    - Contains best practices for indentation, naming, and comments.
- **MISRA C (for Safety-Critical Applications):**
    
    Used in automotive and embedded systems.
    

---

### **11. Compiler Warnings and Static Analysis:**

- Always compile with strict warnings:
    
    ```bash
    bash
    CopierModifier
    gcc -Wall -Wextra -pedantic -o program main.c
    
    ```
    
- Use static analysis tools like:
    - **Clang-Tidy**
    - **Cppcheck**
    - **Valgrind** (for memory leak detection)