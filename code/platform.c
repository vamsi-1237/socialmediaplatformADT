#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Platform platform = {NULL, NULL};

// struct for the Post View Log (tracks viewed posts in reverse chronological order)
typedef struct postLog{
    Post* post;
    struct postLog* next;
} postLog;


postLog* viewLogHead = NULL;
static void updateViewLog(Post *p) {
    if (!p) return;

    postLog *prev = NULL, *curr = viewLogHead;

    while (curr && curr->post != p) {
        prev = curr;
        curr = curr->next;
    }

    if (curr) {
        // post found..it's already in the log.
        // if it's not the head, move it to the head.
        if (prev) {
            prev->next = curr->next;
            curr->next = viewLogHead;
            viewLogHead = curr;
        }
        // if prev is NULL, it is already the head, so no change needed.
    }
    else {

        postLog *newNode = (postLog*)malloc(sizeof(postLog));
        if (!newNode) {
            fprintf(stderr, "Memory allocation failed for postLog node.\n");
            return;
        }

        newNode->post = p;
        newNode->next = viewLogHead;
        viewLogHead = newNode;
    }
}

static Post* getPost(int n) {
    if (n <= 0) return NULL; // Handle invalid input
    Post *p = platform.posts;
    int count = 1;
    while (p && count < n) {
        p = p->next;
        count++;
    }
    return p;
}

bool addPost(const char *username, const char *caption) {
    Post *p = createPost(username, caption);

    if (!p) {
        printf("Memory allocation failed for new Post.\n");
        return false;
    }
    p->next = platform.posts;
    platform.posts = p;


    if (!platform.lastViewedPost)
        platform.lastViewedPost = p;

    return true;
}


static Comment* getComment(Post *p, int n) {
    if (!p || n <= 0) return NULL; // Handle invalid input

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

bool deletePost(int n) {
    if (!platform.posts) {
        printf("Error: No posts available.\n");
        return false;
    }
    if (n <= 0) {
        printf("Error: Post number must be 1 or greater.\n");
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

    Post *deleted_post = curr;


    if (prev)
        prev->next = curr->next;
    else
        platform.posts = curr->next;


    if (platform.lastViewedPost == deleted_post) {
        platform.lastViewedPost = platform.posts;
    }

    postLog *log_prev = NULL, *log_curr = viewLogHead;
    while (log_curr && log_curr->post != deleted_post) {
        log_prev = log_curr;
        log_curr = log_curr->next;
    }

    if (log_curr) {

        if (log_prev)
            log_prev->next = log_curr->next;
        else
            viewLogHead = log_curr->next;

        free(log_curr);
    }

    deleted_post->next = NULL;
    freePost(deleted_post);

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


    updateViewLog(p);

    return p;
}

Post* nextPost() {
    if (!platform.lastViewedPost) {
        printf("No posts available.\n");
        return NULL;
    }

    if (!platform.lastViewedPost->next) {
        printf("Next post does not exist (end of list).\n");
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
        printf("Previous post does not exist (already at the newest post).\n");
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
    if (!p) {
        printf("No post selected to add comment to.\n");
        return false;
    }

    Comment *c = createComment(username, content);
    if (!c) {
        printf("Failed to create new comment.\n");
        return false;
    }

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
    if (n <= 0) {
        printf("Error: Comment number must be 1 or greater.\n");
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

    // Clean up memory
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
    if (n <= 0) {
        printf("Error: Comment number must be 1 or greater.\n");
        return false;
    }

    Comment *c = getComment(p, n);
    if (!c) {
        printf("Comment %d does not exist.\n", n);
        return false;
    }

    Reply *r = createReply(username, content);
    if (!r) {
        fprintf(stderr, "Failed to create new reply.\n");
        return false;
    }

    r->next = NULL;
    // Replies are added to the END of the list
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
    if (n <= 0 || m <= 0) {
        printf("Error: Comment and reply numbers must be 1 or greater.\n");
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
