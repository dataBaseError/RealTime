
#ifndef WRITER_HPP_
#define WRITER_HPP_

#include <iostream>
#include <string>
#include <queue>

#include <atomic>
#include <pthread.h>

using namespace std;

class Writer {

	int socket_descriptor;
	int buffer_size;

public:

	std::atomic<bool > killThread;
	queue<string > buffer;
	pthread_mutex_t emptyMutex;
	pthread_cond_t empty;

	static const int MAX_PROCESSES = 1;

	Writer(int socket_descriptor, int buffer_size);

	static void *run(void *param);

	/**
	 * Send a command to the socket
	 *
	 * @param value The command that will be sent to the socket
	 */
	void sendCommand(string value);

	void release();

private:
	void process();
};


#endif /* WRITER_HPP_ */
