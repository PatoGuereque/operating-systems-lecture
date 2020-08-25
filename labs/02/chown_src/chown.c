#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

int main (int argc, char const *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Expected 1 argument. Usage: ./chown <username>\n");
        return -1;
    }

    struct passwd *pwd = getpwnam(argv[1]);

    if (pwd == NULL) {
        fprintf(stderr, "chown failed, user '%s' not found\n", argv[1]);
        return -1;
    }

    const uid_t owner =  pwd->pw_uid;
    int rc = chown("file.txt", owner, -1);

    if (rc == -1){
        fprintf(stderr, "chown failed, errno = %d\n", errno);
        exit(1);
    }

    return 0;
}
