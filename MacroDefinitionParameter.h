#pragma once
#pragma once
// Cartesian three-dimensional coordinates
struct cartesianCoordinates
{
	float x;
	float y;
	float z;
};
//polar coordinates three-dimensional
struct polarCoordinates
{
	float theta;
	float radius;
	float z;
};
//Critical Angle value
struct criticalAngle {
	float theta=0;
	float alpha;
	float beta;
};

//Coefficient of binary system
struct binaryCoefficient {
	float a;
	float b;
	float c;
	float d;
};
struct binaryRes {
	float x;
	float y;
};


// three arms of mechanical arm unit:cm
#define L_lower 160;
#define L_uper 120;
#define L_simler 90;
//Limit the Angle upper and lower limits
#define PI 3.141592654;
#define halfPI PI/2;
#define Theta_upperLimit PI;
#define Theta_lowerLimit 0;
#define Alpha_upperLimit PI/2;
#define Alpha_lowerLimit 0;
#define Beta_upperLimit PI/2;
#define Beta_lowerLimit 0;
#define Gama_upperLimit PI/2;
#define Gama_lowerLimit 0;
//原点坐标（0，0，0）
//碎石机钎杆坐标（x,y,z）
//碎石小臂与上臂连接处轴的坐标（x',y',z'）

