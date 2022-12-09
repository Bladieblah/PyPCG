# infra-python-template

## Preparing the template

Template for python-based microservices. To do:
 - Add your app to the `infra-dyme-provisioner` repo
 - Add a bucket and serviceaccount for each env in the `infra-system-polder` repo
 - Update setup.cfg

Find and replace:
 - `dyme_module` -> `your_module_name`
 - `dyme-module` -> `your-module-name`
 - `dymemodule-sa` -> gcloud service account name, matching the service account name in  `infra-system-polder`

And then start building!

## Building the module

First, create and activate a virtual environment to prevent versioning conflicts.
```bash
virtualenv dyme_module_venv
source dyme_module_venv/bin/activate
```

Now you can build and install the module.
```bash
python setup.py build
pip install .
```

Build and train the model with 
```bash
python -m dyme_module.create_model
```

## Testing

Write tests in the `tests` folder, following the `test_*.py` naming convention. Run them with
```bash
python -m unittest
```

## Development
```

Specify any dependencies that are not required in production in `requirements-dev.txt`. Install the dependencies with
```bash
pip install -r requirements-dev.txt
```

To make the virtual environment available as a kernel in Jupyter, run
```bash
ipython kernel install --name "dyme_module_venv" --user
```