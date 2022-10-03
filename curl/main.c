// ------------------------------------------------------- //
// Easy Networking in C (libcurl)                          //
// - youtu.be/daA-KBKfJ_o                                  //
//                                                         //
// Using Libcurl in C/C++                                  //
// - dev.to/hi_artem/using-libcurl-in-c-c-application-4668 //
// ------------------------------------------------------- //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct memory_struct {
    char *body;
    size_t size;
};

size_t write_memory_callback(void *content, size_t size, size_t n_items, void *user_ptr);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: try './curl [url]' to make a get request.\n");
        return EXIT_FAILURE;
    }

    CURL *curl_handler = curl_easy_init();

    if (!curl_handler) {
        fprintf(stderr, "init failed\n");
        return EXIT_FAILURE;
    }

    struct memory_struct chunk;
    chunk.body = malloc(1);
    chunk.size = 0;

    // set options
    curl_easy_setopt(curl_handler, CURLOPT_URL, argv[1]);
    curl_easy_setopt(curl_handler, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, write_memory_callback);
    curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, (void *) &chunk);
    curl_easy_setopt(curl_handler, CURLOPT_USERAGENT, "libcurl-dv/1.0");

    // perform action
    CURLcode result = curl_easy_perform(curl_handler);

    if (result != CURLE_OK) {
        fprintf(stderr, "error: %s\n", curl_easy_strerror(result));

    } else {
        printf("size: %lu\n", (unsigned long) chunk.size);
        printf("data: %s\n", chunk.body);
    }

    curl_easy_cleanup(curl_handler);
    free(chunk.body);
    return EXIT_SUCCESS;
}

/**
 * Required to return the bytes processed.
 */
size_t write_memory_callback(void *content, size_t size, size_t n_items, void *user_ptr){
    size_t realsize = size * n_items;
    struct memory_struct *mem = (struct memory_struct *) user_ptr;

    char *ptr = realloc(mem->body, mem->size + realsize + 1);
    if (ptr == NULL) {
        printf("error: not enough memory\n");
        return 0;
    }

    mem->body = ptr;
    memcpy(&(mem->body[mem->size]), content, realsize);
    mem->size += realsize;
    mem->body[mem->size] = 0;

    return realsize;
}

// ---------------------------------------------------------------------------
// :: Other Examples
// ----------------------------------------------------------------------------

/**
 * Simple example, go request and dump it to the stdout.
 * Usage: './curl [url]'
 */
int simple_get(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: try './curl [url]' to make a get request.\n");
        return EXIT_FAILURE;
    }

    CURL *curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "init failed\n");
        return EXIT_FAILURE;
    }

    // set options
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);

    // perform action
    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        fprintf(stderr, "error: %s\n", curl_easy_strerror(result));
    }

    curl_easy_cleanup(curl);
    return EXIT_SUCCESS;
}
