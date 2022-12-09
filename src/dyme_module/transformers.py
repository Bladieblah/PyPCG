import numpy as np

class ExampleTransformer:
    def fit(self, x_train, y_train):
        return self
    
    def transform(self, x_in):
        return np.average(x_in, axis=1);

class ExamplePredictor:
    def fit(self, x_train, y_train):
        return self
    
    def predict(self, x_in):
        return x_in