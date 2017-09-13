
#ifndef _LOG_INCLUDE_H_
#define _LOG_INCLUDE_H_

#define LOG_LINE_MAX 1024   //��־��������ַ�����
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
	enum LOG_LEVEL     // ��־����
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

    // ��ô��ļ��Ƿ�ɹ��ı�ʶ
    bool GetOpenStatus() const
    {
        return m_openSuccess;
    }

	// ����־�ļ�
    void OpenLogFile(const char *pFilePath, LOG_LEVEL level = LL_ERROR);
    void OpenLogFile(const wchar_t *pFilePath, LOG_LEVEL level = LL_ERROR);
	// д��־����
    void WriteLog(LOG_LEVEL level, const char *pLogText, ...);
    void WriteLog(string logText, LOG_LEVEL level = LL_ERROR);
    void WriteLogEx(LOG_LEVEL level, const char *pLogText, ...);
	void WriteLogQstring(int level, QString qLogText,...);
	void WriteLogRunThread(); //workдlog
	void ExitLogRunThread();//�˳�дlog�߳�
	void SetLofFilePath(const char *pFilePath); //�޸�log�ļ�·��
	void SetCurUserInfo(const wchar_t* userTypename, const wchar_t* usaername); //���õ�ǰ�û�/�û�Ȩ��
	void SetCurSoftWarever(wchar_t * CurSoftWarever);				//��������汾
	// �õ���־�ļ���С
	size_t GetLogFileSize();
	// �����־�ļ�����
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
	string WtoC(const wchar_t *pWcsStr);  // wchar_tת��Ϊstring
    string ConvertToRealLogText(const char *pLogText, LOG_LEVEL level = LL_ERROR);
    const std::string &StringFormat(std::string &srcString, const char *pFormatString, ...);
protected:
    fstream m_fileOut;
    bool m_openSuccess;  // ��־�ļ���״̬ true��ʾ�Ѿ��ɹ��� ����û�д�
	string m_logFilePath; // ��־�ļ�����·�� string����
	mutex  m_Mutex;
	int ThreadNumber = 0;
	QStringList m_LogDataList;
protected:
    LOG_LEVEL m_LogLevel;  // ��־��¼���� Ĭ��ΪLL_ERROR
	bool m_showLogFlag;    // ��ʾ��־��־  Ĭ��Ϊtrue
	size_t m_maxLogFileSize; // ��־�ļ�����С �����ô�С����ɾ�� Ĭ��Ϊ10MB
public:
	string m_UserName;		//�û���
	string m_softWarever;    //����汾
	string m_userType;	//�û�����
};

#endif

