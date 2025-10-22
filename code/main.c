#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"

#define MAX_LEN 100

int validInput(int min, int max) {
    int choice;
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n'); // clear buffer
        printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        return -1;
    }
    if (choice < min || choice > max) {
        printf("Input out of range (%d-%d). Returning to main menu.\n", min, max);
        return -1;
    }
    getchar(); // consume newline
    return choice;
}

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
        choice = validInput(0, 11);
        if (choice == -1) continue;

        switch(choice) {
            case 1:
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

            case 2:
                printf("Enter post number to delete: ");
                n = validInput(1, 1000);
                if (n == -1) break;
                deletePost(n);
                break;

            case 3:
                printf("Enter post number to view: ");
                n = validInput(1, 1000);
                if (n == -1) break;
                if (viewPost(n))
                    displayPost(currPost());
                break;

            case 4:
                if (currPost())
                    displayPost(currPost());
                else
                    printf("No posts available.\n");
                break;

            case 5:
                if (previousPost())
                    displayPost(currPost());
                break;

            case 6:
                if (nextPost())
                    displayPost(currPost());
                break;

            case 7:
                printf("Enter username: ");
                fgets(username, MAX_LEN, stdin);
                username[strcspn(username, "\n")] = 0;

                printf("Enter content: ");
                fgets(content, MAX_LEN, stdin);
                content[strcspn(content, "\n")] = 0;

                addComment(username, content);
                break;

            case 8:
                printf("Enter comment number to delete: ");
                n = validInput(1, 1000);
                if (n == -1) break;
                deleteComment(n);
                break;

            case 9: {
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

            case 10:
                printf("Enter username: ");
                fgets(username, MAX_LEN, stdin);
                username[strcspn(username, "\n")] = 0;

                printf("Enter reply content: ");
                fgets(content, MAX_LEN, stdin);
                content[strcspn(content, "\n")] = 0;

                printf("Enter comment number to reply to: ");
                n = validInput(1, 1000);
                if (n == -1) break;

                addReply(username, content, n);
                break;

            case 11:
                printf("Enter comment number: ");
                n = validInput(1, 1000);
                if (n == -1) break;

                printf("Enter reply number to delete: ");
                m = validInput(1, 1000);
                if (m == -1) break;

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
