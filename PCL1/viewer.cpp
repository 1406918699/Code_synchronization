#include<pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
using namespace std;

void viewerOneOff(pcl::visualization::PCLVisualizer& viewer) {
	viewer.setBackgroundColor(1.0, 0.5, 1.0);   //设置背景颜色
}

int main()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());//创建点云对象
	pcl::io::loadPCDFile("C:\\Users\\14069\\Documents\\CAD_files\\Cube.pcd", *cloud);
	cout << *cloud << endl;
	cout << cloud->points[0] << endl;
	cout << cloud->width << endl;
	cout << cloud->is_dense << endl;

	pcl::visualization::PCLVisualizer viewer;
	viewer.addCoordinateSystem();
	viewer.setBackgroundColor(0, 0, 0);
	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color(cloud, 0, 255, 0); // green
	//pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> color(cloud, "z"); // 按照z字段进行渲染
	viewer.addPointCloud(cloud,"cloud");
	//显示带有颜色的点云
	//pcl::visualization::PointCloudColorHandlerRGBAField<pcl::PointXYZRGBA> rgba(cloud);
	//viewer.addPointCloud<pcl::PointXYZRGBA>(cloud, "cloud");
	//自定义点云颜色
	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGBA> rgba(cloud,0,0,255);
	//viewer.addPointCloud<pcl::PointXYZRGBA>(cloud, rgba, "cloud");

	viewer.setShowFPS(60);
	viewer.setWindowName("abc");//设置窗口名字
	//viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloud");//设置点的大小
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