#include <DBSCAN.h>

#include <cmath>
#include <iostream>

namespace dbscan {

_3DPoint::_3DPoint(double x, double y, double z):
    m_x(x),
    m_y(y),
    m_z(z),
    m_clusterID(0),
    m_label(Label::UNCLASSIFIED)
{}

std::ostream &operator<<(std::ostream &output, const dbscan::_3DPoint& P) {
    output << "(" << P.m_x << ", " << P.m_y << ", " << P.m_x << " | " << P.m_clusterID << ")";
    return output;
}

DBSCAN::DBSCAN(double eps, int minPts, std::vector<_3DPoint*>* data):
    m_eps(eps),
    m_minPts(minPts),
    m_data_p(data),
    m_clusterID(1)
{}

void DBSCAN::run() {
    std::vector<_3DPoint*>::iterator iter;
    for (iter = m_data_p->begin(); iter != m_data_p->end(); ++iter) {
        if ((*iter)->m_label == Label::UNCLASSIFIED) {
            if (expandCluster(*iter)) {
                m_clusterID++;
            }
        }
    }
}

bool DBSCAN::expandCluster(_3DPoint* point) {
    std::vector<_3DPoint*>* neighb = getEpsNeighb(point);

    if (neighb->size() < m_minPts) {
        point->m_label = Label::NOISE;
        return false;
    } else {
        std::vector<_3DPoint*>::iterator iter;
        for (iter = neighb->begin(); iter != neighb->end(); ++iter) {
            (*iter)->m_label = Label::CORE;
            (*iter)->m_clusterID = m_clusterID;
        }

        while (!neighb->empty()) {
            _3DPoint* currentP = neighb->back();
            std::vector<_3DPoint*>* innerNeighb = getEpsNeighb(currentP);

            if (innerNeighb->size() >= m_minPts) {
                for (iter = innerNeighb->begin(); iter != innerNeighb->end(); ++iter) {
                    if ((*iter)->m_label == Label::UNCLASSIFIED || (*iter)->m_label == Label::NOISE) {
                        if ((*iter)->m_label == Label::UNCLASSIFIED) {
                            neighb->push_back((*iter));
                        }

                        (*iter)->m_label = Label::CORE;
                        (*iter)->m_clusterID = m_clusterID;
                    }
                }
            }

            neighb->pop_back();
        }
    }

    return true;
}

std::vector<_3DPoint*>* DBSCAN::getEpsNeighb(_3DPoint* point) {
    std::vector<_3DPoint*>* neighb = new std::vector<_3DPoint*>();
    std::vector<_3DPoint*>::iterator iter;
    for (iter = m_data_p->begin(); iter != m_data_p->end(); ++iter) {
        if (euclideanDist((*iter), point) <= m_eps) {
            neighb->push_back((*iter));
        }
    }

    return neighb;
}

double DBSCAN::euclideanDist(_3DPoint* pa, _3DPoint* pb) {
    return sqrt(
        pow((pa->m_x - pb->m_x), 2) +
        pow((pa->m_y - pb->m_y), 2) +
        pow((pa->m_z - pb->m_z), 2)
    );
}

} // dbscan namespace
