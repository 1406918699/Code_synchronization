/*
* @Description: ��δӵ��ƴ������ͼ��
* https://www.cnblogs.com/li-yao7758258/p/6474699.html
* http://robot.czxy.com/docs/pcl/chapter02/range_image/#_1  �Ƽ�
* @Author: HCQ
* @Company(School): UCAS
* @Email: 1756260160@qq.com
* @Date: 2020-10-21 15:08:41
* @LastEditTime: 2020-10-21 15:52:15
* @FilePath: /pcl-learning/06range-images���ͼ��/1�ӵ��ƴ������ͼ/range_image_creation.cpp
*/

#include <pcl/range_image/range_image.h> // //�������ͼ���ͷ�ļ�
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>  //  //PCL���ӻ���ͷ�ļ�
#include <pcl/visualization/range_image_visualizer.h> // //���ͼ���ӻ���ͷ�ļ�
#include <pcl/pcl_macros.h>
int main(int argc, char **argv)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr pointCloudPtr(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ> &pointCloud = *pointCloudPtr;

	// ����һ��������״�ĵ���
	// Generate the data
	// for (float y = -0.5f; y <= 0.5f; y += 0.01f)
	// {
	//     for (float z = -0.5f; z <= 0.5f; z += 0.01f)
	//     {
	//         pcl::PointXYZ point;
	//         point.x = 2.0f - y;
	//         point.y = y;
	//         point.z = z;
	//         pointCloud.points.push_back(point);
	//     }
	// }
	// pointCloud.width = (uint32_t)pointCloud.points.size();
	// pointCloud.height = 1;

	pcl::io::loadPCDFile("hand.pcd", pointCloud);
	// pcl::io::loadPCDFile("../table_scene_lms400_downsampled.pcd", pointCloud);

	//ʵ��һ���ʾ�����״�ĵ���
	// We now want to create a range image from the above point cloud, with a 1deg angular resolution   ����֮ǰ�õ��ĵ���ͼ��ͨ��1deg�ķֱ����������ͼ��
	//angular_resolutionΪģ�����ȴ������ĽǶȷֱ��ʣ������ͼ����һ�����ض�Ӧ�ĽǶȴ�С
	float angularResolution = (float)(1.0f * (M_PI / 180.0f)); //  ����1��
	//max_angle_widthΪģ�����ȴ�������ˮƽ�������Ƕȣ�
	float maxAngleWidth = (float)(360.0f * (M_PI / 180.0f));   //  ����360��
	//max_angle_heightΪģ�⴫�����Ĵ�ֱ�����������Ƕ�  ��תΪ����
	float maxAngleHeight = (float)(180.0f * (M_PI / 180.0f)); // ����180��
	//�������Ĳɼ�λ��
	Eigen::Affine3f sensorPose = (Eigen::Affine3f)Eigen::Translation3f(0.0f, 0.0f, 0.0f);
	//���ͼ����ѭ����ϵͳ
	pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;
	float noiseLevel = 0.00; //noise_level��ȡ���ͼ�����ʱ�����ڵ�Բ�ѯ�����ֵ��Ӱ��ˮƽ
	float minRange = 0.0f;   //min_range������С�Ļ�ȡ���룬С����С��ȡ�����λ��Ϊ��������ä��
	int borderSize = 1;      //border_size������ͼ��ı�Ե�Ŀ��

	boost::shared_ptr<pcl::RangeImage> range_image_ptr(new pcl::RangeImage); // ���ڿ��ӻ�������ָ��
	pcl::RangeImage &rangeImage = *range_image_ptr;

	rangeImage.createFromPointCloud(pointCloud, angularResolution, maxAngleWidth, maxAngleHeight,
		sensorPose, coordinate_frame, noiseLevel, minRange, borderSize);
	/*
	����range_image.createFromPointCloud���������Ľ��� ���漰�ĽǶȶ�Ϊ����Ϊ��λ�� ��
	point_cloudΪ�������ͼ������Ҫ�ĵ���
	angular_resolution_x��ȴ�����X����ĽǶȷֱ���
	angular_resolution_y��ȴ�����Y����ĽǶȷֱ���
	pcl::deg2rad (360.0f)��ȴ�������ˮƽ�������Ƕ�
	pcl::deg2rad (180.0f)��ֱ�������Ƕ�
	scene_sensor_pose���õ�ģ�⴫������λ����һ������任����Ĭ��Ϊ4*4�ĵ�λ����任
	coordinate_frame���尴����������ϵͳ��ϰ��  Ĭ��ΪCAMERA_FRAME
	noise_level  ��ȡ���ͼ�����ʱ���ڽ���Բ�ѯ�����ֵ��Ӱ��ˮƽ
	min_range ������С�Ļ�ȡ���룬С����С�Ļ�ȡ�����λ��Ϊ��������ä��
	border_size  ���û�ȡ���ͼ���Ե�Ŀ�� Ĭ��Ϊ0
	*/
	std::cout << rangeImage << "\n";
	// --------------------------------------------
	// -----Open 3D viewer and add point cloud-----
	// --------------------------------------------
	pcl::visualization::PCLVisualizer viewer("3D Viewer");
	viewer.setBackgroundColor(1, 1, 1);
	// ������ͼ����
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> range_image_color_handler(range_image_ptr, 0, 0, 0);
	viewer.addPointCloud(range_image_ptr, range_image_color_handler, "range image");
	viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 4, "range image");

	// ���ԭʼ����
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> org_image_color_handler(pointCloudPtr, 255, 100, 0);
	viewer.addPointCloud(pointCloudPtr, org_image_color_handler, "orginal image");
	viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "orginal image");

	viewer.initCameraParameters();
	viewer.addCoordinateSystem(1.0);

	//--------------------
	// -----Main loop-----
	//--------------------
	while (!viewer.wasStopped())
	{
		viewer.spinOnce();
		pcl_sleep(0.01);
	}
	return (0);
}