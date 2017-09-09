#pragma once
#include <afxwin.h>
#include <QTreeWidgetItem>

#define PI              3.14159265358979323846
#define SECOND          1000   //1=1ms
#define MM				1000.0 //1=0.001mm
#define DKUNIT          1000.0 // PLC DWORD TO PC double 0.001 ratio
#define DHUNIT          100.0 // PLC DWORD TO PC double 0.01 ratio
#define DTUNIT          10.0 // PLC DWORD TO PC double 0.1 ratio
#define KRATIO          1000.0 // 1000 ratio 
#define KKHZ			1000.0 // 1000K hz
#define HKHZ			100.0 // 100K hz
#define KMM				1000.0 //1=1mm

#define FULLPOW			100.0 //1=1%

#define STEPPER_WORK_IN_SPEED_MODE 0x03

#define REV_PER_SECOND_VALUE 1000//983040.0//ÿ����1ת����Ҫ����ֵ��/60 = 16384//�ٶ�ֵ
#define REV_PER_UNIT_PLUSE 100.0//6000.0
#define REV_LASER_DIST 10.0//10 mm

#define MIN_PLUSE_UNIT 0.002 

#define BRUSH_DIM 30.0

#define AXIS_STATU_ORIGIN		0x0001	//ԭ��λ
#define AXIS_STATU_LIMIT_PLUS	0x0002	//����λ
#define AXIS_STATU_LIMIT_MINUS	0x0004	//����λ
#define AXIS_STATU_ENABLE		0x0008	//ʹ��
#define AXIS_STATU_READY		0x0010	//׼����
#define AXIS_STATU_INPLACE		0x0020	//��λ
#define AXIS_STATU_ALARM		0x0040	//����
#define AXIS_STATU_STOP			0x0080	//��ͣ

//�豸��ͣ�����з���
typedef enum EM_MACHINE_SIGNAL
{
	MACHINE_START = 0,		//����
	MACHINE_RESET,			//��λ
	MACHINE_STOP,			//ֹͣ
	MACHINE_ESTOP,			//��ͣ
	MACHINE_RUNDIR,			//���з���
	MACHINE_ROLLDIR,		//�վ���
	MACHINE_RUNSCHEMA,		//���Զ�ģʽ
	MACHINE_OTHER, //
}EM_MACHINE_SIGNAL;

//ͣ������
typedef enum EM_MACHINE_STOP_TYPE
{
	TYPE_STOP,	//ֹͣ
	TYPE_ESTOP, //��ͣ
}EM_MACHINE_STOP_TYPE;

//������
class  AXIS_ATTRIBUTE
{
public:
	static const unsigned short MOVETOPOS = 1; //����λ�ƶ�
	static const unsigned short GOTOHOME = 2; //�������
	static const unsigned short TRIGGERMOVE = 4; //�������/�����ƶ�
	static const unsigned short SAVEPARAME = 8; //���������
	static const unsigned short ENABLE = 16;//����ʹ�ܲ���
};

//���ƶ��ź�
typedef enum EM_AXIS_MOVE_SIGNAL
{
	ABSOLUTE_MOVE = 0,	//�����ƶ�
	RELATIVE_MOVE,		//����ƶ�
	DISTANCE_MOVE,		//�����ƶ�
	INCHING_MOVE,		//�㶯
	GOTOHOME_MOVE,		//����
}EM_AXIS_MOVE_SIGNAL;

//������ź�
typedef enum EM_AXIS_CTRL_SIGNAL
{
	AXIS_ENABLE = 0, //��ʹ��
	AXIS_CLEANALARM, //�ᱨ�����
	AXIS_STOP,       //��ֹͣ
}EM_AXIS_CTRL_SIGNAL;



//ҳ��ģ������
typedef enum EM_MODULE_DATA_TYPE
{
	_INT = 0,
	_FLOAT,
	_BOOL,
}EM_MODULE_DATA_TYPE;

//MESҳ�����Զ�ģ��
typedef enum EM_UPLOAD_TYPE
{
	UPLOAD_AUTO = 0, //�Զ��ϴ�ģ��
	UPLOAD_MANUAL,	 //�ֶ��ϴ�ģ��
}EM_UPLOAD_TYPE;

//�����������
typedef struct _MOTORPARAM
{
	int nAxisNum;			//���
	double dlStartSpeed;	//�����ٶ�
	double dlMaxSpeed;		//����ٶ�
	double dlAddSpeed;		//���ٶ�(ʱ��)
	double dlDecSpeed;		//���ٶ�(ʱ��)
	double dlGotoHomeSpeed; //�����ٶ�
	double dlHomeToOffset;	//���ƫ��

	_MOTORPARAM()
	{
		nAxisNum		= 0;
		dlStartSpeed	= 0.0;
		dlMaxSpeed		= 0.0;
		dlAddSpeed		= 0.0;
		dlDecSpeed		= 0.0;
		dlGotoHomeSpeed = 0.0;
		dlHomeToOffset	= 0.0;
	};
}ST_MOTORPARAM,*ST_PMOTORPARAM;

//�����������
typedef struct _LASER_DATA
{
	CString strLaserFilePath;	//�����ļ�·��
	CString strLaserFileName;	//�����ļ�����
	int nLaserStep;				//�����ܲ���
	CString strLaserStepInfo;	//���ⲽ������ //�м���'-'�ָ�
	double dlEarWidth;			//�������
	double dlEarHeight;			//�����߶�
	double dlLaser1Power;		//���⹦��
	double dlLaser1Freq;		//����Ƶ��
	double dlLaser2Power;		//���⹦��
	double dlLaser2Freq;		//����Ƶ��

	_LASER_DATA()
	{
		strLaserFilePath	= _T("");
		strLaserFileName	= _T("");
		nLaserStep			= 0;
		strLaserStepInfo	= _T("");
		dlEarWidth			= 0.0;
		dlEarHeight			= 0.0;
		dlLaser1Power		= 0.0;
		dlLaser1Freq		= 0.0;
		dlLaser2Power		= 0.0;
		dlLaser2Freq		= 0.0;
	};
}ST_LASER_DATA,*ST_PLASER_DATA;

typedef enum EM_Type //�����ļ�ʱʹ��
{
	INVALID = -1,
	MD = 0,
	MW,
	QW,
	MX,
	QX,
	IX,
}EM_Type;

//�Ի���ģʽ
typedef enum EM_DIALOG_MODEL
{
	DOMODEL	  = 0,	//ģʽ�Ի���
	NODOMODEL = 1,	//��ģʽ�Ի���
	NOMESSAGE,		//����Ϣ
}EM_DIALOG_MODEL;

typedef enum EM_CHILDPAGEITEM
{
	MAINTENANCE = 0, //�豸ά��
	AUTOMATICPRODUCT,//�Զ�����
	PRODUCTEDITOR,	 //��Ʒ�༭
	HISTORICALINFO,	 //��ʷ��Ϣ
	IODEBUG,		 //IO����
	MOTORDEBUG,		 //�������
	PARAMETERSET,	 //��������
	MESONLOAD,		 //MESҳ��
	EXIT,			 //�˳�
	FILMTRIMMER,	 //UI�����
}EM_CHILDPAGEITEM;

typedef struct MODULEITEM						//����ģ��
{
	QTreeWidgetItem* ParentModuleItem;			//ģ��
	QVector<QTreeWidgetItem*> ChildModuleItems; //����
}ST_MODULEITEM, *ST_PMODULEITEM;

typedef struct VALUECFG			//ÿ�������а�������
{
	QString Addr;
	EM_Type Addr_Type;
	double Vel;
	EM_MODULE_DATA_TYPE Vel_Type;
	int Vel_Accuracy;
	int OtherAttribute;
	QString Function_name;
}ST_VALUECFG;

typedef struct MODULE			//ÿ��ģ��
{
	QVector<ST_VALUECFG> Value_;//����ֵ
	QString ModuleName;			//ģ������
	int m_nModuleLength() const	//ģ���а������������
	{
		return Value_.length();
	};
}ST_MODULE;

typedef struct _UPDATEDATA //�Զ�����������Ϣ
{
	//UI��ʹ��
	int nModuleItem;		//ģ�����
	int nChildItem;			//�������
	double dlData;			//��������
	QString qstrData;		//��������
	QString qstrModultName;	//ģ������
	//���ݴ����ʹ��
	int nAccuracy;			//��ֵ����
	DWORD dwPLCAddr;		//PLC��ַ
	EM_Type PLCAddrType;	//PLC��ַ����
}ST_UPDATEDATA, *ST_PUPDATEDATA;
typedef enum _OtherAttribute //��������
{
	INPUT_ = 0,		//�����
	OUTPUT = 1,		//�����
	ENABLEEDIT = 2,	//�ɱ༭
	DISABLEEDIT = 3,//���ɱ༭
	AUTOUPDATA = 4,//�Զ�����
}EM_OTHERATTRIBUTE;

typedef enum MOTOR_ADDR_ORDER	//��������ļ���ַ����
{
	ORDER_START_SPEED = 0,		//�����ٶ�
	ORDER_MAX_SPEED,			//����ٶ�
	ORDER_GOTOHOME_SPEED,		//�����ٶ�
	ORDER_ADD_SPEED,			//����ʱ��
	ORDER_DEC_SPEED,			//����ʱ��
	ORDER_HOME_OFFSET,			//���ƫ��
	ORDER_ALARM_CLEAN,			//�������
	ORDER_ENABLE,				//ʹ��
	ORDER_STOP,					//ֹͣ
	ORDER_ABS_TRIGGER,			//���Դ���
	ORDER_GOTO_HOME,			//����
	ORDER_JOG,					//�㶯
	ORDER_GET_STATUS,			//��ȡ״̬
	ORDER_SET_TARGET_POS,		//�趨Ŀ��λ��
	ORDER_GET_POS,				//��ȡ��ǰλ��
	ORDER_GET_SPEED,			//��ȡ��ǰ�ٶ�
	ORDER_MOTOR_PULSE,			//����
	ORDER_OTHER_ATTRIBUTE,		//��������
	
}MOTOR_ADDR_ORDER;

typedef struct CHANGE_POINT		//
{
	int nModuleNum;
	int nChildNum;
	double dlData;
}ST_CHANGE_POINT, *PST_CHANGE_POINT;
