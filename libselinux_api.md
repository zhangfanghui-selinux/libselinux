= libselinux 2.3 Library Functions =
These functions have been taken from the following header files of <tt>libselinux</tt> version 2.3:

: /usr/include/selinux/avc.h
: /usr/include/selinux/context.h
: /usr/include/selinux/get_context_list.h
: /usr/include/selinux/get_default_type.h
: /usr/include/selinux/label.h
: /usr/include/selinux/selinux.h

The appropriate '''man'''(3) pages should consulted for detailed usage.


{| border="1"
! Function Name
! Description
! Header File

|-
| avc_add_callback
| Register a callback for security events.
| avc.h

|-
| avc_audit
| Audit the granting or denial of permissions in accordance with the policy. This function is typically called by '''avc_has_perm'''(3) after a permission check, but can also be called directly by callers who use '''avc_has_perm_noaudit'''(3) in order to separate the permission check from the auditing. For example, this separation is useful when the permission check must be performed under a lock, to allow the lock to be released before calling the auditing code.
| avc.h

|-
| avc_av_stats
| Log AV table statistics. Logs a message with information about the size and distribution of the access vector table. The audit callback is used to print the message.
| avc.h

|-
| avc_cache_stats
| Get cache access statistics. Fill the supplied structure with information about AVC activity since the last call to '''avc_init'''(3) or '''avc_reset'''(3).
| avc.h

|-
| avc_cleanup
| Remove unused SIDs and AVC entries.

Search the SID table for SID structures with zero reference counts, and remove them along with all AVC entries that reference them. This can be used to return memory to the system.
| avc.h

|-
| avc_compute_create
| Compute SID for labeling a new object. Call the security server to obtain a context for labeling a new object. Look up the context in the SID table, making a new entry if not found.
| avc.h

|-
| avc_compute_member
| Compute SID for polyinstantation.

Call the security server to obtain a context for labeling an object instance. Look up the context in the SID table, making a new entry if not found.
| avc.h

|-
| avc_context_to_sid

avc_context_to_sid_raw
| Get SID for context. Look up security context <tt>ctx</tt> in SID table, making a new entry if <tt>ctx</tt> is not found. Store a pointer to the SID structure into the memory referenced by <tt>sid</tt>, returning 0 on success or -1 on error with <tt>errno</tt> set.
| avc.h

|-
| avc_destroy
| Free all AVC structures.

Destroy all AVC structures and free all allocated memory. User-supplied locking, memory, and audit callbacks will be retained, but security-event callbacks will not. All SID's will be invalidated. User must call '''avc_init'''(3) if further use of AVC is desired.
| avc.h

|-
| avc_entry_ref_init
| Initialize an AVC entry reference.

Use this macro to initialize an avc entry reference structure before first use. These structures are passed to '''avc_has_perm'''(3), which stores cache entry references in them. They can increase performance on repeated queries.
| avc.h

|-
| avc_get_initial_sid
| Get SID for an initial kernel security identifier.

Get the context for an initial kernel security identifier specified by name using '''security_get_initial_context'''(3) and then call '''avc_context_to_sid'''(3) to get the corresponding SID.
| avc.h

|-
| avc_has_perm
| Check permissions and perform any appropriate auditing.

Check the AVC to determine whether the requested permissions are granted for the SID pair (ssid, tsid), interpreting the permissions based on tclass, and call the security server on a cache miss to obtain a new decision and add it to the cache. Update aeref to refer to an AVC entry with the resulting decisions. Audit the granting or denial of permissions in accordance with the policy. Return 0 if all requested permissions are granted, -1 with errno set to EACCES if any permissions are denied or to another value upon other errors.
| avc.h

|-
| avc_has_perm_noaudit
| Check permissions but perform no auditing. Check the AVC to determine whether the requested permissions are granted for the SID pair (ssid, tsid), interpreting the permissions based on tclass, and call the security server on a cache miss to obtain a new decision and add it to the cache. Update aeref to refer to an AVC entry with the resulting decisions, and return a copy of the decisions in avd. Return 0 if all requested permissions are granted, -1 with errno set to EACCES if any permissions are denied, or to another value upon other errors. This function is typically called by '''avc_has_perm'''(3), but may also be called directly to separate permission checking from auditing, e.g. in cases where a lock must be held for the check but should be released for the auditing.
| avc.h

|-
| avc_init (deprecated)
| Use <tt>avc_open</tt>

Initialize the AVC. Initialize the access vector cache. Return 0 on success or -1 with errno set on failure. If msgprefix is NULL, use "uavc". If any callback structure references are NULL, use default methods for those callbacks (see the definition of the callback structures).
| avc.h

|-
| avc_netlink_acquire_fd
| Create a netlink socket and connect to the kernel.
| avc.h

|-

| avc_netlink_check_nb
| Wait for netlink messages from the kernel.
| avc.h

|-

| avc_netlink_close
| Close the netlink socket.
| avc.h

|-

| avc_netlink_loop
| Acquire netlink socket fd. Allows the application to manage messages from the netlink socket in its own main loop.
| avc.h

|-

| avc_netlink_open
| Release netlink socket fd. Returns ownership of the netlink socket to the library.
| avc.h

|-

| avc_netlink_release_fd
| Check netlink socket for new messages. Called by the application when using <tt>'''avc_netlink_acquire_fd'''(3)</tt> to process kernel netlink events.
| avc.h

|-

| avc_open
| Initialize the AVC. This function is identical to '''avc_init'''(3) except the message prefix is set to "avc" and any callbacks desired should be specified via '''selinux_set_callback'''(3).
| avc.h

|-
| avc_reset
| Flush the cache and reset statistics. Remove all entries from the cache and reset all access statistics (as returned by '''avc_cache_stats'''(3)) to zero. The SID mapping is not affected. Return 0 on success, -1 with errno set on error.
| avc.h

|-
| avc_sid_stats
| Log SID table statistics. Log a message with information about the size and distribution of the SID table. The audit callback is used to print the message.
| avc.h

|-
| avc_sid_to_context

avc_sid_to_context_raw
| Get copy of context corresponding to SID. Return a copy of the security context corresponding to the input sid in the memory referenced by ctx. The caller is expected to free the context with '''freecon'''(3). Return 0 on success, -1 on failure, with errno set to ENOMEM if insufficient memory was available to make the copy, or EINVAL if the input SID is invalid.
| avc.h

|-
| checkPasswdAccess (deprecated)
| Use <tt>'''selinux_check_passwd_access'''(3)</tt> or preferably <tt>'''selinux_check_access'''(3)</tt>

Check a permission in the passwd class. Return 0 if granted or -1 otherwise.
| selinux.h

|-
| context_free
| Free the storage used by a context.
| context.h

|-
| context_new
| Return a new context initialized to a context string.
| context.h

|-
| context_range_get
| Get a pointer to the range.
| context.h

|-
| context_range_set
| Set the range component. Returns nonzero if unsuccessful.
| context.h

|-
| context_role_get
| Get a pointer to the role.
| context.h

|-
| context_role_set
| Set the role component. Returns nonzero if unsuccessful.
| context.h

|-
| context_str
| Return a pointer to the string value of context_t. Valid until the next call to context_str or context_free for the same context_t*.
| context.h

|-
| context_type_get
| Get a pointer to the type.
| context.h

|-
| context_type_set
| Set the type component. Returns nonzero if unsuccessful.
| context.h

|-
| context_user_get
| Get a pointer to the user.
| context.h

|-
| context_user_set
| Set the user component. Returns nonzero if unsuccessful.
| context.h

|-
| fgetfilecon

fgetfilecon_raw
| Wrapper for the xattr API - Get file context, and set <nowiki>*con</nowiki> to refer to it. Caller must free via freecon.
| selinux.h

|-
| fini_selinuxmnt
| Clear <tt>selinuxmnt</tt> variable and free allocated memory.
| selinux.h

|-


| freecon
| Free the memory allocated for a context by any of the get* calls.
| selinux.h

|-



| freeconary
| Free the memory allocated for a context array by '''security_compute_user'''(3).
| selinux.h

|-



| fsetfilecon

fsetfilecon_raw
| Wrapper for the xattr API - Set file context.
| selinux.h

|-



| get_default_context
| Get the default security context for a user session for 'user' spawned by 'fromcon' and set <nowiki>*newcon</nowiki> to refer to it. The context will be one of those authorized by the policy, but the selection of a default is subject to user customizable preferences. If 'fromcon' is NULL, defaults to current context. Returns 0 on success or -1 otherwise. Caller must free via freecon. 
| get_context_list.h

|-



| get_default_context_with_level
| Same as '''get_default_context'''(3), but use the provided MLS level rather than the default level for the user. 
| get_context_list.h

|-



| get_default_context_with_role
| Same as '''get_default_context'''(3), but only return a context that has the specified role.
| get_context_list.h

|-



| get_default_context_with_rolelevel
| Same as '''get_default_context'''(3), but only return a context that has the specified role and level.
| get_context_list.h

|-



| get_default_type
| Get the default type (domain) for 'role' and set 'type' to refer to it. Caller must free via '''free'''(3). Return 0 on success or -1 otherwise. 
| get_default_type.h

|-



| get_ordered_context_list
| Get an ordered list of authorized security contexts for a user session for 'user' spawned by 'fromcon' and set <nowiki>*conary</nowiki> to refer to the NULL-terminated array of contexts. Every entry in the list will be authorized by the policy, but the ordering is subject to user customizable preferences. Returns number of entries in <nowiki>*conary</nowiki>. If 'fromcon' is NULL, defaults to current context. Caller must free via '''freeconary'''(3).
| get_context_list.h

|-



| get_ordered_context_list_with_level
| Same as '''get_ordered_context_list'''(3), but use the provided MLS level rather than the default level for the user.
| get_context_list.h

|-



| getcon

getcon_raw
| Get current context, and set <nowiki>*con</nowiki> to refer to it. Caller must free via '''freecon'''(3). 
| selinux.h

|-



| getexeccon

getexeccon_raw
| Get exec context, and set <nowiki>*con</nowiki> to refer to it. Sets <nowiki>*con</nowiki> to NULL if no exec context has been set, i.e. using default. If non-NULL, caller must free via '''freecon'''(3).
| selinux.h

|-



| getfilecon

getfilecon_raw
| Wrapper for the xattr API - Get file context, and set <nowiki>*con</nowiki> to refer to it. Caller must free via '''freecon'''(3).
| selinux.h

|-



| getfscreatecon

getfscreatecon_raw
| Get fscreate context, and set <nowiki>*con</nowiki> to refer to it. Sets <nowiki>*con</nowiki> to NULL if no fs create context has been set, i.e. using default.If non-NULL, caller must free via '''freecon'''(3).
| selinux.h

|-



| getkeycreatecon

getkeycreatecon_raw
| Get keycreate context, and set <nowiki>*con</nowiki> to refer to it. Sets <nowiki>*con</nowiki> to NULL if no key create context has been set, i.e. using default. If non-NULL, caller must free via '''freecon'''(3).
| selinux.h

|-



| getpeercon

getpeercon_raw
| Wrapper for the socket API - Get context of peer socket, and set <nowiki>*con</nowiki> to refer to it. Caller must free via <tt>'''freecon'''(3)</tt>.
| selinux.h

|-



| getpidcon

getpidcon_raw
| Get context of process identified by pid, and set <nowiki>*con</nowiki> to refer to it. Caller must free via <tt>'''freecon'''(3)</tt>.
| selinux.h

|-



| getprevcon

getprevcon_raw
| Get previous context (prior to last exec), and set <nowiki>*con</nowiki> to refer to it. Caller must free via <tt>'''freecon'''</tt>(3).
| selinux.h

|-



| getseuser
| Get the SELinux username and level to use for a given Linux username and service. These values may then be passed into the get_ordered_context_list* and get_default_context* functions to obtain a context for the user. Returns 0 on success or -1 otherwise. Caller must free the returned strings via '''free'''(3).
| selinux.h

|-



| getseuserbyname
| Get the SELinux username and level to use for a given Linux username. These values may then be passed into the get_ordered_context_list* and get_default_context* functions to obtain a context for the user. Returns 0 on success or -1 otherwise. Caller must free the returned strings via '''free'''(3).
| selinux.h

|-



| getsockcreatecon

getsockcreatecon_raw
| Get sockcreate context, and set <nowiki>*con</nowiki> to refer to it. Sets <nowiki>*con</nowiki> to NULL if no socket create context has been set, i.e. using default. If non-NULL, caller must free via '''freecon'''(3).
| selinux.h

|-



| init_selinuxmnt
| There is a man page for this, however it is not a user accessable function (internal use only - although the <tt>fini_selinuxmnt</tt> is reachable).
| <center>-</center>

|-



| is_context_customizable
| Returns whether a file context is customizable, and should not be relabeled.
| selinux.h

|-



| is_selinux_enabled
| Return 1 if running on a SELinux kernel, or 0 if not or -1 for error.
| selinux.h

|-



| is_selinux_mls_enabled
| Return 1 if we are running on a SELinux MLS kernel, or 0 otherwise.
| selinux.h

|-



| lgetfilecon

lgetfilecon_raw
| Wrapper for the xattr API - Get file context, and set <nowiki>*con</nowiki> to refer to it. Caller must free via '''freecon'''(3).
| selinux.h

|-



| lsetfilecon

lsetfilecon_raw
| Wrapper for the xattr API- Set file context for symbolic link.
| selinux.h

|-



| manual_user_enter_context
| Allow the user to manually enter a context as a fallback if a list of authorized contexts could not be obtained. Caller must free via '''freecon'''(3). Returns 0 on success or -1 otherwise. 
| get_context_list.h

|-



| matchmediacon
| Match the specified media and against the media contexts configuration and set <nowiki>*con</nowiki> to refer to the resulting context. Caller must free con via freecon.
| selinux.h

|-



| matchpathcon
| Match the specified pathname and mode against the file context sconfiguration and set <nowiki>*con</nowiki> to refer to the resulting context.'mode' can be 0 to disable mode matching. Caller must free via freecon. If '''matchpathcon_init'''(3) has not already been called, then this function will call it upon its first invocation with a NULL path.
| selinux.h

|-



| matchpathcon_checkmatches
| Check to see whether any specifications had no matches and report them. The 'str' is used as a prefix for any warning messages.
| selinux.h

|-



| matchpathcon_filespec_add
| Maintain an association between an inode and a specification index, and check whether a conflicting specification is already associated with the same inode (e.g. due to multiple hard links). If so, then use the latter of the two specifications based on their order in the file contexts configuration. Return the used specification index. 
| selinux.h

|-



| matchpathcon_filespec_destroy
| Destroy any inode associations that have been added, e.g. to restart for a new filesystem. 
| selinux.h

|-



| matchpathcon_filespec_eval
| Display statistics on the hash table usage for the associations.
| selinux.h

|-



| matchpathcon_fini
| Free the memory allocated by matchpathcon_init.
| selinux.h

|-



| matchpathcon_index 
| Same as '''matchpathcon'''(3), but return a specification index for later use in a '''matchpathcon_filespec_add'''(3) call.
| selinux.h

|-



| matchpathcon_init
| Load the file contexts configuration specified by 'path' into memory for use by subsequent matchpathcon calls. If 'path' is NULL, then load the active file contexts configuration, i.e. the path returned by '''selinux_file_context_path'''(3). Unless the MATCHPATHCON_BASEONLY flag has been set, this function also checks for a 'path'.homedirs file and a 'path'.local file and loads additional specifications from them if present.
| selinux.h

|-



| matchpathcon_init_prefix
| Same as '''matchpathcon_init'''(3), but only load entries with regexes that have stems that are prefixes of 'prefix'.
| selinux.h

|-



| mode_to_security_class
| Translate mode_t to a security class string name (e.g. <tt>S_ISREG</tt> = "<tt>file</tt>").
| selinux.h

|-



| print_access_vector
| Display an access vector in a string representation.
| selinux.h

|-



| query_user_context
| Given a list of authorized security contexts for the user, query the user to select one and set <nowiki>*newcon</nowiki> to refer to it. Caller must free via '''freecon'''(3). Returns 0 on sucess or -1 otherwise. 
| get_context_list.h

|-



| realpath_not_final
| Resolve all of the symlinks and relative portions of a pathname, but NOT the final component (same a <tt>'''realpath'''(3)</tt> unless the final component is a symlink. Resolved path must be a path of size <tt>PATH_MAX + 1</tt>.
| selinux.h

|-



| rpm_execcon
| Execute a helper for rpm in an appropriate security context.
| selinux.h

|-



| security_av_perm_to_string
| Convert access vector permissions to string names.
| selinux.h

|-



| security_av_string
| Returns an access vector in a string representation. User must free the returned string via '''free'''(3).
| selinux.h

|-



| security_canonicalize_context

security_canonicalize_context_raw
| Canonicalize a security context. Returns a pointer to the canonical (primary) form of a security context in <tt>canoncon</tt> that the kernel is using rather than what is provided by the userspace application in <tt>con</tt>. 
| selinux.h

|-



| security_check_context

security_check_context_raw
| Check the validity of a security context.
| selinux.h

|-



| security_class_to_string
| Convert security class values to string names.
| selinux.h

|-



| security_commit_booleans
| Commit the pending values for the booleans.
| selinux.h

|-



| security_compute_av

security_compute_av_raw
| Compute an access decision. 

Queries whether the policy permits the source context <tt>scon</tt> to access the target context <tt>tcon</tt> via class <tt>tclass</tt> with the <tt>requested</tt> access vector. The decision is returned in <tt>avd</tt>.
| selinux.h

|-



| security_compute_av_flags

security_compute_av__flags_raw
| Compute an access decision and return the flags. 

Queries whether the policy permits the source context <tt>scon</tt> to access the target context <tt>tcon</tt> via class <tt>tclass</tt> with the <tt>requested</tt> access vector. The decision is returned in <tt>avd</tt>. that has an additional <tt>'''flags'''</tt> entry. Currently the only flag defined is SELINUX_AVD_FLAGS_PERMISSIVE that indicates the decision was computed on a permissive domain (i.e. the <tt>'''permissive'''</tt> policy language statement has been used in policy or <tt>'''semanage'''(8)</tt> has been used to set the domain in permissive mode). Note this does not indicate that SELinux is running in permissive mode, only the <tt>scon</tt> domain.
| selinux.h

|-



| security_compute_create

security_compute_create_raw
| Compute a labeling decision and set <nowiki>*newcon</nowiki> to refer to it. Caller must free via '''freecon'''(3).
| selinux.h

|-



| security_compute_create_name

security_compute_create_name_raw
| This is identical to<tt> '''security_compute_create'''(3)</tt> but also takes the name of the new object in creation as an argument.

When a [#5.7.6.type_transition |outline type_transition] </tt>rule on the given class and the <tt>scon</tt> / <tt>tcon</tt> pair has an object name extension, <tt>newcon</tt> will be returned according to the policy. Note that this interface is only supported on the kernels 2.6.40 or later. For older kernels the object name is ignored.
| selinux.h

|-



| security_compute_member

security_compute_member_raw
| Compute a polyinstantiation member decision and set <nowiki>*newcon</nowiki> to refer to it. Caller must free via '''freecon'''(3).
| selinux.h

|-



| security_compute_relabel

security_compute_relabel_raw
| Compute a relabeling decision and set <nowiki>*newcon</nowiki> to refer to it. Caller must free via '''freecon'''(3).
| selinux.h

|-



| security_compute_user

security_compute_user_raw
| Compute the set of reachable user contexts and set <nowiki>*con</nowiki> to refer to the NULL-terminated array of contexts. Caller must free via '''freeconary'''(3). 
| selinux.h

|-



| security_deny_unknown
| Get the behavior for undefined classes / permissions.
| selinux.h

|-



| security_disable
| Disable SELinux at runtime (must be done prior to initial policy load).
| selinux.h

|-



| security_get_boolean_active
| Get the active value for the boolean.
| selinux.h

|-



| security_get_boolean_names
| Get the boolean names
| selinux.h

|-



| security_get_boolean_pending
| Get the pending value for the boolean.
| selinux.h

|-



| security_get_initial_context

security_get_initial_context_raw
| Get the context of an initial kernel security identifier by name. Caller must free via '''freecon'''(3).
| selinux.h

|-



| security_getenforce
| Get the enforce flag value.
| selinux.h

|-



| security_load_booleans
| Load policy boolean settings. Path may be NULL, in which case the booleans are loaded from the active policy boolean configuration file.
| selinux.h

|-



| security_load_policy
| Load a policy configuration.
| selinux.h

|-



| security_policyvers
| Get the policy version number.
| selinux.h

|-



| security_set_boolean
| Set the pending value for the boolean.
| selinux.h

|-



| security_set_boolean_list
| Save a list of booleans in a single transaction.
| selinux.h

|-



| security_setenforce
| Set the enforce flag value.
| selinux.h

|-



| selabel_close
| Destroy the specified handle, closing files, freeing allocated memory, etc. The handle may not be further used after it has been closed.
| label.h

|-



| selabel_lookup

selabel_lookup_raw
| Perform a labeling lookup operation. Return 0 on success, -1 with errno set on failure. The <tt>key</tt> and <tt>type</tt> arguments are the inputs to the lookup operation; appropriate values are dictated by the backend in use. The result is returned in the memory pointed to by con and must be freed by freecon.
| label.h

|-



| selabel_open
| Create a labeling handle.

Open a labeling backend for use. The available backend identifiers are:

SELABEL_CTX_FILE - file_contexts.

SELABEL_CTX_MEDIA - media contexts.

SELABEL_CTX_X - x_contexts.

<tt>SELABEL_CTX_DB</tt> - SE-PostgreSQL contexts.

SELABEL_CTX_ANDROID_PROP - <tt>property</tt>_contexts.

Options may be provided via the opts parameter; available options are:

SELABEL_OPT_UNUSED - no-op option, useful for unused slots in an array of options.

SELABEL_OPT_VALIDATE - validate contexts before returning them (boolean value).

SELABEL_OPT_BASEONLY - don't use local customizations to backend data (boolean value).

SELABEL_OPT_PATH - specify an alternate path to use when loading backend data.

SELABEL_OPT_SUBSET - select a subset of the search space as an optimization (file backend).

Not all options may be supported by every backend. Return value is the created handle on success or NULL with errno set on failure.
| label.h

|-



| selabel_stats
| Log a message with information about the number of queries performed, number of unused matching entries, or other operational statistics. Message is backend-specific, some backends may not output a message.
| label.h

|-



| selinux_binary_policy_path
| Return path to the binary policy file under the policy root directory.
| selinux.h

|-



| selinux_booleans_path
| Return path to the booleans file under the policy root directory.
| selinux.h

|-



| selinux_boolean_sub
| Reads the <tt>/etc/selinux/TYPE/booleans.subs_dist</tt> file looking for a record with <tt>boolean_name</tt>. If a record exists <tt>'''selinux_boolean_sub'''(3)</tt> returns the translated name otherwise it returns the original name. The returned value needs to be freed. On failure NULL will be returned.
| selinux.h

|-



| selinux_booleans_subs_path
| Returns the path to the <tt>booleans.subs_dist</tt> configuration file.
| selinux.h

|-



| selinux_check_access
| Used to check if the source context has the access permission for the specified class on the target context. Note that the permission and class are reference strings.

The <tt>aux</tt> parameter may reference supplemental auditing information. 

Auditing is handled as described in <tt>'''avc_audit'''(3)</tt>.

See <tt>'''security_deny_unknown'''(3)</tt> for how the <tt>deny_unknown</tt> flag can influence policy decisions.
| selinux.h

|-



| selinux_check_passwd_access
| Check a permission in the passwd class. Return 0 if granted or -1 otherwise.

Replaced by <tt>'''selinux_check_access'''(3)</tt>
| selinux.h

|-



| selinux_check_securetty_context 
| Check if the tty_context is defined as a securetty<nowiki>. Return 0 if secure, < 0 otherwise.</nowiki>
| selinux.h

|-



| selinux_colors_path
| Return path to file under the policy root directory.
| selinux.h

|-



| selinux_contexts_path
| Return path to contexts directory under the policy root directory.
| selinux.h

|-



| selinux_current_policy_path
| Return path to the current policy.
| selinux.h

|-



| selinux_customizable_types_path
| Return path to customizable_types file under the policy root directory.
| selinux.h

|-



| selinux_default_context_path
| Return path to default_context file under the policy root directory.
| selinux.h

|-



| selinux_default_type_path
| Return path to <tt>default_type</tt> file.
| get_default_type.h

|-



| selinux_failsafe_context_path
| Return path to failsafe_context file under the policy root directory.
| selinux.h

|-



| selinux_file_context_cmp
| Compare two file contexts, return 0 if equivalent.
| selinux.h

|-



| selinux_file_context_homedir_path
| Return path to <tt>file_context.homedir</tt> file under the policy root directory.
| selinux.h

|-



| selinux_file_context_local_path
| Return path to <tt>file_context.local</tt> file under the policy root directory.
| selinux.h

|-



| selinux_file_context_path
| Return path to <tt>file_context</tt> file under the policy root directory.
| selinux.h

|-



| selinux_file_context_subs_path
| Return path to <tt>file_context.subs</tt> file under the policy root directory.
| selinux.h

|-



| selinux_file_context_subs_dist_path
| Return path to <tt>file_context.subs_dist</tt> file under the policy root directory.
| selinux.h

|-



| selinux_file_context_verify
| Verify the context of the file 'path' against policy. Return 0 if correct.
| selinux.h

|-



|  selinux_get_callback
| Used to get a pointer to the callback function of the given <tt>type</tt>. Callback functions are set using <tt>'''selinux_set_callback'''(3)</tt>.
| selinux.h

|-



| selinux_getenforcemode
| Reads the /etc/selinux/config file and determines whether the machine should be started in enforcing (1), permissive (0) or disabled (-1) mode. 
| selinux.h

|-



| selinux_getpolicytype
| Reads the /<tt>etc/selinux/config</tt> file and determines what the default policy for the machine is. Calling application must free <tt>policytype</tt>.
| selinux.h

|-



| selinux_homedir_context_path
| Return path to file under the policy root directory. Note that this file will only appear in older versions of policy at this location. On systems that are managed using <tt>'''semanage'''(8)</tt> this is now in the policy store.
| selinux.h

|-



| selinux_init_load_policy
| Perform the initial policy load.

This function determines the desired enforcing mode, sets the the <nowiki>*enforce</nowiki> argument accordingly for the caller to use, sets the SELinux kernel enforcing status to match it, and loads the policy. It also internally handles the initial selinuxfs mount required to perform these actions.

The function returns 0 if everything including the policy load succeeds. In this case, init is expected to re-exec itself in order to transition to the proper security context. Otherwise, the function returns -1, and init must check <nowiki>*enforce</nowiki> to determine how to proceed. If enforcing (<nowiki>*enforce</nowiki> > 0), then init should halt the system. Otherwise, init may proceed normally without a re-exec.
| selinux.h

|-



| selinux_lsetfilecon_default
| This function sets the file context to the system defaults. Returns 0 on success.
| selinux.h

|-



| selinux_lxc_contexts_path
| Return the path to the <tt>lxc_contexts</tt> configuration file.
| selinux.h

|-



| selinux_media_context_path
| Return path to file under the policy root directory.
| selinux.h

|-



| selinux_mkload_policy
| Make a policy image and load it. 

This function provides a higher level interface for loading policy than '''security_load_policy'''(3), internally determining the right policy version, locating and opening the policy file, mapping it into memory, manipulating it as needed for current boolean settings and/or local definitions, and then calling '''security_load_policy'''(3) to load it.

'preservebools' is a boolean flag indicating whether current policy boolean values should be preserved into the new policy (if 1) or reset to the saved policy settings (if 0). The former case is the default for policy reloads, while the latter case is an option for policy reloads but is primarily for the initial policy load.
| selinux.h

|-



| selinux_netfilter_context_path
| Returns path to the netfilter_context file under the policy root directory.
| selinux.h

|-



| selinux_path
| Returns path to the policy root directory.
| selinux.h

|-



| selinux_policy_root
| Reads the /etc/selinux/config file and returns the top level directory.
| selinux.h

|-



| selinux_raw_context_to_color
| Perform context translation between security contexts and display colors. Returns a space-separated list of ten ten hex RGB triples prefixed by hash marks, e.g. "<nowiki>#ff0000</nowiki>". Caller must free the resulting string via '''free'''(3). Returns -1 upon an error or 0 otherwise.
| selinux.h

|-



| selinux_raw_to_trans_context
| Perform context translation between the human-readable format ("translated") and the internal system format ("raw"). Caller must free the resulting context via '''freecon'''(3). Returns -1 upon an error or 0 otherwise. If passed NULL, sets the returned context to NULL and returns 0.
| selinux.h

|-



| selinux_removable_context_path
| Return path to <tt>removable_context</tt> file under the policy root directory.
| selinux.h

|-



| selinux_securetty_types_path
| Return path to the securetty_types file under the policy root directory.
| selinux.h

|-



| selinux_sepgsql_context_path
| Return path to <tt>sepgsql_context</tt> file under the policy root directory.
| selinux.h

|-



| selinux_set_callback
| Sets the callback according to the type: <tt>SELINUX_CB_LOG</tt>, <tt>SELINUX_CB_AUDIT</tt>, <tt>SELINUX_CB_VALIDATE</tt>, <tt>SELINUX_CB_SETENFORCE</tt>, <tt>SELINUX_CB_POLICYLOAD</tt>
| selinux.h

|-



| selinux_set_mapping
| Userspace class mapping support that establishes a mapping from a user-provided ordering of object classes and permissions to the numbers actually used by the loaded system policy.
| selinux.h

|-



| selinux_set_policy_root
| Sets an alternate policy root directory path under which the compiled policy file and context configuration files exist.
| selinux.h

|-



| selinux_status_open
| Open and map SELinux kernel status page.
| avc.h

|-



| selinux_status_close
| Unmap and close kernel status page.
| avc.h

|-



| selinux_status_updated
| Inform whether the kernel status has been updated.
| avc.h

|-



| selinux_status_getenforce
| Get the enforce flag value.
| avc.h

|-



| selinux_status_policyload
| Get the number of policy loads.
| avc.h

|-



| selinux_status_deny_unknown
| Get behaviour for undefined classes/permissions.
| avc.h

|-



| selinux_systemd_contexts_path
| Returns the path to the <tt>systemd_contexts</tt> configuration file.
| selinux.h

|-



| selinux_reset_config
| Force a reset of the loaded configuration. '''WARNING''': This is not thread safe. Be very sure that no other threads are calling into <tt>libselinux</tt> when this is called.
| selinux.h

|-



| selinux_trans_to_raw_context
| Perform context translation between the human-readable format ("translated") and the internal system format ("raw"). Caller must free the resulting context via '''freecon'''(3). Returns -1 upon an error or 0 otherwise. If passed NULL, sets the returned context to NULL and returns 0.
| selinux.h

|-



| selinux_translations_path
| Return path to setrans.conf file under the policy root directory.
| selinux.h

|-



| selinux_user_contexts_path
| Return path to file under the policy root directory.
| selinux.h

|-



| selinux_users_path
| Return path to file under the policy root directory.
| selinux.h

|-



| selinux_usersconf_path
| Return path to file under the policy root directory.
| selinux.h

|-



| selinux_virtual_domain_context_path
| Return path to file under the policy root directory.
| selinux.h

|-



| selinux_virtual_image_context_path
| Return path to file under the policy root directory.
| selinux.h

|-



| selinux_x_context_path
| Return path to x_context file under the policy root directory.
| selinux.h

|-



| selinuxfs_exists
| Check if selinuxfs exists as a kernel filesystem.
| selinux.h

|-



| set_matchpathcon_canoncon
| Same as '''set_matchpathcon_invalidcon'''(3), but also allows canonicalization of the context, by changing <nowiki>*context</nowiki> to refer to the canonical form. If not set, and invalidcon is also not set, then this defaults to calling '''security_canonicalize_context'''(3).
| selinux.h

|-



| set_matchpathcon_flags
| Set flags controlling operation of '''matchpathcon_init'''(3) or '''matchpathcon'''(3): 

MATCHPATHCON_BASEONLY - Only process the base file_contexts file. 

MATCHPATHCON_NOTRANS - Do not perform any context translation.

MATCHPATHCON_VALIDATE - Validate/canonicalize contexts at init time.
| selinux.h

|-



| set_matchpathcon_invalidcon
| Set the function used by '''matchpathcon_init'''(3) when checking the validity of a context in the file_contexts configuration. If not set, then this defaults to a test based on '''security_check_context'''(3). The function is also responsible for reporting any such error, and may include the 'path' and 'lineno' in such error messages.
| selinux.h

|-



| set_matchpathcon_printf
| Set the function used by '''matchpathcon_init'''(3) when displaying errors about the file_contexts configuration. If not set, then this defaults to fprintf(stderr, fmt, ...).
| selinux.h

|-



| set_selinuxmnt 
| Set the path to the selinuxfs mount point explicitly. Normally, this is determined automatically during libselinux initialization, but this is not always possible, e.g. for /sbin/init which performs the initial mount of selinuxfs.
| selinux.h

|-



| setcon

setcon_raw
| Set the current security context to con.

Note that use of this function requires that the entire application be trusted to maintain any desired separation between the old and new security contexts, unlike exec-based transitions performed via '''setexeccon'''(3). When possible, decompose your application and use '''setexeccon'''(3)+'''execve'''(3) instead. Note that the application may lose access to its open descriptors as a result of a '''setcon'''(3) unless policy allows it to use descriptors opened by the old context. 
| selinux.h

|-



| setexeccon

setexeccon_raw
| Set exec security context for the next '''execve'''(3). Call with NULL if you want to reset to the default.
| selinux.h

|-



| setexecfilecon
| Set an appropriate security context based on the filename of a helper program, falling back to a new context with the specified type.
| selinux.h

|-



| setfilecon

setfilecon_raw
| Wrapper for the xattr API - Set file context.
| selinux.h

|-



| setfscreatecon

setfscreatecon_raw
| Set the fscreate security context for subsequent file creations. Call with NULL if you want to reset to the default.
| selinux.h

|-



| setkeycreatecon

setkeycreatecon_raw
| Set the keycreate security context for subsequent key creations. Call with NULL if you want to reset to the default.
| selinux.h

|-



| setsockcreatecon

setsockcreatecon_raw
| Set the sockcreate security context for subsequent socket creations. Call with NULL if you want to reset to the default.
| selinux.h

|-



| sidget (deprecated)
| From 2.0.86 this is a no-op.
| avc.h

|-



| sidput (deprecated)
| From 2.0.86 this is a no-op.
| avc.h

|-



| string_to_av_perm
| Convert string names to access vector permissions.
| selinux.h

|-



| string_to_security_class
| Convert string names to security class values.
| selinux.h

|}



{| style="width: 100%;" border="0"
|-
| [[NB_SEforAndroid_2 | '''Previous''']]
| <center>[[NewUsers | '''Home''']]</center>
| <center>[[NB_ObjectClassesPermissions | '''Next''']]</center>
|}



----
<references/>

[[Category:Notebook]]

