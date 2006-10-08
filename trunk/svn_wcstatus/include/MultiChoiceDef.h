#ifndef __TW_WDX_SVN_WCSTATUS_MULTICHOICEDEF__
#define __TW_WDX_SVN_WCSTATUS_MULTICHOICEDEF__

class CContentField;

class CMultiChoiceDef
{
public:
	enum SpecialChoiceEnum
	{
		eMultiChoiceEmpty        = -1,
		eMultiChoiceError        = -2,
		eMultiChoiceInvalidIndex = -3
	};

	CMultiChoiceDef(CContentField& oForField);
	virtual ~CMultiChoiceDef();

	virtual size_t getChoiceCount() const = 0;
	virtual const char* getChoiceName(int iChoice) const = 0;

	virtual int normalizeChoice(int iChoice) const;

	const CContentField& getField() const;

private:
	CContentField& m_oForField;
};

#endif
