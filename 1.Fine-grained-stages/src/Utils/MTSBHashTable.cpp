//
// Created by tony on 13/04/22.
//

#include <Utils/MTSBHashTable.h>
#ifndef HASH
#define HASH(X, MASK) (((X) & MASK))
#endif

#ifndef NEXT_POW_2
/**
 *  compute the next number, greater than or equal to 32-bit unsigned v.
 *  taken from "bit twiddling hacks":
 *  http://graphics.stanford.edu/~seander/bithacks.html
 */
#define NEXT_POW_2(V)                           \
    do {                                        \
        V--;                                    \
        V |= V >> 1;                            \
        V |= V >> 2;                            \
        V |= V >> 4;                            \
        V |= V >> 8;                            \
        V |= V >> 16;                           \
        V++;                                    \
    } while(0)
#endif
//static inline uint32_t mtsb_hash(uint32_t x,uint32_t bits) { return (x * 2654435761U) >> (32 - bits); }
using namespace ADB;
MTSBHashTable::MTSBHashTable(uint32_t _bits, size_t hs) {
  myBits = _bits;
  size_t bks = myBits << 1;
  buckets = vector<MTSBHashTable_bucket>(bks);

  for (size_t i = 0; i < bks; i++) {
    buckets[i].init(hs);
  }
//  buckets[0].appendElement(MTSBHashTable_element(0XFFFF,0));
}