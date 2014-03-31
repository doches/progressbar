Progressbar for C/C++ programs
========================================

progressbar is a C-class for displaying attractive progress bars on the 
command line, similar to what is available for python or ruby.

progressbar is implemented in pure C99, but using a object-oriented convention. 

Example usage::

    progressbar *progress = progressbar_new("Loading",100);
    for(int i=0;i<100;i++)
    {
      // Do some stuff
      progressbar_inc(progress);
    }
    progressbar_finish(progress);

Additional examples can be found in `test/progressbar_demo.c`

Why did you do this?
----------------------

One of the things I miss most when I'm writing C instead of Ruby is the
how ridiculously easy it is to write user-friendly, informative CLI apps
in Ruby. A big part of that, at least for me, is the ProgressBar gem --
and since most of the time when I'm writing C I'm doing so because I need
a tool to handle some long-running, processor-intensive task, I'd really
like to have a way of seeing at a glance how much time is remaining and
how far along we've gotten. Enter progressbar!

License
----------

Progressbar is licensed under a simplified BSD license (see LICENSE).
So feel free to take it and run with it.

