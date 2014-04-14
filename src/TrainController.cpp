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

#include <TrainController.hpp>

TrainController::TrainController() {

}

std::string TrainController::getEvents() {
    return "request(100,view)\n";
}

std::string TrainController::getControl(int id) {
    std::ostringstream stream;
    stream << "request(" << id << ",control,force)" << std::endl;

	return stream.str();
}

std::string TrainController::setDirection(int direction){
    (void) direction;
	return "";
}

std::string TrainController::setSpeed(int direction){
    (void) direction;
	return "";
}

std::string TrainController::setTrackF1(int lane){
    (void) lane;
	return "";
}

std::string TrainController::setTrackF2(int lane){
    (void) lane;
	return "";
}

std::string TrainController::setTrackJ1(int lane){
    (void) lane;
	return "";
}

std::string TrainController::setTrackJ2(int lane){
    (void) lane;
	return "";
}
