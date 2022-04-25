#include <iostream>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/surface/mls.h>
#include <pcl/visualization/pcl_visualizer.h>
#include "resolution.h"
int main(int argc, char** argv)
{
	// Load input file into a PointCloud<T> with an appropriate type
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
	// Load bun0.pcd -- should be available with the PCL archive in test 
	pcl::io::loadPCDFile("C:\\Users\\14069\\Documents\\Visual Studio 2013\\Projects\\PCL1\\PCL1\\files\\new_create.pcd", *cloud);
	double resolution = ComputeCloudResolution(cloud);
	// Create a KD-Tree
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	// Output has the PointNormal type in order to store the normals calculated by MLS
	pcl::PointCloud<pcl::PointNormal> mls_points;
	// Init object (second point type is for the normals, even if unused)
	pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointNormal> mls;
	mls.setInputCloud(cloud);
	mls.setComputeNormals(true); //���Ƕ�֪�������ع�ʱ��Ҫ���Ƶ��Ƶķ�����������MLS�ṩ��һ�ַ��������Ƶ��Ʒ��������������true�Ļ�ע��������ݸ�ʽ����
	mls.setPolynomialFit(true); //���ڷ��ߵĹ������ж���ʽ���ǽ����������ߡ�
	mls.setPolynomialOrder(3); //MLS������ߵĽ�������������ڹ��캯����Ĭ����2�����ǲο����׸������ѡ��3����4
	mls.setSearchMethod(tree);
	mls.setSearchRadius(10 * resolution);
	// Reconstruct
	mls.process(mls_points);

	// Save output
	//pcl::io::savePCDFile("bun0-mls.pcd", mls_points);
	// show
	pcl::visualization::PCLVisualizer viewer_1;
	viewer_1.addPointCloud(cloud, "cloud");
	viewer_1.spin();
	pcl::visualization::PCLVisualizer viewer_2;
	pcl::PointCloud<pcl::PointXYZ>::Ptr result(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::copyPointCloud(mls_points, *result);
	viewer_2.addPointCloud(result, "mls_points");
	viewer_2.spin();
	return 0;
}