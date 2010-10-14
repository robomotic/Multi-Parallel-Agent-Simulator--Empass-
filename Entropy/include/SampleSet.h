/*
 * SampleSet.h
 *
 *  Created on: Jul 5, 2009
 *      Author: Alessio Sclocco <alessio@sclocco.eu>
 *
 *     License: See the end of this file for license information
 */

#ifndef SAMPLESET_H_
#define SAMPLESET_H_

#define MAXIMUM_VARIABLES 1024

#include <vector>
#include <map>
#include "AleatoryVariable.h"

using std::vector;
using std::map;
using std::pair;

namespace ita {

class SampleSet {
public:
	SampleSet();
	~SampleSet();
	void setNullSymbol(char symbol);
	char getNullSymbol() const;
	void addVariable(AleatoryVariable< char > *var);
	unsigned int getVariableNumber() const;
	AleatoryVariable< char > *getVariableById(unsigned int i) const;

private:
	char nullSymbol;
	vector< AleatoryVariable< char > * > vars;
};

}

#endif /* SAMPLESET_H_ */

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
