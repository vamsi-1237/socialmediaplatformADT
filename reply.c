#include "reply.h"
#include <stdlib.h>
#include <string.h>

Reply* createReply(const char *username, const char *content) {
    Reply *r = (Reply*)malloc(sizeof(Reply));
    if (!r) return NULL;

    r->username = strdup(username);
    r->content = strdup(content);
    r->next = NULL;

    return r;
}

void freeReply(Reply *r) {
    while (r) {
        Reply *temp = r;
        r = r->next;
        free(temp->username);
        free(temp->content);
        free(temp);
    }
}

