make -j `nproc`
g++ rocksdb-test.cpp -Iinclude -Iinclude/rocksdb --std=c++17 -L`pwd` -lrocksdb
