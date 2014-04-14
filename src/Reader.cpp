#include <Reader.hpp>

Reader::Reader(int socket_descriptor, int buffer_size) : killThread(false){

	this->socket_descriptor = socket_descriptor;
	this->buffer_size = buffer_size;

	pthread_mutex_init(&newValue,0);
	pthread_cond_init(&available, 0);
	pthread_t thread1;
	value.resize(1);
	pthread_create(&thread1, 0, run, (void *) this);
}

void * Reader::run(void *param) {

	Reader *mt = ((Reader *) param);
	while(!mt->killThread) {

		if(mt->process()) {
			pthread_mutex_lock(&mt->newValue);
			pthread_cond_signal(&mt->available);
			pthread_mutex_unlock(&mt->newValue);
		}

		if(mt->killThread) {
			break;
		}

		usleep(100);
	}

	return NULL;
}

bool Reader::process() {
	//(*value) = next value from the socket
	// return true if the value is valid
	char buffer[buffer_size];
	int numBytes = recv(this->socket_descriptor, buffer, sizeof(buffer), 0);
	if (buffer > 0) {
		//If we got something in the buffer, everything's fine.
		value[0] = buffer;
		return true;
	} else {
		//Otherwise, the socket got closed on us.
		return false;
	}
}

string Reader::readCommand() {
	pthread_mutex_lock(&newValue);
	pthread_cond_wait(&available, &newValue);
	pthread_mutex_unlock(&newValue);
	return value[0];
}

void Reader::release() {
	killThread = true;
	//copthread_cond_signal(&available);
	pthread_cond_signal(&available);

	pthread_mutex_destroy(&newValue);
	//pthread_mutex_destroy(&runMutex);
	pthread_cond_destroy(&available);
	//pthread_cond_destroy(&available);
}
