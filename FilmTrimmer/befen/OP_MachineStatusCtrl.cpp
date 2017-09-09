#include "OP_MachineStatusCtrl.h"
#include "OP_MachineSoftWareMain.h"
#include "DP_LaserInteraction.h"
#include "DP_CfgInterface.hpp"
#include "DP_MotorCtrlInteraction.h"
#include "ui_UI_MessageBox.h"


QString g_qstrMachineCfgPath = QString::fromLocal8Bit("/Data/Machine.cfg");
QString g_qstrPackageFilePath = QString::fromLocal8Bit("/Data/Package/");

OP_MachineStatusCtrl::OP_MachineStatusCtrl()
{
	InitVal();
}


OP_MachineStatusCtrl::~OP_MachineStatusCtrl()
{
	delete m_pMessageBox;
}

void OP_MachineStatusCtrl::InitVal()
{
	m_qstrMachineCfgPath = QCoreApplication::applicationDirPath() + g_qstrMachineCfgPath;
	m_cstrMachineCfgPath = m_qstrMachineCfgPath.toStdWString().data();
	m_qstrPackageFilePath = QCoreApplication::applicationDirPath() + g_qstrPackageFilePath;
	m_bSoftwareIsFirstStart = true;
	//�Ƿ�Ϊ�ѻ���
	m_bComputerCard = ReadIntFromFile(_T("Run"), _T("ComputerCard"), 1, m_cstrMachineCfgPath);
	m_bIsAutoMoveToPos = false;
}

void OP_MachineStatusCtrl::run()
{
	//
}

bool OP_MachineStatusCtrl::MachineCtrlStart()
{
	//�ж��Ƿ�ѡ����Զ���λ
	if (GetIsAutoMovePos())
	{
		//1���жϵ��λ���Ƿ���ȷ
		if (!GetMotorIsInplace())
		{
			emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("�е�����ڹ���λ"),DOMODEL);
			return false;
		}
	}
	//�ϴ�����
	QString qstrPath = m_qstrPackageFilePath + m_qstrCurPkgName + QString::fromLocal8Bit(".pkg");

	ST_LASER_DATA stLaserData;
	stLaserData.nLaserStep = m_qVecPackageInfo.at(1).m_nModuleLength();
	CString cstrStepInfo = "";
	for (int j = 0; j < stLaserData.nLaserStep; j++)
	{
		double dlStepDist = m_qVecPackageInfo.at(1).Value_.at(j).Vel;
		cstrStepInfo.Format(_T(".3f"), dlStepDist);
		stLaserData.strLaserStepInfo = stLaserData.strLaserStepInfo + cstrStepInfo + "-";
	}
	stLaserData.strLaserStepInfo.Left(stLaserData.strLaserStepInfo.GetLength() - 1); //��������Ǹ���-��

	CString strFilePath = qstrPath.toStdWString().data();
	//Ĭ�ϲ���
	stLaserData.strLaserFileName = ReadStringFromFile(_T("�����ļ�"), _T("addr"), _T("Demo"), strFilePath);
	stLaserData.strLaserFilePath = ReadStringFromFile(_T("Run"), _T("LaserFilePath"), _T(""), m_cstrMachineCfgPath)
		+ stLaserData.strLaserFileName + _T(".hms");
	stLaserData.dlEarWidth = ReadDoubleFromFile(_T("�������"), _T("Vel"), 20.0, strFilePath);
	stLaserData.dlEarHeight = ReadDoubleFromFile(_T("�����߶�"), _T("Vel"), 15.0, strFilePath);
	stLaserData.dlLaser1Power = ReadDoubleFromFile(_T("����1����"), _T("Vel"), 30.0, strFilePath);
	stLaserData.dlLaser1Freq = ReadDoubleFromFile(_T("����1Ƶ��"), _T("Vel"), 30.0, strFilePath);
	stLaserData.dlLaser2Power = ReadDoubleFromFile(_T("����2����"), _T("Vel"), 30.0, strFilePath);
	stLaserData.dlLaser2Freq = ReadDoubleFromFile(_T("����2Ƶ��"), _T("Vel"), 30.0, strFilePath);

	if (!LASERINTERFACE.UploadLaserData(stLaserData, m_bComputerCard))
	{
		//�ϴ���������ʧ��
		return false;
	}

	//����

	return true;
}

bool OP_MachineStatusCtrl::MachineCtrlStop()
{
	return true;
}

bool OP_MachineStatusCtrl::MachineCtrlReset()
{
	if (m_bMachineCurModel)//�Զ�
	{
		//
	}
	else
	{
		//
	}
	return true;
}

bool OP_MachineStatusCtrl::MachineCtrlEStop()
{
	return true;
}

bool OP_MachineStatusCtrl::MachineCtrlMaintain()
{
	return true;
}

bool OP_MachineStatusCtrl::RunProcess()
{
	//while (true)
	//{

	//}
	return true;
}

bool OP_MachineStatusCtrl::SetOtherData()
{
	int nMachineRunDir = ReadIntFromFile(_T("Run"), _T("MachineRunDir"), 1, m_cstrMachineCfgPath);
	//�ž���
	int nMachineOnloadDir = ReadIntFromFile(_T("Run"), _T("MachineOnloadDir"), 1, m_cstrMachineCfgPath);

	//��������ҳ�������·�
	QVector<ST_MODULE> qVecParemInfo = MACHINECTRL.m_QveParameterSetting;
	int nLength = qVecParemInfo.length();
	for (int i = 0; i < nLength; i++)
	{
		int nChildNum = qVecParemInfo.at(i).m_nModuleLength();
		for (int j = 0; j < nChildNum; j++)
		{
			if (_BOOL == qVecParemInfo.at(i).Value_.at(j).Vel_Type)
			{
				bool bData = false;
				if (qVecParemInfo.at(i).Value_.at(j).Vel != 0.0)
					bData = true;
				else
					bData = false;

				HC_PLC_INTERFACE.SetBOOLToPLC(bData
					, qVecParemInfo.at(i).Value_.at(j).Addr.toInt()
					, qVecParemInfo.at(i).Value_.at(j).Addr_Type);
			}
			else
			{
				HC_PLC_INTERFACE.SetDWORDToPLC(
					qVecParemInfo.at(i).Value_.at(j).Vel * qVecParemInfo.at(i).Value_.at(j).Vel_Accuracy,
					qVecParemInfo.at(i).Value_.at(j).Addr.toInt(),
					qVecParemInfo.at(i).Value_.at(j).Addr_Type);
			}
		}
	}
	return true;
}

bool OP_MachineStatusCtrl::SetMotorSpeed()
{
	int nModuleNum = MACHINECTRL.m_QveMotorDebug.length();
	double dlStartSpeed = 0;	//�����ٶ�
	double dlMaxSpeed = 0;		//����ٶ�
	double dlAddSpeed = 0;		//����ʱ��
	double dlDecSpeed = 0;		//����ʱ��
	double dlHomeOffSet = 0;	//���ƫ��
	double dlGotoHomeSpeed = 0;	//�����ٶ�
	for (int i = 0; i < nModuleNum; i++)
	{
		dlStartSpeed = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_START_SPEED).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_START_SPEED).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_START_SPEED).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_START_SPEED).Addr_Type);

		dlMaxSpeed = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_MAX_SPEED).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_MAX_SPEED).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_MAX_SPEED).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_MAX_SPEED).Addr_Type);

		dlAddSpeed = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_ADD_SPEED).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_ADD_SPEED).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_ADD_SPEED).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_ADD_SPEED).Addr_Type);

		dlDecSpeed = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_DEC_SPEED).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_DEC_SPEED).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_DEC_SPEED).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_DEC_SPEED).Addr_Type);

		dlHomeOffSet = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_HOME_OFFSET).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_HOME_OFFSET).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_HOME_OFFSET).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_HOME_OFFSET).Addr_Type);

		dlGotoHomeSpeed = MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_GOTOHOME_SPEED).Vel * MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_GOTOHOME_SPEED).Vel_Accuracy;
		HC_PLC_INTERFACE.SetDWORDToPLC(dlStartSpeed,
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_GOTOHOME_SPEED).Addr.toInt(),
			MACHINECTRL.m_QveMotorDebug.at(i).Value_.at(ORDER_GOTOHOME_SPEED).Addr_Type);
	}
	return true;
}

bool OP_MachineStatusCtrl::GetMotorIsInplace()
{
	ST_MODULE stModuleInfo = m_qVecPackageInfo.at(2);
	return MACHINECTRL.GetAllMotorInplace(stModuleInfo);
}

bool OP_MachineStatusCtrl::GetIsAutoMovePos()
{
	QString qstrPath = MACHINECTRL.ReturnPageCfgPath(PARAMETERSET);
	CString cstrPath = qstrPath.toStdWString().data();
	return ReadBoolFromFile(_T("��λʱ����Զ���λ"), _T("Vel"), false, cstrPath);
}

bool OP_MachineStatusCtrl::InitMachineCtrl()
{
	//�·��豸��������(����ٶȡ���Ʒ������������������)
	DWORD dwStartTime = GetTickCount();
	while (1)
	{
		if (MACHINECTRL.GetOnloadConfigStatus())
		{
			//1���·��������
			SetMotorSpeed();
			//2���·���Ʒ��
			//��ȡ��ǰ��Ʒ
			CString m_cstrCurPkgName = ReadStringFromFile(_T("Run"), _T("CurrentPackage"), _T("Demo"), m_cstrMachineCfgPath);
			QString qstrCurPkgName = QString::fromStdWString(m_cstrCurPkgName.GetBuffer());
			m_cstrCurPkgName.ReleaseBuffer();
			if (!SetCrurentPackage(qstrCurPkgName))
			{
				QString strMsg = QString::fromLocal8Bit("���õ�ǰ��Ʒ\"%1\"ʧ��").arg(qstrCurPkgName);
				emit MESSAGEBOX.SigNalMessAgeBoxData(strMsg, DOMODEL);
				return false;
			}
			//3���·���������
			if (!SetOtherData())
			{
				emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("�·����ݵ�PLCʧ��!"), DOMODEL);
				return false;
			}
			break;
		}
		else
		{
			if (GetTickCount() - dwStartTime > 10000)	//���������ļ���ʱ
			{
				emit MESSAGEBOX.SigNalMessAgeBoxData(QString::fromLocal8Bit("��ȡ�豸����ʧ��!"), DOMODEL);
				return false;
			}
			Sleep(10);
		}
	}
	//�����߳�
	start();
	return true;
}

bool OP_MachineStatusCtrl::SetMachineStatus(int nModel, bool bFlag)
{
	m_nMachineCurWork = nModel;
	m_bMachineCurModel = bFlag;
	return true;
}

bool OP_MachineStatusCtrl::SetCrurentPackage(QString qstrCurPkgName)
{
	QString qstrPath = m_qstrPackageFilePath + qstrCurPkgName + QString::fromLocal8Bit(".pkg");
	if (CFGINTERFACE.JudgeFileIsExist(qstrPath))
	{
		QString qstrMsg = QString::fromLocal8Bit("���Ҳ�Ʒ�ļ�\"%1\"ʧ��!").arg(qstrCurPkgName);
		emit MESSAGEBOX.SigNalMessAgeBoxData(qstrMsg, DOMODEL);
		return false;
	}
	
	CFGINTERFACE.initCfgValue(m_qVecPackageInfo, qstrPath);
	int nModuleNum = m_qVecPackageInfo.length();
	if (0 == nModuleNum)
	{
		QString qstrMsg = QString::fromLocal8Bit("��Ʒ�ļ�\"%1\"��Ч!").arg(qstrCurPkgName);
		emit MESSAGEBOX.SigNalMessAgeBoxData(qstrMsg, DOMODEL);
		return false;
	}

	ST_LASER_DATA stLaserData;
	for (int i = 0; i < nModuleNum; i++)
	{
		//��ȡ��������
		if (i <= 1)
		{
			if (i == 1) //�������
			{
				stLaserData.nLaserStep = m_qVecPackageInfo.at(i).m_nModuleLength();
				CString cstrStepInfo = "";
				for (int j = 0; j < stLaserData.nLaserStep; j++)
				{
					double dlStepDist = m_qVecPackageInfo.at(i).Value_.at(j).Vel;
					cstrStepInfo.Format(_T(".3f"), dlStepDist);
					stLaserData.strLaserStepInfo = stLaserData.strLaserStepInfo + cstrStepInfo + "-";
				}
				stLaserData.strLaserStepInfo.Left(stLaserData.strLaserStepInfo.GetLength() - 1); //��������Ǹ���-��
			}
			else //�����������
			{
				CString strFilePath = qstrPath.toStdWString().data();
				int nLength = m_qVecPackageInfo.at(i).m_nModuleLength();
				//Ĭ�ϲ���
				stLaserData.strLaserFileName = ReadStringFromFile(_T("�����ļ�"), _T("addr"), _T("Demo"), strFilePath);
				stLaserData.strLaserFilePath = ReadStringFromFile(_T("Run"), _T("LaserFilePath"), _T(""), m_cstrMachineCfgPath)
					+ stLaserData.strLaserFileName + _T(".hms");
				stLaserData.dlEarWidth = ReadDoubleFromFile(_T("�������"), _T("Vel"), 20.0, strFilePath);
				stLaserData.dlEarHeight = ReadDoubleFromFile(_T("�����߶�"), _T("Vel"), 15.0, strFilePath);
				stLaserData.dlLaser1Power = ReadDoubleFromFile(_T("����1����"), _T("Vel"), 30.0, strFilePath);
				stLaserData.dlLaser1Freq = ReadDoubleFromFile(_T("����1Ƶ��"), _T("Vel"), 30.0, strFilePath);
				stLaserData.dlLaser2Power = ReadDoubleFromFile(_T("����2����"), _T("Vel"), 30.0, strFilePath);
				stLaserData.dlLaser2Freq = ReadDoubleFromFile(_T("����2Ƶ��"), _T("Vel"), 30.0, strFilePath);
				//�������ò���
				//0��Ʒ�ļ�,1�����ļ�,2�������,3�����߶�,4����1����,5����1Ƶ��,6����2���ʣ�7����2Ƶ��Ϊ
				for (int j = 8; j < nLength; j++)
				{
					if (_BOOL == m_qVecPackageInfo.at(i).Value_.at(j).Vel_Type)
					{
						bool bData = false;
						if (m_qVecPackageInfo.at(i).Value_.at(j).Vel != 0.0)
							bData = true;
						else
							bData = false;
						HC_PLC_INTERFACE.SetBOOLToPLC(bData, m_qVecPackageInfo.at(i).Value_.at(j).Addr.toInt(),
							m_qVecPackageInfo.at(i).Value_.at(j).Addr_Type);
					}
					else
					{
						HC_PLC_INTERFACE.SetBOOLToPLC(m_qVecPackageInfo.at(i).Value_.at(j).Vel * m_qVecPackageInfo.at(i).Value_.at(j).Vel_Accuracy, 
							m_qVecPackageInfo.at(i).Value_.at(j).Addr.toInt(),
							m_qVecPackageInfo.at(i).Value_.at(j).Addr_Type);
					}
				}
			}
			continue;
		}
		else //�·�PLC
		{
			if (!m_bSoftwareIsFirstStart) //��һ����������Ҫ���õ��λ��,�����豸���з����
			{
				m_bSoftwareIsFirstStart = false;
			}
			else
			{
				ST_MODULE stMotorModuleInfo = m_qVecPackageInfo.at(i);
				//�Ƿ���Ҫ�Զ���λ
				if (GetIsAutoMovePos())
				{
					if (MACHINECTRL.GetAllMotorIsOrigin())
					{
						MACHINECTRL.AllMotorMoveToPos(m_qVecPackageInfo);
					}
					else
					{
						if (MACHINECTRL.AllMotorGotoHome())
						{
							if (!MACHINECTRL.AllMotorMoveToPos(m_qVecPackageInfo))
							{
								//�ƶ���λʧ��
								return false;
							}
						}
						else
						{
							//����ʧ��
							return false;
						}
					}
				}
			}
		}
		//�ϴ���������
		if (!LASERINTERFACE.UploadLaserData(stLaserData, m_bComputerCard))
		{
			//�ϴ���������ʧ��
			return false;
		}
	}
	m_qstrCurPkgName = qstrCurPkgName;
	return true;
}
