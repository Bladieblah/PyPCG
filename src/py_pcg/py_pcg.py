import PCGCPP

class PCG32:
    def __init__(self, stream = None, state = None):
        self.capsule = PCGCPP.construct(stream, state)
    
    def rand(self, size=1):
        return PCGCPP.rand(self.capsule, size)


if __name__ == '__main__':
    rng = PCG32(42, 54)
    print(rng.rand())