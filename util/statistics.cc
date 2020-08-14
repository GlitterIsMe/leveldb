//
// Created by 張藝文 on 2020/8/14.
//
#include "statistics.h"

#include <fstream>

namespace leveldb{
  Statistics::Statistics() {
    compaction_lat_ = 0;
    IO_lat_ = 0;
    total_lat_ = 0;
  }

  Statistics::~Statistics() {
    Persist();
  }

  void Statistics::RecordLatency(LatType type, uint64_t lat) {
    switch (type) {
      case IOLat:
        IO_lat_ += lat;
        break;
      case CompactionLat:
        compaction_lat_ += lat;
        break;
      case TotalLat:
        total_lat_ += lat;
        break;
      default:
        break;
    }
  }

  void Statistics::Persist() const {
    std::ofstream output;
    output.open("compaction.log", std::ios::out | std::ios::trunc);
    output << compaction_lat_ << ", " << IO_lat_ << ", " << total_lat_ << "\n";
    output.close();
  }

  timepoint Statistics::StartTiming() {
    return std::chrono::high_resolution_clock::now();
  }

  uint64_t Statistics::EndTiming(timepoint start_t) {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - start_t).count();
  }

  Statistics& global_statistics() {
    static Statistics s;
    return s;
  }
}