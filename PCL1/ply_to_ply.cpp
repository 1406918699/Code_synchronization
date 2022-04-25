//#include <iostream>          
//#include <pcl/io/pcd_io.h>  
//#include <pcl/point_types.h> 
//#include <pcl/io/ply_io.h>  
//
//int main(int argc, char** argv)
//{
//	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
//	pcl::io::loadPLYFile("hand.ply", *cloud);
//	pcl::io::savePCDFileBinary("hand.pcd", *cloud);
//
//	return 0;
//}

#include <iostream>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/common/io.h>
#include <pcl/point_cloud.h>

#include <pcl/PolygonMesh.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <pcl/io/vtk_lib_io.h>

#include<pcl/io/io.h>
#include<pcl/io/pcd_io.h>//pcd ��д����ص�ͷ�ļ���
#include<pcl/io/ply_io.h>
#include<pcl/point_types.h> //PCL��֧�ֵĵ�����ͷ�ļ���
#include<string>
#include <sstream>
int user_data;
using namespace std;

string intToString(int num)
{
	stringstream ss;
	ss << num;
	return ss.str();
}
int main()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());//�������ƶ���
	//pcl::PolygonMesh mesh;
	//vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	string file = "triangularization_result";
	string file_path = "C:\\Users\\14069\\Documents\\PCL_files\\";
	string file_ply_org = file_path + file + ".ply";
	string file_ply_trans = file_path + file + ".ply";
	pcl::io::loadPLYFile(file_ply_org, *cloud);									//PCL����VTK��IO�ӿڣ�����ֱ�Ӷ�ȡstl,ply,obj�ȸ�ʽ����ά��������,����PolygonMesh����
	//pcl::io::mesh2vtk(mesh, polydata);												//��PolygonMesh����ת��ΪvtkPolyData����
	//pcl::io::vtkPolyDataToPointCloud(polydata, *cloud);								//��ȡ����
	pcl::io::savePLYFileASCII(file_ply_trans, *cloud);									//�洢Ϊpcb�ļ�

	//for (int i = 0; i < 6; i++)
	//{
	//	file = "final3d_model_pt" + intToString(i + 4);
	//	string file_path = "C:\\Users\\14069\\Documents\\Visual Studio 2013\\Projects\\PCL1\\PCL1\\files\\";
	//	string file_ply = file_path + file + ".ply";
	//	string file_pcd = file_path + file + ".pcd";
	//	pcl::io::loadPLYFile(file_ply, *cloud);
	//	pcl::io::savePCDFileASCII(file_pcd, *cloud);
	//}

	return 0;
}