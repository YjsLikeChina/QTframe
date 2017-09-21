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

#define REV_PER_SECOND_VALUE 1000//983040.0//每秒钟1转所需要的数值、/60 = 16384//速度值
#define REV_PER_UNIT_PLUSE 100.0//6000.0
#define REV_LASER_DIST 10.0//10 mm

#define MIN_PLUSE_UNIT 0.002 

#define BRUSH_DIM 30.0

#define AXIS_STATU_ORIGIN		0x0001	//原点位
#define AXIS_STATU_LIMIT_PLUS	0x0002	//正限位
#define AXIS_STATU_LIMIT_MINUS	0x0004	//负限位
#define AXIS_STATU_ENABLE		0x0008	//使能
#define AXIS_STATU_READY		0x0010	//准备好
#define AXIS_STATU_INPLACE		0x0020	//到位
#define AXIS_STATU_ALARM		0x0040	//报警
#define AXIS_STATU_STOP			0x0080	//暂停

//设备启停，运行方向(页面槽函数发送的信息)
typedef enum EM_MACHINE_SIGNAL
{
	MACHINE_START = 0,		//启动
	MACHINE_RESET,			//复位
	MACHINE_STOP,			//停止
	MACHINE_ESTOP,			//急停
	MACHINE_RUNDIR,			//运行方向
	MACHINE_ROLLDIR,		//收卷方向
	MACHINE_RUNSCHEMA,		//手自动模式
	MACHINE_OTHER, //
}EM_MACHINE_SIGNAL;

typedef enum MACHINE_STATUS
{
	BEGIN_STATUS = 0,//开始状态
	INITIALIZATION_STATUS,		//初始化状态
	READY_STATUS,				//准备状态
	RUN_STATUS,					//运行状态
	ALARM_STATUS,				//报警状态
}MACHINE_STATUS;

typedef enum MACHINE_FLAG
{
	OPERATOR_ING,				//动作执行中
	OPERATOR_END,				//动作执行完成
	OPERATOR_FAIL,				//动作执行失败
}MACHINE_FLAG;

typedef enum MACHINE_STATUSTOOL_COLOR
{
	COLOR_GREEN = 1,
	COLOR_GRAY,
	COLOR_YELLOW,
	COLOR_RED,
}MACHINE_STATUSTOOL_COLOR;

//设备事件
typedef enum MACHINE_EVENT
{
	NULL_EVENT = -1,	 //无事件
	START_EVENT = 0,     //开始事件
	STOP_EVENT,		     //停止事件
	RESET_EVENT,		 //复位事件
	ESTOP_EVENT,		 //急停事件
	NUM_EVENT,           //事件数量
}MACHINE_EVENT;

typedef enum MACHINE_TASK
{
	MACHINE_NULL_TASK = 0,	//无任务
	MACHINE_INIT_TASK = 1,	//初始化任务
	MACHINE_RESET_TASK,		//复位任务
	MACHINE_START_TASK,		//启动任务
	MACHINE_CLEAN_ALARM_TASK,//	报警清除任务
	MACHINE_STOP_TASK,		//停止任务
	MACHINE_ESTOP_TASK,		//急停任务
	MACHINE_MAINTAIN_TASK,	//设备维护任务
}MACHINE_TASK;

//停机类型
typedef enum EM_MACHINE_STOP_TYPE
{
	TYPE_STOP,	//停止
	TYPE_ESTOP, //急停
}EM_MACHINE_STOP_TYPE;

//轴属性
class  AXIS_ATTRIBUTE
{
public:
	static const unsigned short MOVETOPOS = 1; //允许定位移动
	static const unsigned short GOTOHOME = 2; //允许归零
	static const unsigned short TRIGGERMOVE = 4; //允许相对/绝对移动
	static const unsigned short SAVEPARAME = 8; //允许保存参数
	static const unsigned short ENABLE = 16;//允许使能操作
};

//轴移动信号
typedef enum EM_AXIS_MOVE_SIGNAL
{
	ABSOLUTE_MOVE = 0,	//绝对移动
	RELATIVE_MOVE,		//相对移动
	DISTANCE_MOVE,		//定距移动
	INCHING_MOVE,		//点动
	GOTOHOME_MOVE,		//归零
}EM_AXIS_MOVE_SIGNAL;

//轴控制信号
typedef enum EM_AXIS_CTRL_SIGNAL
{
	AXIS_ENABLE = 0, //轴使能
	AXIS_CLEANALARM, //轴报警清除
	AXIS_STOP,       //轴停止
}EM_AXIS_CTRL_SIGNAL;



//页面模组属性
typedef enum EM_MODULE_DATA_TYPE
{
	_INT = 0,
	_FLOAT,
	_BOOL,
}EM_MODULE_DATA_TYPE;

//MES页面手自动模组
typedef enum EM_UPLOAD_TYPE
{
	UPLOAD_AUTO = 0, //自动上传模组
	UPLOAD_MANUAL,	 //手动上传模组
}EM_UPLOAD_TYPE;

//激光基本数据
typedef struct _LASER_DATA
{
	CString strLaserFilePath;	//激光文件路径
	CString strLaserFileName;	//激光文件名称
	int nLaserStep;				//激光总步数
	CString strLaserStepInfo;	//激光步数参数 //中间是'-'分隔
	double dlEarWidth;			//极耳宽度
	double dlEarHeight;			//极耳高度
	double dlLaser1Power;		//激光1功率
	double dlLaser1Freq;		//激光1频率
	double dlLaser2Power;		//激光2功率
	double dlLaser2Freq;		//激光2频率

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

typedef enum EM_Type //配置文件时使用
{
	INVALID = -1,
	MD = 0,
	MW,
	QW,
	MX,
	QX,
	IX,
}EM_Type;

//对话框模式
typedef enum EM_DIALOG_MODEL
{
	DOMODEL	  = 0,	//模式对话框
	NODOMODEL = 1,	//非模式对话框
	NOMESSAGE,		//无信息
}EM_DIALOG_MODEL;

typedef enum EM_CHILDPAGEITEM
{
	MAINTENANCE = 0, //设备维护
	AUTOMATICPRODUCT,//自动生产
	PRODUCTEDITOR,	 //产品编辑
	HISTORICALINFO,	 //历史信息
	IODEBUG,		 //IO调试
	MOTORDEBUG,		 //电机调试
	PARAMETERSET,	 //参数设置
	MESONLOAD,		 //MES页面
	EXIT,			 //退出
	FILMTRIMMER,	 //UI主框架
	ALARMLIST,		//报警信息配置文件
}EM_CHILDPAGEITEM;

typedef struct MODULEITEM						//单个模组
{
	QTreeWidgetItem* ParentModuleItem;			//模组
	QVector<QTreeWidgetItem*> ChildModuleItems; //子项
}ST_MODULEITEM, *ST_PMODULEITEM;

typedef struct VALUECFG			//每个子项中包含的项
{
	QString Addr;
	EM_Type Addr_Type;
	double Vel;
	EM_MODULE_DATA_TYPE Vel_Type;
	int Vel_Accuracy;
	int OtherAttribute;
	QString Function_name;
}ST_VALUECFG;

typedef struct MODULE			//每个模组
{
	QVector<ST_VALUECFG> Value_;//子项值
	QString ModuleName;			//模块名称
	int m_nModuleLength() const	//模组中包含的子项个数
	{
		return Value_.length();
	};
}ST_MODULE;

typedef struct _UPDATEDATA //自动更新数据信息
{
	//UI层使用
	int nModuleItem;		//模组序号
	int nChildItem;			//子项序号
	double dlData;			//更新数据
	QString qstrData;		//更新数据
	QString qstrModultName;	//模组名称
	//数据处理层使用
	int nAccuracy;			//数值精度
	DWORD dwPLCAddr;		//PLC地址
	EM_Type PLCAddrType;	//PLC地址类型
}ST_UPDATEDATA, *ST_PUPDATEDATA;

typedef enum _OtherAttribute //其他属性
{
	INPUT_ = 1,		//输入点
	OUTPUT = 2,		//输出点
	ENABLEEDIT = 4,	//可编辑
	DISABLEEDIT = 8,//不可编辑
	AUTOUPDATA = 16,//自动更新
}EM_OTHERATTRIBUTE;

typedef enum MOTOR_ADDR_ORDER	//电机配置文件地址排序
{
	ORDER_START_SPEED = 0,		//启动速度
	ORDER_MAX_SPEED,			//最大速度
	ORDER_GOTOHOME_SPEED,		//归零速度
	ORDER_ADD_SPEED,			//加速时间
	ORDER_DEC_SPEED,			//减速时间
	ORDER_HOME_OFFSET,			//零点偏移
	ORDER_ALARM_CLEAN,			//报警清除
	ORDER_ENABLE,				//使能
	ORDER_STOP,					//停止
	ORDER_ABS_TRIGGER,			//绝对触发
	ORDER_GOTO_HOME,			//归零
	ORDER_JOG_CW,				//点动(正转)
	ORDER_JOG_CCW,				//点动(反转转)
	ORDER_GET_STATUS,			//获取状态
	ORDER_SET_TARGET_POS,		//设定目标位置
	ORDER_GET_POS,				//获取当前位置
	ORDER_GET_SPEED,			//获取当前速度
	ORDER_MOTOR_PULSE,			//脉冲
	ORDER_OTHER_ATTRIBUTE,		//其他属性
}MOTOR_ADDR_ORDER;

//自动生产页面默认模组排序
typedef enum EM_AUTOURLDETECT_DEFAULT_ORDER
{
	ONLOAD_COILDIAMETER = 0,//放卷卷径
	ONLOAD_TENSION,			//放卷张力
	RECV_COILDIAMETER,		//收卷卷径
	RECV_TENSION,			//收卷张力
	WORK_SPEED,				//工作速度显示
	LASER_STEP,				//激光步数
	LASER_YIELD,			//激光当班产量
	LASER_SUM_YIELD,		//激光总产量
	MACHINE_RUN_DIR,		//设备运行方向
	MACHINE_ONLOAD_DIR,		//设备放卷方向

	MAINAXIS_TRACTIONPOS = 0,//牵引位置 //默认模组1
	MAINAXIS_WORKPOS = 1,	//工作位置 //默认模组1

}EM_AUTOURLDETECT_DEFAULT_ORDER;

//FilmTrimmer默认参数排序
typedef enum EM_FILM_DEFAULT_ORDER
{
	CTRL_MACHINE_MODEL = 0,			//设备手自动模式
	CTRL_MACHINE_HARDWARE_STATUS,	//从PLC中读取硬件按钮状态
	CTRL_MACHINE_START,				//向PLC中写入
	CTRL_MACHINE_STOP,
	CTRL_MACHINE_RESET,
	CTRL_MACHINE_ESTOP,
	CTRL_MACHINE_MAINTAIN,			//设备维护
	CTRL_MACHINE_WORKSPEED,			//工作速度设置
	CTRL_MACHINE_STATUS,			//状态机读取地址(只读)
	CTRL_MACHINE_ALARM,				//状态机读取地址(报警状态)
	CTRL_MACHINE_FLAG,				//状态机标志位(只读)
}EM_FILM_DEFAULT_ORDER;

//产品编辑页面默认排序
typedef enum EM_PRODUCTEDITOR_ORDER
{
	PACKAGE_NAME = 0,		//产品名称
	PACKAGE_LASERNAME,		//激光文件名
	PACKAGE_FILEWIDTH,		//极耳宽度
	PACKAGE_HIGH,			//极耳高度
	PACKAGE_LASER1_POWER,	//激光1功率
	PACKAGE_LASER1_FREQ,	//激光1频率
	PACKAGE_LASER2_POWER,	//激光2功率
	PACKAGE_LASER2_FREQ,	//激光2频率
	PACKAGE_STRAT_LINE,		//起始边使能
	PACKAGE_RISE_TRIGGER,	//上升沿触发
	PACKAGE_FALL_TRIGGER,	//下降沿触发
}EM_PRODUCTEDITOR_ORDER;

typedef struct CHANGE_POINT		//
{
	int nModuleNum;
	int nChildNum;
	double dlData;
}ST_CHANGE_POINT, *PST_CHANGE_POINT;
