/*
* @Description: add: 两个窗口显示点云（滤波前&滤波后） https://blog.csdn.net/weixin_45377028/article/details/104564467
* @Author: HCQ
* @Company(School): UCAS
* @Date: 2020-10-14 11:11:11
* @LastEditors: HCQ
* @LastEditTime: 2020-10-14 11:30:58
*/
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/passthrough.h>

int main(int argc, char **argv)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_1(new pcl::PointCloud<pcl::PointXYZ>());//创建点云对象
	pcl::io::loadPCDFile("C:\\Users\\14069\\Documents\\PCL_files\\hand.pcd", *cloud_1);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_2(new pcl::PointCloud<pcl::PointXYZ>());//创建点云对象
	pcl::io::loadPCDFile("C:\\Users\\14069\\Documents\\PCL_files\\hand_downsampled_005.pcd", *cloud_2);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_3(new pcl::PointCloud<pcl::PointXYZ>());//创建点云对象
	pcl::io::loadPCDFile("C:\\Users\\14069\\Documents\\PCL_files\\hand_downsampled_010.pcd", *cloud_3);

	// 可视化
	pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("点云显示"));
	int v1(0); //设置左右窗口
	int v2(1);
	int v3(2);
	viewer->createViewPort(0.0, 0.0, 0.33, 1.0, v1); //(Xmin,Ymin,Xmax,Ymax)设置窗口坐标
	viewer->createViewPort(0.33, 0.0, 0.66, 1.0, v2);
	viewer->createViewPort(0.66, 0.0, 1.0, 1.0, v3);

	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_out_red(cloud, 255, 0, 0); // 显示红色点云
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> color_1(cloud_1, "z"); // 按照z字段进行渲染
	viewer->addPointCloud(cloud_1, color_1,"cloud_out1", v1);

	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_out_green(cloud, 0, 255, 0); // 显示绿色点云
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> color_2(cloud_2, "z"); // 按照z字段进行渲染
	viewer->addPointCloud(cloud_2, color_2,"cloud_out2", v2);  // 平面

	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_out_blue(cloud, 0, 0, 255); // 显示蓝色点云
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> color_3(cloud_3, "z"); // 按照z字段进行渲染
	viewer->addPointCloud(cloud_3, color_3,"cloud_out3", v3); // 圆柱
	while (!viewer->wasStopped())
	{
		viewer->spinOnce();
	}
	return 0;
}
