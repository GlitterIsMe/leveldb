#! /bin/bash

./build/db_bench  --db=./test \
                  --benchmarks=fillrandom,readrandom,readseq \
                  --value_size=1024 \
                  --num=8000000 \
                  --reads=1600000 \
                  --bloom_bits=10 \
                  --write_buffer_size=`expr 64 \* 1024 \* 1024` \
                  --max_file_size=`expr 64 \* 1024 \* 1024`