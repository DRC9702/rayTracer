#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
//My classes
#include "surface.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "camera.h"
#include "material.h"
#include "ray.h"
#include "exr_test.h"

#include "readscene.h"

#include <cstdlib>	//Nope! Don't need this!

using namespace std;




// this is called from the parseSceneFile function, which uses
// it to get the double from the correspoding position on the line.
//
// return the corresponding token in the inString. Errors out
// if you've asked for more than are in the line.
//
// you really don't need to know what is going on in here, I think.
//
double readscene::getTokenAsDouble (string inString, int whichToken)
{
    
    double thisDoubleVal = 0.;    // the return value
    
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
    
    thisDoubleVal = atof (p);
    
    delete[] cstr;
    
    return thisDoubleVal;
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
// then calls the "getTokenAsDouble" routine to pull out the needed values.
// NOTE: since different commands take different number of arguments, you
// must take care not to call getTokenAsDouble for an index that is beyond the
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


//std::vector<surface*> surfaceList = std::vector<surface*>();
//std::vector<material*> materialList = std::vector<material*>();
//camera cam;

void readscene::parseSceneFile (char *filnam)
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
            	//cout << "got a sphere" << endl;
                // it's a sphere, load in the parameters
                
                double x, y, z, r;
                x = getTokenAsDouble (line, 1);
                y = getTokenAsDouble (line, 2);
                z = getTokenAsDouble (line, 3);
                r = getTokenAsDouble (line, 4);

                // build your sphere here from the parameters
                // i.e. you must call your sphere constructor and set its position
                // and radius from the above values. You must also put your new
                // sphere into the objects list (which can be global)
                // So something like;
                // mySphereClass *ms = new mySphereClass (x, y, z, r);   // make a new instance of your sphere class
                sphere *ms = new sphere(x,y,z,r,surfaceList.size());
            	//cout << "Didn't die making a new sphere" << endl;
                // ms->setMaterial (lastMaterialLoaded)
                //ms->setMaterial(lastMaterialLoaded);
				ms->setMaterialIndex(materialList.size()-1); //Load into ms the index of the last stored material
                //cout << "Didn't die loading last material" << endl;
                // objectsList->push_back (ms);  // objectsList is a global std:vector<surface *> for example.
                surfaceList.push_back(ms);
            	//cout << "Didn't die pushing sphere on surfaceList" << endl;
                
                
#ifdef IM_DEBUGGING
                // if we're debugging, show what we got:
                //cout << "got a sphere with ";
                //cout << "parameters: " << x << " " << y << " " << z << " " << r << endl;
				//cout << "Current material index: " << ms->getMaterialIndex() << endl;
#endif
                break;
            }
            case 't':   // triangle
            {
			double x1, y1, z1, x2, y2, z2, x3, y3, z3;
			//Point1
			x1 = getTokenAsDouble (line, 1);
			y1 = getTokenAsDouble (line, 2);
			z1 = getTokenAsDouble (line, 3);
			//Point2
			x2 = getTokenAsDouble (line, 4);
			y2 = getTokenAsDouble (line, 5);
			z2 = getTokenAsDouble (line, 6);
			//Point3
			x3 = getTokenAsDouble (line, 7);
			y3 = getTokenAsDouble (line, 8);
			z3 = getTokenAsDouble (line, 9);

			triangle *mt = new triangle(x1,y1,z1,x2,y2,z2,x3,y3,z3,surfaceList.size());
			mt->setMaterialIndex(materialList.size()-1);
			surfaceList.push_back(mt);

//			triangle *mt2 = new triangle(x3,y3,z3,x2,y2,z2,x1,y1,z1);
//			mt2->setMaterialIndex(materialList.size()-1);
//			surfaceList.push_back(mt2);

#ifdef IM_DEBUGGING
			// if we're debugging, show what we got:
			//cout << "got a Triangle with ";
			//cout << "parameters: p1[" << x1 << ", " << y1 << ", " << z1
			//		<< "] p2[" << x2 << ", " << y2 << ", " << z2
			//		<< "] p3[" << x3 << ", " << y3 << ", " << z3 << "]"
			//		<< endl;
			//cout << "Current material index: " << ms->getMaterialIndex() << endl;
#endif

			break;
			}
            case 'p':   // plane
            {
//            	double nx, ny, nz, d;
//            	nx = getTokenAsDouble (line, 1);
//				ny = getTokenAsDouble (line, 2);
//				nz = getTokenAsDouble (line, 3);
//				d = getTokenAsDouble (line, 4);
//				plane *mp = new plane(nx,ny,nz,d);
//				mp->setMaterialIndex(materialList.size()-1);
//				surfaceList.push_back(mp);
//
//#ifdef IM_DEBUGGING
//                // if we're debugging, show what we got:
//                //cout << "got a Plane with ";
//                //cout << "parameters: nx[" << nx << "] ny[" << ny << "] nz[" << nz << "] d[" << d << "]" <<  endl;
//				//cout << "Current material index: " << ms->getMaterialIndex() << endl;
//#endif
            	cout << "We got a plane but no way to handle them as inputs because of bounding boxes. :/. Will figure out later." << endl;
                break;
            }
                
            //
            // camera:
            //
            case 'c':
            {   // camera
                // one trick here: the cameras pixel count (width, height) are integers,
                // so cast them.
                double x, y, z, vx, vy, vz, d, iw, ih;
                int pw, ph;
                
                x = getTokenAsDouble (line, 1);
                y = getTokenAsDouble (line, 2);
                z = getTokenAsDouble (line, 3);
                vx = getTokenAsDouble (line, 4);
                vy = getTokenAsDouble (line, 5);
                vz = getTokenAsDouble (line, 6);
                d = getTokenAsDouble (line, 7);
                iw = getTokenAsDouble (line, 8);
                ih = getTokenAsDouble (line, 9);
                pw = (int) getTokenAsDouble (line, 10);
                ph = (int) getTokenAsDouble (line, 11);
                
                cam = camera(x,y,z,vx,vy,vz,d,pw,ph,iw,ih);
                break;
             }   
            //
            // lights:
            //
            case 'l':   // light
                
                // slightly different from the rest, we need to examine the second param,
                // which is at the third position on the line:
                switch (line[2]) { //I'm pretty sure this should be a 1 not a 2. It's in the 2nd position, not third.
                    case 'p':{   // point light
                    	double x,y,z,r,g,b;
                    	x = getTokenAsDouble (line, 2);
						y = getTokenAsDouble (line, 3);
						z = getTokenAsDouble (line, 4);
						r = getTokenAsDouble (line, 5);
						g = getTokenAsDouble (line, 6);
						b = getTokenAsDouble (line, 7);

						pointLight *pl = new pointLight(x,y,z,r,g,b,1); //I have no idea what intensity should be set to.
						pointLightList.push_back(pl);

#ifdef IM_DEBUGGING
		                // if we're debugging, show what we got:
		                //cout << "got a PointLight with ";
		                //cout << "parameters: x[" << x << "] y[" << y << "] z[" << z << "] r[" << r << "] g[" << g << "] b[" << b << "]" << " [No intensity(1 for now)]"<<  endl;
#endif

                    	break;
                    }
                    case 'd':   // directional light
                        break;
                    case 'a':{   // ambient light
                    	double r,g,b;
                    	r = getTokenAsDouble (line, 2);
						g = getTokenAsDouble (line, 3);
						b = getTokenAsDouble (line, 4);
						ambLight = ambientLight(r,g,b);
                    	break;
                    }
                        
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
                double dr, dg, db, sr, sg, sb, r, ir, ig, ib;
                dr = getTokenAsDouble (line, 1);
                dg = getTokenAsDouble (line, 2);
                db = getTokenAsDouble (line, 3);
                sr = getTokenAsDouble (line, 4);
                sg = getTokenAsDouble (line, 5);
                sb = getTokenAsDouble (line, 6);
                r = getTokenAsDouble (line, 7);
                ir = getTokenAsDouble (line, 8);
                ig = getTokenAsDouble (line, 9);
                ib = getTokenAsDouble (line, 10);
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

            case 'w':{ //obj file
            	std::vector<int> tris;
            	std::vector<double> verts;
//            	const char *fileLoc = line.substr(2).c_str();
//            	cout << line << endl;
//            	cout << line.substr(2).c_str() << endl;
//            	printf("%s", fileLoc);
//            	cout << fileLoc << endl;
            	read_wavefront_file(line.substr(2).c_str(), tris, verts); //
            	for(unsigned int i=0; i<tris.size()/3; i++){
//            		cout << "Hello!" << endl;
            		double x1, y1, z1, x2, y2, z2, x3, y3, z3;
					//Point1
					x1 = verts[3*tris[3*i]];
					y1 = verts[3*tris[3*i]+1];
					z1 = verts[3*tris[3*i]+2];
					//Point2
					x2 = verts[3*tris[3*i+1]];
					y2 = verts[3*tris[3*i+1]+1];
					z2 = verts[3*tris[3*i+1]+2];
					//Point3
					x3 = verts[3*tris[3*i+2]];
					y3 = verts[3*tris[3*i+2]+1];
					z3 = verts[3*tris[3*i+2]+2];

					triangle *mt = new triangle(x1,y1,z1,x2,y2,z2,x3,y3,z3,surfaceList.size());
					mt->setMaterialIndex(materialList.size()-1);
					surfaceList.push_back(mt);
            	}
            	break;
            }
        }
        
    }
}


void readscene::getData(std::vector<surface*> *surfaceList, std::vector<material*> *materialList, std::vector<pointLight*> *pointLightList, camera *cam, ambientLight *ambLight){
	*surfaceList = this->surfaceList;
	*materialList = this->materialList;
	*pointLightList = this->pointLightList;
	*cam = this->cam;
	*ambLight = this->ambLight;
}


void readscene::read_wavefront_file (const char *file, std::vector< int > &tris, std::vector< double > &verts){
    
    // clear out the tris and verts vectors:
    tris.clear ();
    verts.clear ();

    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    for (int line=1; in.good(); line++) {
    	cout << "Reading in line[" << line << "] of wavefront file." << endl;
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;

        cmd="";

        istringstream iss (buffer);

        iss >> cmd;

        //cout << "trisSize: " << tris.size() << endl;

        if (cmd[0]=='#' or cmd.empty()) {
            // ignore comments or blank lines
            continue;
        }
        else if (cmd=="v") {
            // got a vertex:

            // read in the parameters:
            double pa, pb, pc;
            iss >> pa >> pb >> pc;

            verts.push_back (pa);
            verts.push_back (pb);
            verts.push_back (pc);
         }
        else if (cmd=="f") {
            // got a face (triangle)

            // read in the parameters:
            int i, j, k;
            iss >> i >> j >> k;

            // vertex numbers in OBJ files start with 1, but in C++ array
            // indices start with 0, so we're shifting everything down by
            // 1
            tris.push_back (i-1);
            tris.push_back (j-1);
            tris.push_back (k-1);
        }
        else {
            std::cerr << "Parser error: invalid command at line " << line << std::endl;
        }
        
     }
    
    in.close();
    
 //   std::cout << "found this many tris, verts: " << tris.size () / 3.0 << "  " << verts.size () / 3.0 << std::endl;
}
