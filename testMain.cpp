#include<iostream>
#include<cmath>
#include"MacroDefinitionParameter.h"
#include<Eigen>
using namespace std;
polarCoordinates cartesian2polar(cartesianCoordinates carc) {
	struct polarCoordinates res;
	float theta;
	if (abs(carc.x - 0) <= 0.000000001f) {
		theta = 0.5f*(float)PI;
	}
	else {
		theta = atan(carc.y / carc.x);
	}

	if (theta < 0.0f) theta +=(float)PI;
	float radius = sqrt(pow(carc.x, 2) + pow(carc.y, 2));
	res.theta = theta;
	res.radius = radius;
	res.z = carc.z;
	return res;
}


binaryRes trigonometricFunctions(binaryCoefficient binc,binaryRes ab) {
	binaryRes res;
	Eigen::MatrixXf A(2, 2);
	Eigen::VectorXf b(2, 1);
	Eigen::MatrixXf x;
	A << binc.a, binc.b, binc.c, binc.d;
	b << ab.x, ab.y;
	/*cout << "A=\n" << A << endl;
	cout << "b=\n" << b << endl;*/
	
	x = A.inverse()*b;
	/*cout << "x=\n" << x << endl;*/
	res.x = x(0, 0);
	res.y = x(1, 0);
	return res;
}

bool getCriticalAngle(polarCoordinates target, criticalAngle & ca){
	float l1 = (float)L_lower;
	float l2 = (float)L_uper;
	float alpha,beta,cos_alpha,cos_beta,r = target.radius, z = target.z;
	binaryCoefficient bincoe;
	binaryRes binb,res;
	cos_beta = (pow(l1, 2) + pow(l2, 2) - pow(r, 2) - pow(z, 2)) / (2*l1*l2);
	
	/*cout << "cos_beta=" << cos_beta << endl;*/
	if (cos_beta <= 0 || cos_beta > 1) {
		std::cout << "There is a calculation error or input coordinate error" << endl;
		return false;
	}
	else {
		
		beta = abs(acos(cos_beta));
		/*cout << "beta=" << beta << endl;*/
		bincoe.a = l1 - l2 * cos(beta);
		bincoe.b = l2 * sin(beta);
		bincoe.c = -1*l2 * sin(beta);
		bincoe.d = l1 - l2 * cos(beta);
		binb.x = r;
		binb.y = z;
		//res.x是alpha角的余弦值
		res = trigonometricFunctions(bincoe, binb);
	}
	cos_alpha = res.x;
	alpha = acos(cos_alpha);

	ca.theta = target.theta;
	ca.alpha = alpha;
	ca.beta = beta;
	cout << "theta=" << ca.theta << endl;
	cout << "alpha=" << ca.alpha << endl;
	cout << "beta=" << ca.beta << endl;
	cout << "************************************************" <<endl;
	return true;
}
//计算碎石机各个轴的转动角度
criticalAngle threeAxisRotationDirection(cartesianCoordinates target_coor,cartesianCoordinates now_coor) {
	polarCoordinates target_polar = cartesian2polar(target_coor);
	polarCoordinates now_polar = cartesian2polar(now_coor);
	criticalAngle target_angle, now_angle, difference_angle;
	getCriticalAngle(target_polar, target_angle);
	getCriticalAngle(now_polar, now_angle);
	difference_angle.theta = target_angle.theta - now_angle.theta;
	difference_angle.alpha = target_angle.alpha - now_angle.alpha;
	difference_angle.beta = target_angle.beta - now_angle.beta;
	return difference_angle;
}




int main() {
	criticalAngle differ_agnle;
	struct cartesianCoordinates target = { -90.0f,67.0f,81.0f };
	struct cartesianCoordinates nowcoor = { 50.0f,60.0f,56.3f };
	differ_agnle = threeAxisRotationDirection(target, nowcoor);

	std::cout << "1：" << differ_agnle.theta << std::endl;
	std::cout << "2：" << differ_agnle.alpha << std::endl;
	std::cout << "3：" << differ_agnle.beta << std::endl;
}