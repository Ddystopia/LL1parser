#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const int length = 5;
struct pair {
  char *name;
  int secs;
};
void initialize();
int toStr(char* buffer, int in);

struct pair time[length];

char *formatDuration (int n) {
  initialize();
  char *res = (char*)malloc(100);
  if (n == 0) {
    strcat(res, "now");
    return res;
  }
  int secs = n;
  for (int i = 0; i < length; ++i) {
    if (secs >= time[i].secs) {
      int val = secs / time[i].secs;
      char sval[10];
      memset((void*)sval, 0, 10);
      sprintf(sval, "%d", val);
      strcat(res, sval);
      strcat(res, " ");
      strcat(res, time[i].name);
      if (val > 1) strcat(res, "s");
      secs %= time[i].secs;
    }
  }
  return res;
}


const size_t BYTES_PER_INT = sizeof(int); 

int toStr(char* buffer, int in) {
	for (size_t i = 0; i < BYTES_PER_INT; i++) {
		size_t shift = 8 * (BYTES_PER_INT - 1 - i);
		buffer[i] = (in >> shift) & 0xff;
	}
	return 0;
}


void initialize() {
  time[0].name = "year";
  time[0].secs = 31557600; 
  time[1].name = "day";
  time[1].secs = 24*60*60; 
  time[2].name = "hour";
  time[2].secs = 60*60; 
  time[3].name = "minute";
  time[3].secs = 60; 
  time[4].name = "second";
  time[4].secs = 1; 
}
