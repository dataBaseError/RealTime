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

#include <Writer.hpp>

//Default constructor.
Writer::Writer(int socket_descriptor, int buffer_size) : killThread(false){

	this->socket_descriptor = socket_descriptor;
	this->buffer_size = buffer_size;

	pthread_mutex_init(&emptyMutex,0);
	pthread_cond_init(&empty, 0);
	pthread_t thread1;
	pthread_create(&thread1, 0, run, (void *) this);
}

void * Writer::run(void *param) {
	Writer *mt = ((Writer *) param);
	while(!mt->killThread) {

		pthread_mutex_lock(&mt->emptyMutex);

		if(mt->buffer.empty()) {
			pthread_cond_wait(&mt->empty, &mt->emptyMutex);
		}
		pthread_mutex_unlock(&mt->emptyMutex);

		if(mt->killThread) {
			break;
		}

		mt->process();
	}

	return NULL;
}

void Writer::process() {
	string message = buffer.front();
	send(this->socket_descriptor, message.c_str(), message.length(), 0);
	buffer.pop();
}

void Writer::sendCommand(string value) {
 	buffer.push(value);
 	pthread_mutex_lock(&emptyMutex);
 	pthread_cond_signal(&empty);
 	pthread_mutex_unlock(&emptyMutex);
}

void Writer::release() {
	killThread = true;
	//copthread_cond_signal(&available);
	pthread_cond_signal(&empty);

	pthread_mutex_destroy(&emptyMutex);
	//pthread_mutex_destroy(&runMutex);
	pthread_cond_destroy(&empty);
	//pthread_cond_destroy(&available);
}
