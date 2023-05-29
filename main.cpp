#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>



struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

void segmentGreen(const std::string& inputImagePath, const std::string& outputImagePath, int greenThreshold) {
    std::ifstream inputFile(inputImagePath, std::ios::binary);
    std::ofstream outputFile(outputImagePath, std::ios::binary);

    if (!inputFile) {
        std::cerr << "Failed to open the input image." << std::endl;
        return;
    }

    if (!outputFile) {
        std::cerr << "Failed to create the output image." << std::endl;
        return;
    }

    std::string header;
    std::getline(inputFile, header);
    outputFile << header << std::endl;

    int width, height;
    inputFile >> width >> height;
    outputFile << width << " " << height << std::endl;

    int maxColorValue;
    inputFile >> maxColorValue;
    outputFile << maxColorValue << std::endl;

    std::vector<Pixel> pixels(width * height);
    for (int i = 0; i < width * height; ++i) {
        inputFile.read(reinterpret_cast<char*>(&pixels[i]), sizeof(Pixel));
    }

    for (Pixel& pixel : pixels) {
        if (pixel.green >= greenThreshold) {
            pixel.red = 0;
            pixel.green = 0;
            pixel.blue = 0;
        } else {
            pixel.red = 255;
            pixel.green = 255;
            pixel.blue = 255;
        }
    }

    for (const Pixel& pixel : pixels) {
        outputFile.write(reinterpret_cast<const char*>(&pixel), sizeof(Pixel));
    }

    std::cout << "Green segmentation completed successfully." << std::endl;
}

int main(int argc, char *argv[])
{

    //std::string inputImagePath = "‪C:/Users/Hadi/pics/rgb.ppm";
    std::string inputImagePath = "C:/Users/Hadi/pics/rgb.ppm";
    std::string outputImagePath = "C:/Users/Hadi/Pictures/output.ppm";
    int greenThreshold = 100;

    segmentGreen(inputImagePath, outputImagePath, greenThreshold);

    return 0;
}
