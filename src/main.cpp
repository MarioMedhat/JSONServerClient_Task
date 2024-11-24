#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "Author.hpp"
#include "Blog.hpp"
#include "JsonServerClient.hpp"
#include "AuthorCRUD.hpp"
#include "BlogCRUD.hpp"

// #include <boost/uuid/uuid.hpp>
// #include <boost/uuid/uuid_io.hpp>
// #include <boost/uuid/uuid_generators.hpp> // For boost::uuids::random_generator

// boost::uuids::random_generator generator;
// boost::uuids::uuid uuid = generator();

// // Convert UUID to string using Boost's to_string()
// std::string uuid_str = boost::uuids::to_string(uuid);
// std::cout << "Generated UUID: " << uuid_str << std::endl;

int main() {

    Author author = AuthorCRUD::getAuthorById("1");
    std::cout << author.getId() << std::endl;
    std::cout << author.getName() << std::endl;
    std::cout << author.getEmail() << std::endl;

    std::vector<Author> authorsVector = AuthorCRUD::getAllAuthors();

    for (const auto& author : authorsVector) {

        std::cout << "id = " << author.getId() << ", name = " << author.getName() << ", email = " << author.getEmail() << std::endl;

    }

    Author createdAuthor("4d", "Mario", "mario@email.com");
    AuthorCRUD::createAuthor(createdAuthor);

    std::cout << "create author done!" << std::endl;
    std::cin.get();

    Author updatedAuthor("4d", "Marioooo", "mario@email.com");
    AuthorCRUD::updateAuthor(updatedAuthor);

    std::cout << "update author done!" << std::endl;
    std::cin.get();

    AuthorCRUD::deleteAuthor("4d");

    std::cout << "delete author done!" << std::endl;
    std::cin.get();

    BlogCRUD& blogCRUD = BlogCRUD::getInstance("http://localhost:3000", "/blogs");

    Blog blog = blogCRUD.getBlogById("1");
    std::cout << blog.getId() << std::endl;
    std::cout << blog.getTitle() << std::endl;
    std::cout << blog.getContent() << std::endl;
    std::cout << blog.getAuthorId() << std::endl;

    std::vector<Blog> blogsVector = blogCRUD.getAllBlogs();

        for (const auto& blog : blogsVector) {

        std::cout << "id = " << blog.getId() << ", title = " << blog.getTitle() << ", content = " << blog.getContent() << ", authorId = " << blog.getAuthorId() << std::endl;

    }


    Blog createdBlog("4k", "test blog", "this is a test blog", "2");
    blogCRUD.createBlog(createdBlog);

    std::cout << "create blog done!" << std::endl;
    std::cin.get();

    Blog updatedBlog("4k", "test blog", "this is a test bloooooooooooog", "2");
    blogCRUD.updateBlog(updatedBlog);

    std::cout << "update blog done!" << std::endl;
    std::cin.get();

    blogCRUD.deleteBlog("4k");

    std::cout << "delete blog done!" << std::endl;

    return 0;
}
