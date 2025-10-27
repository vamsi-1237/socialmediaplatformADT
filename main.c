#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "post.h"
#include "comment.h"
#include "reply.h"

#define MAX_LINE_LENGTH 256

void print_post_info(Post *p) {
    if (p) {
        printf("%s %s\n", p->username, p->caption);
    }
}

void print_comments_recursive(Post *p) {
    if (!p) {
        return;
    }

    Comment *c = p->comments;
    while (c) {

        printf("%s %s\n", c->username, c->content);
        Reply *r = c->replies;
        while (r) {
            printf("%s %s\n", r->username, r->content);
            r = r->next;
        }

        c = c->next;
    }
}

int main()
{
    char line[MAX_LINE_LENGTH];
    char *command;
    Post *p;


    const char *delim = " \t\n";
    printf("Enter double space to end input:\n");
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {


        line[strcspn(line, "\r\n")] = 0;


        command = strtok(line, delim);

        if(strcmp(command,"  ") == 0){
            break;
        }

        if (command == NULL) {
            continue;
        }

        if (strcmp(command, "create_platform") == 0) {
            createPlatform();
        }


        else if (strcmp(command, "add_post") == 0) {
            char *user = strtok(NULL, delim);
            char *caption = strtok(NULL, delim);
            if (user && caption) {
                addPost(user, caption);
            }
        }
        else if (strcmp(command, "delete_post") == 0) {
            char *n_str = strtok(NULL, delim);
            if (n_str) {
                deletePost(atoi(n_str));
            }
        }
        else if (strcmp(command, "view_post") == 0) {
            char *n_str = strtok(NULL, delim);
            if (n_str) {
                p = viewPost(atoi(n_str));
                print_post_info(p);
            }
        }
        else if (strcmp(command, "current_post") == 0) {
            p = currPost();
            print_post_info(p);
        }
        else if (strcmp(command, "previous_post") == 0) {
            p = previousPost();
            print_post_info(p);
        }
        else if (strcmp(command, "next_post") == 0) {
            p = nextPost();
            print_post_info(p);
        }


        else if (strcmp(command, "add_comment") == 0) {
            char *user = strtok(NULL, delim);
            char *content = strtok(NULL, delim);
            if (user && content) {
                addComment(user, content);
            }
        }
        else if (strcmp(command, "delete_comment") == 0) {
            char *n_str = strtok(NULL, delim);
            if (n_str) {
                deleteComment(atoi(n_str));
            }
        }
        else if (strcmp(command, "view_comments") == 0) {
            print_comments_recursive(currPost());
        }
        else if (strcmp(command, "add_reply") == 0) {
            char *user = strtok(NULL, delim);
            char *content = strtok(NULL, delim);
            char *n_str = strtok(NULL, delim);
            if (user && content && n_str) {
                addReply(user, content, atoi(n_str));
            }
        }
        else if (strcmp(command, "delete_reply") == 0) {
            char *n_str = strtok(NULL, delim);
            char *m_str = strtok(NULL, delim);
            if (n_str && m_str) {
                deleteReply(atoi(n_str), atoi(m_str));
            }
        }
    }


    return 0;
}
