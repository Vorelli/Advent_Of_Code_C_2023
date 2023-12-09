#include "rangeHandler.h"
#include <stdlib.h>
#define NUM_ELEMENTS 1000

Bounds *defaultBoundsArray() {
  Bounds *bounds = calloc(sizeof(Bounds *), NUM_ELEMENTS);
  for (short i = 0; i < NUM_ELEMENTS; i++) {
    Bounds b = createBoundsObject(0, 0, 0);
    bounds[i] = b;
  }
  memset(bounds, 0, NUM_ELEMENTS);
  bounds[0] = getDefaultBoundsObject();
  return bounds;
}

Bounds getDefaultBoundsObject() { return createBoundsObject(0, LONG_MAX, 0); };

Bounds createBoundsObject(long start, long end, long long value) {
  Bounds b = {start, end, value};
  return b;
}

long getValue(long value, unsigned long index) { return value + index; }

long getValueFromKey(Bounds *bounds, unsigned long length, long key) {
  Bounds lastBound = bounds[0];
  unsigned long i;
  for (i = 0; i < NUM_ELEMENTS; i++) {
    if (key >= bounds[i].start && key <= bounds[i].end)
      return getValue(bounds[i].offset, i);
    if (key > bounds[i].end)
      break;
    lastBound = bounds[i];
  }
  return getValue(lastBound.offset, i);
}

void setRange(Bounds *bounds, long newStart, long newEnd, long long offset) {
  Bounds b = {newStart, newEnd, offset};
  for (short i = 0; i < NUM_ELEMENTS; i++) {
    if (bounds[i].start == 0 && bounds[i].end == 0)
      break;
    if (bounds[i].start < newStart && newEnd >= bounds[i].start) {
      // modify end of this bound.
    }
  }
}
