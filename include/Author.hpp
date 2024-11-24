#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>

class Author {
private:
    std::string id;
    std::string name;
    std::string email;
    int generateUUID();

public:
    // Constructor
    Author(const std::string id, const std::string& name, const std::string& email);

    // Getters
    std::string getId() const;
    std::string getName() const;
    std::string getEmail() const;

    // Setters
    void setName(const std::string& name);
    void setEmail(const std::string& email);

};

#endif // AUTHOR_H
