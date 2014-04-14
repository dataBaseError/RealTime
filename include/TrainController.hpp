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

class TrainController {

public:

	TrainController();

	string getTrainControl(int train_id);

	string getF1Control();

	string getF2Control();

	string getJ1Control();

	string getJ2Control();

	string setDirection(int direction);

	string setSpeed(int direction);

	string setTrackF1(int lane);

	string setTrackF2(int lane);

	string setTrackJ1(int lane);

	string setTrackJ2(int lane);
};



#endif /* TRAINCONTROLLER_HPP_ */
