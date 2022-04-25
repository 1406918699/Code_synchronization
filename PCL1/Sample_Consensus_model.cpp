/*
* @Description: 1�������һ�����㷨           https://www.cnblogs.com/li-yao7758258/p/6477007.html
* @Author: HCQ
* @Company(School): UCAS
* @Email: 1756260160@qq.com
* @Date: 2020-10-19 15:04:50
* @LastEditTime: 2020-10-19 18:34:17
* @FilePath: /pcl-learning/05sampleconsensus����һ����ģ��/1�������һ�����㷨/random_sample_consensus.cpp
*/

#include <iostream>
#include <pcl/console/parse.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/sample_consensus/sac_model_sphere.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>

boost::shared_ptr<pcl::visualization::PCLVisualizer>
simpleVis(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
	// --------------------------------------------
	// -----Open 3D viewer and add point cloud-----
	// --------------------------------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->setBackgroundColor(0, 0, 0);
	viewer->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
	//viewer->addCoordinateSystem (1.0, "global");
	viewer->initCameraParameters();
	return (viewer);
}
/******************************************************************************************************************
�Ե��ƽ��г�ʼ������������һ������������������Ϊ����ǰ�ĵ�ԭʼ���ƣ����д󲿷ֵ��������ǻ����趨��Բ���ƽ��ģ�ͼ���
���õ�������ֵ��Ϊ���ڵ㣬��1/5�ĵ��������Ǳ�������õľ���㡣
*****************************************************************************************************************/

int
main(int argc, char** argv)
{
	// ��ʼ�����ƶ���
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);  //�洢Դ����
	pcl::PointCloud<pcl::PointXYZ>::Ptr final(new pcl::PointCloud<pcl::PointXYZ>);   //�洢��ȡ�ľ��ڵ�

	// ����������
	cloud->width = 500;                 //��������Ŀ
	cloud->height = 1;                     //�������
	cloud->is_dense = false;
	cloud->points.resize(cloud->width * cloud->height);
	for (size_t i = 0; i < cloud->points.size(); ++i)
	{
		if (pcl::console::find_argument(argc, argv, "-s") >= 0 || pcl::console::find_argument(argc, argv, "-sf") >= 0)
		{
			//���������в�����x^2+y^2+Z^2=1����һ���ֵ������ݣ���ʱ�������1/4��������Ϊ�ڵ�
			cloud->points[i].x = 1024 * rand() / (RAND_MAX + 1.0);
			cloud->points[i].y = 1024 * rand() / (RAND_MAX + 1.0);
			if (i % 5 == 0)
				cloud->points[i].z = 1024 * rand() / (RAND_MAX + 1.0);   //�˴���Ӧ�ĵ�Ϊ�����
			else if (i % 2 == 0)
				cloud->points[i].z = sqrt(1 - (cloud->points[i].x * cloud->points[i].x)
				- (cloud->points[i].y * cloud->points[i].y));
			else
				cloud->points[i].z = -sqrt(1 - (cloud->points[i].x * cloud->points[i].x)
				- (cloud->points[i].y * cloud->points[i].y));
		}
		else
		{ //��x+y+z=1����һ���ֵ������ݣ���ʱ��������ɵ�����ƽ����Ϊ�ڵ�
			cloud->points[i].x = 1024 * rand() / (RAND_MAX + 1.0);
			cloud->points[i].y = 1024 * rand() / (RAND_MAX + 1.0);
			if (i % 2 == 0)
				cloud->points[i].z = 1024 * rand() / (RAND_MAX + 1.0);   //��Ӧ�ľ����
			else
				cloud->points[i].z = -1 * (cloud->points[i].x + cloud->points[i].y);
		}
	}

	std::vector<int> inliers;  //�洢���ڵ㼯�ϵĵ������������

	//�����������һ���Զ���
	pcl::SampleConsensusModelSphere<pcl::PointXYZ>::Ptr
		model_s(new pcl::SampleConsensusModelSphere<pcl::PointXYZ>(cloud));    //�����ģ�͵Ķ���
	pcl::SampleConsensusModelPlane<pcl::PointXYZ>::Ptr
		model_p(new pcl::SampleConsensusModelPlane<pcl::PointXYZ>(cloud));   //���ƽ��ģ�͵Ķ���
	if (pcl::console::find_argument(argc, argv, "-f") >= 0)
	{  //���������в���������������Ӧƽ��ģ�ͣ����洢���Ƶľ��ڵ�
		pcl::RandomSampleConsensus<pcl::PointXYZ> ransac(model_p);
		ransac.setDistanceThreshold(.01);    //��ƽ�����С��0.01 �ĵ��Ϊ���ڵ㿼�ǣ�ע����ڵ����ò���
		ransac.computeModel();                   //ִ�������������
		ransac.getInliers(inliers);                 //�洢�������õľ��ڵ�
	}
	else if (pcl::console::find_argument(argc, argv, "-sf") >= 0)
	{
		//���������в���  ����������Ӧ��Բ��ģ�ͣ��洢���Ƶ��ڵ�
		pcl::RandomSampleConsensus<pcl::PointXYZ> ransac(model_s);
		ransac.setDistanceThreshold(.01);
		ransac.computeModel();
		ransac.getInliers(inliers);
	}

	// ���ƹ���ģ�͵����еľ��ڵ㵽final��
	pcl::copyPointCloud<pcl::PointXYZ>(*cloud, inliers, *final);

	// �������ӻ����󲢼���ԭʼ���ƻ������еľ��ڵ�

	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	
	if (pcl::console::find_argument(argc, argv, "-f") >= 0 || pcl::console::find_argument(argc, argv, "-sf") >= 0)
		viewer = simpleVis(final);
	else
		viewer = simpleVis(cloud);
	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	return 0;
}