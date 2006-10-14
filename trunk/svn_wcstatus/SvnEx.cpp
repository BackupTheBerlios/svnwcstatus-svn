#include "SvnEx.h"

#include "svn_error.h"

CSvnEx::CSvnEx(svn_error_t* pErr) :
	m_pErr(pErr)
{
}

CSvnEx::~CSvnEx()
{
	svn_error_clear(m_pErr);
}
