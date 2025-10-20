# Python Vulnerable Application

## ⚠️ WARNING
This application contains **intentional security vulnerabilities** for testing and educational purposes only.

**DO NOT USE IN PRODUCTION!**

## Vulnerabilities Included

1. **Hardcoded Credentials** - Sensitive credentials stored in source code
2. **SQL Injection** - String concatenation in SQL queries
3. **Command Injection** - Unsanitized input passed to shell commands
4. **Insecure Deserialization** - Using pickle to deserialize untrusted data
5. **Path Traversal** - Insufficient path validation for file access
6. **Weak Random Generator** - Using `random` instead of `secrets` for tokens

## Running the Application

```bash
python3 app.py
```

## Requirements

- Python 3.6+
- No external dependencies required (uses only standard library)

## Example Exploits

### SQL Injection
```python
app.login("admin' OR '1'='1", "wrong_password")
```

### Command Injection
```python
app.ping_server("google.com; cat /etc/passwd")
```

### Path Traversal
```python
app.read_file("../../../etc/passwd")
```
