# 📖 get_next_line | 42 School Project


### Reading a file one line at a time, because why not reinvent the wheel ? 😄

![42 School Badge](https://img.shields.io/badge/42-School-blue)
![Norminette](https://img.shields.io/badge/Norminette-passing-success)
![Score](https://img.shields.io/badge/Score-125%2F100-brightgreen)

> *"Why stick to standard file I/O when you can create your own efficient line reader?"* - Every 42 Student Ever 😎

---

## 🎯 Project Overview

Welcome to my implementation of `get_next_line`, a function that reads a file descriptor line by line. This project dives deep into file handling, static variables, memory management, and system calls.

### 🌟 Key Features

- Reads a file one line at a time.
- Handles multiple file descriptors simultaneously (Bonus).
- Uses dynamic memory allocation for efficient processing.
- Includes robust error handling for edge cases like invalid FDs, EOF, and memory failures.
- Norm-compliant and well-structured code.

---

## 📜 Mandatory Requirements

### **Behavior**
- **Reads one line at a time**: Includes the newline (`\n`) if present.
- **Returns NULL**: When EOF is reached or on an error.
- **Supports dynamic buffer sizes**: Controlled via the `BUFFER_SIZE` macro.

### **System Calls Used**
- **`read()`**: Reads data from a file descriptor into a buffer.
- **`malloc()`**: Allocates memory dynamically for buffers and lines.
- **`free()`**: Frees allocated memory to avoid leaks.

---

## 📋 Supported Use Cases

- Reading files line by line.
- Handling standard input (`stdin`).
- Dealing with valid and invalid file descriptors.
- Edge cases like empty files, very large lines, and dynamic buffer sizes.

### Example: **Reading from a file**
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

---

## 💻 Bonus Requirements

### **Additional Features**
- **Simultaneous file descriptors**: Handles multiple open files without losing the reading state of each.
- **Single static variable per file descriptor**: Uses a static array indexed by the FD.

### Example: **Reading multiple files simultaneously**
```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line1;
    char *line2;

    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);
    printf("File1: %s", line1);
    printf("File2: %s", line2);

    free(line1);
    free(line2);
    close(fd1);
    close(fd2);
    return 0;
}
```

---

## 🚀 Getting Started

### Installation
#### 1. Clone the repository:
```bash
git clone https://github.com/yomazini/42Cursus-get_next_line.git
```
#### 2. Navigate to the project directory:
```bash
cd 42Cursus-get_next_line
```
#### 3. Compile the library:
   


---

## 💡 Implementation Details

### Core Components
- **Main Function**: `get_next_line()`
- **Helper Functions**:
  - `read_line()`: Reads the file into a buffer until a line is complete.
  - `extract_line()`: Extracts the next line and updates the static buffer.
  - Utility functions like `ft_strlen`, `ft_strjoin`, `ft_strdup`, and `ft_substr` for string operations.

### Static Variables
- A static variable is used to store leftover data from previous reads.
- In the bonus part, an array of static variables is used to handle multiple FDs simultaneously.

### Memory Management
- All dynamically allocated memory is freed to prevent leaks.
- The buffer and any unused data are freed before returning NULL.

---

## 🔬 Testing

### Recommended Tests
1. **Basic File with Newlines**:
   - File content:
     ```
     Line 1
     Line 2
     Line 3
     ```
   - Expected output:
     ```
     Line 1\n
     Line 2\n
     Line 3
     ```

2. **Empty File**:
   - Expected output: `NULL`.

3. **Very Large Lines**:
   - Test with a file containing a single line larger than `BUFFER_SIZE`.

4. **Multiple FDs (Bonus)**:
   - Read from two files alternately.

### Edge Cases and Custom Tests
- **Small `BUFFER_SIZE`**:
   - Set `BUFFER_SIZE=1` and test splitting lines character by character.
- **Binary Files**:
   - Use `get_next_line` on a binary file and observe behavior.
- **Interrupted Reads**:
   - Simulate read interruptions using signals or non-blocking I/O.

---

## 🏆 What I Learned
- Advanced file I/O handling.
- Static variables and their behavior across function calls.
- Efficient memory management in C.
- Handling edge cases like EOF, invalid FDs, and large files.
- Writing modular, reusable code for real-world applications.



### Testing Tools
- [42 Tester for get_next_line](https://github.com/Tripouille/gnlTester)
- Custom test cases with different `BUFFER_SIZE` values (Go crazy).

---

## 🔬 Under the Hood

### How `get_next_line` Works:
1. Reads the file in chunks using `read()`.
2. Stores leftover data in a static variable.
3. Extracts and returns one line per call.
4. Cleans up memory when EOF is reached.

### System Calls Used:
- **`read()`**: Fetches file data into the buffer.
- **`malloc()`**: Dynamically allocates memory for buffers and lines.
- **`free()`**: Releases allocated memory.
- **`close()`**: Closes file descriptors.


---

## 🤝 Contribution
Feel free to:
- Open issues
- Submit pull requests
- Provide feedback

---

## 🎭 Author

Made with ☕️ and perseverance by **Youssef Mazini** (ymazini)
- 42 Intra: [ymazini](https://profile.intra.42.fr/users/ymazini)
- GitHub: [yomazini](https://github.com/yomazini)

---

> *"In files we trust, one line at a time!"* 😄
