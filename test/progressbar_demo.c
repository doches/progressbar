#include "progressbar.h"

int main(void)
{
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