/*
 * System groups - groups with GID within specified range. Usually these GIDs are represented
 * by smaller numbers than the regular GIDs. Examples: 24(cdrom), 29(audio), 30(dip)...
 */

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <grp.h>

int main() {
    uid_t uid = getuid();
    struct passwd *pwuid = getpwuid(uid);
    if (pwuid == NULL) {
        fprintf(stderr, "Error calling getpwuid.");
        exit(EXIT_FAILURE);
    }
    
    int ngroups = 255;
    gid_t *groups = malloc(ngroups * sizeof(gid_t));
    struct group *gr;
    
    if (getgrouplist(pwuid->pw_name, pwuid->pw_gid, groups, &ngroups) == -1) {
        fprintf(stderr, "Error calling getgrouplist.");
        exit(EXIT_FAILURE);
    }
    
    printf("uid=%d(%s)", uid, pwuid->pw_name);
    printf(" gid=%d(%s)", pwuid->pw_gid, pwuid->pw_name);
    
    int j;
    
    printf(" groups=");
    
    for (j = 0; j < ngroups; j++) {
        printf("%d", groups[j]);
        gr = getgrgid(groups[j]);
        if (gr != NULL) {
            printf("(%s)", gr->gr_name);
        }
        if (j != ngroups - 1) {
            printf(",");
        }
    }
    printf("\n");
    exit(EXIT_SUCCESS);
}