/*
 * Vulnerable C Application - FOR TESTING PURPOSES ONLY
 * This code intentionally contains security vulnerabilities.
 * DO NOT USE IN PRODUCTION!
 *
 * Compile with: gcc -o vulnerable_app vulnerable_app.c -fno-stack-protector -z execstack -no-pie
 * Or use the provided Makefile: make
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// VULNERABILITY 1: Hardcoded Credentials
#define API_KEY "1234567890abcdef"
#define DB_PASSWORD "super_secret_password"

// VULNERABILITY 2: Buffer Overflow
void vulnerable_strcpy(char *input) {
    char buffer[64];
    printf("[Buffer Overflow Demo]\n");
    printf("Input: %s\n", input);
    strcpy(buffer, input);  // No bounds checking!
    printf("Buffer content: %s\n", buffer);
}

// VULNERABILITY 3: Format String Vulnerability
void vulnerable_printf(char *user_input) {
    printf("[Format String Demo]\n");
    printf(user_input);  // User input directly as format string!
    printf("\n");
}

// VULNERABILITY 4: Use After Free
void use_after_free_demo() {
    printf("[Use After Free Demo]\n");
    char *ptr = (char *)malloc(100);
    strcpy(ptr, "Sensitive data");
    printf("Allocated memory: %s\n", ptr);
    
    free(ptr);
    printf("Memory freed\n");
    
    // Using freed memory - undefined behavior!
    printf("Accessing freed memory: %s\n", ptr);
    strcpy(ptr, "New data in freed memory");  // Writing to freed memory
    printf("Modified freed memory: %s\n", ptr);
}

// VULNERABILITY 5: Integer Overflow
void integer_overflow_demo(unsigned int size) {
    printf("[Integer Overflow Demo]\n");
    printf("Requested size: %u\n", size);
    
    // Integer overflow can bypass size checks
    unsigned int total_size = size + 100;
    printf("Total size (size + 100): %u\n", total_size);
    
    if (total_size < size) {
        printf("Integer overflow detected!\n");
    }
    
    // Allocating with overflowed size - can lead to heap overflow
    char *buffer = (char *)malloc(total_size);
    if (buffer) {
        memset(buffer, 'A', size);  // Writing beyond allocated size
        free(buffer);
    }
}

// VULNERABILITY 6: Memory Leak
void memory_leak_demo() {
    printf("[Memory Leak Demo]\n");
    for (int i = 0; i < 5; i++) {
        char *leak = (char *)malloc(1024);
        sprintf(leak, "Leaked memory block %d", i);
        printf("Allocated: %s\n", leak);
        // Never freed - memory leak!
    }
    printf("Memory leaked: 5 KB\n");
}

// VULNERABILITY 7: Insecure gets() usage
void insecure_input() {
    char buffer[64];
    printf("[Insecure Input Demo]\n");
    printf("Enter text (WARNING: uses gets): ");
    // gets() is deprecated and extremely dangerous
    // Using fgets as gets is removed in C11, but simulating the vulnerability
    fgets(buffer, 256, stdin);  // Reading more than buffer size!
    printf("You entered: %s\n", buffer);
}

// VULNERABILITY 8: Command Injection
void execute_command(char *filename) {
    char command[256];
    printf("[Command Injection Demo]\n");
    // No input sanitization
    sprintf(command, "cat %s", filename);
    printf("Executing: %s\n", command);
    system(command);  // Dangerous!
}

// VULNERABILITY 9: Race Condition (TOCTOU - Time of Check, Time of Use)
void race_condition_demo(char *filename) {
    printf("[Race Condition Demo]\n");
    
    // Check if file exists
    if (access(filename, F_OK) == 0) {
        printf("File exists, processing...\n");
        sleep(1);  // Time gap where file could be replaced
        
        // Use the file - might be different now!
        FILE *fp = fopen(filename, "r");
        if (fp) {
            char buffer[100];
            fgets(buffer, sizeof(buffer), fp);
            printf("Read: %s\n", buffer);
            fclose(fp);
        }
    }
}

// VULNERABILITY 10: Uninitialized Memory Usage
void uninitialized_memory() {
    printf("[Uninitialized Memory Demo]\n");
    int uninitialized_var;  // Not initialized
    printf("Uninitialized variable: %d\n", uninitialized_var);
    
    char *uninitialized_ptr;  // Not initialized
    printf("Uninitialized pointer: %p\n", (void *)uninitialized_ptr);
}

void print_menu() {
    printf("\n");
    printf("=" "========================================================\n");
    printf("VULNERABLE C APPLICATION - TESTING ONLY\n");
    printf("=" "========================================================\n");
    printf("1. Buffer Overflow Demo\n");
    printf("2. Format String Demo\n");
    printf("3. Use After Free Demo\n");
    printf("4. Integer Overflow Demo\n");
    printf("5. Memory Leak Demo\n");
    printf("6. Uninitialized Memory Demo\n");
    printf("7. Show Hardcoded Credentials\n");
    printf("8. Run All Demos\n");
    printf("0. Exit\n");
    printf("=" "========================================================\n");
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--auto") == 0) {
        printf("Running automated demo...\n\n");
        
        printf("\n[Hardcoded Credentials]\n");
        printf("API Key: %s\n", API_KEY);
        printf("DB Password: %s\n", DB_PASSWORD);
        
        vulnerable_strcpy("Normal input");
        printf("\n");
        
        vulnerable_printf("Format: %x %x %x");
        printf("\n");
        
        use_after_free_demo();
        printf("\n");
        
        integer_overflow_demo(4294967200);  // Close to UINT_MAX
        printf("\n");
        
        memory_leak_demo();
        printf("\n");
        
        uninitialized_memory();
        printf("\n");
        
        printf("Demo completed.\n");
        return 0;
    }
    
    int choice;
    char input[100];
    
    while (1) {
        print_menu();
        printf("\nEnter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;
        }
        getchar();  // Consume newline
        
        switch (choice) {
            case 1:
                printf("Enter text for buffer overflow test: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;  // Remove newline
                vulnerable_strcpy(input);
                break;
                
            case 2:
                printf("Enter format string: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                vulnerable_printf(input);
                break;
                
            case 3:
                use_after_free_demo();
                break;
                
            case 4:
                printf("Enter size (try 4294967200): ");
                unsigned int size;
                scanf("%u", &size);
                getchar();
                integer_overflow_demo(size);
                break;
                
            case 5:
                memory_leak_demo();
                break;
                
            case 6:
                uninitialized_memory();
                break;
                
            case 7:
                printf("\n[Hardcoded Credentials]\n");
                printf("API Key: %s\n", API_KEY);
                printf("DB Password: %s\n", DB_PASSWORD);
                break;
                
            case 8:
                printf("\nRunning all demos...\n");
                vulnerable_strcpy("Test input");
                printf("\n");
                vulnerable_printf("Test %x %x");
                printf("\n");
                use_after_free_demo();
                printf("\n");
                integer_overflow_demo(4294967200);
                printf("\n");
                memory_leak_demo();
                printf("\n");
                uninitialized_memory();
                printf("\n");
                printf("API Key: %s\n", API_KEY);
                printf("DB Password: %s\n", DB_PASSWORD);
                break;
                
            case 0:
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}
