import PCGCPP

class PCG32:
    def __init__(self, stream = None, state = None):
        if stream and state:
            self.capsule = PCGCPP.construct(stream, state)
        elif stream:
            self.capsule = PCGCPP.construct(stream)
        else:
            self.capsule = PCGCPP.construct()
    
    def rand(self, size=1):
        result = PCGCPP.rand(self.capsule, size)

        if size == 1:
            return result[0]
        
        return result


if __name__ == '__main__':
    rng = PCG32()
    print(rng.rand())
    rng = PCG32()
    print(rng.rand())
    rng = PCG32(42)
    print(rng.rand())
    rng = PCG32(42, 54)
    print(rng.rand())
    rng = PCG32(42, 54)
    print(rng.rand(2))
    print(rng.rand(2))