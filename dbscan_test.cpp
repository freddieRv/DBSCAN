#include <DBSCAN.h>

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat* loadMatrixFromCSVFile(std::string);
std::vector<std::string> splitLine(std::string, char);

int main(int argc, char const *argv[]) {
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " FILE.csv eps minPts" << std::endl;
        return 1;
    }

    int minPts = std::atoi(argv[3]);
    double eps = std::atof(argv[2]);
    std::vector<dbscan::_3DPoint*> points;

    std::cout << "minPts: " << minPts << std::endl;
    std::cout << "eps: " << eps << std::endl;

    cv::Mat* raw_points = UTILS::loadMatrixFromCSVFile(argv[1]);

    for (size_t i = 0; i < raw_points->cols; i++) {
        points.push_back(
            new dbscan::_3DPoint(
                raw_points->at<double>(0, i),
                raw_points->at<double>(1, i),
                raw_points->at<double>(2, i)
            )
        );
    }

    dbscan::DBSCAN db(eps, minPts, &points);
    db.run();

    std::cout << "Done!" << std::endl;

    std::map<int, std::vector<int>> color_map = std::map<int, std::vector<int>>();
    std::ofstream outf = std::ofstream();

    srand(time(NULL));
    outf.open("test_color_mappign.csv");

    for (size_t i = 0; i < points.size(); i++) {
        // std::cout << *points[i] << std::endl;

        if (points[i]->m_label == dbscan::Label::CORE) {

            std::map<int, std::vector<int>>::iterator label_color = color_map.find(points[i]->m_clusterID);
            if (label_color == color_map.end()) {
                std::vector<int> color(3);
                color[0] = rand() % 255;
                color[1] = rand() % 255;
                color[2] = rand() % 255;
                color_map[points[i]->m_clusterID] = color;
            }

            outf << color_map[points[i]->m_clusterID][0] << ","
                 << color_map[points[i]->m_clusterID][1] << ","
                 << color_map[points[i]->m_clusterID][2] << "\n";

        } else {
            outf << 0 << ","
                 << 0 << ","
                 << 0 << "\n";
        }
    }

    outf.close();

    return 0;
}

cv::Mat* loadMatrixFromCSVFile(std::string file_path) {
    cv::Mat* mat = nullptr;

    if (file_path != "") {
        std::ifstream inf;
        std::string line;
        std::vector<std::string> splited;

        inf.open(file_path);

        if (inf.is_open()) {

            int count = std::count(
                            std::istreambuf_iterator<char>(inf),
                            std::istreambuf_iterator<char>(),
                            '\n'
                        );

            inf.clear();
            inf.seekg(0, std::ios::beg);

            mat = new cv::Mat(3, count, CV_64FC1);

            int line_count = 0;
            while (getline(inf, line)) {
                splited = splitLine(line, ',');

                if (splited.size() == 3) {
                    mat->at<double>(0, line_count) = std::stod(splited[0]);
                    mat->at<double>(1, line_count) = std::stod(splited[1]);
                    mat->at<double>(2, line_count) = std::stod(splited[2]);
                }

                line_count++;
            }

            inf.close();
        }
    }

    return mat;
}

std::vector<std::string> splitLine(std::string line, char delim) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> v = std::vector<std::string>();

    while (getline(ss, token, delim)) {
        v.push_back(token);
    }

    return v;
}
