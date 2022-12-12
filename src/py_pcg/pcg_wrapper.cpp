#include <random>
#include <stdio.h>
#include <vector>

#include "Python.h"
#include "pcg_random.hpp"
#include "py_cpp_conversion.hpp"

using namespace std;

// ------------------- Class wrappers -------------------

PyObject *construct32(PyObject *self, PyObject *args) {
    uint64_t stream = 0xda3e39cb94b95bdbULL; // Taken from the minimal C implementation
    uint64_t state = 0x853c49e6748fea9bULL;

    fprintf(stderr, "ParseTuple\n");

    PyArg_ParseTuple(args, "|kk", &stream, &state);

    fprintf(stderr, "Seeding rng\n");
    
    pcg32 *rng = new pcg32();
    rng->seed(pcg_extras::seed_seq_from<std::random_device>());

    fprintf(stderr, "Capsule\n");
    
    PyObject *rngCapsule = PyCapsule_New((void *)rng, "rngPtr", NULL);
    PyCapsule_SetPointer(rngCapsule, (void *)rng);

    fprintf(stderr, "Returning\n");
    
    return Py_BuildValue("O", rngCapsule);
}

PyObject *rand32(PyObject *self, PyObject *args) {
    vector<uint32_t> result;
    uint32_t size = 1;
    
    PyObject *rngCapsule = NULL;
    PyArg_ParseTuple(args, "O|I", &rngCapsule, &size);
    
    pcg32 rng = *(pcg32 *)PyCapsule_GetPointer(rngCapsule, "rngPtr");
    result.reserve(size);


    fprintf(stderr, "Pulling %d random numbers\n", size);

    for (uint32_t i = 0; i < size; i++) {
        result[i] = rng();
    }
    
    return vectorUint32ToListInt(result);
}

PyMethodDef PCGCPPFunctions[] = {
    {"construct",
      construct32, METH_VARARGS,
     "Create `PCGCPP` object."},
    
    {"rand",
      rand32, METH_VARARGS,
     "Obtain 1 or more random integers."},

    {NULL, NULL, 0, NULL}      // Last function description must be empty.
                               // Otherwise, it will create seg fault while
                               // importing the module.
};


struct PyModuleDef PCGCPPModule = {
/*
 *  Structure which defines the module.
 *
 *  For more info look at: https://docs.python.org/3/c-api/module.html
 *
 */
   PyModuleDef_HEAD_INIT,
   "PCGCPP",
   "Python wrapper around the pcg-cpp library.", 
   // Docstring for the module.
   -1,                   // Used by sub-interpreters, if you do not know what
                         // it is then you do not need it, keep -1 .
   PCGCPPFunctions
};


PyMODINIT_FUNC PyInit_PCGCPP(void) {
    return PyModule_Create(&PCGCPPModule);
}