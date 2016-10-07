#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
//My classes
#include "surface.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "ray.h"
#include "exr_test.h"

using namespace std;

#define IM_DEBUGGING


// this is called from the parseSceneFile function, which uses
// it to get the float from the correspoding position on the line.
//
// return the corresponding token in the inString. Errors out
// if you've asked for more than are in the line.
//
// you really don't need to know what is going on in here, I think.
//
float getTokenAsFloat (string inString, int whichToken)
{
    
    float thisFloatVal = 0.;    // the return value
    
    if (whichToken == 0) {
        cerr << "error: the first token on a line is a character!" << endl;
        exit (-1);
    }
    
    // c++ string class has no super-easy way to tokenize, let's use c's:
    char *cstr = new char [inString.size () + 1];
    
    strcpy (cstr, inString.c_str());
    
    char *p = strtok (cstr, " ");
    if (p == 0) {
        cerr << "error: the line has nothing on it!" << endl;
        exit (-1);
    }
    
    for (int i = 0; i < whichToken; i++) {
        p = strtok (0, " ");
        if (p == 0) {
            cerr << "error: the line is not long enough for your token request!" << endl;
            exit (-1);
        }
    }
    
    thisFloatVal = atof (p);
    
    delete[] cstr;
    
    return thisFloatVal;
}


//
// read the scene file.
//
// You'll need a few globals (or add arguments to this function): for the
// list of surfaces (geometric objects like spheres, triangles, planes) and
// another for the lights. These can be of type std::vector. You'll also
// need a global (or other parameter) for the camera.
//
// This should be pretty self-explanatory: it reads through the lines, and
// using the first character figures out what kind of command it is. It
// then calls the "getTokenAsFloat" routine to pull out the needed values.
// NOTE: since different commands take different number of arguments, you
// must take care not to call getTokenAsFloat for an index that is beyond the
// end of the line!
//
// One tricky bit: when a material is read in, we want
// to keep a pointer to it so that for the next geometric object read in ,
// we can add that material to the object. In the code that follows, I use the
// variable "lastSurfaceLoaded" to do that, but the code is commented out since
// I don't know the class names you will be using.
//
// Very minimal error check here. You might improve it slightly, but we'll
// only use "correct" scene files.
//
//


std::vector<surface*> surfaceList = std::vector<surface*>();
std::vector<material*> materialList = std::vector<material*>();
camera cam;
//material lastMaterialLoaded;

void parseSceneFile (char *filnam)
{
    
    ifstream inFile(filnam);    // open the file
    string line;
    
    if (! inFile.is_open ()) {  // if it's not open, error out.
        cerr << "can't open scene file" << endl;
        exit (-1);
    }
    
    
    // Note: you'll have to keep track of whatever the last material
    // you loaded in was, so you can apply it to any geometry that gets loaded. 
    // So here, you'll have something like:
    //
    // myMaterialClass *lastMaterialLoaded = 0;  // 0 or maybe a default material?
    material *lastMaterialLoaded = new material();
	materialList.push_back(lastMaterialLoaded);
    //
    // and each time you load in a new piece of geometry (sphere, triangle, plane)
    // you will set its material to lastMaterialLoaded.

    
    while (! inFile.eof ()) {   // go through every line in the file until finished
        
        getline (inFile, line); // get the line
        
        switch (line[0])  {     // we'll decide which command based on the first character
            
            //
            // geometry types:
            //
            // NOTE: whichever type of geo you load in, set its material to
            // be "lastMaterialLoaded"
            //
            case 's':
            {
            	cout << "got a sphere" << endl;
                // it's a sphere, load in the parameters
                
                float x, y, z, r;
                x = getTokenAsFloat (line, 1); 
                y = getTokenAsFloat (line, 2); 
                z = getTokenAsFloat (line, 3); 
                r = getTokenAsFloat (line, 4);

                // build your sphere here from the parameters
                // i.e. you must call your sphere constructor and set its position
                // and radius from the above values. You must also put your new
                // sphere into the objects list (which can be global)
                // So something like;
                // mySphereClass *ms = new mySphereClass (x, y, z, r);   // make a new instance of your sphere class
                sphere *ms = new sphere(x,y,z,r);
            	cout << "Didn't die making a new sphere" << endl;
                // ms->setMaterial (lastMaterialLoaded)
                ms->setMaterial(lastMaterialLoaded);
                cout << "Didn't die loading last material" << endl;
                // objectsList->push_back (ms);  // objectsList is a global std:vector<surface *> for example.
                surfaceList.push_back(ms);
            	cout << "Didn't die pushing sphere on surfaceList" << endl;
                
                
#ifdef IM_DEBUGGING
                // if we're debugging, show what we got:
                cout << "got a sphere with ";
                cout << "parameters: " << x << " " << y << " " << z << " " << r << endl;
#endif
                break;
            }
            case 't':   // triangle
                break;
                
            case 'p':   // plane
                break;
                
            //
            // camera:
            //
            case 'c':
            {   // camera
                // one trick here: the cameras pixel count (width, height) are integers,
                // so cast them.
                float x, y, z, vx, vy, vz, d, iw, ih;
                int pw, ph;
                
                x = getTokenAsFloat (line, 1); 
                y = getTokenAsFloat (line, 2); 
                z = getTokenAsFloat (line, 3); 
                vx = getTokenAsFloat (line, 4);
                vy = getTokenAsFloat (line, 5);
                vz = getTokenAsFloat (line, 6);
                d = getTokenAsFloat (line, 7);
                iw = getTokenAsFloat (line, 8);
                ih = getTokenAsFloat (line, 9);
                pw = (int) getTokenAsFloat (line, 10);
                ph = (int) getTokenAsFloat (line, 11);
                
                cam = camera(x,y,z,vx,vy,vz,d,pw,ph,iw,ih);
                break;
             }   
            //
            // lights:
            //
            case 'l':   // light
                
                // slightly different from the rest, we need to examine the second param,
                // which is at the third position on the line:
                switch (line[2]) {
                    case 'p':   // point light
                        break;
                    case 'd':   // directional light
                        break;
                    case 'a':   // ambient light
                        break;
                        
                }
                
                break;
            
            //
            //
            // materials:
            case 'm':   // material
            {
                // the trick here: we should keep a pointer to the last material we read in,
                // so we can apply it to any subsequent geometry. Say it's called "lastMaterialLoaded"
                // we migh then do something like this:
                //
                //  1. read in the 10 material parameters: dr, dg, db, sr, sg, sb, r, ir, ig, ib
                float dr, dg, db, sr, sg, sb, r, ir, ig, ib;
                dr = getTokenAsFloat (line, 1); 
                dg = getTokenAsFloat (line, 2); 
                db = getTokenAsFloat (line, 3); 
                sr = getTokenAsFloat (line, 4);
                sg = getTokenAsFloat (line, 5);
                sb = getTokenAsFloat (line, 6);
                r = getTokenAsFloat (line, 7);
                ir = getTokenAsFloat (line, 8);
                ig = getTokenAsFloat (line, 9);
                ib = getTokenAsFloat (line, 10);
                //  2. call lastMaterialLoaded->setMaterial(dr, dg, db,...);
                lastMaterialLoaded = new material(dr, dg, db, sr, sg, sb, r, ir, ig, ib);
				materialList.push_back(lastMaterialLoaded);
                //
                break;
			}
            
            case '/':
                // don't do anything, it's a comment
                break;
                

            //
            // options
            //
            case 'o':   // make your own options if you wish
                break;
        }
        
    }
}







void writeRgba (const char fileName[], const Rgba *pixels, int width, int height)
{
    //
    // Write an RGBA image using class RgbaOutputFile.
    //
    //	- open the file
    //	- describe the memory layout of the pixels
    //	- store the pixels in the file
    //
    
    
    RgbaOutputFile file (fileName, width, height, WRITE_RGBA);
    file.setFrameBuffer (pixels, 1, width);
    file.writePixels (height);
}



//
// the main just makes sure that there is an argument passed, which is
// supposed to be the scenefile.
//
int main (int argc, char *argv[])
{
  
    if (argc != 2) {
        cerr << "useage: raytra scenefilename" << endl;
        return -1;
    }
    cout << "no error before parsing" << endl;
    parseSceneFile (argv[1]);
    cout << cam.nx << "\t" << cam.ny << endl;
    
    
    
    //cout << surfaceList -> at(0) -> intersectT(ray (0, 13.67, 0, 0, 0, -1)) << endl;
	cout << surfaceList.at(0) -> intersectT(ray (0, 13.67, 0, 0, 0, -1)) << endl;
    

    try{
    	int w = cam.nx;
    	int h = cam.ny;
        Array2D<Rgba> p (h,w);
		p.resizeErase(h,w);

		//int totalPixels = w*h;
		//int currentPixelCount =0;
        
        for(int i=0; i < h; i++){
			for(int j=0; j < w; j++) {
				bool assigned = false;
				int index = -1;
				float minT = -1;
				for(int k=0; k < surfaceList.size(); k++){
					//We need to flip the y axis orientation because while our math uses a traditional x+ right, y+ up grid, the pixels are created with x+ right,y+ down
					//In this loop, I will represent the pixel index from the bottom, so since we want pixel index from the top, we calculate our rays with (h-i)
					if(	(!assigned && surfaceList.at(k) -> intersectT(cam.generateRayForPixel(j,h-i)) > 0) || (assigned && surfaceList.at(k) -> intersectT(cam.generateRayForPixel(j,h-i)) < minT)	){
						assigned=true;						
						index = k;
						minT = surfaceList.at(k) -> intersectT(cam.generateRayForPixel(j,h-i));
					}
				}
				Rgba &px = p[i][j]; 
				if(index != -1)
				{
					material *mat = surfaceList.at(index)->getMaterial();
					px.r=mat->dr; px.g=mat->dg; px.b=mat->db;
					//px.r=0.7; px.g=0; px.b=1;
				}
				else
				{
					px.r=0; px.g=0; px.b=0;
				}
				//currentPixelCount++;
				//if(currentPixelCount%(totalPixels/100)==0)
				//	cout << "|";
			}
    		writeRgba (((std::string(argv[1]))+".exr").c_str(), &p[0][0], w, h);
		}
		cout << "Didn't die while editing the pixels." << endl;

		cout << "Finished writing file" << endl;

        
    }
    catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    
    
    
    
    
    return 0;
}
