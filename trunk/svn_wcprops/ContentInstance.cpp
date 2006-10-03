#include "ContentInstance.h"

CContentInstance::CContentInstance(const CContentField& oField, const char* pchPath) :
	m_oField(oField)
{
	strncpy(m_achFile, pchPath, sizeof(m_achFile) - 1);
	m_achFile[sizeof(m_achFile) - 1] = '\0';
}

CContentInstance::~CContentInstance()
{
}

const CContentField& CContentInstance::getType() const
{
	return m_oField;
}
