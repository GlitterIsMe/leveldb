//
// Created by 張藝文 on 2020/8/14.
//

#ifndef LEVELDB_STATISTICS_H
#define LEVELDB_STATISTICS_H
#include <iostream>
#include <chrono>
namespace leveldb {
using timepoint = std::chrono::high_resolution_clock::time_point;
enum LatType {
  IOLat,
  CompactionLat,
  TotalLat,
};

class Statistics {
 public:
  Statistics();
  ~Statistics();

  void RecordLatency(LatType type, uint64_t lat);

  void Persist() const;

  static timepoint StartTiming();
  static uint64_t EndTiming(timepoint start_t);

 private:
  uint64_t compaction_lat_;
  uint64_t IO_lat_;
  uint64_t total_lat_;

};

  Statistics& global_statistics();
}


#endif  // LEVELDB_STATISTICS_H
