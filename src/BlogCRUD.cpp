#include "BlogCRUD.hpp"
#include "JsonServerClient.hpp"
#include <nlohmann/json.hpp>
#include <stdexcept>
#include "Author.hpp"
#include "AuthorCRUD.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp> // For boost::uuids::random_generator

// Initialize the static unique_ptr instance to nullptr
std::unique_ptr<BlogCRUD> BlogCRUD::instance = nullptr;

// Static method to access the BlogCRUD instance
BlogCRUD& BlogCRUD::getInstance(const std::string& baseUrl, const std::string& endpoint)
{
    if (!instance) {
        instance = std::unique_ptr<BlogCRUD>(new BlogCRUD(baseUrl, endpoint));
    }
    return *instance;
}

// Constructor
BlogCRUD::BlogCRUD(const std::string& baseUrl, const std::string& endpoint)
    : baseUrl(baseUrl), endpoint(endpoint)
{
    std::cout << "BlogCRUD instance created." << std::endl;
}

// Destructor
BlogCRUD::~BlogCRUD()
{
    std::cout << "BlogCRUD instance destroyed." << std::endl;
}

// Method to get all blogs
std::vector<Blog> BlogCRUD::getAllBlogs()
{
    JsonServerClient client(baseUrl);
    nlohmann::json getData = client.get(endpoint);

    std::vector<Blog> blogsVector;

    for (const auto& blogData : getData) {
        Blog blog(blogData["id"], blogData["title"], blogData["content"], blogData["authorId"]);
        blogsVector.push_back(blog);
    }

    return blogsVector;
}

Blog BlogCRUD::getBlogById(std::string id) {

    JsonServerClient client(baseUrl);
    nlohmann::json getData = client.get(endpoint + (std::string)"/" + id);
    return(Blog(getData["id"], getData["title"], getData["content"], getData["authorId"]));

}

bool BlogCRUD::createBlog(const std::string& title, const std::string& content, const std::string& authorId) {

    bool returnVal = false;
    try{

        std::shared_ptr<Author> authorPtr = AuthorCRUD::getAuthorById(authorId);
        
        if (authorPtr != nullptr) {

            JsonServerClient client(baseUrl);

            boost::uuids::random_generator generator;
            boost::uuids::uuid uuid = generator();

            // Convert UUID to string using Boost's to_string()
            std::string uuid_str = boost::uuids::to_string(uuid);

            nlohmann::json payload;
            payload["id"] = uuid_str;
            payload["name"] = title;
            payload["content"] = content;
            payload["authorId"] = authorId;
            client.post(endpoint, payload);

            returnVal = true;

        }    
        else {

            std::cout << "New blog not created" << std::endl;
            returnVal = false;
        
        }

    }

    catch (const std::exception& e) {

        std::cout << "New blog not created" << std::endl;
        returnVal = false;

    }

    return returnVal;

}

bool BlogCRUD::updateBlog(const Blog& blog) {

    JsonServerClient client(baseUrl);

    nlohmann::json payload;
    payload["title"] = blog.getTitle();
    payload["content"] = blog.getContent();
    payload["authorId"] = blog.getAuthorId();
    client.put(endpoint + "/" + blog.getId(), payload);

    return true;

}
bool BlogCRUD::deleteBlog(std::string id) {

    JsonServerClient client(baseUrl);

    client.del(endpoint + "/" + id);

    return true;

}