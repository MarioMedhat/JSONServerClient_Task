#ifndef AUTHOR_CRUD_HPP
#define AUTHOR_CRUD_HPP

#include <string>
#include <nlohmann/json.hpp>
#include "Author.hpp"

class AuthorCRUD {
public:

    static std::vector<Author> getAllAuthors();
    static Author getAuthorById(std::string id);
    static bool createAuthor(const Author& author);
    static bool updateAuthor(const Author& author);
    static bool deleteAuthor(std::string id);

    static std::string baseUrl;
    static std::string endpoint;

};

#endif // AUTHOR_CRUD_HPP