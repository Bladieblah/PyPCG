import PCGCPP

class PCG32:
    """Wrapper around the pcg32 class.
    
    >>> rng = PCG32(42)
    >>> rng.randint()
    589627368
    >>> rng.randint()
    2336806640
    
    >>> rng = PCG32(42, 54)
    >>> rng.randint(2)
    [1070908346, 3346215311]
    >>> rng.randint(2, bound=100)
    [67, 65]
    """
    def __init__(self, stream = None, state = None):
        if stream and state:
            self.capsule = PCGCPP.construct(stream, state)
        elif stream:
            self.capsule = PCGCPP.construct(stream)
        else:
            self.capsule = PCGCPP.construct()
    
    def randint(self, size=1, bound = 0):
        result = PCGCPP.randint(self.capsule, size, bound)

        if size == 1:
            return result[0]
        
        return result

if __name__ == "__main__":
    import doctest
    doctest.testmod()
