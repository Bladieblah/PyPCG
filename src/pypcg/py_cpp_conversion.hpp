#ifndef PY_CPP_CONVERSION_H
#define PY_CPP_CONVERSION_H

#include <string>
#include <vector>

#include "Python.h"

// ------------------- Helpers for converting between Python and C++ -------------------

PyObject *vectorUint32ToListInt(const std::vector<uint32_t> &data);

PyObject *vectorVectorUint32ToListListInt(const std::vector< std::vector<uint32_t> > &data);

#endif