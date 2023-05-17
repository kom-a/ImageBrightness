#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>
#include <inttypes.h>
#include <string>
#include <math.h>
#include <iostream>
#include <ios>

#define CHANNELS 3
#define MIN_RGB_VALUE 0
#define MAX_RGB_VALUE 255

int Clamp(int value, int minimum, int maximum)
{
	return std::min(maximum, std::max(value, minimum));
}

struct Image
{
	Image(const std::string& filename);
	~Image();

	void BrightnessAdd(int brightness);
	void Save(const std::string& filename) const;

	int32_t Width;
	int32_t Height;
	uint8_t* Pixels;
};

Image::Image(const std::string& filename)
{
	Pixels = stbi_load(filename.c_str(), &Width, &Height, nullptr, CHANNELS);

	if (!Pixels)
		throw std::ios_base::failure("Failed to open image");
}

Image::~Image()
{
	stbi_image_free(Pixels);
}

void Image::BrightnessAdd(int brightness)
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			const int pixelIndex = (y * Width + x) * CHANNELS;
			for (int c = 0; c < CHANNELS; c++)
			{
				int channelColor = (int)Pixels[pixelIndex + c];
				Pixels[pixelIndex + c] = (uint8_t)Clamp(channelColor + brightness, MIN_RGB_VALUE, MAX_RGB_VALUE);
			}
		}
	}
}

void Image::Save(const std::string& filename) const
{
	stbi_write_jpg(filename.c_str(), Width, Height, CHANNELS, Pixels, 0);
}

int main()
{
	try
	{
		Image image("Res/sourceImage.jpg");
		image.BrightnessAdd(-100);
		image.Save("Res/darkImage.jpg");
		image.BrightnessAdd(150);
		image.Save("Res/brightImage.jpg");
	}
	catch (std::ios_base::failure e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}