#include <random>
#include <stdio.h>
#include <vector>

#include "Python.h"
#include "pcg_random.hpp"
#include "py_cpp_conversion.hpp"

using namespace std;

// ------------------- Class wrappers -------------------

PyObject *construct32(PyObject *self, PyObject *args) {
    uint64_t *stream = NULL;
    uint64_t state = 0x853c49e6748fea9bULL; // Taken from the minimal C implementation
    PyArg_ParseTuple(args, "|kk", stream, &state);
    
    pcg32 *rng;
    if (stream) {
        rng = new pcg32(state, *stream);
    } else {
        rng = new pcg32();
        rng->seed(pcg_extras::seed_seq_from<std::random_device>());
    }
    
    PyObject *rngCapsule = PyCapsule_New((void *)rng, "rngPtr", NULL);
    PyCapsule_SetPointer(rngCapsule, (void *)rng);
    
    return Py_BuildValue("O", rngCapsule);
}

PyObject *rand32(PyObject *self, PyObject *args) {
    vector<uint32_t> result;
    uint32_t size = 1;
    
    PyObject *rngCapsule = NULL;
    PyArg_ParseTuple(args, "|I", &size);
    result.reserve(size);
    
    pcg32 rng = *(pcg32 *)PyCapsule_GetPointer(rngCapsule, "rngPtr");

    for (uint32_t i = 0; i < size; i++) {
        result[i] = rng();
    }
    
    return vectorUint32ToListInt(result);
}

PyMethodDef PyPcgFunctions[] = {
    {"construct",
      construct32, METH_VARARGS,
     "Create `PyPCG` object."},
    
    {"rand",
      rand32, METH_VARARGS,
     "Obtain 1 or more random integers."},

    {NULL, NULL, 0, NULL}      // Last function description must be empty.
                               // Otherwise, it will create seg fault while
                               // importing the module.
};


struct PyModuleDef PyPcgModule = {
/*
 *  Structure which defines the module.
 *
 *  For more info look at: https://docs.python.org/3/c-api/module.html
 *
 */
   PyModuleDef_HEAD_INIT,
   "PyPCG",
   "Python wrapper around the pcg-cpp library.", 
   // Docstring for the module.
   -1,                   // Used by sub-interpreters, if you do not know what
                         // it is then you do not need it, keep -1 .
   PyPcgFunctions
};


PyMODINIT_FUNC PyInit_PyPcg(void) {
    return PyModule_Create(&PyPcgModule);
}