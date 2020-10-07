#include "Image.h"

namespace HRRKYL008{

Image::Image(){}

Image::Image(string name)//:rows(width), columns(height)
{
    load(name);
}

Image::Image(int width, int height):width(width),height(height){
    /*    this->width = width;
    this->height = height;*/
    data = unique_ptr<unsigned char[]>(new unsigned char[width*height]);
}

Image::Image(int width, int height, int intensity):width(width),height(height) {

    unsigned char * imageData =  new unsigned char[width*height];

    for (int i = 0 ; i < width*height; i++){
        imageData[i] = intensity;
    }
    data = std::unique_ptr<unsigned char[]> (imageData);
}


Image::Image(int width, int height, unsigned char*& imageData):width(width),height(height){

    data = std::unique_ptr<unsigned char[]> (imageData);
}

unsigned char* Image::getPixel(int index){
    if(index > width*height){
        cout << "Invalid index" << endl;
        exit(1);
    }
    return data.get() + index;
}

//COPY CONSTRUCTOR
Image::Image (const Image & rhs):width(rhs.width),height(rhs.height){
    data.reset(rhs.data.get());
}

//MOVE CONSTRUCTOR
Image::Image(Image&& rhs):width(std::move(rhs.width)),height(std::move(rhs.height)){
    data.reset(rhs.data.get());
    rhs.data.reset();
}

void Image::copy(Image &rhs){
    Image::iterator beg = this->begin(), end = this->end();
    Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

    while(beg != end){

        *beg = *inStart;
        ++beg;
        ++inStart;

    }
}

void Image::load(string name){
    ifstream imagestream;
    imagestream.open(name, ios::in | ios::binary);

    if (!imagestream.is_open())
    {
        cout << "Can't read image: " << name << endl;
        exit(1);
    }
    imagestream >> *this;
}

void Image::save(string name){
    ofstream stream;
    stream.open(name, ios::out | ios::binary);
    stream << "P5" <<endl;
    stream << width << " " << height << endl;
    stream << "255" << endl;
    stream << *this;
}



Image Image::operator+(Image &rhs)
{
    Image temp(rhs.width, rhs.height);

    Image::iterator thisB = this->begin();
    Image::iterator thisE = this->end();
    Image::iterator rhsB = rhs.begin();
    Image::iterator rhsE = rhs.end();

    Image::iterator tempB = temp.begin();

    while(thisB != thisE){
        if(*rhsB + *thisB > 255){
            *tempB = 255;
        }
        else{
            *tempB = *rhsB + *thisB;
        }
        ++rhsB;
        ++thisB;
        ++tempB;
    }

    return temp;
}

Image Image::operator - (Image & rhs){

    Image::iterator thisB = this->begin(), thisE = this->end();
    Image::iterator rhsB = rhs.begin(), rhsE = rhs.end();

    Image temp(rhs.width, rhs.height);

    Image::iterator tempB = temp.begin();

    while(thisB != thisE){

        if (*thisB > *rhsB){

            *tempB = *thisB - *rhsB ;

        }
        else{
            *tempB = 0;
        }

        ++thisB;
        ++rhsB;
        ++tempB;
    }

    return temp;
}

Image Image::operator !(){
    Image temp(width, height);
    Image::iterator thisB = this->begin(), thisE = this->end();
    Image::iterator tempB = temp.begin();

    while (thisB != thisE){
        *tempB = 255 - *thisB;
        ++thisB;
        ++tempB;
    }

    return temp;
}

Image Image::operator / (Image & rhs){

    Image::iterator thisB = this->begin(), thisE = this->end();
    Image::iterator rhsB = rhs.begin(), rhsE = rhs.end();

    Image temp(rhs.width, rhs.height);

    Image::iterator tempB = temp.begin();

    while(thisB != thisE){

        if (*rhsB == 255){

            *tempB = *thisB ;

        }
        else{
            *tempB = 0;
        }

        ++thisB;
        ++rhsB;
        ++tempB;
    }

    return temp;

}

Image Image::operator * (int f){

    Image temp(width, height);
    Image::iterator tempB = temp.begin();
    Image::iterator thisB = this->begin(), thisE = this->end();

    while (thisB != thisE){

        if (*thisB > f){
            *tempB = 255;
        }
        else{
            *tempB = 0;
        }
        ++thisB;
	++tempB;
    }

    return temp;
}




ostream& operator<<(ostream& stream, Image &rhs){
    stream.write((char*)rhs.data.get(), rhs.width*rhs.height);
    return stream;
}

ifstream& operator>>(ifstream& imagestream, Image &rhs){
    string line;
    getline(imagestream, line);

    if(line.substr(0, 2)!="P5"){
        cout << "Image is not PGM" << endl;
        exit(1);
    }

    getline(imagestream, line);
    while(line.substr(0, 1)=="#")
        getline(imagestream, line);

    istringstream ss(line);
    ss >> rhs.width >> ws >> rhs.height;

    rhs.data = unique_ptr<unsigned char[]>(new unsigned char[rhs.width*rhs.height]);

    imagestream.read((char*)rhs.data.get(), rhs.width*rhs.height);
    return imagestream;
}

Image::~Image()
{
	data.release();
}

}
