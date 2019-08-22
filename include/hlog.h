/**
  * License: Modified BSD Software License Agreement
  * Author: Feng DING
  * Description: log
  */

#ifndef _HLOG_H_
#define _HLOG_H_
#include <pthread.h>
#include <glog/logging.h>
#include <glog/log_severity.h>

namespace itd_lidar {
class HLog {
public:
 static HLog *Instance();
 int InitHLog(const char* log_init,
              const char* log_file_path = "./lidar_log/",
              int n_log_severity_to_print = google::GLOG_WARNING,
              int n_log_severity_to_file = google::GLOG_INFO);
 void HLogMsg(const int& n_log_severity, const char *format, ...);

private:
 HLog();
 ~HLog();
 HLog(const HLog&);
 HLog& operator=(const HLog&);
 static HLog* instance_;
 static pthread_mutex_t mutex_;
 char p_log_buf_[2048];
};
#define LOGINIT(...) itd_lidar::HLog::Instance()->InitHLog(__VA_ARGS__);
#define LOGINFO(...) itd_lidar::HLog::Instance()->HLogMsg(0, __VA_ARGS__);
#define LOGWARNING(...) itd_lidar::HLog::Instance()->HLogMsg(1, __VA_ARGS__);
#define LOGERROR(...) itd_lidar::HLog::Instance()->HLogMsg(2, __VA_ARGS__);
#define LOGFATAL(...) itd_lidar::HLog::Instance()->HLogMsg(3, __VA_ARGS__);
} // namespace itd_lidar

#endif // _HLOG_H_
