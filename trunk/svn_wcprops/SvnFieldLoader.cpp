#include "SvnFieldLoader.h"
#include "ContentInstanceString.h"
#include "ContentFieldInstance.h"

CSvnFieldLoader::CSvnFieldLoader() : 
	m_fieldAuthor("svn-author", *this)
{
}

CSvnFieldLoader::~CSvnFieldLoader()
{
}

const CContentField& CSvnFieldLoader::getFieldByIndex(int iIdx)
{
	switch (iIdx)
	{
	case 0:
		return m_fieldAuthor;

	default:
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchFieldIndex);
	}
}

CContentInstancePtr CSvnFieldLoader::getInstanceByFile(const CContentField& oRequestedType, const char* pchFile)
{
	if (&m_fieldAuthor == &oRequestedType)
	{
		return instanciateAuthor(pchFile);
	}

	throw new CFieldLoader::Ex(CFieldLoader::exNoSuchFieldIndex);
}

CContentInstancePtr CSvnFieldLoader::instanciateAuthor(const char* pchFile)
{
	return CContentInstancePtr(new CContentInstanceString(m_fieldAuthor, pchFile, pchFile));
}
