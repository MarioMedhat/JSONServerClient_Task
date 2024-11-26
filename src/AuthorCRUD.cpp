#include <iostream>
#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include "Author.hpp"
#include "JsonServerClient.hpp"
#include "AuthorCRUD.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp> // For boost::uuids::random_generator

std::vector<Author> AuthorCRUD::getAllAuthors() {

    std::vector<Author> authorsVector;
    try {

        JsonServerClient client(baseUrl);

        nlohmann::json getData = client.get(endpoint);

        for (const auto& authorData : getData) {

            Author author(authorData["id"], authorData["name"], authorData["email"]);
            authorsVector.push_back(author);

        }

    }
    catch (const std::exception& e) {

        std::cout << "Copuld not fetch authors data" << std::endl;

    }

    return authorsVector;

}


std::shared_ptr<Author> AuthorCRUD::getAuthorById(std::string id) {

    JsonServerClient client(baseUrl);
    std::shared_ptr <Author> authorPtr = nullptr;

    try {

        nlohmann::json getData = client.get(endpoint + (std::string)"/" + id);
        authorPtr = std::shared_ptr<Author> (new Author(getData["id"], getData["name"], getData["email"]));

    }

    catch (const std::exception& e) {

        std::cout << "author with id = " << id << " is not foud" << std::endl;

    }

    return(authorPtr);

}


bool AuthorCRUD::createAuthor(const std::string& name, const std::string& email) {

    bool returnVal = false;

    try {

        JsonServerClient client(baseUrl);

        boost::uuids::random_generator generator;
        boost::uuids::uuid uuid = generator();

        // Convert UUID to string using Boost's to_string()
        std::string uuid_str = boost::uuids::to_string(uuid);

        nlohmann::json payload;
        payload["id"] = uuid_str;
        payload["name"] = name;
        payload["email"] = email;
        client.post(endpoint, payload);

        returnVal = true;

    }

    catch (const std::exception& e) {

        std::cout << "Author not created" << std::endl;

    }

    return returnVal;

}

bool AuthorCRUD::updateAuthor(const Author& author) {

    bool returnVal = false;

    try {

        JsonServerClient client(baseUrl);

        nlohmann::json payload;
        payload["name"] = author.getName();
        payload["email"] = author.getEmail();
        client.put(endpoint + (std::string)"/" + author.getId(), payload);

        returnVal = true;
    }

    catch (const std::exception& e) {

        std::cout << "Author not updated" << std::endl;

    }

    return returnVal;

}

bool AuthorCRUD::deleteAuthor(std::string id) {

    bool returnVal = false;

    try {

        JsonServerClient client(baseUrl);
        client.del(endpoint + "/" + id);
        returnVal = true;
    }

    catch (const std::exception& e) {

        std::cout << "Author not updated" << std::endl;

    }

    return returnVal;

}