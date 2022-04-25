/**

** Filename:icp.h

** Copyright (c) 2017-2018

** Author:Rson

** Date:2018/04/03

** Modifier:

** Date:

** Description:

**

** Version:

**/

#ifndef _ICP_H
#define _ICP_H

#include <vector>
#include <string>

#include <pcl\point_cloud.h>
#include <pcl\point_types.h>
#include <pcl\visualization\pcl_visualizer.h>

struct Vertex
{
	double coord[3];
};

struct Point
{
	float x;
	float y;
	float z;
};

class ICP
{
public:
	ICP();
	ICP(int controlnum = 1000, double thre = 0.01, int iter = 100);
	virtual ~ICP();

	void readfile(std::string firstname, std::string secondname);
	void run();
	void writefile(std::string name);
	void showcloud(std::string firstname, std::string secondname, std::string thirdname);

private:
	void initransmat();//��ʼ����ת�����ƽ�ƾ���
	void sample();//�������Ƶ�
	double closest();//�ҳ�����㲢�������
	void getcenter();//��ȡ�������Ƶ������
	void rmcontcenter();//�ƶ��������Ƶ������
	void transform();//����Ԫ��ת���ɾ��󲢸���������ת����
	void uprotate();// ���±任����
	void uptranslate();
	void updata();//���¿��Ƶ�����
	void applyall();

private:
	double distance(Vertex a, Vertex b);
	void printTT();
	void printTR();


private:
	int conNum;//���Ƶ���Ŀ
	int iterate;//��������
	double threshold;//��ֵ
	std::vector<Vertex> VarrP;//��ʼ��
	std::vector<Vertex> VarrQ;
	Vertex meanP;//���Ƶ�����
	Vertex meanQ;
	Vertex *contP;//P���Ƶ�
	Vertex *contQ;
	Vertex *rmcoP;//�ƶ���Ŀ��Ƶ�
	Vertex *rmcoQ;

	int *index; //�ڲ������Ƶ��Ѱ����Ӧ�ĵ�����ʱʹ��

	double TT[3];//ƽ������
	double TR[3][3];//��ת����
	double Rw[3][3];//��ת�Ĳ���
	double Tw[3];//ƽ�ƵĲ���
	double quad[4];//��Ԫ��


};

#endif  /* ICP_H */