# C Vulnerable Application

## ⚠️ WARNING
This application contains **intentional security vulnerabilities** for testing and educational purposes only.

**DO NOT USE IN PRODUCTION!**

## Vulnerabilities Included

1. **Hardcoded Credentials** - API keys and passwords in source code
2. **Buffer Overflow** - Using unsafe strcpy() without bounds checking
3. **Format String Vulnerability** - User input as printf format string
4. **Use After Free** - Accessing and writing to freed memory
5. **Integer Overflow** - Arithmetic overflow in size calculations
6. **Memory Leaks** - Allocated memory never freed
7. **Insecure Input** - Using unsafe input functions
8. **Command Injection** - Unsanitized input to system()
9. **Race Condition** - TOCTOU (Time of Check, Time of Use)
10. **Uninitialized Memory** - Using variables before initialization

## Building the Application

```bash
make
```

Or manually:
```bash
gcc -o vulnerable_app vulnerable_app.c -fno-stack-protector -z execstack -no-pie
```

**Note:** The application is compiled with security protections disabled:
- `-fno-stack-protector` - Disables stack canaries
- `-z execstack` - Makes stack executable
- `-no-pie` - Disables position independent executable

## Running the Application

### Interactive mode:
```bash
./vulnerable_app
```

### Automated demo:
```bash
make demo
```
or
```bash
./vulnerable_app --auto
```

## Requirements

- GCC compiler
- Linux/Unix environment
- Make (optional, for using Makefile)

## Example Exploits

### Buffer Overflow
```bash
# Input a string longer than 64 characters
./vulnerable_app
# Choose option 1, then enter a long string (e.g., 100 A's)
```

### Format String
```bash
# Use format specifiers to read stack memory
./vulnerable_app
# Choose option 2, then enter: %x %x %x %x
```

### Integer Overflow
```bash
# Try with value close to UINT_MAX
./vulnerable_app
# Choose option 4, then enter: 4294967200
```

## Security Analysis Tools

You can analyze this code with:
- **Valgrind**: `valgrind ./vulnerable_app --auto`
- **AddressSanitizer**: Recompile with `-fsanitize=address`
- **Static analyzers**: cppcheck, clang static analyzer
