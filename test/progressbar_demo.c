#include "progressbar.h"
#include "statusbar.h"
#include "unistd.h"

int main(void)
{
    // Status bar
    statusbar *status = statusbar_new("Indeterminate");
    for (int i=0; i<30; i++) {
		for(int k=0;k<50000000;k++);
        statusbar_inc(status);
    }
    statusbar_finish(status);
    
    status = statusbar_new("Status bar with a really long label");
    for (int i=0; i<10; i++) {
		for(int k=0;k<50000000;k++);
        statusbar_inc(status);
    }
    statusbar_finish(status);
    
    status = statusbar_new_with_format("Custom","(|)|");
    for (int i=0; i<30; i++) {
		for(int k=0;k<50000000;k++);
        statusbar_inc(status);
    }
    statusbar_finish(status);
    
    // Progress bar
	int max = 240;
	progressbar *progress = progressbar_new("Smooth",max);
	for(int i=0;i<max;i++) {
		progressbar_inc(progress);
		for(int k=0;k<2500000;k++);
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
		for(int k=0;k<1000000;k++);
		progressbar_inc(progress);
	}
	progressbar_finish(progress);
}