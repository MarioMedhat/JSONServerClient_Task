#ifndef BLOG_CRUD_HPP
#define BLOG_CRUD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Blog.hpp"

class BlogCRUD {
public:
    static BlogCRUD& getInstance(const std::string& baseUrl, const std::string& endpoint);

    std::vector<Blog> getAllBlogs();
    Blog getBlogById(std::string id);
    bool createBlog(const std::string& title, const std::string& content, const std::string& authorId);
    bool updateBlog(const Blog& blog);
    bool deleteBlog(std::string id);

    BlogCRUD(const BlogCRUD&) = delete;
    BlogCRUD& operator=(const BlogCRUD&) = delete;

    ~BlogCRUD(); // Destructor made public, as it's needed by the unique pointer

private:
    BlogCRUD(const std::string& baseUrl, const std::string& endpoint);

    std::string baseUrl;
    std::string endpoint;

    static std::unique_ptr<BlogCRUD> instance;
};

#endif // BLOG_CRUD_HPP
