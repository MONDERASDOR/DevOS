#include <stdio.h>
#include <string.h>
#define MAX_USERS 8
#define MAX_UNAME 32

struct user {
    char name[MAX_UNAME];
    int uid;
    int used;
};

static struct user users[MAX_USERS];
static int user_count = 0;

void user_add(const char *name, int uid) {
    if (user_count < MAX_USERS) {
        strncpy(users[user_count].name, name, MAX_UNAME-1);
        users[user_count].uid = uid;
        users[user_count].used = 1;
        user_count++;
    }
}

void user_list() {
    printf("Users:\n");
    for (int i = 0; i < user_count; i++) {
        if (users[i].used) printf("- %s (uid=%d)\n", users[i].name, users[i].uid);
    }
}
