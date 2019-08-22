#include "hlog.h"

int main(int argc, char* argv[]) {
  LOGINIT(argv[0]);
  LOGINFO("First Number: %d.", 1);
  LOGWARNING("First Numbsdfsadfsdfdsfsdfasdfer: %d.", 1);
  LOGERROR("Second Number: %d.", 2);
  return 0;
}
