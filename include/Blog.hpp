#ifndef BLOG_H
#define BLOG_H

#include <string>

class Blog {
private:
    std::string id;
    std::string title;
    std::string content;
    std::string authorId;

public:
    // Constructor
    Blog(const std::string& id, const std::string& title, const std::string& content, const std::string& authorId);

    // Getters
    std::string getId() const;
    std::string getTitle() const;
    std::string getContent() const;
    std::string getAuthorId() const;

    // Setters
    void setTitle(const std::string& title);
    void setContent(const std::string& content);
    void setAuthorId(const std::string& authorId);
};

#endif // BLOG_H
