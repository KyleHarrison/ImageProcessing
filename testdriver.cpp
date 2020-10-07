#include "Image.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Move and Copy semantics\n",""){

    int width = 100;
    int height = 100;

    HRRKYL008::Image image1(width,height, 1);

    //Copy constructor
    HRRKYL008::Image image2(image1);

    for (int i = 0; i < width * height; i++){
        REQUIRE(*(image1.getPixel(i)) == *(image2.getPixel(i)));
    }

    //Move constructor
    HRRKYL008::Image image3 = std::move(image1);
    for (int i = 0; i < width * height; i++){
        REQUIRE(*(image3.getPixel(i)) == *(image2.getPixel(i)));
    }

}
TEST_CASE("Iterator and its operators (including boundary conditions)"){
    int width = 100;
    int height = 100;

    HRRKYL008::Image image1 (width,height, 255);
    HRRKYL008::Image::iterator beg = image1.begin();
    HRRKYL008::Image::iterator end = image1.end();

    int i =0;
    while(beg != end){
        REQUIRE(*beg == *image1.getPixel(i));
        ++beg;
        i++;
    }
}

TEST_CASE("Thresholding, inverting and masking operator overloads",""){

    int width = 100;
    int height = 100;


    HRRKYL008::Image image1 (width,height, 255);
    HRRKYL008::Image image2 (width,height, 100);

    HRRKYL008::Image threshold = image1 * 0;


    for (int i = 0; i < width * height; i++){
        REQUIRE((int)*(threshold.getPixel(i)) == 255);
    }

    HRRKYL008::Image invert = !image1;

    for (int i = 0; i < width * height; i++){
        REQUIRE( (int)*(invert.getPixel(i)) == 0);
    }

    HRRKYL008::Image mask = image2 / image1;

    for (int i = 0; i < width * height; i++){
        REQUIRE( (int)*(mask.getPixel(i)) == 100);
    }
}

TEST_CASE("Addition and Subtraction of Images",""){

    int width = 100;
    int height = 100;


    HRRKYL008::Image image1 (width,height, 255);
    HRRKYL008::Image image2 (width,height, 1);

    HRRKYL008::Image add = image1 + image2;


    for (int i = 0; i < width * height; i++){
        REQUIRE((int)*(add.getPixel(i)) == 255);
    }


    HRRKYL008::Image subtract = image1 - image2;

    for (int i = 0; i < width * height; i++){
        REQUIRE( (int)*(subtract.getPixel(i)) == 254);
    }
}

TEST_CASE("Simple Qualitative Test",""){

    HRRKYL008::Image image1;
    image1.load("Lenna_hat_mask.pgm");

    //1:image mask
    HRRKYL008::Image M1 = image1 * 150;


    //2:inverted mask
    HRRKYL008::Image M2 = !image1;

    //3 + 4:
    HRRKYL008::Image U1("Lenna_standard.pgm");

    HRRKYL008::Image U2("Lenna_hat_mask.pgm");

    HRRKYL008::Image MImage (U1/M1);
    HRRKYL008::Image M2Image (U2/M2);

    //5 create a mask
    HRRKYL008::Image M3Image(MImage + M2Image);

    M3Image.save("QualitativeTest.pgm");

}
