#pragma once

#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

#include "Matrix2D.hpp"

template<typename T>
std::vector<T> split(std::string str, const char splitChar = ',') {
    std::string tempStr;
    std::vector<T> vecResult;
    size_t splitPos;
    long double temp;

    do {
        splitPos = str.find(splitChar);
        if (splitPos == std::string::npos)
            splitPos = str.find("\n");

        temp = std::stod(str.substr(0, splitPos));

        vecResult.push_back(static_cast<T>(temp));

        str = str.substr(splitPos + 1);
    } while (splitPos != std::string::npos);

    return vecResult;
}

template <typename T>
void readFilePoints(std::string path, std::vector<std::vector<T>>& pointVec) {
    std::string str;
    std::fstream input;
    input.open(path.c_str(), std::ios::in);

    if (!input.is_open())
        throw std::runtime_error("File is not open: " + path);

    while (std::getline(input, str))
        pointVec.push_back(split<T>(str));
    
    input.close();
}

std::vector<Matrix2D<double>> readFilePoints(std::string path) {
    std::fstream input;
    input.open(path.c_str(), std::ios::in);
    
    std::vector<Matrix2D<double>> points;

    if (!input.is_open())
        throw std::runtime_error("File is not open: " + path);

    std::string str;


    while (std::getline(input, str)) {
        auto count = std::count(str.begin(), str.end(), ',');
        Matrix2D<double> point (static_cast<int>(count) + 1, 1);
        std::vector<double> tempVec = split<double>(str);
        for (int i = 0; i < tempVec.size(); ++i) {
            point.at(i, 0) = tempVec.at(i);
        }
        points.push_back(point);
    }
    input.close();

    return points;
}