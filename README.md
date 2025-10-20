# vulnerable-code-test

⚠️ **WARNING: This repository contains intentionally vulnerable code for security testing and educational purposes only. DO NOT USE IN PRODUCTION!**

Bu repository, YZO projesi için kasıtlı olarak güvenlik açıkları içeren test kodlarını barındırır. **TEST REPOSUDUR.**

## Projects

This repository contains three vulnerable applications demonstrating common security vulnerabilities:

### 1. Python Vulnerable Application
Location: `python-vulnerable-app/`

Vulnerabilities:
- Hardcoded credentials
- SQL injection
- Command injection
- Insecure deserialization
- Path traversal
- Weak random number generation

[See Python project README](python-vulnerable-app/README.md)

### 2. JavaScript Vulnerable Application
Location: `javascript-vulnerable-app/`

Vulnerabilities:
- Hardcoded secrets
- Cross-Site Scripting (XSS)
- Path traversal
- Command injection
- Eval injection
- Prototype pollution
- Insecure Direct Object Reference (IDOR)
- Mass assignment

[See JavaScript project README](javascript-vulnerable-app/README.md)

### 3. C Vulnerable Application
Location: `c-vulnerable-app/`

Vulnerabilities:
- Hardcoded credentials
- Buffer overflow
- Format string vulnerability
- Use after free
- Integer overflow
- Memory leaks
- Insecure input handling
- Command injection
- Race conditions
- Uninitialized memory

[See C project README](c-vulnerable-app/README.md)

## Usage

Each project directory contains:
- Source code with vulnerabilities
- README with detailed documentation
- Build/run instructions
- Example exploits

## Purpose

These applications are designed for:
- Security testing
- Vulnerability scanning tool validation
- Security training and education
- Penetration testing practice

## Legal Disclaimer

This code is provided for educational and testing purposes only. Using these vulnerabilities against systems you do not own or have permission to test is illegal. The authors are not responsible for any misuse of this code.
