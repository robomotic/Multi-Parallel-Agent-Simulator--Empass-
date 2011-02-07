/*
 * SampleSetWriter.h
 *
 *  Created on: Jul 14, 2009
 *      Author: Alessio Sclocco <alessio@sclocco.eu>
 *
 *     License: See the end of this file for license information
 */

#ifndef SAMPLESETWRITER_H_
#define SAMPLESETWRITER_H_

#include "SampleSet.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>

using std::string;
using std::ofstream;
using std::vector;
using std::map;
using std::endl;

namespace ita {

class SampleSetWriter {
public:
	SampleSetWriter(string pathFile);
	~SampleSetWriter();
	void setSamplesNumber(unsigned int i);
	inline const unsigned int getSamplesCounter();
	SampleSetWriter &operator<<(SampleSet &sset);

private:
	ofstream file;
	unsigned int samples;
};

}

#endif /* SAMPLESETWRITER_H_ */

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
