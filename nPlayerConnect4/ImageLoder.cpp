#include "ImageLoder.h"

#include <iostream>

#include <fstream>
#include <string>
#include <exception>

#include <vector>




//https://blog.nobel-joergensen.com/2010/11/07/loading-a-png-as-texture-in-opengl-using-libpng/
bool ImageLoder::loadPNGFromFile(const char *name, int& pngWidth, int& pngHeight, bool& outHasAlpha, GLubyte** outData)
{
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int color_type, interlace_type;
	FILE *fp;
#ifdef _WIN32
	fopen_s(&fp, name, "rb");
#else
	fp = fopen(name, "rb");
#endif

	if (fp == NULL)
	{
		std::cerr << "Couldn't open texture file\n";
		perror("fopen");
		return false;
	}
	/* Create and initialize the png_struct
	 * with the desired error handler
	 * functions.  If you want to use the
	 * default stderr and longjump method,
	 * you can supply NULL for the last
	 * three parameters.  We also supply the
	 * the compiler header file version, so
	 * that we know if the application
	 * was compiled with a compatible version
	 * of the library.  REQUIRED
	 */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
									 NULL, NULL, NULL);


	if (png_ptr == NULL) {
		fclose(fp);
		//if (fp) { delete fp; }
		std::cerr << "png_create_read_struct returned NULL\n";
		return false;
	}

	/* Allocate/initialize the memory
	 * for image information.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		if (fp) { delete fp; }
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		std::cerr << "info_ptr is NULL\n";
		return false;
	}

	/* Set error handling if you are
	 * using the setjmp/longjmp method
	 * (this is the normal method of
	 * doing things with libpng).
	 * REQUIRED unless you  set up
	 * your own error handlers in
	 * the png_create_read_struct()
	 * earlier.
	 */
	if (setjmp(png_jmpbuf(png_ptr))) {
		/* Free all of the memory associated
		 * with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		//if (fp) { delete fp; }
		/* If we get here, we had a
		 * problem reading the file */
		std::cerr << "Problem reading file\n";
		return false;
	}
	/* Set up the output control if
	 * you are using standard C streams */
	png_init_io(png_ptr, fp);

	/* If we have already
	 * read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);

	/*
	 * If you have enough memory to read
	 * in the entire image at once, and
	 * you need to specify only
	 * transforms that can be controlled
	 * with one of the PNG_TRANSFORM_*
	 * bits (this presently excludes
	 * dithering, filling, setting
	 * background, and doing gamma
	 * adjustment), then you can read the
	 * entire image (including pixels)
	 * into the info structure with this
	 * call
	 *
	 * PNG_TRANSFORM_STRIP_16 |
	 * PNG_TRANSFORM_PACKING  forces 8 bit
	 * PNG_TRANSFORM_EXPAND forces to
	 *  expand a palette into RGB
	 */
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	png_uint_32 width, height;
	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
				 &interlace_type, NULL, NULL);
	pngWidth = width;
	pngHeight = height;

	//std::cout << "Colour_type\t" << color_type << "\n";

	outHasAlpha = (color_type & PNG_COLOR_MASK_ALPHA) != 0;

	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);

	*outData = (unsigned char*) malloc(row_bytes * pngHeight);

	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

	for (int i = 0; i < pngHeight; i++) {
		// note that png is ordered top to
		// bottom, but OpenGL expect it bottom to top
		// so the order or swapped
		//memcpy(*outData+(row_bytes * ((int)rect.height-1-i)), row_pointers[i], row_bytes);
		memcpy(*outData+(row_bytes * ((int)pngHeight-1-i)), row_pointers[i], row_bytes);
	}

	/* Clean up after the read,
	 * and free any memory allocated */
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	/* Close the file */
	fclose(fp);
	//if (fp) { delete fp; }
	/* That's it */


	return true;
}

GLuint ImageLoder::loadPNG(const char* path)
{
	//nv::Image img;
	GLuint texID;
	GLubyte* image = NULL;
	//Rect imageRect;
	int width = 0, height = 0;
	bool hasAlpha = false;

	if (ImageLoder::loadPNGFromFile(path,width,height,hasAlpha,&image))
	{
		/*for (int i = 0; i < width * height; i++) {
			std::cout << (int)image[i] << " ";
		}
		*//*
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				std::cout << (int)image[width * j + i] << "\t";
			}
			std::cout << "\n";
		}*/
		//std::cout << width << " " << height << "\n";
		//hasAlpha = false;
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, /*img.getFormat()*/GL_RGBA, GL_UNSIGNED_BYTE, &image);
		glTexImage2D(GL_TEXTURE_2D, 0, (hasAlpha ? GL_RGBA : GL_RGB), width, height, 0, /*img.getFormat()*/(hasAlpha ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, image);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
	else
	{
		std::cerr << "Error failed to load texture\n";
		texID = NULL;
	}

	if (image) {
		delete image;
	}

	return texID;
}