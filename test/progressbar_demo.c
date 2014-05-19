#include "progressbar.h"
#include "statusbar.h"
#include "unistd.h"

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
 * \date 2010-2014
 * \copyright BSD 3-Clause
 *
 *
 **/

#define SLEEP_MS 100000

/**
 *Example for statusbar and progressbar usage
 **/
int main(void)
{
    // Status bar
    statusbar *status = statusbar_new("Indeterminate");
    for (int i=0; i<30; i++) {
        usleep(SLEEP_MS);
        statusbar_inc(status);
    }
    statusbar_finish(status);

    status = statusbar_new("Status bar with a really long label");
    for (int i=0; i<10; i++) {
        usleep(SLEEP_MS);
        statusbar_inc(status);
    }
    statusbar_finish(status);

    status = statusbar_new_with_format("Custom","(|)|");
    for (int i=0; i<30; i++) {
        usleep(SLEEP_MS);
        statusbar_inc(status);
    }
    statusbar_finish(status);

    // Progress bar
    int max = 240;
    progressbar *progress = progressbar_new("Smooth",max);
    for(int i=0;i<max;i++) {
        usleep(SLEEP_MS);
        progressbar_inc(progress);
    }
    progressbar_finish(progress);

    progress = progressbar_new("Three Second Task with a long label",3);
    for(int i=0;i<3;i++) {
        progressbar_inc(progress);
        sleep(1);
    }
    progressbar_finish(progress);

    progress = progressbar_new("Fast",100);
    for(int i=0;i<100;i++) {
        usleep(SLEEP_MS);
        progressbar_inc(progress);
    }
    progressbar_finish(progress);
}
