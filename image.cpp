#include "image.h"
#include <fstream>

Image::Image() : width(600), height(600)
{
    Color c();
    std::vector<Color> tmp = std::vector<Color>(width);
    pixels = std::vector< std::vector<Color> >(height, tmp);
}

Image::Image(const int imSize) : width(imSize), height(imSize)
{
    Color c();
    std::vector<Color> tmp(width);
    pixels = std::vector< std::vector<Color> >(height, tmp);
}


Image::Image(const int w, const int h) : width(w), height(h)
{
    Color c();
    std::vector<Color> tmp(width);
    pixels = std::vector< std::vector<Color> >(height, tmp);
}

Image::Image( std::vector< std::vector<Color> > pxs ) : pixels(pxs)
{
    width = pixels.size();
    height = pixels[0].size();
}

Color Image::getPixel(const int x, const int y) const
{
    return pixels[x][y];
}

void Image::setPixel(const int x, const int y, const Color& c)
{
    pixels[x][y] = c;
}

void Image::save(const std::string& filepath)
{
    std::ofstream file;
    file.open(filepath.c_str(), std::ios::binary);
    file<<'P'<<'6'<<'\n'<<pixels[0].size()<<' '<<pixels.size()<<'\n'<<'2'<<'5'<<'5'<<'\n';
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            file.put(255*pixels[i][j].r);
            file.put(255*pixels[i][j].g);
            file.put(255*pixels[i][j].b);
        }
    file.close();

}

Image::~Image()
{
    //dtor
}
