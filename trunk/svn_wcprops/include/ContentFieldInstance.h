#ifndef __TW_WDX_SVN_WCPROPS_CONTENTFIELDINSTANCE__
#define __TW_WDX_SVN_WCPROPS_CONTENTFIELDINSTANCE__

#include "ContentField.h"

template <int field_type>
class TContentFieldInstance : public CContentField
{
public:
	TContentFieldInstance(const char* pchName, CFieldLoader& oParent);
	virtual ~TContentFieldInstance();

	virtual const char* getName() const;
	virtual int getType() const;
	virtual CContentInstancePtr getInstance(const char* pchFile) const;

private:
	char* m_achName;
	CFieldLoader& m_oParent;
};

template <int field_type>
TContentFieldInstance<field_type>::TContentFieldInstance(const char* pchName, CFieldLoader& oParent) :
	m_oParent(oParent)
{
	m_achName = new char[strlen(pchName) + 1];
	strcpy(m_achName, pchName);
}

template <int field_type>
TContentFieldInstance<field_type>::~TContentFieldInstance()
{
	if (m_achName)
	{
		delete [] m_achName;
		m_achName = NULL;
	}
}

template <int field_type>
int TContentFieldInstance<field_type>::getType() const
{
	return field_type;
}

template <int field_type>
const char* TContentFieldInstance<field_type>::getName() const
{
	return m_achName;
}

template <int field_type>
CContentInstancePtr TContentFieldInstance<field_type>::getInstance(const char* pchFile) const
{
	return m_oParent.getInstanceByFile(*this, pchFile);
}

#endif