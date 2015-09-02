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
  assert(3 == strlen(format) && "format must be 3 characters in length");
  new->format.begin = format[0];
  new->format.fill = format[1];
  new->format.end = format[2];
  new->termtype = getenv("TERM");

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
  bar->label = label;
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
  free(bar);
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

static void fill(char* buffer, char fill, unsigned current_step, unsigned max_steps)
{
    // Fill the bar to the current step...
    for(unsigned int i=0; i < current_step; i++) {
      buffer[i] = fill;
    }
    for(unsigned int i=current_step; i < max_steps; i++) {
      buffer[i] = ' ';
    }
    buffer[max_steps] = 0;
}

/**
* Render a progress bar. You probably don't need to call this directly; it's
* automatically called when you update a progressbar and a re-render is required.
*/
void progressbar_draw(const progressbar *bar, unsigned int timeleft)
{
  char buffer[PROGRESSBAR_WIDTH+1];
  fill(buffer, bar->format.fill, bar->step, bar->steps);
  // Convert the time to display into HHH:MM:SS
  unsigned int h = timeleft / 3600;
  timeleft -= h*3600;
  unsigned int m = timeleft / 60;
  timeleft -= m*60;
  unsigned int s = timeleft;
  // ...and display!
  fprintf(stderr,
          "%s %c%s%c ETA:%2dh%02dm%02ds\r",
          bar->label,
          bar->format.begin,
          buffer,
          bar->format.end,
          h,
          m,
          s);
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
  progressbar_draw(bar, offset);

  // Print a newline, so that future outputs to stderr look prettier
  fprintf(stderr, "\n");

  // We've finished with this progressbar, so go ahead and free it.
  progressbar_free(bar);

  return;
}
