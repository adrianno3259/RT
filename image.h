#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include <vector>
#include <string>

class Image
{
    public:
        Image(); // imagem preta 200 x 200
        Image(const int imSize); //imagem preta imSize x imSize
        Image(const int w, const int h); // imagem preta w x h
        Image( std::vector< std::vector<Color> > pxs ); // imagem a partir de matriz de pixels

        Color getPixel(const int x, const int y) const;
        void setPixel(const int x, const int y, const Color& c);

        void save(const std::string& filename);

        virtual ~Image();

    protected:
        std::vector< std::vector<Color> > pixels;
        int width, height;
    private:

};

#endif // IMAGE_H
