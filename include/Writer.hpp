
#ifndef WRITER_HPP_
#define WRITER_HPP_

#include <string>

#include <atomic>
#include <pthread.h>

using namespace std;

class Writer {

public:

	std::atomic<bool > killThread;
	std::atomic<std::string > buffer;
	//std::atomic<int> activeCount;
	pthread_mutex_t emptyMutex;
	pthread_cond_t empty;
	pthread_mutex_t runMutex;
	pthread_cond_t available;

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
