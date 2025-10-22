#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdbool.h>
#include "post.h"

typedef struct Platform {
    Post *posts;          // Head of post list
    Post *lastViewedPost; // Last viewed post
} Platform;

extern Platform platform; // Global instance

Platform* createPlatform();
bool addPost(const char *username, const char *caption);
bool deletePost(int n);
Post* viewPost(int n);
Post* currPost();
Post* nextPost();
Post* previousPost();

bool addComment(const char *username, const char *content);
bool deleteComment(int n);
Comment* viewComments();

bool addReply(const char *username, const char *content, int n);
bool deleteReply(int n, int m);

#endif

