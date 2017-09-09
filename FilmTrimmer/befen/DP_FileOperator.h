#pragma once
#include <afxwin.h>
#include "BaseDataType.h"

bool WriteIntToFile(CString strSection, CString strKey, int nData, CString strPath);
bool WriteDoubleToFile(CString strSection, CString strKey, double dlData, CString strPath);
bool WriteStringToFile(_In_opt_ LPCWSTR strSection, _In_opt_ LPCWSTR strKey, _In_opt_ LPCWSTR strData, _In_opt_ LPCWSTR strPath);
//bool WriteStringToFile(CString strSection, CString strKey, CString strData, CString strPath);
bool WriteTypeToFile(CString strSection, CString strKey, EM_Type typeData, CString strPath);
bool WriteBoolToFile(CString strSection, CString strKey, bool bData, CString strPath);

int ReadIntFromFile(CString strSection, CString strKey, int ndefault, CString strPath);
double ReadDoubleFromFile(CString strSection, CString strKey, double dldefault, CString strPath);
CString ReadStringFromFile(CString strSection, CString strKey, CString strdefault, CString strPath);
EM_Type ReadTypeFromFile(CString strSection, CString strKey, EM_Type typedefault, CString strPath);
bool ReadBoolFromFile(CString strSection, CString strKey, bool bdefault, CString strPath);
