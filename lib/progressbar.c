/**
* \file
* \author Trevor Fountain
* \author Johannes Buchner
* \author Erik Garrison
* \date 2010-2014
* \copyright BSD 3-Clause
*
* progressbar -- a C class (by convention) for displaying progress
* on the command line (to stderr).
*/

#include <termcap.h>  /* tgetent, tgetnum */
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "progressbar.h"

#define PROGRESSBAR_WIDTH 200

/**
* Create a new progress bar with the specified label, max number of steps, and format string.
* Note that `format` must be exactly three characters long, e.g. "<->" to render a progress
* bar like "<---------->".
*/
progressbar *progressbar_new_with_format(char *label, unsigned long max, const char *format)
{
  progressbar *new = malloc(sizeof(progressbar));
  new->max = max;
  new->value = 0;
  new->start = time(NULL);
  new->step = 0;
  new->steps = 0;
  new->progress_str = calloc(PROGRESSBAR_WIDTH+1, sizeof(char));
  new->format = strdup(format);
  memset(new->progress_str,' ', PROGRESSBAR_WIDTH);
  new->progress_str[new->steps] = 0;
  new->last_printed = 0;
  new->termtype = getenv("TERM");

  new->label = NULL;
  progressbar_update_label(new, label);
  progressbar_draw(new, 0);

  return new;
}

/**
* Create a new progress bar with the specified label and max number of steps.
*/
progressbar *progressbar_new(char *label, unsigned long max)
{
  return progressbar_new_with_format(label, max, "|=|");
}

void progressbar_update_label(progressbar *bar, char *label)
{
  free(bar->label);
  bar->label = label = strdup(label);

  int newsteps;
  unsigned int columns = 80; // by default 80
  static char termbuf[2048];
  if (!(tgetent(termbuf, bar->termtype) < 0)) {
    // otherwise size of terminal if it works
    columns = tgetnum("co") - 2;
  }
  // make sure newsteps is positive
  unsigned int maxstrlen = columns - 17;
  if (maxstrlen - 10 > 10 && strlen(label) > maxstrlen - 10) {
    label[maxstrlen - 10] = 0;
  }
  if (strlen(label) >= maxstrlen) {
    label[maxstrlen] = 0;
  }
  // Reserve two possible colums for pre- and post- spacing
  columns -= 2;

  newsteps = columns - (strlen(label) + 17);
  if (newsteps < 0) {
    newsteps = 0;
  }
  if (newsteps > PROGRESSBAR_WIDTH - 1) {
    newsteps = PROGRESSBAR_WIDTH - 1;
  }
  if (newsteps != (int)bar->steps && bar->step >= bar->steps) {
    bar->step = 0;
  }
  bar->steps = newsteps;
}

/**
* Delete an existing progress bar.
*/
void progressbar_free(progressbar *bar)
{
  // We malloc'd a couple of strings, so let's be sure to free those...
  free(bar->progress_str);
  free(bar->format);
  free(bar->label);
  // ...before we free the struct itself.
  free(bar);

  return;
}

/**
* Increment an existing progressbar by `value` steps.
*/
void progressbar_update(progressbar *bar, unsigned long value)
{
  bar->value = value;
  unsigned int current_step = (bar->value * (unsigned long)bar->steps / (long double)bar->max);

  // Only redraw the progressbar if the visual progress display (the current 'step')
  // has changed.
  if(1 || current_step != bar->step) {
    // Fill the bar to the current step...
    for(unsigned int i=0; i < current_step; i++) {
      bar->progress_str[i] = bar->format[1];
    }
    for(unsigned int i=current_step; i < bar->steps; i++) {
      bar->progress_str[i] = ' ';
    }
    bar->progress_str[bar->steps] = 0;
    bar->step = current_step;

    // Draw using a rough estimated time remaining.
    // Time remaining is estimated quite roughly, as the number of increments
    // remaining * the average time per increment thus far.
    double offset = difftime(time(NULL), bar->start);
    unsigned int estimate;
    if (bar->value > 0 && offset > 0) {
       estimate = (offset/(long double)bar->value) * (bar->max - bar->value);
    } else {
      estimate = 0;
    }
    progressbar_draw(bar, estimate);
  }
}

/**
* Increment an existing progressbar by a single step.
*/
void progressbar_inc(progressbar *bar)
{
  progressbar_update(bar, bar->value+1);
}

/**
* Render a progress bar. You probably don't need to call this directly; it's
* automatically called when you update a progressbar and a re-render is required.
*/
void progressbar_draw(progressbar *bar, unsigned int timeleft)
{
  // Convert the time to display into HHH:MM:SS
  unsigned int h = timeleft / 3600;
  timeleft -= h*3600;
  unsigned int m = timeleft / 60;
  timeleft -= m*60;
  unsigned int s = timeleft;
  // ...and display!
  bar->last_printed = fprintf(
            stderr,
            "%s %c%s%c ETA:%2dh%02dm%02ds\r",
            bar->label,
            bar->format[0],
            bar->progress_str,
            bar->format[2],
            h,
            m,
            s
        );
  return;
}

/**
* Finish a progressbar, indicating 100% completion, and free it.
*/
void progressbar_finish(progressbar *bar)
{
  // Draw one more time, with the actual time to completion instead of a useless
  // 00:00:00 remaining estimate.
  unsigned int offset = time(NULL) - (bar->start);
  // Make sure we fill the progressbar too, so things look complete.
  for(unsigned int i=0; i < bar->steps; i++) {
    bar->progress_str[i] = bar->format[1];
  }
  progressbar_draw(bar, offset);

  // Print a newline, so that future outputs to stderr look prettier
  fprintf(stderr, "\n");

  // We've finished with this progressbar, so go ahead and free it.
  progressbar_free(bar);

  return;
}
