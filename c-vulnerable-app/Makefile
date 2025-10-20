# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wno-deprecated-declarations -fno-stack-protector -z execstack -no-pie -g
TARGET = vulnerable_app

# Source files
SRC = vulnerable_app.c

# Default target
all: $(TARGET)

# Build the vulnerable application
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@echo "Built: $(TARGET)"
	@echo "WARNING: This binary has security protections disabled!"

# Run automated demo
demo: $(TARGET)
	./$(TARGET) --auto

# Clean build artifacts
clean:
	rm -f $(TARGET)
	@echo "Cleaned build artifacts"

# Help target
help:
	@echo "Available targets:"
	@echo "  make        - Build the vulnerable application"
	@echo "  make demo   - Build and run automated demo"
	@echo "  make clean  - Remove build artifacts"
	@echo "  make help   - Show this help message"

.PHONY: all demo clean help
