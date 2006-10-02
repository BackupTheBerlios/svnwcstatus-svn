#ifndef __TW_WDX_SVN_WCPROPS_CONTENTFIELDIMPL__
#define __TW_WDX_SVN_WCPROPS_CONTENTFIELDIMPL__

#include "ContentField.h"

template <int field_type>
class TContentFieldImpl : public CContentField
{
public:
	TContentFieldImpl(const char* pchName, CFieldLoader& oParent);
	virtual ~TContentFieldImpl();

	virtual const char* getName() const;
	virtual int getType() const;
	virtual CContentInstancePtr getInstance(const char* pchFile) const;

private:
	char* m_achName;
	CFieldLoader& m_oParent;
};

template <int field_type>
TContentFieldImpl<field_type>::TContentFieldImpl(const char* pchName, CFieldLoader& oParent) :
	m_oParent(oParent)
{
	m_achName = new char[strlen(pchName) + 1];
	strcpy(m_achName, pchName);
}

template <int field_type>
TContentFieldImpl<field_type>::~TContentFieldImpl()
{
	if (m_achName)
	{
		delete [] m_achName;
		m_achName = NULL;
	}
}

template <int field_type>
int TContentFieldImpl<field_type>::getType() const
{
	return field_type;
}

template <int field_type>
const char* TContentFieldImpl<field_type>::getName() const
{
	return m_achName;
}

template <int field_type>
CContentInstancePtr TContentFieldImpl<field_type>::getInstance(const char* pchFile) const
{
	return m_oParent.getInstanceByFile(*this, pchFile);
}

#endif