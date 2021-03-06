#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/operators.h>
#include "geometry.hpp"


namespace py = pybind11;

void init_geometry(py::module_ &m)
{
    py::class_<Polygon>(m, "Polygon")
        .def(py::init<Eigen::Ref<const Eigen::MatrixX2d>>())
        .def_property_readonly("points", &Polygon::points)
        .def_property_readonly("n_points", &Polygon::n_points)
        .def_property_readonly("orientation", &Polygon::orientation)
        .def_property_readonly("is_solid", &Polygon::is_solid)
        .def_property_readonly("is_hollow", &Polygon::is_hollow)
        .def("__getitem__", [](const Polygon& polygon, int i) {return polygon[i];});

    m.def("inside_polygon", &inside_polygon);
    m.def("segments_intersect", &segments_intersect);
    m.def("segment_intersects_polygon", &segment_intersects_polygon);
}