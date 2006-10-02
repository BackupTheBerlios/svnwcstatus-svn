#include "ContentFieldSvnAuthor.h"
#include "ContentInstanceString.h"

CContentFieldSvnAuthor::CContentFieldSvnAuthor()
{
}

CContentFieldSvnAuthor::~CContentFieldSvnAuthor()
{
}

const char* CContentFieldSvnAuthor::getName() const
{
	return "svn-author";
}

int CContentFieldSvnAuthor::getType() const
{
	return ft_string;
}

CContentInstancePtr CContentFieldSvnAuthor::getInstance(const char* pchFile)
{
	return new CContentInstanceString(*this, pchFile, pchFile);
}
