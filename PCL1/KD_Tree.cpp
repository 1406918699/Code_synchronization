#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/search/kdtree.h> // ����kdtreeͷ�ļ�
typedef pcl::PointXYZ PointT;
int main()
{
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	pcl::io::loadPCDFile("hand.pcd", *cloud);
	// ����KDTree����
	pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
	kdtree->setInputCloud(cloud); // ����Ҫ�����ĵ��ƣ�����KDTree
	std::vector<int> indices; // �洢��ѯ���ڵ�����
	std::vector<float> distances; // �洢���ڵ��Ӧ�����ƽ��
	PointT point = cloud->points[0]; // ��ʼ��һ����ѯ��

	// ��ѯ��point�����k����
	int k = 10;
	int size = kdtree->nearestKSearch(point, k, indices, distances);
	std::cout << "search point : " << size << std::endl;
	// ��ѯpoint�뾶Ϊradius�������ڵĵ�
	double radius = 2.0;
	size = kdtree->radiusSearch(point, radius, indices, distances);
	std::cout << "search point : " << size << std::endl;
	system("pause");
	return 0;
}