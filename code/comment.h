#ifndef COMMENT_H
#define COMMENT_H

#include "reply.h"

typedef struct Comment {
    char *username;
    char *content;
    Reply *replies;
    struct Comment *next;
} Comment;

Comment* createComment(const char *username, const char *content);
void freeComment(Comment *c);

#endif

