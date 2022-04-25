#include<pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/common/transforms.h>

#include <iostream>
//#include<string>
#include<sstream>
using namespace std;

int main()
{
	pcl::PointCloud<pcl::PointXYZ> cloud;//创建点云对象
	pcl::io::loadPCDFile("C:/Users/14069/OneDrive/文档/机器人学/原始点.pcd", cloud);
	cout << cloud << endl;
	cout << cloud.points[0] << endl;
	cout << cloud.width << endl;
	cout << cloud.is_dense << endl;

	//------------------------------------------------------------------------------------
	//从右到左
	float theta1_x = M_PI / 2;		// 旋转弧度
	float theta1_z = M_PI / 2;		// 旋转弧度
	// 创建矩阵对象transform_1.matrix()，初始化为4×4单位阵
	Eigen::Affine3f transform_1 = Eigen::Affine3f::Identity();
	// 定义在x轴上的平移，2.5m
	transform_1.translation() << 0.0, 0.0, 0.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移
	// 从右到左
	transform_1.rotate(Eigen::AngleAxisf(theta1_x, Eigen::Vector3f::UnitX()));
	transform_1.rotate(Eigen::AngleAxisf(theta1_z, Eigen::Vector3f::UnitZ()));




	// 打印平移、旋转矩阵
	std::cout << "\n方式2: 使用Affine3f\n";
	std::cout << transform_1.matrix() << std::endl;	

	for (int i = 0; i < 6; i++)
	{
		cloud.points[i] = pcl::transformPoint(cloud.points[i], transform_1);
	}

	float theta2_z1 = M_PI;		// 旋转弧度
	float theta2_z2 = -M_PI/2;		// 旋转弧度
	float theta2_x = M_PI / 2;		// 旋转弧度
	// 创建矩阵对象transform_2.matrix()，初始化为4×4单位阵
	Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();

	// 从右到左
	//transform_2.rotate(Eigen::AngleAxisf(theta2_z2, Eigen::Vector3f::UnitZ()));	//同理，UnitX(),绕X轴；UnitY(),绕Y轴.
	//transform_2.rotate(Eigen::AngleAxisf(theta2_x, Eigen::Vector3f::UnitX()));	//同理，UnitX(),绕X轴；UnitY(),绕Y轴.
	//transform_2.rotate(Eigen::AngleAxisf(theta2_z1, Eigen::Vector3f::UnitZ()));	//同理，UnitX(),绕X轴；UnitY(),绕Y轴.
	////transform_2.translation() << 4.0, 0.0, 0.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移x4,z13,x-2
	////transform_2.translation() << 4.0, 0.0, 9.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移x4,z9,x-2
	//transform_2.translation() << 2.0, 0.0, 9.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移x4,z9,x-2

	transform_2.translation() << 2.0, 0.0, 9.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移x4,z9,x-2
	
	// 打印平移、旋转矩阵
	std::cout << "\n方式2: 使用Affine3f\n";
	std::cout << transform_2.matrix() << std::endl;




	//----------------------------------------------------------------------------------------------
	//第二种方法但是没有平移到坐标系原点
	//float theta1_x = M_PI / 2;		// 旋转弧度
	//float theta1_z = M_PI / 2;		// 旋转弧度
	//// 创建矩阵对象transform_1.matrix()，初始化为4×4单位阵
	//Eigen::Affine3f transform_1 = Eigen::Affine3f::Identity();
	//// 定义在x轴上的平移，2.5m
	//transform_1.translation() << 0.0, 0.0, 0.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移
	//// 从左到右
	//transform_1.rotate(Eigen::AngleAxisf(theta1_x, Eigen::Vector3f::UnitX()));	//同理，UnitX(),绕X轴；UnitY(),绕Y轴.
	//transform_1.rotate(Eigen::AngleAxisf(theta1_z, Eigen::Vector3f::UnitZ()));	//同理，UnitX(),绕X轴；UnitY(),绕Y轴.



	//// 打印平移、旋转矩阵
	//std::cout << "\n方式2: 使用Affine3f\n";
	//std::cout << transform_1.matrix() << std::endl;

	//for (int i = 0; i < 6; i++)
	//{
	//	cloud.points[i] = pcl::transformPoint(cloud.points[i], transform_1);
	//}

	//float theta2_y = M_PI;		// 旋转弧度
	//float theta2_z2 = M_PI/2;		// 旋转弧度
	//float theta2_x = -M_PI/2;		// 旋转弧度
	//// 创建矩阵对象transform_2.matrix()，初始化为4×4单位阵
	//Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();

	//// 
	//transform_2.rotate(Eigen::AngleAxisf(theta2_y, Eigen::Vector3f::UnitY()));	//同理，UnitX(),绕X轴；UnitY(),绕Y轴.
	//transform_2.rotate(Eigen::AngleAxisf(theta2_x, Eigen::Vector3f::UnitX()));	//同理，UnitX(),绕X轴；UnitY(),绕Y轴.
	//transform_2.rotate(Eigen::AngleAxisf(theta2_z2, Eigen::Vector3f::UnitZ()));	//同理，UnitX(),绕X轴；UnitY(),绕Y轴.

	////transform_2.translation() << -13.0, 0.0, 0.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移x4,z13,x-2
	////transform_2.translation() << -13.0, -2.0, 0.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移x4,z9,x-2
	////transform_2.translation() << -9, -2.0, 0.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移x4,z9,x-2
	//// 打印平移、旋转矩阵
	//std::cout << "\n方式2: 使用Affine3f\n";
	//std::cout << transform_2.matrix() << std::endl;

	//for (int i = 6; i < 12; i++)
	//{
	//	cloud.points[i] = pcl::transformPoint(cloud.points[i], transform_2);
	//}

	cout << cloud.points[1].x - cloud.points[8].x << endl;
	cout << cloud.points[1].y - cloud.points[8].y << endl;
	cout << cloud.points[1].z - cloud.points[8].z << endl;

	pcl::visualization::PCLVisualizer viewer;
	viewer.setCameraPosition(14.2774, 10.5557, 4.9943,
		-0.151838, -0.122677, 0.980763,
		0,0,1);//设置观察视角姿态
	viewer.addCoordinateSystem(2);//显示坐标轴
	string position_str_temp;
	string id_temp = "point" + to_string(0);
	for (size_t i = 0; i < cloud.points.size();i++)
	{
		position_str_temp = "(" + to_string(cloud.points[i].x).substr(0, 3) + "," + to_string(cloud.points[i].y).substr(0, 3) + "," + to_string(cloud.points[i].z).substr(0, 3) + ")";
		id_temp = "point" + to_string(i);
		viewer.addText3D(position_str_temp, cloud.points[i], 0.1, 0, 0, 0, id_temp, 0);
	}
	viewer.setBackgroundColor(0, 0, 0);
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color(0, 0, 0); // green
	//pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> color(cloud, "z"); // 按照z字段进行渲染
	pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_temp(&cloud);
	viewer.addPointCloud(ptr_temp, color, "cloud");

	viewer.addLine(cloud.points[0], cloud.points[1], 0, 0, 0, "line0-1");
	viewer.addLine(cloud.points[1], cloud.points[2], 0, 0, 0, "line1-2");
	viewer.addLine(cloud.points[2], cloud.points[0], 0, 0, 0, "line2-0");
	viewer.addLine(cloud.points[3], cloud.points[4], 0, 0, 0, "line3-4");
	viewer.addLine(cloud.points[4], cloud.points[5], 0, 0, 0, "line4-5");
	viewer.addLine(cloud.points[5], cloud.points[3], 0, 0, 0, "line5-3");

	viewer.addLine(cloud.points[0], cloud.points[3], 0, 0, 0, "line0-3");
	viewer.addLine(cloud.points[1], cloud.points[4], 0, 0, 0, "line1-4");
	viewer.addLine(cloud.points[2], cloud.points[5], 0, 0, 0, "line2-5");


	viewer.addLine(cloud.points[6], cloud.points[7], 0, 0, 0, "line6-7");
	viewer.addLine(cloud.points[7], cloud.points[8], 0, 0, 0, "line7-8");
	viewer.addLine(cloud.points[8], cloud.points[6], 0, 0, 0, "line8-6");
	viewer.addLine(cloud.points[9], cloud.points[10], 0, 0, 0, "line9-10");
	viewer.addLine(cloud.points[10], cloud.points[11], 0, 0, 0, "line10-11");
	viewer.addLine(cloud.points[11], cloud.points[9], 0, 0, 0, "line11-9");

	viewer.addLine(cloud.points[6], cloud.points[9], 0, 0, 0, "line6-9");
	viewer.addLine(cloud.points[7], cloud.points[10], 0, 0, 0, "line7-10");
	viewer.addLine(cloud.points[8], cloud.points[11], 0, 0, 0, "line8-11");



	//显示带有颜色的点云
	//pcl::visualization::PointCloudColorHandlerRGBAField<pcl::PointXYZRGBA> rgba(cloud);
	//viewer.addPointCloud<pcl::PointXYZRGBA>(cloud, "cloud");
	//自定义点云颜色
	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGBA> rgba(cloud,0,0,255);
	//viewer.addPointCloud<pcl::PointXYZRGBA>(cloud, rgba, "cloud");
	viewer.setBackgroundColor(255, 255, 255);   //设置背景颜色
	viewer.setShowFPS(60);
	viewer.setWindowName("abc");//设置窗口名字
	viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud");//设置点的大小
	//viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_LINE_WIDTH, 3, "line01");
	//viewer.spin();
	while (!viewer.wasStopped())
	{
		viewer.spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
		// 可添加其他操作
	}

	//pcl::visualization::CloudViewer viewer("Cloud Viewer");	//创建可视化viewer对象
	//viewer.showCloud(cloud);//CloudViewer不好用，不能设置参数

	system("pause");

	return 0;
}