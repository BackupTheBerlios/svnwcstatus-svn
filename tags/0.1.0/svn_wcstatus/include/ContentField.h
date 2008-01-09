/* Copyright 2007, 2008 Tom Wieczorek
 *
 * This file is part of svn_wcstatus.
 *
 * svn_wcstatus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * svn_wcstatus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with svn_wcstatus. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELD__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELD__

#include "ContentInstance.h"

class CMultiChoiceDef;

class CContentField
{
public:
	virtual ~CContentField();

	virtual const char* getName() const = 0;
	virtual int getType() const = 0;

	virtual bool hasMultiChoiceDef() const;
	virtual const CMultiChoiceDef* getMultiChoiceDef() const;
	virtual void getUnits(char* pchUnits, int iMaxBuf) const;

	virtual int fillInDefinition(char* pchName, char* pchUnits, int iMaxBuf) const;

	virtual CContentInstance* getInstance(const char* pchPath) = 0;
};

#endif
