#include "SvnFieldLoader.h"
#include "ContentInstanceString.h"

CSvnFieldLoader::CSvnFieldLoader() : 
	m_fieldAuthor("svn-author", *this)
{
}

CSvnFieldLoader::~CSvnFieldLoader()
{
}

CContentField& CSvnFieldLoader::getFieldByIndex(int iIdx)
{
	switch (iIdx)
	{
	case 0:
		return m_fieldAuthor;

	default:
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchFieldIndex);
	}
}
