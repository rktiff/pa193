#include <stdexcept>

#include "urls.h"


using namespace std;

Urls::Urls():m_url(nullptr), m_imgurl(nullptr), m_vidurl(nullptr)
{
}

Urls::~Urls(){
    delete m_url;
    delete m_imgurl;
    delete m_vidurl;
}

std::string* Urls::getUrl() const{
    return m_url;
}

bool Urls::isValid(const string &url) const{
    if(url.length()>255)
        return false;

    // TODO: implement regexp ^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$

    return true;
}

void Urls::setUrl(const string& url){
    if(!isValid(url))
        throw logic_error("invalid url");

    m_url = new string(url);
}

void Urls::setImgUrl(const string& url){
    if(!isValid(url))
        throw logic_error("invalid url");

    m_imgurl = new string(url);
}

void Urls::addAltUrl(const string& url){
    if(!isValid(url))
        throw logic_error("invalid url");

    m_alturl.push_back(url);
}

void Urls::setVidUrl(const string& url){
    if(!isValid(url))
        throw logic_error("invalid url");

    //povolene iba youtube
    m_vidurl = new string(url);
}
