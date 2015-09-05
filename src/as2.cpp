// as2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Scene.h"
#include "Parser.h"
#include <time.h>


using namespace std;


int main(int argc, char* argv[]) {
    bool write = false, disp = true;
    string inputFile, writeFile;

    Scene scene;

    if (argc > 1) {
        scene = Scene();
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-i") == 0) {
                inputFile = string(argv[i + 1]);
                i++;
            } else if (strcmp(argv[i], "-w") == 0) {
                write = true;
                writeFile = string(argv[i + 1]);
                i++;
            } else if (strcmp(argv[i], "-nd") == 0) {
                disp = false;
            }
        }

        cout << "Input File: " << inputFile << endl;
        if (write) cout << "Output File: " << writeFile << endl;
        if (disp) cout << "Display on" << endl;
        cout << endl;

        cout << "Parsing info:" << endl;
        loadScene(inputFile, scene);
        scene.debug();
    } else {
        scene = Scene(2, 1, 0); //for testing purposes only
        scene.debug(); //move outside
    }

    time_t start = time(NULL);
    scene.render();
    time_t end = time(NULL);
    cout << "DONE!" << endl;
    cout << "Render Time: "<<  difftime(end, start) << " seconds" << endl;

    if (write) scene.film.writeFile(writeFile);
    if (disp) scene.film.display();

    return 0;
}
