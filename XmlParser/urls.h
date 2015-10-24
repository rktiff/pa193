#ifndef URLS_H
#define URLS_H

#include <iostream>
#include <list>

class Urls{
    std::string* m_url;
    std::string* m_imgurl;
    std::list<std::string> m_alturl;
    std::string* m_vidurl;

    bool isValid(const std::string & url) const;


public:
    ~Urls();

    std::string* getUrl() const;//musi byt mozne overit unikatnost url v ramci feedu

    void setUrl(const std::string& url);
    void setImgUrl(const std::string& url);
    void addAltUrl(const std::string& url);
    void setVidUrl(const std::string& url);

};

#endif // URLS_H
