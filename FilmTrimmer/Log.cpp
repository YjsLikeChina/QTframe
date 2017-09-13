
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
// 构造函数  filepath表示日志文件完整路径
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
	m_UserName = WtoC(L"张三");
	m_userType = WtoC(L"管理员");
}

void CLog::OpenLogFile(const char *pFilePath, LOG_LEVEL level)
{
	if (pFilePath)
	{
		if (m_openSuccess)  // 如果已经打开文件 关闭原文件
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
		if (m_openSuccess)  // 如果已经打开文件 关闭原文件
		{
			CloseLogFile();
		}
		m_fileOut.open(pFilePath, ios::out | ios::app);
	}
	m_openSuccess = m_fileOut.is_open();
	m_LogLevel = level;
	m_logFilePath = WtoC(pFilePath);
}

// <Summary>宽字节字符转多字节字符</Summary>
// <DateTime>2013/9/9</DateTime>
// <Parameter name="pWcsStr" type="IN">宽字节字符串</Parameter>
// <Returns>多字节字符串</Returns>
string CLog::WtoC(const wchar_t *pWcsStr)
{
	char* old_locale = _strdup(setlocale(LC_CTYPE, NULL)); //抱存老的语系												   
	setlocale(LC_CTYPE, setlocale(LC_ALL, "")); // 设置新的语系
    size_t wcsStrLen = wcslen(pWcsStr) + 1;   // 宽字符串pWcsStr 字符个数 包括null字符
	char *pDestString = (char *)malloc(wcsStrLen*2);        // 申请转换后的字符串内存空间
	if (NULL == pDestString)
	{
		return string("");
	}
	size_t numberOfCharConverted = 0;                      // 实际转化的字符个数 包括null字符
	wcstombs_s(&numberOfCharConverted, pDestString, wcsStrLen*2, pWcsStr, _TRUNCATE);
	QString temp(QString::fromStdWString(pWcsStr));
	string tempc = temp.toStdString();
	const char * temp2 = tempc.c_str();
	string mbsStr(pDestString);
	
	free(pDestString);
	setlocale(LC_CTYPE, old_locale);            //恢复原来的语系
	return mbsStr;
	
}

// <Summary>得到日志文件大小</Summary>
// <DateTime>2013/9/9</DateTime>
// <Returns>日志文件大小</Returns>
size_t CLog::GetLogFileSize()
{
	if (!m_openSuccess)
	{
		return 0;
	}
	streampos curPos = m_fileOut.tellg();  // 当前文件指针位置

	m_fileOut.seekg(0, ios::end);  // 将文件指针指向文件末尾 
	streampos pos = m_fileOut.tellg(); // 获取文件指针的位置 该值即为文件大小
	m_fileOut.seekg(curPos);   // 恢复文件指针位置
	return static_cast<size_t>(pos);
}

// 将logText写入日志文件
// level: 该条日志信息级别  logText：日志内容
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
        if (m_maxLogFileSize > 0 && GetLogFileSize() > m_maxLogFileSize)  // 日志信息超过最大日志大小 则先清空日志
		{
			ClearLogFile();
		}
		// 写日志信息
		m_fileOut.write(logText.c_str(), logText.size()); 
		// 在日志后添加时间信息
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

// <Summary>格式化字符串</Summary>
// <DateTime>2013/10/31</DateTime>
// <Parameter name="srcString" type="IN">需要进行格式化的字符串</Parameter>
// <Parameter name="pFormatString" type="IN">格式字符串</Parameter>
// <Returns>格式化后的字符串</Returns>
const string& CLog::StringFormat(std::string &srcString, const char *pFormatString, ...)
{
    va_list args;
    char tempString[2048] = {0};  // 格式化字符串最大支持2048个字节
    va_start(args, pFormatString);
    vsnprintf_s(tempString, sizeof(tempString), pFormatString, args);
    srcString = tempString;
    return srcString;
}

// <Summary>将日志字符串转化为真正的日志信息</Summary>
// <DateTime>2013/10/31</DateTime>
// <Parameter name="pLogText" type="IN">日志字符串</Parameter>
// <Parameter name="level" type="IN">日志级别</Parameter>
// <Returns>真正的日志信息</Returns>
string CLog::ConvertToRealLogText(const char *pLogText, LOG_LEVEL level)
{
    if (NULL == pLogText)
    {
        return string("");
    }

    // 得到当前系统时间
    time_t nowTime = time(NULL);
    struct tm *pLocalTime = localtime(&nowTime);

    string strLogText(pLogText);
    string::size_type pos = strLogText.find("$(");
    while (pos != string::npos)
	{
	//	pLogText = 0x04dcf8f0 "{$(SOFTWAREVER)}_[$(DATETIME)]_[$(USER)]_log测试来了！log_Text_0_[$(LEVELFLAG)]\n"
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
// 新增函数 用于将日志按要求的格式输出
// 以logText的实际内容和格式记录日志，为了便于日志记录，设置一些预定义常量，用于代表某些特殊的信息
// 常量的引用格式，类似makefile文件中的变量，即$(常量名称),常量名称为大写，目标已经可用的常量有：
//   1.$(DATE):表示当前日期 格式为YYYY-MM-DD
//   2.$(TIME):表示当前时间 格式为HH:MM:SS
//   3.$(LEVELFLAG):表示该日志的级别标志
//   4.$(DATETIME):表示当前日期和时间 格式为YYYY-MM-DD HH:mm:SS
// 例子：WriteLogEx(LL_ERROR, "[$(DATE) $(TIME)] 线程退出 线程id=%d [$(LEVELFLAG)]", 10);
// 效果：[2013-10-31 09:55:30] 线程退出 线程id=10 [ERROR]
// </Summary>
// <DateTime>2013/10/31</DateTime>
// <Parameter name="logText" type="IN">日志内容</Parameter>
// <Parameter name="level" type="IN">日志级别</Parameter>
void CLog::WriteLogEx(LOG_LEVEL level, const char *pLogText, ...)
{
    if (m_openSuccess )//&& level <= m_LogLevel)
    {
        va_list args;
        char szLogText[LOG_LINE_MAX] = {0};
        va_start(args, pLogText);
        vsnprintf_s(szLogText, LOG_LINE_MAX - 1, pLogText, args);
        string strRealLogText = ConvertToRealLogText(szLogText, level);
        if (m_maxLogFileSize > 0 && GetLogFileSize() > m_maxLogFileSize)  // 日志信息超过最大日志大小 则更换文件//先清空日志
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
		temp = "{[$(DATETIME)]-[软件版本：$(SOFTWAREVER)]-[用户名：$(USER)($(USERTYPE))]}" + temp + "-[$(LEVELFLAG)]\n";
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
	m_fileOut.clear();  // 清理流状态
	m_fileOut.close();  // 关闭流
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
    m_fileOut.clear();  // 清理流状态
    m_fileOut.close();  // 关闭流
    m_openSuccess = false;
}

// 删除日志文件内容
void CLog::ClearLogFile()
{
    if (!m_openSuccess || m_logFilePath == string(""))  // 流未成功打开
    {
        return;
    }

    CloseLogFile(); // 关闭流
    m_fileOut.open(m_logFilePath, ios::out | ios::trunc); // 以截断方式打开文件
    m_openSuccess = m_fileOut.is_open();
}