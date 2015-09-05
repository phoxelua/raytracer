#include "stdafx.h"
#include "Scene.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>


void loadScene(std::string file, Scene& scene) {

    //store variables and set stuff at the end

    //Camera variables
    int width = 0, height = 0;
    vec3 lookAt(0,0,0), lookFrom(0,0,0), up(0,0,0);
    float fov = 0, apR = 0;

    Material currMat = Material(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 0, vec3(0,0,0), vec3(0,0,0));

    vector<vec3> vertices;
    vector<pair<vec3,vec3> > vertexNormals;

    std::string fname = "output.jpg";

    std::ifstream inpfile(file.c_str());
    if(!inpfile.is_open()) {
        std::cout << "Unable to open file" << std::endl;
    } else {
        std::string line;
        //MatrixStack mst;

        while(inpfile.good()) {
            std::vector<std::string> splitline;
            std::string buf;

            std::getline(inpfile,line);
            std::stringstream ss(line);

            while (ss >> buf) {
                splitline.push_back(buf);
            }
            //Ignore blank lines
            if(splitline.size() == 0) {
                continue;
            }

            //Ignore comments
            if(splitline[0][0] == '#') {
                continue;
            }

            //Valid commands:
            //size width height
            //  must be first command of file, controls image size
            else if(!splitline[0].compare("size")) {
                width = atoi(splitline[1].c_str());
                height = atoi(splitline[2].c_str());
            }
            //maxdepth depth
            //  max # of bounces for ray (default 5)
            else if(!splitline[0].compare("maxdepth")) {
                scene.depth = atoi(splitline[1].c_str());
            }
            //output filename
            //  output file to write image to
            else if(!splitline[0].compare("output")) {
                fname = splitline[1];
            }

            //camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
            //  speciﬁes the camera in the standard way, as in homework 2.
            else if(!splitline[0].compare("camera")) {
                lookFrom = vec3(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
                lookAt = vec3(atof(splitline[4].c_str()), atof(splitline[5].c_str()), atof(splitline[6].c_str()));
                up = vec3(atof(splitline[7].c_str()), atof(splitline[8].c_str()), atof(splitline[9].c_str()));
                fov = atof(splitline[10].c_str());
            }

            //aperture radius
            //specifies aperture size for depth of field computations, default zero
            else if(!splitline[0].compare("aperture")) {
                apR = atof(splitline[1].c_str());
            }

            //distrib number
            //specifies number of random samples per pixel, default one
            else if(!splitline[0].compare("distrib")) {
                scene.distrib = atoi(splitline[1].c_str());
            }

            //sphere x y z radius
            //  Deﬁnes a sphere with a given position and radius.
            else if(!splitline[0].compare("sphere")) {
                scene.allShapes.push_back(new Sphere(vec3(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str())), atof(splitline[4].c_str()), currMat, scene.transformation));
            }
            //maxverts number
            //  Deﬁnes a maximum number of vertices for later triangle speciﬁcations.
            //  It must be set before vertices are deﬁned.
            else if(!splitline[0].compare("maxverts")) {
                // Care if you want
                // Here, either declare array size
                // Or you can just use a STL vector, in which case you can ignore this
            }
            //maxvertnorms number
            //  Deﬁnes a maximum number of vertices with normals for later speciﬁcations.
            //  It must be set before vertices with normals are deﬁned.
            else if(!splitline[0].compare("maxvertnorms")) {
                // Care if you want
            }
            //vertex x y z
            //  Deﬁnes a vertex at the given location.
            //  The vertex is put into a pile, starting to be numbered at 0.
            else if(!splitline[0].compare("vertex")) {
                vertices.push_back(vec3(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str())));
                /*Create a new vertex with these 3 values, store in some array*/
            }
            //vertexnormal x y z nx ny nz
            //  Similar to the above, but deﬁne a surface normal with each vertex.
            //  The vertex and vertexnormal set of vertices are completely independent
            //  (as are maxverts and maxvertnorms).
            else if(!splitline[0].compare("vertexnormal")) {
                vertexNormals.push_back(pair<vec3,vec3>(vec3(atof(splitline[1].c_str()),
                                                        atof(splitline[2].c_str()),
                                                        atof(splitline[3].c_str())),
                                                        vec3(atof(splitline[4].c_str()),
                                                                atof(splitline[5].c_str()),
                                                                atof(splitline[6].c_str()))));
                // Create a new vertex+normal with these 6 values, store in some array
            }
            //tri v1 v2 v3
            //  Create a triangle out of the vertices involved (which have previously been speciﬁed with
            //  the vertex command). The vertices are assumed to be speciﬁed in counter-clockwise order. Your code
            //  should internally compute a face normal for this triangle.
            else if(!splitline[0].compare("tri")) {
                scene.allShapes.push_back(new Triangle(vertices[atoi(splitline[1].c_str())],
                                                       vertices[atoi(splitline[2].c_str())],
                                                       vertices[atoi(splitline[3].c_str())],
                                                       currMat, scene.transformation));
                // Create new triangle:
                //   Store pointer to array of vertices
                //   Store 3 integers to index into array
                //   Store current property values
                //   Store current top of matrix stack
            }
            //trinormal v1 v2 v3
            //  Same as above but for vertices speciﬁed with normals.
            //  In this case, each vertex has an associated normal,
            //  and when doing shading, you should interpolate the normals
            //  for intermediate points on the triangle.
            else if(!splitline[0].compare("trinormal")) {
                int v1 = atoi(splitline[1].c_str()), v2 = atoi(splitline[2].c_str()), v3=atof(splitline[3].c_str());
                scene.allShapes.push_back(new Triangle(vertexNormals[v1].first,
                                                       vertexNormals[v2].first,
                                                       vertexNormals[v3].first,
                                                       vertexNormals[v1].second,
                                                       vertexNormals[v2].second,
                                                       vertexNormals[v3].second,
                                                       currMat, scene.transformation));
                // Create new triangle:
                //   Store pointer to array of vertices (Different array than above)
                //   Store 3 integers to index into array
                //   Store current property values
                //   Store current top of matrix stack
            }

            //translate x y z
            //  A translation 3-vector
            else if(!splitline[0].compare("translate")) {
                scene.transformation.translate(vec3(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str())));
                //cout << "translation" << vec3(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str())) << endl << endl;
                //cout << scene.transformation.transform << endl << endl << endl;
                // Update top of matrix stack
            }
            //rotate x y z angle
            //  Rotate by angle (in degrees) about the given axis as in OpenGL.
            else if(!splitline[0].compare("rotate")) {
                scene.transformation.rotate(vec3(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str())),atof(splitline[4].c_str()));
                // Update top of matrix stack
            }
            //scale x y z
            //  Scale by the corresponding amount in each axis (a non-uniform scaling).
            else if(!splitline[0].compare("scale")) {
                scene.transformation.scale(vec3(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str())));
                //cout << "scale" << vec3(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str())) << endl << endl;
                // Update top of matrix stack
            }
            //pushTransform
            //  Push the current modeling transform on the stack as in OpenGL.
            //  You might want to do pushTransform immediately after setting
            //   the camera to preserve the “identity” transformation.
            else if(!splitline[0].compare("pushTransform")) {
                scene.transformation.push();
                //cout<<"PUSH"<<endl;
                //mst.push();
            }
            //popTransform
            //  Pop the current transform from the stack as in OpenGL.
            //  The sequence of popTransform and pushTransform can be used if
            //  desired before every primitive to reset the transformation
            //  (assuming the initial camera transformation is on the stack as
            //  discussed above).
            else if(!splitline[0].compare("popTransform")) {
                scene.transformation.pop();
                //cout<<"POP"<<endl;
                //mst.pop();
            }

            //directional x y z r g b
            //  The direction to the light source, and the color, as in OpenGL.
            else if(!splitline[0].compare("directional")) {
                scene.allDirLights.push_back(DirLight(vec3(atof(splitline[4].c_str()),atof(splitline[5].c_str()),atof(splitline[6].c_str())),
                                                      vec3(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()))));
                // add light to scene...
            }
            //point x y z r g b
            //  The location of a point source and the color, as in OpenGL.
            else if(!splitline[0].compare("point")) {
                scene.allPtLights.push_back(PtLight(vec3(atof(splitline[4].c_str()),atof(splitline[5].c_str()),atof(splitline[6].c_str())),
                                                    vec3(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()))));
                // add light to scene...
            }
            //attenuation const linear quadratic
            //  Sets the constant, linear and quadratic attenuations
            //  (default 1,0,0) as in OpenGL.
            else if(!splitline[0].compare("attenuation")) {
                // const: atof(splitline[1].c_str())
                // linear: atof(splitline[2].c_str())
                // quadratic: atof(splitline[3].c_str())
            }
            //ambient r g b
            //  The global ambient color to be added for each object
            //  (default is .2,.2,.2)
            else if(!splitline[0].compare("ambient")) {
                currMat.ambient = vec3(atof(splitline[1].c_str()), atof(splitline[2].c_str()),atof(splitline[3].c_str()));
            }

            //diﬀuse r g b
            //  speciﬁes the diﬀuse color of the surface.
            else if(!splitline[0].compare("diffuse")) {
                currMat.diffuse = vec3(atof(splitline[1].c_str()), atof(splitline[2].c_str()),atof(splitline[3].c_str()));
                // r: atof(splitline[1].c_str())
                // g: atof(splitline[2].c_str())
                // b: atof(splitline[3].c_str())
                // Update current properties
            }
            //specular r g b
            //  speciﬁes the specular color of the surface.
            else if(!splitline[0].compare("specular")) {
                currMat.specular = vec3(atof(splitline[1].c_str()), atof(splitline[2].c_str()),atof(splitline[3].c_str()));
                // r: atof(splitline[1].c_str())
                // g: atof(splitline[2].c_str())
                // b: atof(splitline[3].c_str())
                // Update current properties
            }
            //shininess s
            //  speciﬁes the shininess of the surface.
            else if(!splitline[0].compare("shininess")) {
                currMat.coeff = atof(splitline[1].c_str());
                // Update current properties
            }
            //emission r g b
            //  gives the emissive color of the surface.
            else if(!splitline[0].compare("emission")) {
                currMat.emissive= vec3(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
                // Update current properties
            }
            //reflection r g b
            //  gives the reflection color of the surface.
            else if(!splitline[0].compare("reflect")) {
                currMat.reflect= vec3(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
                // Update current properties
            }

            //refraction r g b
            //  gives the refraction color of the surface.
            else if(!splitline[0].compare("refract")) {
                currMat.refract= vec3(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
                // Update current properties
            }
            //indexRefract
            //  gives the index of refraction
            else if (!splitline[0].compare("indexRefract")) {
                currMat.indexRefract = atof(splitline[1].c_str());
                // Update current properties
            }

            //environment front back left right top bottom
            // specify six environment mapping image files to form sides of cube
            else if(!splitline[0].compare("environment")) {
                scene.environment = true;
                scene.front = cimg_library::CImg<double>(splitline[1].c_str());
                scene.back = cimg_library::CImg<double>(splitline[2].c_str());
                scene.left = cimg_library::CImg<double>(splitline[3].c_str());
                scene.right = cimg_library::CImg<double>(splitline[4].c_str());
                scene.top = cimg_library::CImg<double>(splitline[5].c_str());
                scene.bottom = cimg_library::CImg<double>(splitline[6].c_str());
            }
            //antialiasing aafactor
            // turn antialiasing on / off with aafactor by aafactor distribution
            else if (!splitline[0].compare("antialiasing")) {
                scene.antialiasing = true;
                scene.aaFactor = atoi(splitline[1].c_str());
            }
            //unknown command
            else {
                std::cerr << "Unknown command: " << splitline[0] << std::endl;
            }
        }

        inpfile.close();
    }
    scene.camera = Camera(lookFrom, lookAt, up, fov, width, height, apR);
    scene.film = Film(width,height);

    //cout << scene.allDirLights.size() << endl;
    //cout << scene.allPtLights.size() << endl;
    //cout << scene.allShapes.size() << endl;

}
