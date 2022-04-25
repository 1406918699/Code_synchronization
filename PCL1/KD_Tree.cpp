#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/search/kdtree.h> // 包含kdtree头文件
typedef pcl::PointXYZ PointT;
int main()
{
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	pcl::io::loadPCDFile("hand.pcd", *cloud);
	// 定义KDTree对象
	pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
	kdtree->setInputCloud(cloud); // 设置要搜索的点云，建立KDTree
	std::vector<int> indices; // 存储查询近邻点索引
	std::vector<float> distances; // 存储近邻点对应距离的平方
	PointT point = cloud->points[0]; // 初始化一个查询点

	// 查询距point最近的k个点
	int k = 10;
	int size = kdtree->nearestKSearch(point, k, indices, distances);
	std::cout << "search point : " << size << std::endl;
	// 查询point半径为radius邻域球内的点
	double radius = 2.0;
	size = kdtree->radiusSearch(point, radius, indices, distances);
	std::cout << "search point : " << size << std::endl;
	system("pause");
	return 0;
}