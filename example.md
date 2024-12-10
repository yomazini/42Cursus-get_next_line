Here are **8 unique examples** — 4 for the **mandatory part** and 4 for the **bonus part**. These examples cover different cases, edge cases, and scenarios that will help you visualize the algorithm using tools like **tldraw** for easier traceability.

---

### **Mandatory Part Examples (4)**

#### **Example 1: Basic File with Newlines**
- **File content**:  
  ```
  Line 1
  Line 2
  Line 3
  ```
- **Behavior**:
  - `get_next_line(fd)` reads the file line by line.
  - The function returns `"Line 1\n"` for the first call, `"Line 2\n"` for the second call, and `"Line 3\n"` for the third.
  - Returns `NULL` on the fourth call (EOF reached).

#### **Example 2: File with No Newlines**
- **File content**:  
  ```
  This is a single line without newline at the end.
  ```
- **Behavior**:
  - `get_next_line(fd)` reads the entire file and returns the whole content on the first call, `"This is a single line without newline at the end."`.
  - Returns `NULL` on the second call (EOF reached).
  
#### **Example 3: File with Only Newlines**
- **File content**:  
  ```
  \n\n\n
  ```
- **Behavior**:
  - `get_next_line(fd)` reads a newline (`\n`) on the first call, `" \n"`, then the second call returns `" \n"`, and so on for each newline.
  - Returns `NULL` after reading all newlines.

#### **Example 4: Reading from Standard Input (`stdin`)**
- **Input**:
  ```
  Hello
  World
  ```
- **Behavior**:
  - The user types `"Hello"`, followed by pressing enter (newline).
  - `get_next_line(0)` returns `"Hello\n"`.
  - The user types `"World"`, followed by pressing enter.
  - `get_next_line(0)` returns `"World\n"`, then `NULL` after EOF.

---

### **Bonus Part Examples (4)**

#### **Example 1: Multiple File Descriptors (Different Files)**
- **File 1 content**:  
  ```
  File 1, Line 1
  File 1, Line 2
  ```
- **File 2 content**:  
  ```
  File 2, Line 1
  File 2, Line 2
  ```
- **Behavior**:
  - Call `get_next_line(3)` → returns `"File 1, Line 1\n"`.
  - Call `get_next_line(4)` → returns `"File 2, Line 1\n"`.
  - Call `get_next_line(3)` → returns `"File 1, Line 2\n"`.
  - Call `get_next_line(4)` → returns `"File 2, Line 2\n"`.
  - Each FD is independent and doesn't mix data.

#### **Example 2: Multiple File Descriptors with Same File**
- **File content**:  
  ```
  Line 1
  Line 2
  Line 3
  ```
- **Behavior**:
  - `get_next_line(3)` returns `"Line 1\n"`.
  - `get_next_line(4)` returns `"Line 1\n"`.
  - `get_next_line(3)` returns `"Line 2\n"`.
  - `get_next_line(4)` returns `"Line 2\n"`.
  - `get_next_line(3)` returns `"Line 3\n"`, and both FD3 and FD4 will return `NULL` on subsequent calls.

#### **Example 3: FD Switching Between Different Files**
- **File 1 content**:  
  ```
  File 1, Line 1
  ```
- **File 2 content**:  
  ```
  File 2, Line 1
  ```
- **Behavior**:
  - Call `get_next_line(3)` → returns `"File 1, Line 1\n"`.
  - Call `get_next_line(4)` → returns `"File 2, Line 1\n"`.
  - Call `get_next_line(3)` → returns `NULL` (EOF for File 1).
  - Call `get_next_line(4)` → returns `NULL` (EOF for File 2).

#### **Example 4: Large File with Small `BUFFER_SIZE`**
- **File content**:  
  ```
  1234567890
  1234567890
  1234567890
  ```
- **Behavior**:
  - Set `BUFFER_SIZE = 2`.
  - `get_next_line(fd)` reads in chunks of `2` bytes at a time.
  - Call `get_next_line(fd)` → returns `"12\n"`.
  - Call `get_next_line(fd)` → returns `"34\n"`.
  - The function continues reading until all the data is processed, returning chunks and then finally `NULL` at EOF.

---

### **Traceability with tldraw**

You can now visualize the above examples with **tldraw** by tracing the following steps for each case:

1. **File Content**: Represent the file content as a long rectangle.
2. **Reading the File**: Use arrows to show how data is being read from the file, chunk by chunk.
3. **Returned Lines**: Label the returned lines on each step as the function processes the data.
4. **Multiple FD Handling**: Use different colored arrows or boxes to represent each file descriptor's independent reading state.

---

### **Summary**
- These **8 examples** provide a good mix of common use cases (reading multiple lines, handling different file contents, and managing multiple file descriptors).
- For each example, you should be able to trace how data is read from the file and how the function handles edge cases (EOF, empty file, multiple FDs).
- Use **tldraw** to visually represent the flow of data, memory, and function calls to solidify your understanding of how `get_next_line()` works in different scenarios.

Let me know if you need further clarification on any of these examples or help with visualizing them!


-----

Here are **two different examples** of using your **mandatory `get_next_line` function** to read from `stdin`. These examples will help you practice handling different scenarios:

---

### **Example 1: Read Lines from `stdin` and Print Them**
In this example, you continuously read lines from `stdin` (standard input) until the user presses `Ctrl+D` (end-of-file).

```c
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    char *line;

    printf("Enter lines (Ctrl+D to quit):\n");
    while ((line = get_next_line(STDIN_FILENO)) != NULL)  // STDIN_FILENO = 0
    {
        printf("Read: %s", line);  // Print each line read
        free(line);  // Free the memory allocated by get_next_line
    }
    return (0);
}
```

#### **How It Works**:
1. `get_next_line(STDIN_FILENO)` reads from `stdin` line by line.
2. The user inputs text, and each line is printed after being read.
3. The loop ends when `get_next_line` returns `NULL` (when `Ctrl+D` is pressed).

---

### **Example 2: Count the Number of Lines Entered**
This example reads lines from `stdin` and counts how many lines were entered before the user presses `Ctrl+D`.

```c
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    char *line;
    int line_count = 0;

    printf("Enter lines (Ctrl+D to quit):\n");
    while ((line = get_next_line(STDIN_FILENO)) != NULL)
    {
        line_count++;
        free(line);  // Free the memory allocated by get_next_line
    }
    printf("Total lines entered: %d\n", line_count);
    return (0);
}
```

#### **How It Works**:
1. Each line is read from `stdin` using `get_next_line(STDIN_FILENO)`.
2. For every line read, the `line_count` is incremented.
3. After exiting the loop (by pressing `Ctrl+D`), the total number of lines entered is printed.

---

### **How to Test These Examples**:
1. **Compile the program**:
   ```bash
   cc main.c get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=42
   ```
2. **Run the program**:
   ```bash
   ./a.out
   ```

3. **Input Example for Example 1**:
   ```plaintext
   Enter lines (Ctrl+D to quit):
   Hello, world!
   Read: Hello, world!
   This is a test.
   Read: This is a test.
   ```
   After pressing `Ctrl+D`, the program will exit.

4. **Input Example for Example 2**:
   ```plaintext
   Enter lines (Ctrl+D to quit):
   Line one
   Line two
   Line three
   Total lines entered: 3
   ```

---

### **Key Differences Between Examples**:
- **Example 1**: Focuses on reading and printing each line.
- **Example 2**: Counts the total number of lines entered.

These examples will help you practice both `stdin` input handling and memory management (`free(line)`).