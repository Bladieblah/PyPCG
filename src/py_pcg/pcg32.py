import PCGCPP

class PCG32:
    """Wrapper around the pcg32 class.
    
    >>> rng = PCG32(42)
    >>> rng.randint()
    589627368
    >>> rng.randint()
    2336806640
    """
    def __init__(self, stream = None, state = None):
        if stream and state:
            self.capsule = PCGCPP.construct(stream, state)
        elif stream:
            self.capsule = PCGCPP.construct(stream)
        else:
            self.capsule = PCGCPP.construct()
    
    def randint(self, size = 1, bound = 0):
        """Draw a random integer, with an optional upper bound.
        
        >>> rng = PCG32(42, 54)
        >>> rng.randint(2)
        [1070908346, 3346215311]
        >>> rng.randint(2, bound=100)
        [67, 65]
        """
        result = PCGCPP.randint(self.capsule, size, bound)

        if size == 1:
            return result[0]
        
        return result
    
    def rand(self, size = 1):
        """Draw a uniform random number in the interval [0,1).

        >>> rng = PCG32(42 ,54)
        >>> rng.rand(2)
        [0.24934027949348092, 0.7791014646645635]
        """
        result = PCGCPP.rand(self.capsule, size)

        if size == 1:
            return result[0]
        
        return result
    
    def randn(self, size = 1):
        """Draw a random number following a standard normal PDF.

        >>> rng = PCG32(42 ,54)
        >>> rng.rand(2)
        [0.24934027949348092, 0.7791014646645635]
        """
        result = PCGCPP.rand(self.capsule, size)

        if size == 1:
            return result[0]
        
        return result

if __name__ == "__main__":
    import doctest
    doctest.testmod()
