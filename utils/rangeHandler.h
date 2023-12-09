#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  long start;
  long end;
  long long offset;
} Bounds;

Bounds getDefaultBoundsObject();
Bounds getNullBoundsObject();
Bounds createBoundsObject(long start, long end, long long value);
long getValueFromKey(Bounds *bounds, unsigned long length, long key);
Bounds *defaultBoundsArray();
void setRange(Bounds *bounds, long start, long end, long long offset);
