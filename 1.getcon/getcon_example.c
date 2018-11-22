#include <stdio.h>
#include <stdlib.h>
#include <selinux/selinux.h>

int main(int argc, char **argv)
{
    int rc;
    security_context_t context;

#ifdef INFO
    printf("The getcon example will retrieve and display the current "
                    "process context.\nPress return to continue\n");
    getchar();
#endif
    printf("Executing: getcon_raw(&context);\n");
    /* 
       getcon_raw: Get current context, and set context to refer to it.
       Caller must free via freecon. 
    */

    if ((rc = getcon_raw(&context)) == -1) {
        printf("Failed to obtain context\n");
        perror("getcon_raw - ERROR");
        exit(1);
    }
    printf("The returned context is:\n\t%s\n", context);
    freecon(context);
    exit(0);
}
