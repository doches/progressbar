/**
 * \file
 * \mainpage Progressbar and Statusbar -- Continuous console status updates
 *
 * \section Progressbar
 * Creating and starting the progress bar: \ref progressbar_new
 *
 * Updating the current progress: \ref progressbar_update, \ref progressbar_inc, \ref progressbar_update_label
 *
 * Finishing the progressbar (on success or failure): \ref progressbar_finish
 *
 * \section Statusbar
 *
 * Creating and starting the status bar: \ref statusbar_new
 *
 * Updating the current progress: \ref statusbar_inc
 *
 * Finishing the progressbar (on success or failure): \ref statusbar_finish
 *
 * \section Example Example Code
 * See \ref main in progressbar_demo.c
 *
 * Download the code from the repository at https://github.com/JohannesBuchner/progressbar
 *
 * \author Trevor Fountain
 * \author Johannes Buchner
 * \author Erik Garrison
 * \date 2010-2014
 * \copyright BSD 3-Clause
 *
 *
 **/

 #include "progressbar.h"
 #include "statusbar.h"
 #include <unistd.h>

#define SLEEP_US 100000

/**
 *Example for statusbar and progressbar usage
 **/
int main(void)
{
    // Progress bar
    int max = 60;
    progressbar *smooth = progressbar_new("Smooth",max);
    for(int i=0; i < max; i++) {
        usleep(SLEEP_US);
        progressbar_inc(smooth);
    }
    progressbar_finish(smooth);

    progressbar *longlabel = progressbar_new("Three Second Task with a long label",3);
    for(int i=0; i < 3; i++) {
        progressbar_inc(longlabel);
        sleep(1);
    }
    progressbar_finish(longlabel);

    progressbar *fast = progressbar_new("Fast",20);
    for(int i=0; i < 20; i++) {
        usleep(SLEEP_US);
        progressbar_inc(fast);
    }
    progressbar_finish(fast);

    progressbar *custom = progressbar_new_with_format("Custom",max,"<.>");
    for(int i=0; i < max; i++) {
      usleep(SLEEP_US);
      progressbar_inc(custom);
    }
    progressbar_finish(custom);

    // Status bar
    statusbar *status = statusbar_new("Indeterminate");
    for(int i=0; i < 30; i++) {
        usleep(SLEEP_US);
        statusbar_inc(status);
    }
    statusbar_finish(status);

    statusbar *longStatus = statusbar_new("Status bar with a really long label");
    for(int i=0; i < 10; i++) {
        usleep(SLEEP_US);
        statusbar_inc(longStatus);
    }
    statusbar_finish(longStatus);

    statusbar *customStatus = statusbar_new_with_format("Custom","(|)|");
    for(int i=0; i < 30; i++) {
        usleep(SLEEP_US);
        statusbar_inc(customStatus);
    }
    statusbar_finish(customStatus);
}
