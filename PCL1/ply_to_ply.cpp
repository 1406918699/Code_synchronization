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
#include<pcl/io/pcd_io.h>//pcd 读写类相关的头文件。
#include<pcl/io/ply_io.h>
#include<pcl/point_types.h> //PCL中支持的点类型头文件。
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
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());//创建点云对象
	//pcl::PolygonMesh mesh;
	//vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	string file = "triangularization_result";
	string file_path = "C:\\Users\\14069\\Documents\\PCL_files\\";
	string file_ply_org = file_path + file + ".ply";
	string file_ply_trans = file_path + file + ".ply";
	pcl::io::loadPLYFile(file_ply_org, *cloud);									//PCL利用VTK的IO接口，可以直接读取stl,ply,obj等格式的三维点云数据,传给PolygonMesh对象
	//pcl::io::mesh2vtk(mesh, polydata);												//将PolygonMesh对象转化为vtkPolyData对象
	//pcl::io::vtkPolyDataToPointCloud(polydata, *cloud);								//获取点云
	pcl::io::savePLYFileASCII(file_ply_trans, *cloud);									//存储为pcb文件

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