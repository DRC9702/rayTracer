#include<iostream>
#include "sphere.h"
#include "surface.h"
#include "camera.h"
#include "point.h"
#include "vector.h"
#include "ray.h"

using namespace std;

int main(){
	cout << "Hello world. Let's make points." << endl;
	
	
	surface s = sphere(0,0,5,2);
	ray r = ray(point(0,3,0), vector(0,0,1));
	cout << "t = " << s.intersectT(r) << endl;
	
	return 0;
}
