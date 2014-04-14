
#ifndef READER_HPP_
#define READER_HPP_

#include <iostream>
#include <string>
#include <queue>

#include <atomic>
#include <pthread.h>
#include <unistd.h>

class Reader {

public:

	std::atomic<bool > killThread;
	std::vector<std::string > value;
	//pthread_mutex_t emptyMutex;
	//pthread_cond_t empty;
	pthread_mutex_t newValue;
	pthread_cond_t available;

	static const int MAX_PROCESSES = 1;

	Reader();

	//virtual void run();
	//void run();
	static void *run(void *param);

	void release();

private:
	bool process();
};


#endif /* READER_HPP_ */
