/*
 * SampleSet.cpp
 *
 *  Created on: Jul 8, 2009
 *      Author: Alessio Sclocco <alessio@sclocco.eu>
 *
 *     License: See the end of this file for license information
 */

#include "include/SampleSet.h"

namespace ita {

SampleSet::SampleSet() {
	this->nullSymbol = '\0';
}

SampleSet::~SampleSet() {

}

void SampleSet::setNullSymbol(char symbol) {
	this->nullSymbol = symbol;
}

char SampleSet::getNullSymbol() const {
	return this->nullSymbol;
}

void SampleSet::addVariable(AleatoryVariable< char > *var) {
	(this->vars).push_back(var);
}

unsigned int SampleSet::getVariableNumber() const {
	return static_cast< unsigned int >((this->vars).size());
}

AleatoryVariable< char > *SampleSet::getVariableById(unsigned int i) const {
	return (this->vars)[i];
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
