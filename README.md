# Python-PCG

This is a python wrapper around the pcg-cpp library, for randum number generation using the _permuted congruential generator_ method. For more information, see [the official website](https://www.pcg-random.org/).

## Installation
```bash
pip install Python-PCG
```

## Usage:

```python
import py_pcg

rng = py_pcg.PCG32()
rng = py_pcg.PCG32(42, 9001) # Seed with initial stream and state.

rng.rand()     # Generate a single random uniform number.
rng.randn(100)     # Generate a list of random numbers following a standard normal PDF.
rng.randint(1000, bound=100) # Generate a list of bounded random integers.
```