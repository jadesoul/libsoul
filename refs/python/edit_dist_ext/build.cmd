rm -r build
rm *.pyd
python setup.py build_ext --inplace
python test.py