#include<iostream>
#include<pcl/io/io.h>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<string>

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;
using namespace std;

int main()
{
	PointCloud::Ptr cloud(new PointCloud);
	pcl::io::loadPCDFile("C:\\Users\\14069\\Documents\\PCL_files\\hand.pcd", *cloud);
	cloud->points
	return 0;
}
