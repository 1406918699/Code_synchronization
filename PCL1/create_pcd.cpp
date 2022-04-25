#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
using namespace std;


int main(int argc, char** argv)
{
	pcl::PointCloud<pcl::PointXYZ> cloud;
	// Fill in the cloud data
	cloud.width = 10000;
	cloud.height = 1;
	cloud.is_dense = true;//true则说明不包含nan点，false则说明包含nan点
	cloud.points.resize(cloud.width * cloud.height);
	//for (size_t i = 0; i < cloud.width; ++i)
	//{
	//	for (size_t j = 0; j < cloud.height; j++)
	//	{

	//		cloud.at(i, j).x = 10000 * rand() / (RAND_MAX + 1.0f);
	//		cloud.at(i, j).y =10000 * rand() / (RAND_MAX + 1.0f);
	//		cloud.at(i, j).z = 0;
	//	}
	//}
	for (size_t i = 0; i < cloud.points.size(); ++i)
	{
		//cloud.points[i].x = 10000 * rand() / (RAND_MAX + 1.0f);
		//cloud.points[i].y = 10000 * rand() / (RAND_MAX + 1.0f);
		//cloud.points[i].z = 10000 * rand() / (RAND_MAX + 1.0f);
		cloud.points[i].x = 50 + 100 * rand() / (RAND_MAX + 1.0f);
		cloud.points[i].y = 50 + 100 * rand() / (RAND_MAX + 1.0f);
		cloud.points[i].z = -500 - 500 * rand() / (RAND_MAX + 1.0f);
	}

	pcl::io::savePCDFileASCII("C:/Users/14069/Documents/PCL_files/orignal_cloud.pcd", cloud);
	//std::cerr << "Saved " << cloud.points.size() << " data points to test_pcd.pcd." << std::endl;

	//for (size_t i = 0; i < cloud.points.size(); ++i)
	//	std::cerr << " " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;

	system("pause");
	return 0;
}




//#include <iostream>
//#include <pcl/io/pcd_io.h>
//#include <pcl/point_types.h>
//
//int main()
//{
//	pcl::PointCloud<pcl::PointXYZ> cloud;
//	// 创建点云
//	cloud.width = 5;
//	cloud.height = 2;
//	cloud.is_dense = true;
//	cloud.points.resize(cloud.width*cloud.height);
//	for (size_t i = 0; i<cloud.points.size(); ++i)
//	{
//		cloud.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
//		cloud.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
//		cloud.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
//	}
//
//
//
//	for (size_t i = 0; i < cloud.points.size(); ++i)
//	{
//		std::cerr << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;
//	}
//	std::cout << "     " << std::endl;
//	cloud.width = 5;
//	cloud.height = 2;
//	for (size_t h = 0; h < cloud.height; ++h)
//	{
//		for (size_t w = 0; w < cloud.width; ++w)
//		{
//			std::cout << cloud.at(w, h).x << " : " << cloud.at(w, h).y << " : " << cloud.at(w, h).z << std::endl;; // 正确
//		}
//	}
//	system("pause");
//	return(0);
//}