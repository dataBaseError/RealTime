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

#ifndef WRITER_HPP_
#define WRITER_HPP_

#include <iostream>
#include <string>
#include <queue>

#include <atomic>
#include <pthread.h>

using namespace std;

class Writer {
	//Stores the socket descriptor for the socket we've bound to.
	int socket_descriptor;

	//Specifies the maximum length of a message we can send.
	int buffer_size;

public:
	//Concurrency operators.
	std::atomic<bool > killThread;
	queue<string > buffer;
	pthread_mutex_t emptyMutex;
	pthread_cond_t empty;

	//Maximum number of writers allowed to run.
	static const int MAX_PROCESSES = 1;

	/**
	 * Default constructor.
	 */
	Writer(int socket_descriptor, int buffer_size);

	/**
	 * Run call-back for the thread.
	 */
	static void *run(void *param);

	/**
	 * Send a command to the socket.
	 *
	 * @param value The command that will be sent to the socket
	 */
	void sendCommand(string value);

	/**
	 * Releases the writer thread, but doesn't close the socket.
	 */
	void release();

private:
	/**
	 * Run method for the writer thread.
	 */
	void process();
};


#endif /* WRITER_HPP_ */
