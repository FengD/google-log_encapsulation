/**
  * License: Modified BSD Software License Agreement
  * Author: Feng DING
  * Description: log
  */

#include "hlog.h"
#include <stdio.h>
#include <iostream>
#include <stdarg.h>
#include <stdint.h>
#include <assert.h>
#include <string>

namespace itd_lidar {
  pthread_mutex_t HLog::mutex_;
  HLog* HLog::Instance() {
    pthread_mutex_lock(&mutex_);
    static HLog obj;
    pthread_mutex_unlock(&mutex_);
    return &obj;
  }

  HLog::HLog() {
    pthread_mutex_init(&mutex_, NULL);
    memset(p_log_buf_, 0, 2048);
  }
  HLog::~HLog() {}
  HLog::HLog(const HLog&) {}
  HLog& HLog::operator=(const HLog&) {}

  int HLog::InitHLog(const char* log_init,
                     const char* log_file_path,
                     int n_log_severity_to_print,
                     int n_log_severity_to_file) {
    CHECK_NOTNULL(log_init);

    google::InitGoogleLogging(log_init);

    if (0 != access(log_file_path, 0)) {
      std::string command = log_file_path;
      command = "mkdir -p " + command;
      system(command.c_str());
    }

    google::SetLogDestination(n_log_severity_to_file, log_file_path);
    google::SetStderrLogging(n_log_severity_to_print);
  }

  void HLog::HLogMsg(const int& n_log_severity, const char *format, ...) {
    va_list arg_ptr;
    va_start(arg_ptr, format);
    vsprintf(p_log_buf_, format, arg_ptr);
    switch(n_log_severity) {
      case 0:
        LOG(INFO) << p_log_buf_;
        break;
      case 1:
        LOG(WARNING) << p_log_buf_;
        break;
      case 2:
        LOG(ERROR) << p_log_buf_;
        break;
      case 3:
        LOG(FATAL) << p_log_buf_;
        break;
      default:
        assert(false);
    }
    va_end(arg_ptr);
    memset(p_log_buf_, 0, 2048);
  }
}
