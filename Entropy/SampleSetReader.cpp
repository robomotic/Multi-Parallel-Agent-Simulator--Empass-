/*
 * SampleSetReader.cpp
 *
 *  Created on: Jul 5, 2009
 *      Author: Alessio Sclocco <alessio@sclocco.eu>
 *
 *     License: See the end of this file for license information
 */

#include "include/SampleSetReader.h"

namespace ita {

SampleSetReader::SampleSetReader(string pathFile) {
	(this->file).open(pathFile.c_str());
}

SampleSetReader::~SampleSetReader() {
	(this->file).close();
}

SampleSetReader & SampleSetReader::operator>>(SampleSet &sset) {
	char tempRow[MAXIMUM_VARIABLES];
	/* Variables number */
	unsigned int varNumber = 0;
	/* Symbol counter for variables */
	map< unsigned int, map< char, unsigned int > > symbolCounter;
	/* Sequence holder */
	map< unsigned int, vector< char > > sequencesHolder;
	/* Samples number */
	unsigned int samplesNumber = 0;

	while ( true ) {
		file.getline(tempRow, MAXIMUM_VARIABLES);

		if ( file.eof() ) {
			break;
		}
		else {
			unsigned int i = 0;
			char tempSymbol = '\0';

			varNumber = 0;
			samplesNumber++;

			while ( (tempSymbol = tempRow[i++]) != '\0' ) {
				if ( tempSymbol == ' ' || tempSymbol == '\r' ) {
					continue;
				}

				sequencesHolder[varNumber].push_back(tempSymbol);

				map< unsigned int, map< char, unsigned int > >::iterator varIterator;
				if ( (varIterator = symbolCounter.find(varNumber)) == symbolCounter.end() ) {
					map< char, unsigned int > tempMap;
					tempMap.insert(pair< char, unsigned int >(tempSymbol, 1));
					symbolCounter.insert(pair< unsigned int, map< char, unsigned int > >(varNumber, tempMap));

				}
				else {
					map< char, unsigned int >::iterator symbolIterator;
					if ( (symbolIterator = (*varIterator).second.find(tempSymbol)) == (*varIterator).second.end() ) {
						(*varIterator).second.insert(pair< char, unsigned int >(tempSymbol, 1));
					}
					else {
						(*symbolIterator).second++;
					}
				}

				varNumber++;
			}
		}
	}

	varNumber = 0;
	for ( map< unsigned int, map< char, unsigned int > >::const_iterator varIterator = symbolCounter.begin(); varIterator != symbolCounter.end(); varIterator++ ) {
		unsigned int notNullSamples = 0;
		AleatoryVariable< char > *var = new AleatoryVariable< char >();
		ostringstream converter;
		converter << (*varIterator).first;
		var->setName(converter.str());

		map< char, unsigned int >::const_iterator nullSymbol;
		if ( (nullSymbol = (*varIterator).second.find(sset.getNullSymbol())) != (*varIterator).second.end() ) {
			notNullSamples = (samplesNumber - (*nullSymbol).second) + ((*nullSymbol).second * ((*varIterator).second.size() - 1));
		}
		else {
			notNullSamples = samplesNumber;
		}

		for ( map< char, unsigned int >::const_iterator symbolIterator = (*varIterator).second.begin(); symbolIterator != (*varIterator).second.end(); symbolIterator++ ) {
			if ( symbolIterator != nullSymbol ) {
				if ( nullSymbol != (*varIterator).second.end() ) {
					var->addSymbol((*symbolIterator).first, static_cast< double >((*symbolIterator).second + (*nullSymbol).second) / notNullSamples);
				}
				else {
					var->addSymbol((*symbolIterator).first, static_cast< double >((*symbolIterator).second) / notNullSamples);
				}
			}
		}

		for ( vector< char >::const_iterator sequenceIterator = sequencesHolder[varNumber].begin(); sequenceIterator != sequencesHolder[varNumber].end(); sequenceIterator++  ) {
			var->enqueueInSequence(*sequenceIterator);
		}

		sset.addVariable(var);
		varNumber++;
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
