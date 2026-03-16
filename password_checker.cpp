#include <iostream>
#include <string>
#include <vector>
#include <cctype>

struct PasswordFeedback {
    std::string strength;
    std::vector<std::string> suggestions;
};

PasswordFeedback evaluatePassword(const std::string& password) {
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    PasswordFeedback feedback;

    for (char ch : password) {
        if (std::isupper(static_cast<unsigned char>(ch))) hasUpper = true;
        else if (std::islower(static_cast<unsigned char>(ch))) hasLower = true;
        else if (std::isdigit(static_cast<unsigned char>(ch))) hasDigit = true;
        else if (std::ispunct(static_cast<unsigned char>(ch))) hasSpecial = true;
    }

    int score = 0;
    if (password.length() >= 8) ++score;
    if (hasUpper) ++score;
    if (hasLower) ++score;
    if (hasDigit) ++score;
    if (hasSpecial) ++score;

    if (score <= 2) feedback.strength = "Weak";
    else if (score <= 4) feedback.strength = "Moderate";
    else feedback.strength = "Strong";

    if (password.length() < 8) feedback.suggestions.push_back("Use at least 8 characters.");
    if (!hasUpper) feedback.suggestions.push_back("Add an uppercase letter.");
    if (!hasLower) feedback.suggestions.push_back("Add a lowercase letter.");
    if (!hasDigit) feedback.suggestions.push_back("Include a digit.");
    if (!hasSpecial) feedback.suggestions.push_back("Use a special character (!@#$%^&* etc.).");

    return feedback;
}

int main() {
    std::string password;
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    PasswordFeedback result = evaluatePassword(password);

    std::cout << "\nPassword Strength: " << result.strength << "\n";
    if (!result.suggestions.empty()) {
        std::cout << "Suggestions:\n";
        for (const std::string& suggestion : result.suggestions) {
            std::cout << "- " << suggestion << "\n";
        }
    } else {
        std::cout << "Your password is strong. Good job!\n";
    }

    return 0;
}
