
#include <pcl/common/transforms.h>

#include <iostream>
//#include<string>
#include<sstream>
using namespace std;

int main()
{

	float theta2_z1 = M_PI;		// ��ת����
	float theta2_z2 = -M_PI / 2;		// ��ת����
	float theta2_x = M_PI / 2;		// ��ת����
	// �����������transform_2.matrix()����ʼ��Ϊ4��4��λ��
	Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();

	// ���ҵ���
	transform_2.rotate(Eigen::AngleAxisf(theta2_z2, Eigen::Vector3f::UnitZ()));	//ͬ��UnitX(),��X�᣻UnitY(),��Y��.
	transform_2.rotate(Eigen::AngleAxisf(theta2_x, Eigen::Vector3f::UnitX()));	//ͬ��UnitX(),��X�᣻UnitY(),��Y��.
	transform_2.rotate(Eigen::AngleAxisf(theta2_z1, Eigen::Vector3f::UnitZ()));	//ͬ��UnitX(),��X�᣻UnitY(),��Y��.
	//transform_2.translation() << 4.0, 0.0, 0.0;	// �������ֱ��ӦX�ᡢY�ᡢZ�᷽���ϵ�ƽ��x4,z13,x-2
	//transform_2.translation() << 4.0, 0.0, 9.0;	// �������ֱ��ӦX�ᡢY�ᡢZ�᷽���ϵ�ƽ��x4,z9,x-2
	transform_2.translation() << 2.0, 0.0, 9.0;	// �������ֱ��ӦX�ᡢY�ᡢZ�᷽���ϵ�ƽ��x4,z9,x-2


	// ��ӡƽ�ơ���ת����
	std::cout << "\n��ʽ2: ʹ��Affine3f\n";
	std::cout << transform_2.matrix() << std::endl;
	system("pause");
	return 0;
}