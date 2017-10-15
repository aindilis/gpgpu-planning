/*
 * Timer.h
 *
 * Created on 12.10.2010
 * Author: sulewski
 */

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <sys/time.h>

#ifndef TIMER_H_
#define TIMER_H_

using namespace std;

typedef struct {
		unsigned long long secs;
		unsigned int	usecs;
} TIME_DIFF;


class Timer {
	private:
		struct timeval starttime,endtime; //time the timer was started
		TIME_DIFF running_time; //running time in miliseconds
		bool running;
	public:
		Timer();
		bool reset(); //resets the running time to zero
		bool start(); //starts the timer
		bool stop(); //stops the timer and adds milisecconds to running time;
		void print(ostream& ostr); // shows elapsed time 
};

std::ostream &operator<<(std::ostream &ostr, Timer t) ;

#endif  /* TIMER_H_ */
