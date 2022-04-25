#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
// �������ͷ�ļ�
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/uniform_sampling.h>
typedef pcl::PointXYZ PointT;
int main(int argc, char** argv)
{
	// ��ȡ����
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	pcl::io::loadPCDFile("C:\\Users\\14069\\Documents\\Visual Studio 2013\\Projects\\PCL1\\PCL1\\hand.pcd", *cloud);
	std::cout << "original cloud size : " << cloud->size() << std::endl;
	// ʹ�����ػ�����(VoxelGrid)�����²���
	pcl::VoxelGrid<PointT> grid; //�����˲�����
	const float leaf = 0.005f;
	grid.setLeafSize(leaf, leaf, leaf); // �����������
	grid.setInputCloud(cloud); // ���õ���
	pcl::PointCloud<PointT>::Ptr voxelResult(new pcl::PointCloud<PointT>);
	grid.filter(*voxelResult); // ִ���˲���������
	std::cout << "voxel downsample size :" << voxelResult->size() << std::endl;
	// ʹ��UniformSampling�����²���
	pcl::UniformSampling<PointT> uniform_sampling;
	uniform_sampling.setInputCloud(cloud);
	double radius = 0.005f;
	uniform_sampling.setRadiusSearch(radius);
	pcl::PointCloud<PointT>::Ptr uniformResult(new pcl::PointCloud<PointT>);
	uniform_sampling.filter(*uniformResult);
	std::cout << "UniformSampling size :" << uniformResult->size() << std::endl;

	system("pause");
	return 0;
}