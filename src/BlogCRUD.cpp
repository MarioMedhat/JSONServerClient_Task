#include "BlogCRUD.hpp"
#include "JsonServerClient.hpp"
#include <nlohmann/json.hpp>

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

bool BlogCRUD::createBlog(const Blog& blog) {

    JsonServerClient client(baseUrl);

    nlohmann::json payload;
    payload["id"] = blog.getId();
    payload["name"] = blog.getTitle();
    payload["email"] = blog.getContent();
    payload["authorId"] = blog.getAuthorId();
    client.post(endpoint, payload);

    return true;

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