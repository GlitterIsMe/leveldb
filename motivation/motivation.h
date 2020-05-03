//
// Created by 張藝文 on 2020/5/3.
//

#ifndef LEVELDB_MOTIVATION_H
#define LEVELDB_MOTIVATION_H
#include <vector>
#include <iostream>
#include <chrono>

namespace motivation{
    class Metrics {
    public:
        Metrics();

        ~Metrics() {PersistMetrics();};

        void AddWriteLatency(uint64_t lat) {write_latency_ += lat;};
        void AddWALLatency(uint64_t lat) {wal_latency_ += lat;};
        void AddMemtableLatency(uint64_t lat) {memtable_insertion_latency_ += lat;};

        void AddReadLatency(uint64_t lat) {read_latency_ += lat;};
        void AddLocatingLatency(uint64_t lat) {locating_latency_ += lat;};
        void AddDiskReadLatency(uint64_t lat) {disk_read_latency_ += lat;};

        void AddFlushTime(uint64_t lat) {flush_time_.push_back(lat);};
        void AddCompactionTime(uint64_t lat) {compaction_time_.push_back(lat);};
        void AddCompactionReadBytes(uint64_t bytes) {compaction_read_bytes_.push_back(bytes);};
        void AddCompactionWriteBytes(uint64_t bytes) {compaction_write_bytes_.push_back(bytes);};

        void AddDiskReadBytes(uint64_t bytes) {total_disk_read_bytes_ += bytes;};
        void AddDiskWriteBytes(uint64_t bytes) {total_disk_write_bytes_ += bytes;};
        void AddPMWriteBytes(uint64_t bytes) {pm_write_bytes_.push_back(bytes);};

        uint64_t write_latency() {return write_latency_;};
        uint64_t wal_latency() {return wal_latency_;};
        uint64_t memtable_insertion_latency() {return memtable_insertion_latency_;};

        uint64_t read_latency() {return read_latency_;};
        uint64_t locating_latency() {return locating_latency_;};
        uint64_t disk_read_latency() {return disk_read_latency_;};

        uint64_t flush__time(size_t idx) {
            return idx >= flush_time_.size() ? 0 : flush_time_[idx];
        };
        uint64_t compaction_time(size_t idx) {
            return idx >= compaction_time_.size() ? 0 : compaction_time_[idx];
        };
        uint64_t compaction_read_bytes(size_t idx) {
            return idx >= compaction_read_bytes_.size() ? 0 : compaction_read_bytes_[idx];
        };
        uint64_t compaction_write_bytes(size_t idx) {
            return idx >= compaction_write_bytes_.size() ? 0 : compaction_write_bytes_[idx];
        };

        uint64_t total_disk_read_bytes() {return total_disk_read_bytes_;}
        uint64_t total_disk_write_bytes() {return total_disk_write_bytes_;};
        uint64_t total_pm_write_bytes(size_t idx) {
            return idx >= pm_write_bytes_.size() ? 0 : pm_write_bytes_[idx];
        };

        std::chrono::time_point<std::chrono::high_resolution_clock> now(){
            return std::chrono::high_resolution_clock::now();
        };

        void PersistMetrics();

    private:
        // write metrics
        uint64_t write_latency_;
        uint64_t wal_latency_;
        uint64_t memtable_insertion_latency_;

        // read metrics
        uint64_t read_latency_;
        uint64_t locating_latency_;
        uint64_t disk_read_latency_;

        // compaction and flush metrics
        std::vector<uint64_t > flush_time_;
        std::vector<uint64_t > compaction_time_;
        std::vector<uint64_t > compaction_read_bytes_;
        std::vector<uint64_t > compaction_write_bytes_;

        // total statistics
        uint64_t total_disk_read_bytes_;
        uint64_t total_disk_write_bytes_;
        std::vector<uint64_t > pm_write_bytes_;
    };

    Metrics& metrics();
}
#endif //LEVELDB_MOTIVATION_H
