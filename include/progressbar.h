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

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Progressbar data structure (do not modify or create directly)
 */
typedef struct _progressbar_t
{
  /// maximum value
  unsigned long max;
  /// current value
  unsigned long value;

  /// maximum number of steps
  unsigned int steps;
  /// current step
  unsigned int step;

  /// time progressbar was started
  time_t start;
  /// label
  const char *label;
  /// the progress bar stored as text
  char *progress_str;
  /// characters for the beginning, filling and end of the
  /// progressbar. E.g. |###    | has |#|
  char *format;
  /// number of characters printed on last output
  int last_printed;
  /// terminal information
  char * termtype;
} progressbar;

/// Create a new progressbar with the specified label and # of steps
progressbar *progressbar_new(char *label, unsigned long max);

/// Create a new progressbar with the specified label, # of steps, and format string.
/// Format strings are three-character strings indicating the left bar, fill, and
/// right bar (in that order). For example, "(.)" would result in a progress bar
/// like "(...........)".
progressbar *progressbar_new_with_format(char *label, unsigned long max, const char *format);

/// Free an existing progress bar. Don't call this directly; call *progressbar_finish* instead.
void progressbar_free(progressbar *bar);

/// Increment the given progressbar. Don't increment past the initialized # of steps, though.
void progressbar_inc(progressbar *bar);

/// Set the current status on the given progressbar.
void progressbar_update(progressbar *bar, unsigned long value);

/// Change the current label
/// Does not update display or copy the label
void progressbar_update_label(progressbar *bar, char *label);

/// Finalize (and free!) a progressbar. Call this when you're done, or if you break out
/// partway through.
void progressbar_finish(progressbar *bar);

/// Draw a progressbar to the screen with the specified time display. Don't call this directly,
/// as it's called internally by *progressbar_inc*.
void progressbar_draw(progressbar *bar, unsigned int time);

#endif
