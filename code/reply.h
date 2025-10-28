#ifndef REPLY_H
#define REPLY_H

typedef struct Reply {
    char *username;
    char *content;
    struct Reply *next;
} Reply;

Reply* createReply(const char *username, const char *content);
void freeReply(Reply *r);

#endif

