#include "comment.h"
#include <stdlib.h>
#include <string.h>

Comment* createComment(const char *username, const char *content) {
    Comment *c = (Comment*)malloc(sizeof(Comment));
    if (!c) return NULL;

    c->username = strdup(username);
    c->content = strdup(content);
    c->replies = NULL;
    c->next = NULL;

    return c;
}

void freeComment(Comment *c) {
    while (c) {
        Comment *temp = c;
        c = c->next;
        free(temp->username);
        free(temp->content);
        freeReply(temp->replies);
        free(temp);
    }
}

