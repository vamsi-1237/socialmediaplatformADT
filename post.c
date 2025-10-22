#include "post.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Post* createPost(const char *username, const char *caption) {
    Post *p = (Post*)malloc(sizeof(Post));
    if (!p) return NULL;

    p->username = strdup(username);
    p->caption = strdup(caption);
    p->comments = NULL;
    p->next = NULL;

    return p;
}

void displayPost(Post *p) {
    if (!p) return;
    printf("Post by: %s\nCaption: %s\n", p->username, p->caption);
}

void freePost(Post *p) {
    while (p) {
        Post *temp = p;
        p = p->next;
        free(temp->username);
        free(temp->caption);
        freeComment(temp->comments);
        free(temp);
    }
}

