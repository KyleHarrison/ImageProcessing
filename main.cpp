#include <iostream>
#include "Image.h"
using namespace std;

int main(int argc, char *argv[])
{
    if(argc == 1){
        cout << "No argument specified" << endl;
        return 0;
    }
    string operation = argv[1];

    //-a I1 I2 (add I1 and I2)
    if (operation == "-a"){
	cout << "Adding Images: " << argv[2] << " + " << argv[3] << endl;
        HRRKYL008::Image image1(argv[2]);
        HRRKYL008::Image image2(argv[3]);
        HRRKYL008::Image add = image1 + image2;
        add.save(argv[4]);
    }

    //-s I1 I2 (subtract I2 from I1)
    if (operation ==  "-s"){
	cout << "Subtracting Images: " << argv[2] << " - " << argv[3] << endl;
        HRRKYL008::Image image1(argv[2]);
        HRRKYL008::Image image2(argv[3]);
        HRRKYL008::Image sub = image1 - image2;
        sub.save(argv[4]);
    }


    //-i I1 (invert I1)
    if (operation == "-i"){
	cout << "Inverting image: " << argv[2] << endl;
        HRRKYL008::Image image1(argv[2]);
        HRRKYL008::Image invert = !image1;
        invert.save(argv[3]);
    }


    //-l I1 I2 (mask I1 with I2)
    if (operation == "-l"){
	cout << "Masking Images: " << argv[2] << " / " << argv[3] << endl;
        HRRKYL008::Image image1(argv[2]);
        HRRKYL008::Image image2(argv[3]);
        HRRKYL008::Image mask = image1 / image2;
        mask.save(argv[4]);
    }


    //-t I1 f (threshold I1 with integer value f)
    if (operation == "-t"){
	cout << "Threshold image: " << argv[2] << " * " << argv[3] << endl;
        HRRKYL008::Image image1(argv[2]);
        int f = atoi(argv[3]);
        HRRKYL008::Image thresh = image1 * f;
        thresh.save(argv[4]);
    }

    return 0;
}

