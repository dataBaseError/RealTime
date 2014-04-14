
#include <Writer.hpp>
#include <Reader.hpp>
#include <unistd.h>
#include <sstream>

int main(int argc, char *argv[])
{
	/*Writer w;
	unsigned int i;
	for(i = 0; i < 10; i++) {
		stringstream sstm;
		sstm << "hello " << i;
		//cout << sstm.str() << endl;
		w.buffer.push(sstm.str());
		pthread_mutex_lock(&w.emptyMutex);
		pthread_cond_signal(&w.empty);
		pthread_mutex_unlock(&w.emptyMutex);

	}


	//usleep(1);
	w.release();*/

	/*Reader r;
	unsigned int i;
	for(i = 0; i < 10; i++) {
		pthread_mutex_lock(&r.newValue);
		pthread_cond_wait(&r.available, &r.newValue);
		pthread_mutex_unlock(&r.newValue);

		cout << "Value " << r.value[0] << endl;
	}

	r.release();*/

	return 0;
}
