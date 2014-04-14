
#ifndef WRITER_HPP_
#define WRITER_HPP_

#include <iostream>
#include <string>
#include <queue>

#include <atomic>
#include <pthread.h>

using namespace std;

class Writer {

public:

	std::atomic<bool > killThread;
	queue<string > buffer;
	//std::atomic<std::string* > buffer;
	//std::atomic<int> activeCount;
	pthread_mutex_t emptyMutex;
	pthread_cond_t empty;

	static const int MAX_PROCESSES = 1;

	Writer();

	//virtual void run();
	//void run();
	static void *run(void *param);

	void release();

private:
	void process();
};


#endif /* WRITER_HPP_ */
