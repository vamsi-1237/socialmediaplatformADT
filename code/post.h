#ifndef POST_H
#define POST_H

#include "comment.h"

typedef struct Post {
    char *username;
    char *caption;
    Comment *comments;
    struct Post *next;
} Post;

Post* createPost(const char *username, const char *caption);
void displayPost(Post *p);
void freePost(Post *p);

#endif

