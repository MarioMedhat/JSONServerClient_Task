#include "Blog.hpp"

// Constructor
Blog::Blog(const std::string& id, const std::string& title, const std::string& content, const std::string& authorId)
    : id(id), title(title), content(content), authorId(authorId) {}

// Getters
std::string Blog::getId() const {
    return id;
}

std::string Blog::getTitle() const {
    return title;
}

std::string Blog::getContent() const {
    return content;
}

std::string Blog::getAuthorId() const {
    return authorId;
}

// Setters
void Blog::setTitle(const std::string& title) {
    this->title = title;
}

void Blog::setContent(const std::string& content) {
    this->content = content;
}

void Blog::setAuthorId(const std::string& authorId) {
    this->authorId = authorId;
}


