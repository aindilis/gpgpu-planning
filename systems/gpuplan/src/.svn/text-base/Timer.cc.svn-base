#include "Timer.h"
#include <assert.h>

using namespace std;

Timer::Timer(){
	running = false;
	reset();
}

bool Timer::reset(){
	running_time.secs = 0;
	running_time.usecs = 0;
}

bool Timer::start(){
	assert(!running);
	running = true;
	gettimeofday (&starttime,NULL);
}

bool Timer::stop(){
	assert(running);
	gettimeofday (&endtime,NULL);
	running = false;
	if (starttime.tv_sec == endtime.tv_sec) {
		running_time.usecs += endtime.tv_usec - starttime.tv_usec;
	}
	else {
		running_time.usecs += 1000000 - starttime.tv_usec;
		running_time.secs += (endtime.tv_sec - (starttime.tv_sec + 1));
		running_time.usecs += endtime.tv_usec;
	}
	if (running_time.usecs >= 1000000) {
		running_time.usecs -= 1000000;
		running_time.secs += 1;
	}
}

void Timer::print(ostream& ostr){
	if (running) {  //get current running time
		stop();
		start();
	}
	ostr << running_time.secs << "s" << running_time.usecs/1000 << "ms ";
	assert(running_time.secs < 1000);
}

std::ostream &operator<<(std::ostream &ostr, Timer t) {
	t.print(ostr);
	return ostr; 
}
