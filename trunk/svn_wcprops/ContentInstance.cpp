#include "ContentInstance.h"

CContentInstance::CContentInstance(const CContentField& oField, const char* pchFile) :
	m_oField(oField)
{
	strncpy(m_achFile, pchFile, sizeof(m_achFile) - 1);
	m_achFile[sizeof(m_achFile) - 1] = '\0';
}

CContentInstance::~CContentInstance()
{
}

const CContentField& CContentInstance::getType() const
{
	return m_oField;
}
