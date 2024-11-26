#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "Author.hpp"
#include "Blog.hpp"
#include "JsonServerClient.hpp"
#include "AuthorCRUD.hpp"
#include "BlogCRUD.hpp"

std::string AuthorCRUD::baseUrl = "http://localhost:3000";
std::string AuthorCRUD::endpoint = "/authors";

int main() {
    
    std::shared_ptr<Author> author = AuthorCRUD::getAuthorById("k");
    if (author != nullptr) {
        std::cout << author->getId() << std::endl;
        std::cout << author->getName() << std::endl;
        std::cout << author->getEmail() << std::endl;
    }
    
    std::vector<Author> authorsVector = AuthorCRUD::getAllAuthors();

    for (const auto& author : authorsVector) {

        std::cout << "id = " << author.getId() << ", name = " << author.getName() << ", email = " << author.getEmail() << std::endl;

    }

    AuthorCRUD::createAuthor("Mario", "mario@email.com");

    std::cout << "create author done!" << std::endl;

    std::string authorId;
    std::cout << "write author id to be updated" << std::endl;
    std::cin >>authorId;
    Author updatedAuthor(authorId, "Marioooo", "mario@email.com");
    AuthorCRUD::updateAuthor(updatedAuthor);
    
    std::cout << "update author done!" << std::endl;

    std::cout << "write author id to be deleted" << std::endl;
    std::cin >>authorId;
    AuthorCRUD::deleteAuthor(authorId);

    std::cout << "delete author done!" << std::endl;

    BlogCRUD& blogCRUD = BlogCRUD::getInstance("http://localhost:3000", "/blogs");

    std::shared_ptr<Blog> blog = blogCRUD.getBlogById("bengaraaaaaaab");
    if (blog != nullptr) {

        std::cout << blog->getId() << std::endl;
        std::cout << blog->getTitle() << std::endl;
        std::cout << blog->getContent() << std::endl;
        std::cout << blog->getAuthorId() << std::endl;

    }

    blog = blogCRUD.getBlogById("1");
    if (blog != nullptr) {

        std::cout << blog->getId() << std::endl;
        std::cout << blog->getTitle() << std::endl;
        std::cout << blog->getContent() << std::endl;
        std::cout << blog->getAuthorId() << std::endl;

    }

    std::vector<Blog> blogsVector = blogCRUD.getAllBlogs();

        for (const auto& blog : blogsVector) {

        std::cout << "id = " << blog.getId() << ", title = " << blog.getTitle() << ", content = " << blog.getContent() << ", authorId = " << blog.getAuthorId() << std::endl;

    }


    blogCRUD.createBlog("test blog", "this is a test blog", "yala negarab");

    std::cout << "create blog done!" << std::endl;
    blogCRUD.createBlog("test blog", "this is a test blog", "1");

    std::cout << "create blog done!" << std::endl;
    std::string blogId;
    std::cout << "write blog id to be updated" << std::endl;
    std::cin >>blogId;

    Blog updatedBlog(blogId, "test blog", "this is a test bloooooooooooog", "2");
    blogCRUD.updateBlog(updatedBlog);

    std::cout << "update blog done!" << std::endl;
    
    std::cout << "write blog id to be deleted" << std::endl;
    std::cin >>blogId;

    blogCRUD.deleteBlog(blogId);

    std::cout << "delete blog done!" << std::endl;

    return 0;
}
