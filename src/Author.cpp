#include "Author.hpp"
#include <random>

// Constructor
Author::Author(const std::string id, const std::string& name, const std::string& email)
    :id (id), name(name), email(email) {}

// Getters
std::string Author::getId() const {
    return id;
}

std::string Author::getName() const {
    return name;
}

std::string Author::getEmail() const {
    return email;
}

// Setters
void Author::setName(const std::string& name) {
    this->name = name;
}

void Author::setEmail(const std::string& email) {
    this->email = email;
}

int Author::generateUUID() {
    std::random_device rd;           // Non-deterministic random number generator
    std::mt19937 gen(rd());          // Standard Mersenne Twister random engine
    std::uniform_int_distribution<int> dist(100000, 999999); // 6-digit integer range

    return dist(gen);
}
