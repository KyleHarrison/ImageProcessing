#ifndef IMAGE_H
#define IMAGE_H
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
namespace HRRKYL008{

using namespace std;

class Image
{
    friend ostream& operator<<(ostream& stream, Image &rhs);
    friend ifstream& operator>>(ifstream& stream, Image &rhs);

private:
    int width, height;
    std::unique_ptr<unsigned char[]> data;

public:
    // iterator begin(void) { return iterator(data.get())}; // etc
    Image();
    ~Image();

    Image(string);
    Image(int, int);
    Image (const Image& rhs);
    Image (Image&& rhs);
    Image(int width, int height, int intensity);
    Image(int width, int height, unsigned char*& imageData);

    void load(string name);
    void save(string name);
    void copy(Image & rhs);
    unsigned char* getPixel(int index);

    Image operator +(Image &rhs);
    Image operator -(Image &rhs);
    Image operator ! ();
    Image operator / (Image & rhs);
    Image operator * (int f);

    class iterator
    {
    private:
        unsigned char *ptr;
        // grant private access to Image class functions
        friend class Image;
        // construct only via Image class (begin/end)

        iterator(unsigned char *p) : ptr(p) {}

    public:
        //copy construct is public
        iterator( const iterator & rhs) : ptr(rhs.ptr) {}

        // define overloaded ops: *, ++, --, =
        iterator & operator=(const iterator & rhs)
        {
            ptr = rhs.ptr;
            return *this;
        }

        bool operator !=(const iterator & rhs){
            return ptr != rhs.ptr;
        }

        unsigned char& operator*()
        {
            return *ptr;
        }

        iterator & operator++(void)
        {
            ptr++;
            return *this;
        }

        iterator operator++(int)
        {
            iterator postfix = *this;

            ptr++;
            return postfix;
        }


    };
    // define begin()/end() to get iterator to start and
    // "one-past" end.
    iterator begin(void) {
        return iterator(data.get());
    }

    iterator end(void) {
        return iterator(data.get() + width*height);
    }
};
#endif
}
