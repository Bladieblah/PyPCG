import numpy as np
import unittest

from src.dyme_module.transformers import ExampleTransformer

class TestExample(unittest.TestCase):
    def test_example(self):
        transformer = ExampleTransformer()

        self.assertEqual([1], transformer.transform(np.array([[0, 2]])))

if __name__ == '__main__':
    unittest.main()