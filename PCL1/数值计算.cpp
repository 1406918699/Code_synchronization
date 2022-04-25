
#include <pcl/common/transforms.h>

#include <iostream>
//#include<string>
#include<sstream>
using namespace std;

int main()
{

	float theta2_z1 = M_PI;		// 旋转弧度
	float theta2_z2 = -M_PI / 2;		// 旋转弧度
	float theta2_x = M_PI / 2;		// 旋转弧度
	// 创建矩阵对象transform_2.matrix()，初始化为4×4单位阵
	Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();

	// 从右到左
	transform_2.rotate(Eigen::AngleAxisf(theta2_z2, Eigen::Vector3f::UnitZ()));	//同理，UnitX(),绕X轴；UnitY(),绕Y轴.
	transform_2.rotate(Eigen::AngleAxisf(theta2_x, Eigen::Vector3f::UnitX()));	//同理，UnitX(),绕X轴；UnitY(),绕Y轴.
	transform_2.rotate(Eigen::AngleAxisf(theta2_z1, Eigen::Vector3f::UnitZ()));	//同理，UnitX(),绕X轴；UnitY(),绕Y轴.
	//transform_2.translation() << 4.0, 0.0, 0.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移x4,z13,x-2
	//transform_2.translation() << 4.0, 0.0, 9.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移x4,z9,x-2
	transform_2.translation() << 2.0, 0.0, 9.0;	// 三个数分别对应X轴、Y轴、Z轴方向上的平移x4,z9,x-2


	// 打印平移、旋转矩阵
	std::cout << "\n方式2: 使用Affine3f\n";
	std::cout << transform_2.matrix() << std::endl;
	system("pause");
	return 0;
}