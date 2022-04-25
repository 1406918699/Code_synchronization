#include<pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <iostream>
#include<vector>
#include <pcl/search/kdtree.h>

double ComputeCloudResolution(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr& cloud)
{
	double res = 0.0;
	int n_points = 0;
	int nres;
	std::vector<int> indices(2);
	std::vector<float> sqr_distances(2);
	//step1: �½�kdtree��������
	pcl::search::KdTree<pcl::PointXYZ> tree;
	tree.setInputCloud(cloud);

	//step2: ��������ÿ���㣬���ҳ�������������ĵ�
	for (size_t i = 0; i < cloud->size(); ++i)
	{
		if (!pcl_isfinite((*cloud)[i].x))
		{
			continue;
		}
		// ȡ�ڶ������룬��Ϊ��һ����������
		nres = tree.nearestKSearch(i, 2, indices, sqr_distances);
		//step3: ͳ����С����͡���Ч������
		if (nres == 2)
		{
			res += sqrt(sqr_distances[1]);
			++n_points;
		}
	}

	//step4: ����ռ�ֱ���
	if (n_points != 0)
	{
		res /= n_points;
	}
	return res;
}