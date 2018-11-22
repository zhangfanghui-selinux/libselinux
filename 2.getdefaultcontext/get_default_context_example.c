#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <selinux/selinux.h>
#include <selinux/get_context_list.h>

/* Get entries from $HOME/notebook.conf file */
extern void get_config_entry(char *entry, char **content);

int main(int argc, char **argv)
{
    const char *user;
    security_context_t fromcon;
    security_context_t newcon;
    int rc;

#ifdef INFO
    printf("\nThe get_default_context example requires a user and context "
                "entry to be\nselected. The default context for the user "
                "is then obtained.\nNote: Select the context NULL entry to "
				"use the current process context.\nPress return to continue\n");
    getchar();
#endif

    get_config_entry("[user]", (char **)&user);
    get_config_entry("[raw_context]", &fromcon);
    if ((strcmp(fromcon, "NULL")) == 0)
        fromcon = NULL;

    printf("Executing: get_default_context(%s, %s, newcon);\n", user, fromcon);

    if ((rc = get_default_context(user, fromcon, &newcon)) != 0) {
		printf("Could not retrieve a default context.\n");
        perror("get_default_context - ERROR");
        free(fromcon);
        exit(1);
    }
    printf("The returned default context is: \n\t%s\n", newcon);
    freecon(fromcon);
    freecon(newcon);
    exit(0);
}
