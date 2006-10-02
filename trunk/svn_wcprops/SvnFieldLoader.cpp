#include "SvnFieldLoader.h"
#include "ContentFieldImpl.h"
#include "ContentInstanceString.h"

CSvnFieldLoader::CSvnFieldLoader() :
	m_pFields(new CContentField*[2]),
	m_nFieldCount(0)
{
	m_pFields[m_nFieldCount++] = new TContentFieldImpl<ft_string>("svn-author", *this);
	m_pFields[m_nFieldCount] = NULL;
}

CSvnFieldLoader::~CSvnFieldLoader()
{
	for (CContentField* pField = *m_pFields; pField; ++pField)
	{
		delete pField;
	}

	delete [] m_pFields;
}

CContentField& CSvnFieldLoader::getFieldByIndex(int iIdx)
{
	if (iIdx < 0 || (size_t)iIdx >= m_nFieldCount)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchFieldIndex);
	}

	return *(m_pFields[iIdx]);
}
