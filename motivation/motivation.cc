//
// Created by 張藝文 on 2020/5/3.
//

#include "motivation.h"
#include <fstream>
#include <cassert>
#include <elf.h>

namespace motivation {
    Metrics::Metrics() :
            write_latency_(0),
            wal_latency_(0),
            memtable_insertion_latency_(0),
            read_latency_(0),
            locating_latency_(0),
            disk_read_latency_(0),
            total_disk_read_bytes_(0),
            total_disk_write_bytes_(0){
        flush_time_.clear();
        compaction_time_.clear();
        compaction_read_bytes_.clear();
        compaction_write_bytes_.clear();
        pm_write_bytes_.clear();
    }

    void Metrics::PersistMetrics() {
        std::fstream output;
        std::fstream flush;
        std::fstream compaction;
        std::fstream pm_write;

        output.open("statistics.csv", std::ios::trunc | std::ios::out);
        output  << "write_latency, " << write_latency_ << "\n"
                << "wal_latency, " << wal_latency_ << "\n"
                << "memtable_latency, " << memtable_insertion_latency_ << "\n"
                << "read_latency, " << read_latency_ << "\n"
                << "locating_latency, " << locating_latency_ << "\n"
                << "disk_read_latency, " << disk_read_latency_ << "\n"
                << "total_disk_read, " << total_disk_read_bytes_ << "\n"
                << "total_disk_write, " << total_disk_write_bytes_ << "\n";
        output.close();

        uint64_t total_flush = 0;
        flush.open("flush_metrics.csv", std::ios::trunc | std::ios::out);
        assert(flush_time_.size() == flush_time_.size());
        flush << "creation_time, insertion_time\n";
        for (size_t i = 0; i < flush_time_.size(); i++) {
            total_flush += flush_time_[i];
            flush   << flush_time_[i] << " ,\n";
        }
        flush << "total_flush, " << total_flush << ",\n";
        flush.close();

        uint64_t total_compaction_time = 0, total_write_bytes = 0, total_read_bytes = 0;
        compaction.open("compaction_metrics.csv", std::ios::trunc | std::ios::out);
        assert(compaction_time_.size() == compaction_read_bytes_.size());
        assert(compaction_time_.size() == compaction_write_bytes_.size());
        compaction << "compaction_time, read_bytes, write_bytes\n";
        for (size_t i = 0; i < compaction_time_.size(); i++) {
            total_compaction_time += compaction_time_[i];
            total_read_bytes += compaction_read_bytes_[i];
            total_write_bytes += compaction_write_bytes_[i];
            compaction  << compaction_time_[i] << ", "
                        << compaction_read_bytes_[i] << ", "
                        << compaction_write_bytes_[i] << ", \n";
        }
        compaction << "compaction, " << total_compaction_time << ", "
                   << "compaction read, " << total_read_bytes << ", "
                   << "compaction write, " << total_write_bytes << ", \n";
        compaction.close();

        uint64_t total_pm_write = 0;
        pm_write.open("pm_write.csv", std::ios::trunc | std::ios::out);
        pm_write << "pm_write\n";
        for (size_t i = 0; i < pm_write_bytes_.size(); i++) {
            total_pm_write += pm_write_bytes_[i];
            pm_write   << pm_write_bytes_[i] << " ,\n";
        }
        pm_write << "total_pm_write, " << total_pm_write << ",\n";
        pm_write.close();
    }

    Metrics& metrics(){
        static Metrics m;
        return m;
    }
}