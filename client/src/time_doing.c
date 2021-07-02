#include "client.h"

const char *time_doing(void) {  
  time_t rawtime;  
  struct tm * timeinfo;
  const char *time_doing = NULL;

  time ( &rawtime );  
  timeinfo = localtime ( &rawtime );  
  time_doing = strdup(asctime (timeinfo));  
  return time_doing;  
} 
