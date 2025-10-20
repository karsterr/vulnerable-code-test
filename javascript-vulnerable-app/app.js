/**
 * Vulnerable JavaScript Application - FOR TESTING PURPOSES ONLY
 * This code intentionally contains security vulnerabilities.
 * DO NOT USE IN PRODUCTION!
 */

const http = require('http');
const url = require('url');
const fs = require('fs');
const path = require('path');
const { exec } = require('child_process');

// VULNERABILITY 1: Hardcoded Secrets
const API_SECRET = "my-super-secret-api-key-12345";
const JWT_SECRET = "jwt-secret-key-do-not-share";
const DATABASE_PASSWORD = "admin123";

class VulnerableApp {
    constructor() {
        this.users = [
            { id: 1, username: 'admin', password: 'admin123', role: 'admin' },
            { id: 2, username: 'user', password: 'user123', role: 'user' }
        ];
    }

    // VULNERABILITY 2: XSS (Cross-Site Scripting)
    generateUserProfile(username) {
        // Directly embedding user input without sanitization
        return `
            <html>
            <body>
                <h1>Welcome ${username}!</h1>
                <p>Your profile page</p>
            </body>
            </html>
        `;
    }

    // VULNERABILITY 3: Path Traversal
    readUserFile(filename) {
        // No validation of filename, allowing directory traversal
        const filePath = path.join('/tmp/userfiles', filename);
        try {
            return fs.readFileSync(filePath, 'utf8');
        } catch (error) {
            return `Error reading file: ${error.message}`;
        }
    }

    // VULNERABILITY 4: Command Injection
    executeSystemCommand(userInput) {
        // Directly executing user input
        return new Promise((resolve, reject) => {
            exec(`echo ${userInput}`, (error, stdout, stderr) => {
                if (error) {
                    reject(error);
                } else {
                    resolve(stdout);
                }
            });
        });
    }

    // VULNERABILITY 5: Insecure eval() usage
    calculateExpression(expression) {
        // Using eval on user input
        try {
            return eval(expression);
        } catch (error) {
            return `Error: ${error.message}`;
        }
    }

    // VULNERABILITY 6: Prototype Pollution
    mergeObjects(target, source) {
        // Vulnerable to prototype pollution
        for (let key in source) {
            if (typeof source[key] === 'object' && source[key] !== null) {
                target[key] = target[key] || {};
                this.mergeObjects(target[key], source[key]);
            } else {
                target[key] = source[key];
            }
        }
        return target;
    }

    // VULNERABILITY 7: Insecure Direct Object Reference
    getUserById(userId) {
        // No authorization check
        return this.users.find(u => u.id == userId);
    }

    // VULNERABILITY 8: Mass Assignment
    updateUser(userId, updates) {
        // Allows updating any property including role
        const user = this.users.find(u => u.id == userId);
        if (user) {
            Object.assign(user, updates);
            return user;
        }
        return null;
    }
}

// Create HTTP server to demonstrate vulnerabilities
const app = new VulnerableApp();

const server = http.createServer((req, res) => {
    const parsedUrl = url.parse(req.url, true);
    const pathname = parsedUrl.pathname;
    const query = parsedUrl.query;

    res.setHeader('Content-Type', 'text/html');

    if (pathname === '/') {
        res.writeHead(200);
        res.end(`
            <html>
            <body>
                <h1>Vulnerable JavaScript App - Testing Only</h1>
                <h2>Available Endpoints:</h2>
                <ul>
                    <li><a href="/profile?username=Admin">/profile?username=NAME</a> - XSS vulnerability</li>
                    <li><a href="/file?name=test.txt">/file?name=FILE</a> - Path traversal</li>
                    <li><a href="/calc?expr=2+2">/calc?expr=EXPR</a> - Eval injection</li>
                    <li><a href="/user?id=1">/user?id=ID</a> - IDOR vulnerability</li>
                    <li><a href="/secrets">/secrets</a> - Hardcoded secrets</li>
                </ul>
            </body>
            </html>
        `);
    } else if (pathname === '/profile') {
        // XSS vulnerability demo
        const username = query.username || 'Guest';
        res.writeHead(200);
        res.end(app.generateUserProfile(username));
    } else if (pathname === '/file') {
        // Path traversal demo
        const filename = query.name || 'default.txt';
        res.writeHead(200);
        res.end(`<pre>File content: ${app.readUserFile(filename)}</pre>`);
    } else if (pathname === '/calc') {
        // Eval injection demo
        const expr = query.expr || '0';
        res.writeHead(200);
        res.end(`<pre>Result: ${app.calculateExpression(expr)}</pre>`);
    } else if (pathname === '/user') {
        // IDOR demo
        const userId = parseInt(query.id) || 1;
        const user = app.getUserById(userId);
        res.writeHead(200);
        res.end(`<pre>${JSON.stringify(user, null, 2)}</pre>`);
    } else if (pathname === '/secrets') {
        // Exposed secrets
        res.writeHead(200);
        res.end(`
            <pre>
API Secret: ${API_SECRET}
JWT Secret: ${JWT_SECRET}
DB Password: ${DATABASE_PASSWORD}
            </pre>
        `);
    } else {
        res.writeHead(404);
        res.end('Not found');
    }
});

// Demo function for command-line testing
function runDemo() {
    console.log('=' .repeat(60));
    console.log('VULNERABLE JAVASCRIPT APPLICATION - TESTING ONLY');
    console.log('=' .repeat(60));
    
    console.log('\n[XSS Demo]');
    console.log(app.generateUserProfile('<script>alert("XSS")</script>'));
    
    console.log('\n[Hardcoded Secrets]');
    console.log(`API Secret: ${API_SECRET}`);
    console.log(`JWT Secret: ${JWT_SECRET}`);
    
    console.log('\n[Eval Injection Demo]');
    console.log(`Result of 2+2: ${app.calculateExpression('2+2')}`);
    console.log(`Dangerous eval: ${app.calculateExpression('process.env')}`);
    
    console.log('\n[Prototype Pollution Demo]');
    const obj1 = {};
    const obj2 = JSON.parse('{"__proto__": {"polluted": "yes"}}');
    app.mergeObjects(obj1, obj2);
    console.log(`Object polluted: ${({}).polluted}`);
    
    console.log('\n[IDOR Demo]');
    console.log('User 1:', app.getUserById(1));
    console.log('User 2:', app.getUserById(2));
    
    console.log('\n[Mass Assignment Demo]');
    console.log('Before:', app.getUserById(2));
    app.updateUser(2, { role: 'admin' });
    console.log('After privilege escalation:', app.getUserById(2));
}

if (require.main === module) {
    if (process.argv[2] === '--server') {
        const PORT = 3000;
        server.listen(PORT, () => {
            console.log(`Vulnerable server running on http://localhost:${PORT}`);
            console.log('Press Ctrl+C to stop');
        });
    } else {
        runDemo();
    }
}

module.exports = VulnerableApp;
