#include <stdio.h>
#include <stdlib.h>
#include <selinux/get_default_type.h>

/* Get entries from $HOME/notebook.conf file */
extern void get_config_entry(char *entry, char **content);

int main(int argc, char **argv)
{
    char *role;
    char *type = NULL;
    int rc;

#ifdef INFO
    printf("\nThe get_default_type example requires a role to be selected.\n"
                    "The default type is then obtained from the policy "
                    "'contexts/default_type' file.\nNote: The default "
                    "type is not validated.\nPress return to continue\n");
    getchar();
#endif

    get_config_entry("[role]", (char **)&role);

    printf("Executing: get_default_type(%s, &type);\n", role);

    if ((rc = get_default_type(role, &type)) != 0) {
        printf("default type not found in 'default_type' file\n");
        perror("get_default_type - ERROR");
        exit(1);
    }

    printf("The returned default type is: %s\n", type);
    free(type);
    exit(0);
}
