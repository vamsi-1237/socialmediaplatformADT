#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"

#define MAX_LEN 100

void printMenu() {
    printf("\n--- Social Media Platform ---\n");
    printf("1. Add post\n");
    printf("2. Delete post\n");
    printf("3. View post\n");
    printf("4. Current post\n");
    printf("5. Previous post\n");
    printf("6. Next post\n");
    printf("7. Add comment\n");
    printf("8. Delete comment\n");
    printf("9. View comments\n");
    printf("10. Add reply\n");
    printf("11. Delete reply\n");
    printf("0. Exit\n");
    printf("Choose an action: ");
}

int main() {
    createPlatform();

    char username[MAX_LEN];
    char content[MAX_LEN];
    char caption[MAX_LEN];
    int choice, n, m;

    while (1) {
        printMenu();
        scanf("%d", &choice);
        getchar(); // consume newline

        switch(choice) {
            case 1: // add post
                printf("Enter username: ");
                fgets(username, MAX_LEN, stdin);
                username[strcspn(username, "\n")] = 0;

                printf("Enter caption: ");
                fgets(caption, MAX_LEN, stdin);
                caption[strcspn(caption, "\n")] = 0;

                if (addPost(username, caption))
                    printf("Post added successfully.\n");
                else
                    printf("Failed to add post.\n");
                break;

            case 2: // delete post
                printf("Enter post number to delete: ");
                scanf("%d", &n);
                getchar();
                deletePost(n);
                break;

            case 3: // view post
                printf("Enter post number to view: ");
                scanf("%d", &n);
                getchar();
                if (viewPost(n))
                    displayPost(currPost());
                break;

            case 4: // current post
                if (currPost())
                    displayPost(currPost());
                else
                    printf("No posts available.\n");
                break;

            case 5: // previous post
                if (previousPost())
                    displayPost(currPost());
                break;

            case 6: // next post
                if (nextPost())
                    displayPost(currPost());
                break;

            case 7: // add comment
                printf("Enter username: ");
                fgets(username, MAX_LEN, stdin);
                username[strcspn(username, "\n")] = 0;

                printf("Enter content: ");
                fgets(content, MAX_LEN, stdin);
                content[strcspn(content, "\n")] = 0;

                addComment(username, content);
                break;

            case 8: // delete comment
                printf("Enter comment number to delete: ");
                scanf("%d", &n);
                getchar();
                deleteComment(n);
                break;

            case 9: { // view comments
                Comment *c = viewComments();
                if (!c) {
                    printf("No comments available.\n");
                    break;
                }
                while (c) {
                    printf("%s %s\n", c->username, c->content);
                    Reply *r = c->replies;
                    while (r) {
                        printf("  %s %s\n", r->username, r->content);
                        r = r->next;
                    }
                    c = c->next;
                }
                break;
            }

            case 10: // add reply
                printf("Enter username: ");
                fgets(username, MAX_LEN, stdin);
                username[strcspn(username, "\n")] = 0;

                printf("Enter reply content: ");
                fgets(content, MAX_LEN, stdin);
                content[strcspn(content, "\n")] = 0;

                printf("Enter comment number to reply to: ");
                scanf("%d", &n);
                getchar();

                addReply(username, content, n);
                break;

            case 11: // delete reply
                printf("Enter comment number: ");
                scanf("%d", &n);
                getchar();

                printf("Enter reply number to delete: ");
                scanf("%d", &m);
                getchar();

                deleteReply(n, m);
                break;

            case 0:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
