import numpy as np
from sklearn.pipeline import Pipeline
import sklearn.metrics as skm
import joblib

from . import transformers

def make_pipeline(x_train, y_train):
    pipeline = Pipeline([
        ('transform', transformers.ExampleTransformer()),
        ('predict', transformers.ExamplePredictor())
    ])

    pipeline.fit(x_train, y_train)

    return pipeline

def test_pipeline(pipeline, x_test, y_test):
    y_pred = pipeline.predict(x_test)
    print(skm.mean_absolute_error(y_test, y_pred))

if __name__ == '__main__':
    x_train = np.array([[1, 2], [3, 4]])
    y_train = np.array([1.5, 3.5])

    x_test = np.array([[4, 5], [6, 7]])
    y_test = np.array([4.5, 6.5])

    pipeline = make_pipeline(x_train, y_train)
    test_pipeline(pipeline, x_test, y_test)

    joblib.dump(pipeline, 'model.joblib')