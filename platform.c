#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Platform platform = {NULL, NULL};

// Helper: get nth recent post (1-based)
static Post* getPost(int n) {
    Post *p = platform.posts;
    int count = 1;
    while (p && count < n) {
        p = p->next;
        count++;
    }
    return p;
}

// Helper function: get the n-th recent comment of a post
static Comment* getComment(Post *p, int n) {
    if (!p) return NULL;

    Comment *c = p->comments;
    int count = 1;
    while (c && count < n) {
        c = c->next;
        count++;
    }
    return c; // returns NULL if n > number of comments
}


Platform* createPlatform() {
    platform.posts = NULL;
    platform.lastViewedPost = NULL;
    return &platform;
}

bool addPost(const char *username, const char *caption) {
    Post *p = createPost(username, caption);
    if (!p) return false;

    p->next = platform.posts;
    platform.posts = p;

    if (!platform.lastViewedPost)
        platform.lastViewedPost = p;

    return true;
}

bool deletePost(int n) {
    if (!platform.posts) {
        printf("Error: No posts available.\n");
        return false;
    }

    Post *prev = NULL, *curr = platform.posts;
    int count = 1;
    while (curr && count < n) {
        prev = curr;
        curr = curr->next;
        count++;
    }

    if (!curr) {
        printf("Error: Invalid post number %d.\n", n);
        return false;
    }

    if (prev)
        prev->next = curr->next;
    else
        platform.posts = curr->next;

    if (platform.lastViewedPost == curr)
        platform.lastViewedPost = platform.posts;

    curr->next = NULL;
    freePost(curr);

    printf("Post %d deleted successfully.\n", n);
    return true;
}

Post* viewPost(int n) {
    Post *p = getPost(n);
    if (!p) {
        printf("Post %d does not exist.\n", n);
        return NULL;
    }
    platform.lastViewedPost = p;
    return p;
}

Post* nextPost() {
    if (!platform.lastViewedPost) {
        printf("No posts available.\n");
        return NULL;
    }

    if (!platform.lastViewedPost->next) {
        printf("Next post does not exist.\n");
        return platform.lastViewedPost;
    }

    platform.lastViewedPost = platform.lastViewedPost->next;
    return platform.lastViewedPost;
}

Post* previousPost() {
    if (!platform.lastViewedPost) {
        printf("No posts available.\n");
        return NULL;
    }

    Post *p = platform.posts;
    Post *prev = NULL;
    while (p && p != platform.lastViewedPost) {
        prev = p;
        p = p->next;
    }

    if (!prev) {
        printf("Previous post does not exist.\n");
        return platform.lastViewedPost;
    }

    platform.lastViewedPost = prev;
    return platform.lastViewedPost;
}


Post* currPost() {
    if (!platform.lastViewedPost)
        return platform.posts;
    return platform.lastViewedPost;
}

bool addComment(const char *username, const char *content) {
    Post *p = currPost();
    if (!p) return false;

    Comment *c = createComment(username, content);
    if (!c) return false;

    c->next = NULL;
    if (!p->comments)
        p->comments = c;
    else {
        Comment *temp = p->comments;
        while (temp->next) temp = temp->next;
        temp->next = c;
    }
    return true;
}

bool deleteComment(int n) {
    Post *p = currPost();
    if (!p) {
        printf("No post selected to delete comment from.\n");
        return false;
    }

    Comment *prev = NULL, *curr = p->comments;
    int count = 1;
    while (curr && count < n) {
        prev = curr;
        curr = curr->next;
        count++;
    }

    if (!curr) {
        printf("Comment %d does not exist.\n", n);
        return false;
    }

    if (prev) prev->next = curr->next;
    else p->comments = curr->next;

    curr->next = NULL;
    freeComment(curr);
    return true;
}

Comment* viewComments() {
    Post *p = currPost();
    return p ? p->comments : NULL;
}

bool addReply(const char *username, const char *content, int n) {
    Post *p = currPost();
    if (!p) {
        printf("No post selected to add reply.\n");
        return false;
    }

    Comment *c = getComment(p, n);
    if (!c) {
        printf("Comment %d does not exist.\n", n);
        return false;
    }

    Reply *r = createReply(username, content);
    if (!r) return false;

    r->next = NULL;
    if (!c->replies) c->replies = r;
    else {
        Reply *temp = c->replies;
        while (temp->next) temp = temp->next;
        temp->next = r;
    }
    return true;
}

bool deleteReply(int n, int m) {
    Post *p = currPost();
    if (!p) {
        printf("No post selected to delete reply.\n");
        return false;
    }

    Comment *c = getComment(p, n);
    if (!c) {
        printf("Comment %d does not exist.\n", n);
        return false;
    }

    Reply *prev = NULL, *curr = c->replies;
    int count = 1;
    while (curr && count < m) {
        prev = curr;
        curr = curr->next;
        count++;
    }

    if (!curr) {
        printf("Reply %d to Comment %d does not exist.\n", m, n);
        return false;
    }

    if (prev) prev->next = curr->next;
    else c->replies = curr->next;

    curr->next = NULL;
    freeReply(curr);
    return true;
}


