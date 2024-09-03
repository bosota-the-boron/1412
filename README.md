# 1412

🔐 Password Strength Checker with Wordlist Verification

Welcome to the Password Strength Checker repository! This C program is designed to assess the security of your passwords by evaluating their composition and checking them against a wordlist of commonly used passwords. The program provides helpful recommendations for improving password strength and ensuring that your credentials are secure.
🚀 Features

    Password Length Verification: Ensures that your password meets a minimum length requirement for enhanced security.
    Character Composition Analysis: Checks for the presence of uppercase letters, lowercase letters, digits, and special characters.
    Password Strength Scoring: Calculates a comprehensive score based on the elements of your password.
    Custom Wordlist Verification: Scans your password against a wordlist of common passwords to prevent the use of easily guessable credentials.
    User Guidance: Provides tailored recommendations based on the password's score to help you create a stronger password.
    Command-Line Interface: Simple and intuitive command-line interface with a --help option to guide you through usage.

📖 Usage
Basic Usage

To check the strength of your password, simply run the program and input your password when prompted:

bash

./password_checker wordlist.txt

Help Option

To display usage instructions and available options, use the -h or --help flag:

bash

./password_checker -h

Example Output

plaintext

Enter the password to test: MySecurePassword123!
Password Score: 35/35
Your password is very strong! It meets all the security criteria.

🛠️ How It Works

The program evaluates the password based on the following criteria:

    Length Check: Ensures the password is at least 32 characters long.
    Uppercase Letters: Verifies the presence of at least one uppercase letter.
    Lowercase Letters: Verifies the presence of at least one lowercase letter.
    Digits: Checks if the password contains digits.
    Special Characters: Ensures that special characters are included for enhanced security.
    Wordlist Check: Cross-references the password with a provided wordlist to ensure it's not a common or weak password.

Each criterion contributes to the final score, with specific recommendations provided based on the score.
👨‍💻 Installation

Clone the repository and compile the program using a C compiler:

bash

git clone https://github.com/yourusername/password-checker.git
cd password-checker
gcc -o password_checker password_checker.c

📝 Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request if you have any improvements or bug fixes.
📄 License @bosota-the-boron
