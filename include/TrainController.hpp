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

#ifndef TRAINCONTROLLER_HPP_
#define TRAINCONTROLLER_HPP_

#include <string.h>
#include <sstream>

using namespace std;

class TrainController {

public:
    enum corners {
        F1 = 20002,
        F2 = 20000,
        J1 = 20001,
        J2 = 20003
    };

    enum decoders {
        DECODER_100 = 100,
        DECODER_101 = 101
    };

	static const string TRAIN_1_ID;

	static const string FORWARD;
	static const string BACKWARD;

	static const string STATION_A;
	static const string STATION_B;

	TrainController();

	string getTrainControl(string train_id);
	string watchSensors(int decoder_id);
	string getSwitchControl(int corner_id);

	string setDirection(string direction);
	string setSpeed(int speed);
	string setSwitch(int corner_id, string station_id);

private:
    stringstream ss;

    bool validateTrainId(string train_id);
    bool validateStationId(string station_id);
    bool validateCornerId(int corner_id);
    bool validateDecoderId(int decoder_id);

    void cleanStream();
};

#endif /* TRAINCONTROLLER_HPP_ */
