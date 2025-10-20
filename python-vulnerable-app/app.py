#!/usr/bin/env python3
"""
Vulnerable Python Application - FOR TESTING PURPOSES ONLY
This code intentionally contains security vulnerabilities.
DO NOT USE IN PRODUCTION!
"""

import sqlite3
import pickle
import subprocess
import os

# VULNERABILITY 1: Hardcoded credentials
DB_USER = "admin"
DB_PASSWORD = "SuperSecret123!"
API_KEY = "sk-1234567890abcdef"

class User:
    def __init__(self, username, role):
        self.username = username
        self.role = role

class VulnerableApp:
    def __init__(self):
        self.db_connection = sqlite3.connect(':memory:')
        self.setup_database()
    
    def setup_database(self):
        cursor = self.db_connection.cursor()
        cursor.execute('''
            CREATE TABLE users (
                id INTEGER PRIMARY KEY,
                username TEXT,
                password TEXT,
                email TEXT
            )
        ''')
        cursor.execute(
            "INSERT INTO users VALUES (1, 'admin', 'admin123', 'admin@example.com')"
        )
        self.db_connection.commit()
    
    # VULNERABILITY 2: SQL Injection
    def login(self, username, password):
        """
        Vulnerable to SQL injection
        Example exploit: username = "admin' OR '1'='1"
        """
        cursor = self.db_connection.cursor()
        query = f"SELECT * FROM users WHERE username='{username}' AND password='{password}'"
        print(f"Executing query: {query}")
        cursor.execute(query)
        return cursor.fetchone()
    
    # VULNERABILITY 3: Command Injection
    def ping_server(self, hostname):
        """
        Vulnerable to command injection
        Example exploit: hostname = "google.com; cat /etc/passwd"
        """
        command = f"ping -c 1 {hostname}"
        print(f"Executing command: {command}")
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return result.stdout
    
    # VULNERABILITY 4: Insecure Deserialization
    def load_user_session(self, session_data):
        """
        Vulnerable to insecure deserialization
        Pickle can execute arbitrary code during deserialization
        """
        try:
            user = pickle.loads(session_data)
            return user
        except Exception as e:
            print(f"Error deserializing user: {e}")
            return None
    
    # VULNERABILITY 5: Path Traversal
    def read_file(self, filename):
        """
        Vulnerable to path traversal
        Example exploit: filename = "../../etc/passwd"
        """
        base_path = "/tmp/uploads"
        file_path = base_path + "/" + filename
        try:
            with open(file_path, 'r') as f:
                return f.read()
        except Exception as e:
            return f"Error: {e}"
    
    # VULNERABILITY 6: Weak Random for Security
    def generate_token(self):
        """
        Using weak random for security-sensitive operations
        """
        import random
        return str(random.randint(1000, 9999))

def main():
    print("=" * 60)
    print("VULNERABLE PYTHON APPLICATION - TESTING ONLY")
    print("=" * 60)
    
    app = VulnerableApp()
    
    # Demo SQL Injection
    print("\n[SQL Injection Demo]")
    print("Normal login:")
    result = app.login("admin", "admin123")
    print(f"Result: {result}")
    
    print("\nMalicious login (SQL injection):")
    result = app.login("admin' OR '1'='1", "wrong")
    print(f"Result: {result}")
    
    # Demo Command Injection
    print("\n[Command Injection Demo]")
    print("Normal ping:")
    result = app.ping_server("127.0.0.1")
    print(f"Result: {result[:100]}...")
    
    # Demo hardcoded credentials
    print("\n[Hardcoded Credentials]")
    print(f"Database password: {DB_PASSWORD}")
    print(f"API Key: {API_KEY}")
    
    # Demo weak token
    print("\n[Weak Token Generation]")
    print(f"Generated token: {app.generate_token()}")

if __name__ == "__main__":
    main()
