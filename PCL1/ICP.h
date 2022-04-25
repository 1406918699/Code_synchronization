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
	void initransmat();//初始化旋转矩阵和平移矩阵
	void sample();//采样控制点
	double closest();//找出最近点并返回误差
	void getcenter();//获取两个控制点的中心
	void rmcontcenter();//移动两个控制点的中心
	void transform();//将四元数转换成矩阵并更新整个旋转矩阵
	void uprotate();// 更新变换矩阵
	void uptranslate();
	void updata();//更新控制点坐标
	void applyall();

private:
	double distance(Vertex a, Vertex b);
	void printTT();
	void printTR();


private:
	int conNum;//控制点数目
	int iterate;//迭代次数
	double threshold;//阈值
	std::vector<Vertex> VarrP;//起始点
	std::vector<Vertex> VarrQ;
	Vertex meanP;//控制点中心
	Vertex meanQ;
	Vertex *contP;//P控制点
	Vertex *contQ;
	Vertex *rmcoP;//移动后的控制点
	Vertex *rmcoQ;

	int *index; //在采样控制点和寻找相应的点索引时使用

	double TT[3];//平移向量
	double TR[3][3];//旋转矩阵
	double Rw[3][3];//旋转的步距
	double Tw[3];//平移的步距
	double quad[4];//四元数


};

#endif  /* ICP_H */