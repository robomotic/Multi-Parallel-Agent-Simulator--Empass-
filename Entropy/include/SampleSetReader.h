/*
 * SampleSetReader.h
 *
 *  Created on: Jul 5, 2009
 *      Author: Alessio Sclocco <alessio@sclocco.eu>
 *
 *     License: See the end of this file for license information
 */

#ifndef SAMPLESETREADER_H_
#define SAMPLESETREADER_H_

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

#include "SampleSet.h"

using std::string;
using std::ostringstream;
using std::ifstream;
using std::vector;
using std::map;
using std::pair;

namespace ita {

class SampleSetReader {
public:
	SampleSetReader(string pathFile);
	~SampleSetReader();
	SampleSetReader &operator>>(SampleSet &sset);

private:
	ifstream file;
};

}

#endif /* SAMPLESETREADER_H_ */

/*
 * Copyright 2009 Alessio Sclocco <alessio@sclocco.eu>
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
 *
 */
