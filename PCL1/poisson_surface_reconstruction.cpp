#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/poisson.h>
#include <pcl/visualization/pcl_visualizer.h>
#include "resolution.h"
int main(int argc, char** argv)
{
	// Load input file into a PointCloud<T> with an appropriate type
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PCLPointCloud2 cloud_blob;
	pcl::io::loadPCDFile("C:\\Users\\14069\\Documents\\Visual Studio 2013\\Projects\\PCL1\\PCL1\\files\\new_create.pcd", cloud_blob);
	pcl::fromPCLPointCloud2(cloud_blob, *cloud);
	//* the data should be available in cloud
	double resolution = ComputeCloudResolution(cloud);
	// Normal estimation*
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud);
	n.setInputCloud(cloud);
	n.setSearchMethod(tree);
	n.setKSearch(48);
	n.compute(*normals);
	// normals should not contain the point normals + surface curvatures
	// Concatenate the XYZ and normal fields*
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
	pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);
	// cloud_with_normals = cloud + normals
	// Create search tree*
	pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
	tree2->setInputCloud(cloud_with_normals);

	//重建部分
	pcl::Poisson<pcl::PointNormal> pn;
	pn.setConfidence(false);
	pn.setDegree(2);
	pn.setDepth(8);
	pn.setIsoDivide(8);
	pn.setManifold(false);
	pn.setOutputPolygons(false);
	pn.setSamplesPerNode(3.0);
	pn.setScale(1.25);
	pn.setSolverDivide(8);
	pn.setSearchMethod(tree2);
	pn.setInputCloud(cloud_with_normals);
	pcl::PolygonMesh mesh;
	pn.performReconstruction(mesh);

	// show
	pcl::visualization::PCLVisualizer viewer;
	viewer.addPolygonMesh(mesh, "mesh");
	viewer.spin();
	// Finish
	return (0);
}