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

#include <main.hpp>

int open(const char* hostname, const uint16_t port) {
    // The socket address
    struct sockaddr_in address;

    // The socket host
    struct hostent* host = gethostbyname(hostname);

    // The socket's file descriptor
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // allocate address with null bytes
    bzero((char *) &address, sizeof(address));

    // set the address format to IPV4
    address.sin_family = AF_INET;

    // set the host in the address
    memmove((char *) &address.sin_addr.s_addr, (char *) host->h_addr, host->h_length);

    // set the port in the address
    address.sin_port = htons(port);

    // connect to the socket
    connect(sockfd, (struct sockaddr *) &address, sizeof(address));

    // return the socket
    return sockfd;
}

int tm(unsigned int ms) {
    return usleep(ms * 1000);
}

int main(int argc, char** argv) {
    (void) argc;
    (void) argv;

    int s = open("192.168.0.1", 1234);

	// Instantiate reader thread here; bind to connected socket.
	Reader r(s, MAX_BUFFER_SIZE);
	// Instantiate writer thread here; bind to connected socket.
	Writer w(s, MAX_BUFFER_SIZE);

    // Instantiate the train controller
    TrainController controller;

    // 1. Request control of the train
    //    request(1004,control,force)
    w.sendCommand(controller.getTrainControl(TrainController::TRAIN_1_ID));

	// 2. Signal the writer thread to subscribe to the events.
	//    Put the following into the buffer, and notify the writer thread:
    //    request(100,view)
    w.sendCommand(controller.watchSensors(TrainController::DECODER_100));

    // 3. Get Control of F1
    //    request(20002,control,force)
    w.sendCommand(controller.getSwitchControl(TrainController::F1));

    // sleep 100 ms
    tm(100);

    // 4. Get Control of F2
    //    request(20000,control,force)
    w.sendCommand(controller.getSwitchControl(TrainController::F2));

    // sleep 100 ms
    tm(100);

    // 5. Get Control of J1
    //    request(20001,control,force)
    w.sendCommand(controller.getSwitchControl(TrainController::J1));

    // sleep 100 ms
    tm(100);

    // 6. Get Control of J2
    //    request(20003,control,force)
    w.sendCommand(controller.getSwitchControl(TrainController::J2));

    // 7.

	// Begin main control loop:
	while (true) {
		// Check if we've received something from the socket.
		// Output it to the console.
		cout << r.readCommand() << endl;
	}

	// Join and release the reader thread.
	r.release();
	// Join and release the writer thread.
	w.release();

	return 0;
}
