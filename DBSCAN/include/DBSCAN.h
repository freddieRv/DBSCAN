#ifndef H_DBSCAN_H
#define H_DBSCAN_H

#include <vector>
#include <ostream>

namespace dbscan {

enum class Label {
    UNCLASSIFIED,
    NOISE,
    CORE
};

class _3DPoint {
public:
    _3DPoint(double, double, double);
    friend std::ostream &operator<<(std::ostream &, const dbscan::_3DPoint&);

    double m_x, m_y, m_z;
    Label m_label;
    int m_clusterID;
};

class DBSCAN {
public:
    DBSCAN(double, int, std::vector<_3DPoint*>*);
    void run();

private:
    bool expandCluster(_3DPoint*);
    std::vector<_3DPoint*>* getEpsNeighb(_3DPoint*);
    double euclideanDist(_3DPoint*, _3DPoint*);

    double m_eps;
    int m_minPts;
    int m_clusterID;
    std::vector<_3DPoint*>* m_data_p;
};

} // dbscan namespace

#endif
