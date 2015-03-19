#include "ImageWriter.hpp"

ImageWriter::ImageWriter( Image<RGB> _image)
: image( _image ), colorGamut( 255 )
{
}

ImageWriter::~ImageWriter()
{
}

void ImageWriter::writeOnPPM( const std::string _imagepath )
{
	std::ofstream file;
	file.open( _imagepath.c_str(), std::ios_base::binary );
	file << "P3" << std::endl;
	file << image.getWidth() << " " << image.getHeight() << std::endl;
	file << colorGamut << std::endl;

	for( unsigned int i = 0; i < image.data.size(); ++i ){
		for( unsigned int j = 0; j < image.data[i].size(); ++j ){
			RGB color = image.data[i][j];
			file << std::min((int)(color.r * colorGamut), colorGamut) << " " 
				 << std::min((int)(color.g * colorGamut), colorGamut) << " " 
				 << std::min((int)(color.b * colorGamut), colorGamut) << " ";
		}
	}

	file.close();
}


void ImageWriter::setColorGamut( const int _colorGamut )
{
	this->colorGamut = _colorGamut;
}
