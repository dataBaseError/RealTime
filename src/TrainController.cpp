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

const string TrainController::F1 = "20002";
const string TrainController::F2 = "20000";
const string TrainController::J1 = "20001";
const string TrainController::J2 = "20003";

const string TrainController::DECODER_100 = "100";
const string TrainController::DECODER_101 = "101";

const string TrainController::TRAIN_1_ID = "1005";

const string TrainController::FORWARD = "0";
const string TrainController::BACKWARD = "1";

const string TrainController::STATION_A = "0";
const string TrainController::STATION_B = "1";

TrainController::TrainController() {}

string TrainController::getTrainControl(string train_id) {
    if (validateTrainId(train_id)) {
	    return "request(" + train_id + ",control,force)";
    }

    return string();
}

string TrainController::watchSensors(string decoder_id) {
	return "request(" + decoder_id + ",view)";
}

string TrainController::getSwitchControl(string corner_id) {
	if (validateCornerId(corner_id)) {
		return "request("+corner_id+",control,force)";
	}
	return string();
}

string TrainController::setDirection(string direction){
	if (direction == FORWARD || direction == BACKWARD) {
		return "set(1005,dir[" + direction + "])";
	}

	return string();
}

string TrainController::setSpeed(int speed){
	if (speed >= 0 && speed <= 120) {
		ss << "set(1005,speed[" << speed << "])";

		string value = ss.str();
		cleanStream();

		return value;
	}

	return string();
}

string TrainController::setSwitch(string corner_id, string station_id) {
	if (validateCornerId(corner_id) && validateStationId(station_id)) {
		return "set(" + corner_id + ",state[" + station_id + "])";
	}

	return string();
}

bool TrainController::validateTrainId(string train_id) {
    return train_id == TRAIN_1_ID;
}

bool TrainController::validateStationId(string station_id) {
	return station_id == STATION_A || station_id == STATION_B;
}

bool TrainController::validateCornerId(string corner_id) {
	return corner_id == F1 || corner_id == F2 || corner_id == J1 || corner_id == J2;
}

void TrainController::cleanStream() {
	ss.str(std::string());
}
