#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/xattr.h>

#include <selinux/selinux.h>

/* The config file that is installed in $HOME */
char *config_file = "notebook.conf";


/*
 * This is a common function to find the [entry] in the $HOME/config_file and
 * return a buffer ptr and number of entries found.
  */
int get_entry(char *entry, char **buffer)
{
	FILE *fp;
    char path[PATH_MAX];
    const char *homedir = getenv("HOME");
	char *line_buf = NULL;
	size_t line_len, buffer_len = 0;
	int rc, size, num_entries = 0;
	struct stat sb;
    char *buf_ptr;
    char *entry_buffer;

    snprintf(path, PATH_MAX, "%s/%s", homedir, config_file);
	num_entries = 0;
    if ((fp = fopen(path, "r")) == NULL) {
        printf("Cannot open %s file, so enter your own %s:\n", config_file, entry);
        return num_entries;
    }

	if (fstat(fileno(fp), &sb) < 0) {
	    printf("Cannot stat the %s file\n", path);
	    perror("FAILED");
	    exit(0);
	}

    buffer_len = sb.st_size;
	entry_buffer = malloc(buffer_len);
	if (!entry_buffer) {
        perror("buffer malloc - FAILED");
        exit(0);
    }
	bzero(entry_buffer, buffer_len);
	num_entries = 0;

    while ((rc = getline(&line_buf, &line_len, fp)) != -1) {
         if ((rc = strncmp(line_buf, entry, strlen(entry))) == 0)
            break;
    }
    buf_ptr = entry_buffer;

    while ((rc = getline(&line_buf, &line_len, fp)) != -1) {
        if (line_buf[0] == '#' || line_buf[0] == ' ' || line_buf[0] == '\n')
            continue;

        if (line_buf[0] == '[')
            break;
    /* move string into the buffer */
        num_entries++;
        size = strlen(line_buf);
        strncpy(buf_ptr, line_buf, (strlen(line_buf) - 1));
        buf_ptr += size;
    }
    fclose(fp);
    *buffer = entry_buffer;
    return num_entries;
}



/*
 * This function finds any of the [.....] entries in the $HOME/config_file
 * that are not specifically covered by the other get_*  functions.
 * It will return the selected string.
 */
void get_config_entry(char *entry, char **content)
{
	int num_entries, size, i , choice = 0;
    char *buffer;
    char *buf_ptr;
    char answer [80];
    char *return_buf;

	num_entries = 0;
    num_entries = get_entry(entry, &buffer);

/* Now have the entries in the buffer with the number of entries so now
 * process as required by the field type.
 */

    if (num_entries == 0) {
        printf("Cannot find an entry so enter your own %s:\n", entry);
        goto manual_entry;
    }

/* Now have all entries for this [xxx] area */
    buf_ptr = buffer;

 /* Now print them to screen */
    printf("\nThe available %s entries are:\n", entry);
    for (i = 0; i != num_entries; i++) {
        printf("[%d] %s\n", i+1, buf_ptr);
        size = strlen(buf_ptr);
        buf_ptr += size+1;
    }

    do {
        printf("\nEnter number for choice or press return to enter "
													"your own %s:\n", entry);
        fflush(stdin);
        fgets (answer, sizeof(answer), stdin);
        choice = strtol(answer, NULL, 10);
    } while (choice > num_entries);

    if (choice == 0) {
        free(buffer);
        printf("Enter your %s entry: ", entry);
manual_entry:
        fflush(stdin);
        fgets (answer, sizeof(answer), stdin);
        size = strlen(answer);
        answer[size-1] = 0;
        return_buf = malloc(size);
        strncpy(return_buf, answer, size);
        *content = return_buf;
        printf("The chosen %s is: %s\n", entry, *content);
        return;
    }

    /* Choice is a good value */
    buf_ptr = buffer;
    i = 1;
    while (1) {
        size = strlen(buf_ptr);
        if (i == choice)
            break;
        buf_ptr += size+1;
        i++;
    }

    /* Get the space for return field */
	return_buf = malloc(size+1);
	if (!return_buf) {
        perror("return_buf malloc - FAILED");
        exit(0);
    }
    strncpy(return_buf, buf_ptr, size);
    return_buf[size] = '\0';
    *content = return_buf;

    free(buffer);
    printf("The chosen %s is: %s\n", entry, *content);
    return;
}


/*
 * This function finds the [context_list] entries in the $HOME/config_file
 * and returns a list of the entries. This is for the query_user_context()
 * function.
 */
void get_config_list(char *entry, char ***list)
{
	int num_entries, i, size;
    char *buf_ptr;
    char **entry_ptr;
    char *buffer;

	num_entries = 0;
    num_entries = get_entry(entry, &buffer);

/*
 * Now have the entries in the buffer with the number of entries so now
 * process as required by the field type.
 */
    if (num_entries == 0) {
        printf("Cannot find an entry for %s so quitting:\n", entry);
        exit(0);
    }

    buf_ptr = buffer;
    /* Got here and found all entries ok */
	entry_ptr = (char **)malloc(sizeof(char *) * num_entries);
	if (!entry_ptr) {
        perror("entry_ptr malloc - FAILED");
        exit(0);
    }

    for (i = 0; i < num_entries; i++) {
        entry_ptr[i] = buf_ptr;
        size = strlen(buf_ptr);
        buf_ptr += size+1;
    }

    entry_ptr[i] = NULL;
    *list = entry_ptr;
    free(buffer);
    return;
}




/*
 * This function finds the [boolean_list] entries in the $HOME/config_file and
 * returns a list of the entries. This is for the security_set_boolean_list()
 * function.
 */
void get_config_boollist(char *entry, SELboolean ** boollist, size_t * boolcnt)
{
	int num_entries, i, n, size;
    char *buffer;
    char *buf_ptr;
    SELboolean *bool_list;

	num_entries = 0;
    num_entries = get_entry(entry, &buffer);

/*
 * Now have the entries in the buffer with the number of entries so now
 * process as required by the field type.
 */
    if (num_entries == 0) {
        printf("Cannot find an entry for %s so quitting:\n", entry);
        exit(0);
    }

    buf_ptr = buffer;
    /* Got here and found all entries ok */
    bool_list = malloc(num_entries * 100);
    if (!bool_list) {
        perror("bool_list malloc - FAILED");
        exit(0);
    }

    /* Now get the entries and convert to the SELboolean struct format */
    for (i = 0; i < num_entries; i++) {
        size = strlen(buf_ptr);
        /* This holds a ptr to the boolean name in the buffer */
        bool_list[i].name = buf_ptr;
        n = strcspn(buf_ptr, "=");
        *(buf_ptr+n) = '\0';
        bool_list[i].value = atoi(buf_ptr+n+1);
        buf_ptr += size+1;
    }

    *boollist = bool_list;
    *boolcnt = num_entries;
    /* do not free the buffer as it holds the boolean names */
    return;
}
