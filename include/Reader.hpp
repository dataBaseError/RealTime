
#ifndef READER_HPP_
#define READER_HPP_

#include <iostream>
#include <string>
#include <queue>

#include <atomic>
#include <pthread.h>
#include <unistd.h>

using namespace std;

class Reader {

	int socket_descriptor;
	int buffer_size;

public:

	std::atomic<bool > killThread;
	vector<string > value;
	//pthread_mutex_t emptyMutex;
	//pthread_cond_t empty;
	pthread_mutex_t newValue;
	pthread_cond_t available;

	static const int MAX_PROCESSES = 1;

	Reader(int socket_descriptor, int buffer_size);

	//virtual void run();
	//void run();
	static void *run(void *param);

	/**
	 * Read the response from the socket
	 *
	 * @return Any response message from the socket
	 */
	string readCommand();

	void release();

private:
	bool process();
};


#endif /* READER_HPP_ */
