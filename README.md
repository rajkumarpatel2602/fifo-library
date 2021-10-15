# fifo-library
- This repo contains source and header of fifo library

# Test suite
- `make test` will compile the test file.
- Run test file to get the result.

# Code coverage
Testing done on centos 7.9
- yum install lcov # install lcov if not already installed
- vim foo.c # creat example file
- gcc -fprofile-arcs -ftest-coverage foo.c # create test or app executable
- ./a.out # run executable
- lcov -c -d . -o coverage.info # create coverage info for the executable
- genhtml coverage.info -o coverage # print coverage info

