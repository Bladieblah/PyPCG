#include <iostream>
#include <vector>

#include "Python.h"
#include "py_cpp_conversion.hpp"

using namespace std;

// ------------------- Helpers for converting between Python and C++ -------------------

PyObject *vectorUint32ToListInt(const vector<uint32_t> &data) {
    PyObject *listObj = PyList_New(data.size());
	if (!listObj) throw logic_error("Unable to allocate memory for Python list 3");
	
	for (unsigned int i = 0; i < data.size(); i++) {
		PyObject *num = PyLong_FromLong( (long) data[i]);
		if (!num) {
			Py_DECREF(listObj);
			throw logic_error("Unable to allocate memory for Python list 4");
		}
		PyList_SET_ITEM(listObj, i, num);
	}
    
	return listObj;
}

PyObject *vectorVectorUint32ToListListInt(const vector< vector<uint32_t> > &data) {
    PyObject *list = PyList_New( data.size() );
	if (!list) throw logic_error("Unable to allocate memory for Python list 5");
	
	for (unsigned int i = 0; i < data.size(); i++) {
		PyObject* subList = NULL;
		try {
			subList = vectorUint32ToListInt(data[i]);
		} catch (logic_error &e) {
			throw e;
		}
		if (!subList) {
			Py_DECREF(list);
			throw logic_error("Unable to allocate memory for Python list of lists 1");
		}
		PyList_SET_ITEM(list, i, subList);
	}

    return list;
}

PyObject *vectorDoubleToListFloat(const std::vector<double> &data) {
    PyObject *listObj = PyList_New(data.size());
	if (!listObj) throw logic_error("Unable to allocate memory for Python list 3");
	
	for (unsigned int i = 0; i < data.size(); i++) {
		PyObject *num = PyFloat_FromDouble( data[i]);
		if (!num) {
			Py_DECREF(listObj);
			throw logic_error("Unable to allocate memory for Python list 4");
		}
		PyList_SET_ITEM(listObj, i, num);
	}
    
	return listObj;
}
