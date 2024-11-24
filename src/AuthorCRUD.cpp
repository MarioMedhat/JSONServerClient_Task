#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "Author.hpp"
#include "JsonServerClient.hpp"
#include "AuthorCRUD.hpp"

std::vector<Author> AuthorCRUD::getAllAuthors() {

    JsonServerClient client("http://localhost:3000");
    nlohmann::json getData = client.get("/authors");

    std::vector<Author> authorsVector;

    for (const auto& authorData : getData) {

        Author author(authorData["id"], authorData["name"], authorData["email"]);
        authorsVector.push_back(author);

    }

    return authorsVector;

}


Author AuthorCRUD::getAuthorById(std::string id) {

    JsonServerClient client("http://localhost:3000");
    nlohmann::json getData = client.get("/authors" + (std::string)"/" + id);
    return(Author(getData["id"], getData["name"], getData["email"]));

}


bool AuthorCRUD::createAuthor(const Author& author) {

    JsonServerClient client("http://localhost:3000");

    std::string endpoint = "/authors";

    nlohmann::json payload;
    payload["id"] = author.getId();
    payload["name"] = author.getName();
    payload["email"] = author.getEmail();
    client.post(endpoint, payload);

    return true;

}

bool AuthorCRUD::updateAuthor(const Author& author) {

    JsonServerClient client("http://localhost:3000");

    std::string endpoint = "/authors/" + author.getId();

    nlohmann::json payload;
    payload["name"] = author.getName();
    payload["email"] = author.getEmail();
    client.put(endpoint, payload);

    return true;

}

bool AuthorCRUD::deleteAuthor(std::string id) {

    JsonServerClient client("http://localhost:3000");

    std::string endpoint = "/authors/" + id;

    client.del(endpoint);

    return true;

}