/*
 * SampleSetWriter.cpp
 *
 *  Created on: Jul 14, 2009
 *      Author: Alessio Sclocco <alessio@sclocco.eu>
 *
 *     License: See the end of this file for license information
 */

#include "include/SampleSetWriter.h"

namespace ita {

SampleSetWriter::SampleSetWriter(string pathFile) {
	(this->file).open(pathFile.c_str());
}

SampleSetWriter::~SampleSetWriter() {
	(this->file).close();
}

void SampleSetWriter::setSamplesNumber(unsigned int i) {
	this->samples = i;
}

inline const unsigned int SampleSetWriter::getSamplesCounter() {
	return this->samples;
}

SampleSetWriter &SampleSetWriter::operator <<(SampleSet &sset) {
	map< unsigned int, vector< char > > idToDistribution;

	for ( unsigned int i(0); i < sset.getVariableNumber(); i++ ) {
		unsigned int counter = 0;
		AleatoryVariable< char > *var = sset.getVariableById(i);
		vector< char > tempVector(100, '\0');

		var->resetNextSymbol();

		try {
			while ( true ) {
				char symbol = var->getNextSymbol();

				for ( unsigned int probability = static_cast< unsigned int >(var->getSymbolProbability(symbol) * 100); probability > 0; probability-- ) {
					tempVector[counter++] = symbol;
				}
			}
		} catch ( ... ) {
			var->resetNextSymbol();
		}

		idToDistribution[i] = tempVector;
	}

	for ( unsigned int i(0); i < this->getSamplesCounter(); i++ ) {
		for ( unsigned int j(0); j < sset.getVariableNumber(); j++ ) {
			this->file << (idToDistribution[j])[rand() % 100];
			if ( j != sset.getVariableNumber() - 1 ) {
				this->file << " ";
			}
		}
		this->file << endl;
	}

	return *(this);
}

}

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
