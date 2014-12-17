#ifndef CURLHTTPAGENT_H
#define CURLHTTPAGENT_H

extern "C" {
#include "curl/curl.h"
#include "curl/easy.h"
}
#include <QString>

class CurlHttpAgent
{
public:
    CurlHttpAgent();
    void downloadURL(const char* url, const char* file);
};

#endif // CURLHTTPAGENT_H
