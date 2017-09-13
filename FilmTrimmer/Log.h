
#ifndef _LOG_INCLUDE_H_
#define _LOG_INCLUDE_H_

#define LOG_LINE_MAX 1024   //日志单行最大字符长度
#include <fstream>
#include "QStringList"
#include <mutex>

using std::mutex;
using std::string;
using std::fstream;
using std::ios;

class CLog
{
public:
	enum LOG_LEVEL     // 日志级别
	{
		LL_ERROR = 1,              
		LL_WARN = 2,               
		LL_INFORMATION = 3         
	};

public:
    CLog(void):m_openSuccess(false), m_LogLevel(LL_ERROR), m_showLogFlag(true), 
		m_maxLogFileSize(10 * 1024 *1024)
    {
    }
    CLog(const char *filePath, LOG_LEVEL level = LL_ERROR);
	CLog(const wchar_t *filePath, LOG_LEVEL level = LL_ERROR);
    virtual ~CLog(void)
    {
        if (m_openSuccess)
        {
			CloseLogFile();
        }
    }

    // 获得打开文件是否成功的标识
    bool GetOpenStatus() const
    {
        return m_openSuccess;
    }

	// 打开日志文件
    void OpenLogFile(const char *pFilePath, LOG_LEVEL level = LL_ERROR);
    void OpenLogFile(const wchar_t *pFilePath, LOG_LEVEL level = LL_ERROR);
	// 写日志操作
    void WriteLog(LOG_LEVEL level, const char *pLogText, ...);
    void WriteLog(string logText, LOG_LEVEL level = LL_ERROR);
    void WriteLogEx(LOG_LEVEL level, const char *pLogText, ...);
	void WriteLogQstring(int level, QString qLogText,...);
	void WriteLogRunThread(); //work写log
	void ExitLogRunThread();//退出写log线程
	void SetLofFilePath(const char *pFilePath); //修改log文件路径
	void SetCurUserInfo(const wchar_t* userTypename, const wchar_t* usaername); //设置当前用户/用户权限
	void SetCurSoftWarever(wchar_t * CurSoftWarever);				//设置软件版本
	// 得到日志文件大小
	size_t GetLogFileSize();
	// 清空日志文件内容
	void ClearLogFile();
	void CloseLogFile();

    void SetLogLevel(LOG_LEVEL level = LL_ERROR)
    {
        m_LogLevel = level;
    }
    LOG_LEVEL GetLogLevel() const
    {
        return m_LogLevel;
    }

    void SetShowFlag(bool flag = true)
    {
        m_showLogFlag = flag;
    }
    bool GetShowFlag() const
    {
        return m_showLogFlag;
    }

    void SetMaxLogFileSize(size_t size)
    {
        m_maxLogFileSize = size;
    }
    size_t GetMaxLogFileSize() const
    {
        return m_maxLogFileSize;
    }
private:
    CLog(const CLog &clog){};
	void initVal();

protected:
	string WtoC(const wchar_t *pWcsStr);  // wchar_t转化为string
    string ConvertToRealLogText(const char *pLogText, LOG_LEVEL level = LL_ERROR);
    const std::string &StringFormat(std::string &srcString, const char *pFormatString, ...);
protected:
    fstream m_fileOut;
    bool m_openSuccess;  // 日志文件打开状态 true表示已经成功打开 否则没有打开
	string m_logFilePath; // 日志文件完整路径 string类型
	mutex  m_Mutex;
	int ThreadNumber = 0;
	QStringList m_LogDataList;
protected:
    LOG_LEVEL m_LogLevel;  // 日志记录级别 默认为LL_ERROR
	bool m_showLogFlag;    // 显示日志标志  默认为true
	size_t m_maxLogFileSize; // 日志文件最大大小 超过该大小将被删除 默认为10MB
public:
	string m_UserName;		//用户名
	string m_softWarever;    //软件版本
	string m_userType;	//用户类型
};

#endif

