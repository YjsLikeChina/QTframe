#include "DP_FileOperator.h"

bool WriteIntToFile(CString strSection, CString strKey, int nData, CString strPath)
{
	CString strData;
	strData.Format(_T("%d"), nData);
	bool res = WritePrivateProfileString(strSection, strKey, strData, strPath);
	return res;
}

bool WriteDoubleToFile(CString strSection, CString strKey, double dlData, CString strPath)
{
	CString strData;
	strData.Format(_T("%.04f"), dlData);
	bool res = WritePrivateProfileString(strSection, strKey, strData, strPath);
	return res;
}

//bool WriteStringToFile(CString strSection, CString strKey, CString strData, CString strPath)
//{
//	bool res = WritePrivateProfileString(strSection, strKey, strData, strPath);
//	return res;
//}

bool WriteStringToFile(_In_opt_ LPCWSTR strSection, _In_opt_ LPCWSTR strKey, _In_opt_ LPCWSTR strData, _In_opt_ LPCWSTR strPath)
{
	bool res = WritePrivateProfileString(strSection, strKey, strData, strPath);
	return res;
}

bool WriteTypeToFile(CString strSection, CString strKey, EM_Type typeData, CString strPath)
{
	CString strData;
	switch (typeData)
	{
	case MD:
		strData = _T("MD");
		break;
	case MW:
		strData = _T("MW");
		break;
	case MX:
		strData = _T("MX");
		break;
	case QX:
		strData = _T("QX");
		break;
	case IX:
		strData = _T("IX");
		break;
	default:
		strData = _T("INVALID");
		break;
	}
	bool res = WritePrivateProfileString(strSection, strKey, strData, strPath);
	return res;
}

bool WriteBoolToFile(CString strSection, CString strKey, bool bData, CString strPath)
{
	CString strData;
	if (bData)
		strData = _T("TRUE");
	else
		strData = _T("FALSE");
	
	return WriteStringToFile(strSection, strKey, strData, strPath);	
}

int ReadIntFromFile(CString strSection, CString strKey, int ndefault, CString strPath)
{
	return GetPrivateProfileInt(strSection, strKey, ndefault, strPath);
}

double ReadDoubleFromFile(CString strSection, CString strKey, double dldefault, CString strPath)
{
	WCHAR* wcResult = new WCHAR[255];
	memset(wcResult, 0, 255);
	GetPrivateProfileString(strSection, strKey, _T("NULL"), wcResult, 254, strPath);
	if (!wcscmp(wcResult, _T("NULL")))
	{
		return dldefault;
	}
	else
	{
		return _ttof(wcResult);
	}
}

CString ReadStringFromFile(CString strSection, CString strKey, CString strdefault, CString strPath)
{
	WCHAR* wcResult = new WCHAR[255];
	memset(wcResult, 0, 255);
	GetPrivateProfileString(strSection, strKey, _T("NULL"), wcResult, 254, strPath);
	if (!wcscmp(wcResult, _T("NULL")))
	{
		return strdefault;
	}
	else
	{
		return wcResult;
	}
}

EM_Type ReadTypeFromFile(CString strSection, CString strKey, EM_Type typedefault, CString strPath)
{
	CString strDefault;
	strDefault.Format(_T("%d"), typedefault);
	CString strData = ReadStringFromFile(strSection, strKey, strDefault, strPath);
	if(!wcscmp(strData, _T("MD")))
	{
		return MD;
	}
	else if (!wcscmp(strData, _T("MW")))
	{
		return MW;
	}
	else if (!wcscmp(strData, _T("MX")))
	{
		return MX;
	}
	else if (!wcscmp(strData, _T("QX")))
	{
		return QX;
	}
	else if (!wcscmp(strData, _T("IX")))
	{
		return IX;
	}
	else
	{
		return EM_Type::INVALID;
	}
}

bool ReadBoolFromFile(CString strSection, CString strKey, bool bdefault, CString strPath)
{
	CString strdefault;
	if (bdefault)
		strdefault = _T("TRUE");
	else
		strdefault = _T("FLASE");
	CString strRes = ReadStringFromFile(strSection, strKey, strdefault, strPath);
	if (strRes == _T("TRUE"))
		return true;
	else
		return false;
}

