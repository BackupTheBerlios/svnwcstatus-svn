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

#include "MultiChoiceDefSchedule.h"
#include "ContentField.h"

static const char* s_ppchNames[] = 
{
	"normal",
	"add",
	"delete",
	"replace"
};

CMultiChoiceDefSchedule::CMultiChoiceDefSchedule(CContentField& oForField) :
	CMultiChoiceDef(oForField)
{
}

CMultiChoiceDefSchedule::~CMultiChoiceDefSchedule()
{
}

size_t CMultiChoiceDefSchedule::getChoiceCount() const
{
	return (sizeof(s_ppchNames) / sizeof(char*));
}

const char* CMultiChoiceDefSchedule::getChoiceName(int iChoice) const
{
	if (iChoice < 1 || (size_t)iChoice > getChoiceCount())
	{
		return NULL;
	}

	return s_ppchNames[iChoice - 1];
}
