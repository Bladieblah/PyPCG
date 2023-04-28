#include <random>
#include <stdio.h>

#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

#include "normal_cdf.hpp"
#include "pcg_random.hpp"

using namespace std;

#define PCG32_MAX1 (double)4294967296.0

// ------------------- Class wrappers -------------------

PyObject *construct32(PyObject *self, PyObject *args) {
    uint64_t stream = 0xda3e39cb94b95bdbULL; // Taken from the minimal C implementation
    uint64_t state = 0x853c49e6748fea9bULL;

    PyArg_ParseTuple(args, "|kk", &stream, &state);
    
    pcg32 *rng;

    if (stream == 0xda3e39cb94b95bdbULL) {
        rng = new pcg32();
        rng->seed(pcg_extras::seed_seq_from<std::random_device>());
    } else {
        rng = new pcg32(state, stream);
    }
    
    PyObject *rngCapsule = PyCapsule_New((void *)rng, "rngPtr", NULL);
    PyCapsule_SetPointer(rngCapsule, (void *)rng);
    
    return Py_BuildValue("O", rngCapsule);
}

PyObject *randint32(PyObject *self, PyObject *args) {
    uint32_t *result;
    uint32_t size = 1;
    uint32_t bound = 0;
    
    PyObject *rngCapsule = NULL;
    PyArg_ParseTuple(args, "O|II", &rngCapsule, &size, &bound);
    
    pcg32 *rng = (pcg32 *)PyCapsule_GetPointer(rngCapsule, "rngPtr");
    result = (uint32_t *)malloc(size * sizeof(uint32_t));

    if (bound > 0) {
        for (uint32_t i = 0; i < size; i++) {
            result[i] = rng->operator()(bound);
        }
    } else {
        for (uint32_t i = 0; i < size; i++) {
            result[i] = rng->operator()();
        }
    }
    
    npy_intp dims[1] = {size};
    return PyArray_SimpleNewFromData(1, dims, NPY_UINT32, result);
}

PyObject *rand32(PyObject *self, PyObject *args) {
    double *result;
    uint32_t size = 1;
    
    PyObject *rngCapsule = NULL;
    PyArg_ParseTuple(args, "O|I", &rngCapsule, &size);
    
    pcg32 *rng = (pcg32 *)PyCapsule_GetPointer(rngCapsule, "rngPtr");
    result = (double *)malloc(size * sizeof(double));

    for (uint32_t i = 0; i < size; i++) {
        result[i] = rng->operator()() / PCG32_MAX1;
    }
    
    npy_intp dims[1] = {size};
    return PyArray_SimpleNewFromData(1, dims, NPY_DOUBLE, result);
}

PyObject *randn32(PyObject *self, PyObject *args) {
    double *result;
    uint32_t size = 1;
    
    PyObject *rngCapsule = NULL;
    PyArg_ParseTuple(args, "O|I", &rngCapsule, &size);
    
    pcg32 *rng = (pcg32 *)PyCapsule_GetPointer(rngCapsule, "rngPtr");
    result = (double *)malloc(size * sizeof(double));

    for (uint32_t i = 0; i < size; i++) {
        result[i] = inverse_normal_cdf(rng->operator()() / PCG32_MAX1);
    }
    
    npy_intp dims[1] = {size};
    return PyArray_SimpleNewFromData(1, dims, NPY_DOUBLE, result);
}

// --------------------- Module definitions ---------------------

PyMethodDef PCGCPPFunctions[] = {
    {"construct",
      construct32, METH_VARARGS,
     "Create `PCGCPP` object."},
    
    {"randint",
      randint32, METH_VARARGS,
     "Obtain 1 or more random integers, with an optional bound."},
    
    {"rand",
      rand32, METH_VARARGS,
     "Obtain 1 or more random doubles in the range [0,1)."},
    
    {"randn",
      randn32, METH_VARARGS,
     "Obtain 1 or more random doubles following a standard normal PDF."},

    {NULL, NULL, 0, NULL}
};

struct PyModuleDef PCGCPPModule = {
   PyModuleDef_HEAD_INIT,
   "PCGCPP",
   "Python wrapper around the pcg-cpp library.", 
   -1,
   PCGCPPFunctions
};


PyMODINIT_FUNC PyInit_PCGCPP(void) {
    import_array();
    return PyModule_Create(&PCGCPPModule);
}