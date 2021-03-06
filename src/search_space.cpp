#include <random>
#include "search_space.hpp"


Eigen::MatrixXd PolygonSpace::sample_free_space(int n) const
{
    Eigen::MatrixXd samples(n, 2);

    for (int i=0; i<n; i++) {
        Eigen::Vector2d sample;
        int count = 0;
        do {
            sample = {_sample_x(), _sample_y()};
            count++;
        } while(inside_any_polygon(sample, _polygons) && count < 1000000);

        samples.row(i) = sample;
    }

    return samples;
}

bool PolygonSpace::valid_transition(const Eigen::VectorXd& a, const Eigen::VectorXd& b) const
{
    std::pair<Eigen::VectorXd, Eigen::VectorXd> segment = {a, b};
    for (auto polygon : _polygons) {
        if (segment_intersects_polygon(segment, polygon) > 0)
            return false;
    }
    return true;
}

double PolygonSpace::transition_cost(const Eigen::VectorXd& a, const Eigen::VectorXd& b) const
{
    Eigen::VectorXd ab = b - a;
    return ab.dot(ab);
}