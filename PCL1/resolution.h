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
	//step1: 新建kdtree用于搜索
	pcl::search::KdTree<pcl::PointXYZ> tree;
	tree.setInputCloud(cloud);

	//step2: 遍历点云每个点，并找出与它距离最近的点
	for (size_t i = 0; i < cloud->size(); ++i)
	{
		if (!pcl_isfinite((*cloud)[i].x))
		{
			continue;
		}
		// 取第二个距离，因为第一个是它本身
		nres = tree.nearestKSearch(i, 2, indices, sqr_distances);
		//step3: 统计最小距离和、有效点数量
		if (nres == 2)
		{
			res += sqrt(sqr_distances[1]);
			++n_points;
		}
	}

	//step4: 计算空间分辨率
	if (n_points != 0)
	{
		res /= n_points;
	}
	return res;
}