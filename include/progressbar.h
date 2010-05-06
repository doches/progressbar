#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* progressbar -- a C class (by convention) for displaying progress
 * on the command line (to stderr).
 */
typedef struct _progressbar_t
{
	unsigned int max;
	unsigned int value;
	
	unsigned int step;
	unsigned int steps;
	
	unsigned int start;
	const char *label;
	char *progress_str;
	char *format;
	int last_printed;
} progressbar;

// Create a new progressbar with the specified label and # of steps
progressbar *progressbar_new(const char *label,unsigned int max);

// Free an existing progress bar. Don't call this directly; call *progressbar_finish* instead.
void progressbar_free(progressbar *bar);

// Increment the given progressbar. Don't increment past the initialized # of steps, though.
void progressbar_inc(progressbar *bar);

// Finalize (and free!) a progressbar. Call this when you're done, or if you break out 
// partway through.
void progressbar_finish(progressbar *bar);

// Draw a progressbar to the screen with the specified time display. Don't call this directly, 
// as it's called internally by *progressbar_inc*.
void progressbar_draw(progressbar *bar,unsigned int time);

#endif