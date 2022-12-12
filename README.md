# PyPCG

This is a python wrapper around the pcg-cpp library, for randum number generation using the _permuted congruential generator_ method.

Usage:

```python
import py_pcg

rng = py_pcg.pcg32()
rng = py_pcg.pcg32(42, 9001) # Seed with initial stream and state

rng.rand()     # Generate a single random number
rng.rand(1000) # Generate a list of random numbers
```