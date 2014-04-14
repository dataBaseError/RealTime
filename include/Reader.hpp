/**
 * Copyright (C) 2014 Jonathan Gillett, Joseph Heron, Khalil Fazal, Daniel Smullen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef READER_HPP_
#define READER_HPP_

#include <iostream>
#include <string>
#include <queue>
#include <sys/socket.h>

#include <atomic>
#include <pthread.h>
#include <unistd.h>

using namespace std;

class Reader {

	//Stores the socket descriptor for the socket we've bound to.
	int socket_descriptor;

	//Specifies the maximum length of a message we can read in.
	int buffer_size;

public:

	//Concurrency operators.
	std::atomic<bool > killThread;
	vector<string > value;
	pthread_mutex_t newValue;
	pthread_cond_t available;

	//Maximum number of readers allowed to run.
	static const int MAX_PROCESSES = 1;

	/**
	 * Default constructor.
	 */
	Reader(int socket_descriptor, int buffer_size);

	/**
	 * Run call-back for the thread.
	 */
	static void *run(void *param);

	/**
	 * Read the response from the socket.
	 *
	 * @return Any response message from the socket
	 */
	string readCommand();

	/**
	 * Releases the reader thread, but doesn't close the socket.
	 */
	void release();

private:
	/**
	 * Run method for the reader thread.
	 */
	bool process();
};


#endif /* READER_HPP_ */
