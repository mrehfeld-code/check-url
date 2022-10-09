#include <iostream>
#include <fstream>

#include <curl/curl.h>


#define URLS "urls.txt"

int check_url(std::string url) {
    std::cout << "Checking " << url << " ...\t";
    CURL* handle = curl_easy_init();
    CURLcode res;
    if(handle) {
        curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(handle, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(handle);
        if(res != CURLE_OK) {
            std::cout << "\033[1;31m[ERROR]\033[22m " << curl_easy_strerror(res) << "\033[0m\n";
            return 1;
        }

        long http_code;
        curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &http_code);
        if(http_code == 200) {
            std::cout << "\033[1;32m[OK]\033[0m" << std::endl;
            return 0;
        } else {
            std::cout << "\033[1;33m[WARNING]\033[22m HTTP Response Code: " << http_code << "\033[0m\n";
            return 2;
        }
    } 
    return -1;
}

int main(int argc, char * argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);

    std::fstream fp(URLS, std::ios::in);
    std::string line;
    long url_counter = 0;

    while(std::getline(fp, line)) {
        check_url(line);
        url_counter++;
    }

    std::cout << "Checked " << url_counter << " URLs.\n";
    fp.close();

    return 0;
}