
#include <ctime>
#include <string>
#include <cstdarg>
#include "Log.h"
#include "QDebug"
#include "QThread"
using std::fstream;
using std::string;
using std::ios;
using std::streampos;
using std::thread;
using std::mutex;
using std::time;
// ���캯��  filepath��ʾ��־�ļ�����·��
CLog::CLog(const char *filePath, LOG_LEVEL level):m_showLogFlag(true), m_LogLevel(level),
	m_maxLogFileSize(10 * 1024 * 1024), m_logFilePath(filePath)
{
	m_fileOut.open(filePath,ios::out | ios::app);
	m_openSuccess = m_fileOut.is_open();
	thread WriteLogThread(&CLog::WriteLogRunThread, this);
	WriteLogThread.detach();
	initVal();
}

CLog::CLog(const wchar_t *filePath, LOG_LEVEL level):m_showLogFlag(true), m_LogLevel(level),
	m_maxLogFileSize(10 * 1024 * 1024)
{
	m_fileOut.open(filePath, ios::out | ios::app);
	m_openSuccess = m_fileOut.is_open();
	m_logFilePath = WtoC(filePath);
	thread WriteLogThread(&CLog::WriteLogRunThread, this);
	WriteLogThread.detach();
	initVal();
}


void CLog::initVal()
{
	m_softWarever = "1.0.0.1";
	m_UserName = WtoC(L"����");
	m_userType = WtoC(L"����Ա");
}

void CLog::OpenLogFile(const char *pFilePath, LOG_LEVEL level)
{
	if (pFilePath)
	{
		if (m_openSuccess)  // ����Ѿ����ļ� �ر�ԭ�ļ�
		{
			CloseLogFile();
		}
		m_fileOut.open(pFilePath, ios::out | ios::app);
	}
	m_openSuccess = m_fileOut.is_open();
	m_LogLevel = level;
	m_logFilePath = pFilePath;
}

void CLog::OpenLogFile(const wchar_t *pFilePath, LOG_LEVEL level)
{
	if (pFilePath)
	{
		if (m_openSuccess)  // ����Ѿ����ļ� �ر�ԭ�ļ�
		{
			CloseLogFile();
		}
		m_fileOut.open(pFilePath, ios::out | ios::app);
	}
	m_openSuccess = m_fileOut.is_open();
	m_LogLevel = level;
	m_logFilePath = WtoC(pFilePath);
}

// <Summary>���ֽ��ַ�ת���ֽ��ַ�</Summary>
// <DateTime>2013/9/9</DateTime>
// <Parameter name="pWcsStr" type="IN">���ֽ��ַ���</Parameter>
// <Returns>���ֽ��ַ���</Returns>
string CLog::WtoC(const wchar_t *pWcsStr)
{
	char* old_locale = _strdup(setlocale(LC_CTYPE, NULL)); //�����ϵ���ϵ												   
	setlocale(LC_CTYPE, setlocale(LC_ALL, "")); // �����µ���ϵ
    size_t wcsStrLen = wcslen(pWcsStr) + 1;   // ���ַ���pWcsStr �ַ����� ����null�ַ�
	char *pDestString = (char *)malloc(wcsStrLen*2);        // ����ת������ַ����ڴ�ռ�
	if (NULL == pDestString)
	{
		return string("");
	}
	size_t numberOfCharConverted = 0;                      // ʵ��ת�����ַ����� ����null�ַ�
	wcstombs_s(&numberOfCharConverted, pDestString, wcsStrLen*2, pWcsStr, _TRUNCATE);
	QString temp(QString::fromStdWString(pWcsStr));
	string tempc = temp.toStdString();
	const char * temp2 = tempc.c_str();
	string mbsStr(pDestString);
	
	free(pDestString);
	setlocale(LC_CTYPE, old_locale);            //�ָ�ԭ������ϵ
	return mbsStr;
	
}

// <Summary>�õ���־�ļ���С</Summary>
// <DateTime>2013/9/9</DateTime>
// <Returns>��־�ļ���С</Returns>
size_t CLog::GetLogFileSize()
{
	if (!m_openSuccess)
	{
		return 0;
	}
	streampos curPos = m_fileOut.tellg();  // ��ǰ�ļ�ָ��λ��

	m_fileOut.seekg(0, ios::end);  // ���ļ�ָ��ָ���ļ�ĩβ 
	streampos pos = m_fileOut.tellg(); // ��ȡ�ļ�ָ���λ�� ��ֵ��Ϊ�ļ���С
	m_fileOut.seekg(curPos);   // �ָ��ļ�ָ��λ��
	return static_cast<size_t>(pos);
}

// ��logTextд����־�ļ�
// level: ������־��Ϣ����  logText����־����
void CLog::WriteLog(string logText, LOG_LEVEL level)
{
    if (m_openSuccess && level <= m_LogLevel)
    {
        string flag;
        if (level <= LL_ERROR)
        {
            flag = "[ERROR] ";
        }
        else if (level >= LL_INFORMATION)
        {
            flag = "[INFORMATION] ";
        }
        else 
        {
            flag = "[WARN] ";
        }
        if (m_showLogFlag)
        {
        	logText = flag + logText;
        }
        if (m_maxLogFileSize > 0 && GetLogFileSize() > m_maxLogFileSize)  // ��־��Ϣ���������־��С ���������־
		{
			ClearLogFile();
		}
		// д��־��Ϣ
		m_fileOut.write(logText.c_str(), logText.size()); 
		// ����־�����ʱ����Ϣ
		time_t nowTime = time(NULL);
        struct tm *pLocalTime = localtime(&nowTime);
		char timeString[100] = {0};
		sprintf_s(timeString, " [%04d-%02d-%02d %02d:%02d:%02d]\n", pLocalTime->tm_year + 1900, pLocalTime->tm_mon + 1, 
			pLocalTime->tm_mday, pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec);
		m_fileOut.write(timeString, strnlen(timeString, sizeof(timeString)));
        m_fileOut.flush();
    }
    return;
}

void CLog::WriteLog(LOG_LEVEL level, const char *pLogText, ...)
{
    va_list args;
    char logText[LOG_LINE_MAX] = {0};
    va_start(args, pLogText);
    vsnprintf_s(logText, LOG_LINE_MAX - 1, pLogText, args);
    WriteLog(logText, level);
}

// <Summary>��ʽ���ַ���</Summary>
// <DateTime>2013/10/31</DateTime>
// <Parameter name="srcString" type="IN">��Ҫ���и�ʽ�����ַ���</Parameter>
// <Parameter name="pFormatString" type="IN">��ʽ�ַ���</Parameter>
// <Returns>��ʽ������ַ���</Returns>
const string& CLog::StringFormat(std::string &srcString, const char *pFormatString, ...)
{
    va_list args;
    char tempString[2048] = {0};  // ��ʽ���ַ������֧��2048���ֽ�
    va_start(args, pFormatString);
    vsnprintf_s(tempString, sizeof(tempString), pFormatString, args);
    srcString = tempString;
    return srcString;
}

// <Summary>����־�ַ���ת��Ϊ��������־��Ϣ</Summary>
// <DateTime>2013/10/31</DateTime>
// <Parameter name="pLogText" type="IN">��־�ַ���</Parameter>
// <Parameter name="level" type="IN">��־����</Parameter>
// <Returns>��������־��Ϣ</Returns>
string CLog::ConvertToRealLogText(const char *pLogText, LOG_LEVEL level)
{
    if (NULL == pLogText)
    {
        return string("");
    }

    // �õ���ǰϵͳʱ��
    time_t nowTime = time(NULL);
    struct tm *pLocalTime = localtime(&nowTime);

    string strLogText(pLogText);
    string::size_type pos = strLogText.find("$(");
    while (pos != string::npos)
	{
	//	pLogText = 0x04dcf8f0 "{$(SOFTWAREVER)}_[$(DATETIME)]_[$(USER)]_log�������ˣ�log_Text_0_[$(LEVELFLAG)]\n"
        string::size_type tempPos = strLogText.find(")", pos);
        if (tempPos != string::npos)
        {
            string strSubString = strLogText.substr(pos, tempPos - pos + 1);
            if (strSubString == string("$(DATE)"))
            {
                StringFormat(strSubString, "%04d-%02d-%02d", pLocalTime->tm_year + 1900, pLocalTime->tm_mon + 1, pLocalTime->tm_mday);
            }
            else if (strSubString == string("$(TIME)"))
            {
                StringFormat(strSubString, "%02d:%02d:%02d", pLocalTime->tm_hour, pLocalTime->tm_min, pLocalTime->tm_sec);
            }
            else if (strSubString == string("$(DATETIME)"))
            {
                StringFormat(strSubString, "%04d-%02d-%02d %02d:%02d:%02d", pLocalTime->tm_year + 1900, 
                    pLocalTime->tm_mon + 1, pLocalTime->tm_mday, pLocalTime->tm_hour, pLocalTime->tm_min, 
                    pLocalTime->tm_sec);
            }
			else if (strSubString == string("$(SOFTWAREVER)"))
			{
				strSubString = m_softWarever;
			}
			else if (strSubString == string("$(USER)"))
			{
				strSubString = m_UserName;
			}
			else if (strSubString == string("$(USERTYPE)"))
			{
				strSubString = m_userType;
			}
            else if (strSubString == string("$(LEVELFLAG)"))
            {
                if (LL_ERROR == level)
                {
                    strSubString = "ERROR";
                }
                else if (LL_WARN == level)
                {
                    strSubString = "WARN";
                }
                else if (LL_INFORMATION == level)
                {
                    strSubString = "INFORMATION";
                }
            }
            strLogText.replace(pos, tempPos - pos + 1, strSubString);
			tempPos = strLogText.find(strSubString) + strSubString.length();
            pos = strLogText.find("$(", tempPos + 1);
        }
        else 
        {
            break;
        }
    }

    return strLogText;
}

// <Summary>
// �������� ���ڽ���־��Ҫ��ĸ�ʽ���
// ��logText��ʵ�����ݺ͸�ʽ��¼��־��Ϊ�˱�����־��¼������һЩԤ���峣�������ڴ���ĳЩ�������Ϣ
// ���������ø�ʽ������makefile�ļ��еı�������$(��������),��������Ϊ��д��Ŀ���Ѿ����õĳ����У�
//   1.$(DATE):��ʾ��ǰ���� ��ʽΪYYYY-MM-DD
//   2.$(TIME):��ʾ��ǰʱ�� ��ʽΪHH:MM:SS
//   3.$(LEVELFLAG):��ʾ����־�ļ����־
//   4.$(DATETIME):��ʾ��ǰ���ں�ʱ�� ��ʽΪYYYY-MM-DD HH:mm:SS
// ���ӣ�WriteLogEx(LL_ERROR, "[$(DATE) $(TIME)] �߳��˳� �߳�id=%d [$(LEVELFLAG)]", 10);
// Ч����[2013-10-31 09:55:30] �߳��˳� �߳�id=10 [ERROR]
// </Summary>
// <DateTime>2013/10/31</DateTime>
// <Parameter name="logText" type="IN">��־����</Parameter>
// <Parameter name="level" type="IN">��־����</Parameter>
void CLog::WriteLogEx(LOG_LEVEL level, const char *pLogText, ...)
{
    if (m_openSuccess )//&& level <= m_LogLevel)
    {
        va_list args;
        char szLogText[LOG_LINE_MAX] = {0};
        va_start(args, pLogText);
        vsnprintf_s(szLogText, LOG_LINE_MAX - 1, pLogText, args);
        string strRealLogText = ConvertToRealLogText(szLogText, level);
        if (m_maxLogFileSize > 0 && GetLogFileSize() > m_maxLogFileSize)  // ��־��Ϣ���������־��С ������ļ�//�������־
        {
			time_t nowTime = time(NULL);
			struct tm *pLocalTime = localtime(&nowTime);
			string strSubString;
			StringFormat(strSubString, "%04d-%02d-%02d %02d.%02d.%02d", pLocalTime->tm_year + 1900,
				pLocalTime->tm_mon + 1, pLocalTime->tm_mday, pLocalTime->tm_hour, pLocalTime->tm_min,
				pLocalTime->tm_sec);
			strSubString = strSubString + ".log";
			SetLofFilePath(strSubString.c_str());
        }
       m_fileOut.write(strRealLogText.c_str(), strRealLogText.length());
    }
}

void CLog::WriteLogQstring( int level, QString qLogText, ...)
{
	/*string temp(WtoC(qLogText.toStdWString().c_str()));
	temp = "{$(SOFTWAREVER)}_[$(DATETIME)]_[$(USER)]_" + temp + "_[$(LEVELFLAG)]\n";
	*/
	int LevelValue = (int)level;
	QString LevelQstr = QString::number(LevelValue);
	qLogText = LevelQstr+ qLogText ;
	m_Mutex.lock();
	m_LogDataList.push_back(qLogText);
	m_Mutex.unlock();
}

void CLog::WriteLogRunThread()
{
	/*try
	{
		m_Mutex.lock();
		WriteLogEx(level, pLogText.c_str());
		m_Mutex.unlock();
	}
	catch(...)
	{
		WriteLogEx(LL_ERROR,"{$(SOFTWAREVER)}_[$(DATETIME)]_[$(USER)]_ LogWritError_[$(LEVELFLAG)]\n");
		m_Mutex.unlock();
	}*/
	while (1)
	{
		QString LogDataTemp;
		m_Mutex.lock();
		if (m_LogDataList.length() > 0)
		{
			LogDataTemp = m_LogDataList.at(0);
			m_Mutex.unlock();
		}
		else
		{
			m_Mutex.unlock();
			continue;
		}
		if (LogDataTemp == "ExitThead")
			return;
		QString FileData = LogDataTemp.right(LogDataTemp.length()-1);
		LOG_LEVEL LevelValue = (LOG_LEVEL)(LogDataTemp.left(1).toInt());
		string temp(WtoC(FileData.toStdWString().c_str()));
		temp = "{[$(DATETIME)]-[����汾��$(SOFTWAREVER)]-[�û�����$(USER)($(USERTYPE))]}" + temp + "-[$(LEVELFLAG)]\n";
		WriteLogEx(LevelValue, temp.c_str());
		m_Mutex.lock();
		m_LogDataList.removeAt(0);
		m_Mutex.unlock();
	}
}

void CLog::ExitLogRunThread()
{
	m_Mutex.lock();
	while (m_LogDataList.length() !=0)
	{
		m_Mutex.unlock();
		_sleep(20);
		m_Mutex.lock();
	}
	m_Mutex.unlock();
	m_Mutex.lock();
	m_LogDataList << "ExitThead";
	m_Mutex.unlock();
}

void CLog::SetLofFilePath(const char *pFilePath)
{
	m_fileOut.clear();  // ������״̬
	m_fileOut.close();  // �ر���
	m_openSuccess = false;
	m_fileOut.open(pFilePath, ios::out | ios::app);
	m_openSuccess = m_fileOut.is_open();
}

void CLog::SetCurUserInfo( const wchar_t* userTypename, const wchar_t* usaername)
{
	m_UserName = WtoC(userTypename);
}

void CLog::SetCurSoftWarever(wchar_t * CurSoftWarever)
{

}

void CLog::CloseLogFile()
{
    m_fileOut.clear();  // ������״̬
    m_fileOut.close();  // �ر���
    m_openSuccess = false;
}

// ɾ����־�ļ�����
void CLog::ClearLogFile()
{
    if (!m_openSuccess || m_logFilePath == string(""))  // ��δ�ɹ���
    {
        return;
    }

    CloseLogFile(); // �ر���
    m_fileOut.open(m_logFilePath, ios::out | ios::trunc); // �ԽضϷ�ʽ���ļ�
    m_openSuccess = m_fileOut.is_open();
}