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

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <netdb.h>     // gethostbyname, hostent
#include <string.h>    // bzero, memmove

#include <Reader.hpp>
#include <TrainController.hpp>
#include <Writer.hpp>

// Declare the maximum buffer size for interacting with the socket.
#define MAX_BUFFER_SIZE 256

int open(const char* hostname, const uint16_t port);
int tm(unsigned int ms);
int main(int argc, char** argv);

#endif /* MAIN_HPP_ */
