#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/* 
 * Functions defined here carry out system commands and return
 * a file pointer to the output stream which is the command's
 * output, if needed. Otherwise returns exit status.
*/


FILE * eselect_kernel_list() {
    FILE * fp;

    fp = popen("/usr/bin/eselect kernel list", "r");    // Execute command and read
    if (errno != 0 || fp == NULL) {                                   // Check that execution was successful
        fprintf(stderr, "%s: Failed to run command.\n", strerror(errno));    // If not, error and exit.
        exit(1);
    }

    return fp;
}

void eselect_kernel_set(int target) {
    //FILE * fp;
    char command[50];
    int status;

    sprintf(command, "/usr/bin/doas /usr/bin/eselect kernel set %d", target); 
    //TODO: this is the easy way, root access needs to be handled better
    status = system(command);
    if (status != 0) {
        fprintf(stderr, "eselect_kernel_set: Command exited with code %d\n", status);
        exit(1);
    }

}

void make_mrproper() {
    chdir("/usr/src/linux");
    system("make mrproper");
}