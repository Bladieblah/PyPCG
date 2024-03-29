from typing import Any, Optional, overload
import numpy.typing as npt


class RngCapsule: ...

@overload
def construct(stream: int, state: int) -> RngCapsule: ...
@overload
def construct(stream: int) -> RngCapsule: ...
@overload
def construct() -> RngCapsule: ...

def randint(capsule: RngCapsule, size: Optional[int] = 1, bound: Optional[int] = 0) -> npt.NDArray[Any]: ...
def rand(capsule: RngCapsule, size: Optional[int]) -> npt.NDArray[Any]: ...
def randn(capsule: RngCapsule, size: Optional[int]) -> npt.NDArray[Any]: ...
