# cpuid
CPUID library, maybe...

# Building
From the root of the project:
`
mkdir build
cd build
cmake ../
make            # builds the python module shared object and cpuid exe
make install    # installs cpuid exe only
`

# Installing python package
Run the following from the root of the project:
`
python -m build .
cd dist/
pip install *.whl
`
