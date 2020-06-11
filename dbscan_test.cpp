#include <DBSCAN.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

std::vector<dbscan::_3DPoint*>* loadMatrixFromCSVFile(std::string);
std::vector<std::string> splitLine(std::string, char);

int main(int argc, char const *argv[]) {
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " INPUT.csv eps minPts" << std::endl;
        return 1;
    }

    int minPts = std::atoi(argv[3]);
    double eps = std::atof(argv[2]);
    std::vector<dbscan::_3DPoint*>* points = loadMatrixFromCSVFile(argv[1]);

    std::cout << "minPts: " << minPts << std::endl;
    std::cout << "eps: " << eps << std::endl;

    dbscan::DBSCAN db(eps, minPts, points);
    db.run();

    std::cout << "Done!" << std::endl;

    return 0;
}

std::vector<dbscan::_3DPoint*>* loadMatrixFromCSVFile(std::string file_path) {
    std::vector<dbscan::_3DPoint*>* mat = nullptr;

    if (file_path != "") {
        std::ifstream inf;
        std::string line;
        std::vector<std::string> splited;

        inf.open(file_path);

        if (inf.is_open()) {
            mat = new std::vector<dbscan::_3DPoint*>();
            while (getline(inf, line)) {
                splited = splitLine(line, ',');
                if (splited.size() == 3) {
                    mat->push_back(
                        new dbscan::_3DPoint(
                            std::stod(splited[0]),
                            std::stod(splited[1]),
                            std::stod(splited[2])
                        )
                    );
                }
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
