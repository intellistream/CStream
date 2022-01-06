#include <Utils/MemAddresser.hpp>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
using namespace ADB;
MemAddresser::MemAddresser() {
  numberOfBitsUsed = 0;
  numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE * 8;
  readOffset = 0;
  //data = ( uint8_t* ) malloc( 32 );
  data = (uint8_t *) NULL;
#ifdef _DEBUG
  //	assert( data );
#endif
  //memset(data, 0, 32);
  copyData = true;
}
MemAddresser::MemAddresser(uint8_t *_data, length_t lengthInBytes) {
  numberOfBitsUsed = 0;
  readOffset = 0;
  numberOfBitsAllocated = lengthInBytes << 3;
  data = (uint8_t *) _data;
}
MemAddresser::~MemAddresser() {

}
void MemAddresser::writeBits(uint8_t *input, length_t numberOfBitsToWrite) {
  if (numberOfBitsToWrite <= 0)
    return;
  length_t offset = 0;
  uint8_t dataByte;
  length_t numberOfBitsUsedMod8;
  while (numberOfBitsToWrite > 0) {
    numberOfBitsUsedMod8 = numberOfBitsUsed & 7;

    dataByte = *(input + offset);

    if (numberOfBitsUsedMod8 == 0)
      *(data + (numberOfBitsUsed >> 3)) = dataByte;
    else {
      // Copy over the new data.
      *(data + (numberOfBitsUsed >> 3)) |= dataByte << (numberOfBitsUsedMod8); // First half

      if (8 - (numberOfBitsUsedMod8) < 8 && 8 - (numberOfBitsUsedMod8)
          < numberOfBitsToWrite)   // If we didn't write it all out in the first half (8 - (numberOfBitsUsed%8) is the number we wrote in the first half)
      {
        *(data + (numberOfBitsUsed >> 3) + 1) =
            (uint8_t) (dataByte >> (8 - (numberOfBitsUsedMod8))); // Second half (overlaps byte boundary)

      }
    }

    if (numberOfBitsToWrite >= 8)
      numberOfBitsUsed += 8;
    else
      numberOfBitsUsed += numberOfBitsToWrite;

    numberOfBitsToWrite -= 8;
    offset++;
  }
}
bool MemAddresser::readBits(uint8_t *output, length_t numberOfBitsToRead) {
  uint8_t bitMask[] = {
      0, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff
  };
  if (numberOfBitsToRead <= 0)
    return false;
  if (readOffset + numberOfBitsToRead > numberOfBitsAllocated)
    return false;
  length_t readOffsetMod8;
  length_t offset = 0;
  while (numberOfBitsToRead > 0) {
    readOffsetMod8 = readOffset & 7;
    *(output + offset) |= *(data + (readOffset >> 3)) >> (readOffsetMod8); // First half
    //return false;
    if (readOffsetMod8 > 0 && numberOfBitsToRead
        > 8 - (readOffsetMod8))   // If we have a second half, we didn't read enough bytes in the first half
      *(output + offset) |=
          *(data + (readOffset >> 3) + 1) << (8 - (readOffsetMod8)); // Second half (overlaps byte boundary)

    numberOfBitsToRead -= 8;

    if (numberOfBitsToRead
        < 0)   // Reading a partial byte for the last byte, shift right so the data is aligned on the right
    {
      length_t smallBits = 8 + numberOfBitsToRead;
      *(output + offset) = *(output + offset) & bitMask[smallBits];

      readOffset += smallBits;

    } else
      readOffset += 8;
    offset++;
  }
  return true;
}
void MemAddresser::reset(void) {
  numberOfBitsUsed = 0;
  readOffset = 0;
}
void MemAddresser::higherReset(uint8_t *input, length_t lengthInBytes) {
  data = input;
  copyData = false;
  numberOfBitsUsed = 0;
  readOffset = 0;
  numberOfBitsAllocated = lengthInBytes << 3;
}
void MemAddresser::write0(void) {
  if ((numberOfBitsUsed & 7) == 0)
    data[numberOfBitsUsed >> 3] = 0;

  numberOfBitsUsed++;
}
void MemAddresser::write1(void) {
  length_t numberOfBitsMod8 = numberOfBitsUsed & 7;
  if (numberOfBitsMod8 == 0)
    data[numberOfBitsUsed >> 3] = 0x80;
  else
    data[numberOfBitsUsed >> 3] |= 0x80 >> (numberOfBitsMod8); // Set the bit to 1
  numberOfBitsUsed++;
}
bool MemAddresser::readBit(void) {
  return (bool) (data[readOffset >> 3] & (0x80 >> ((readOffset++) & 7)));
}
void MemAddresser::alignReadToByteBoundary(void) {
  if (readOffset & 7)
    readOffset += 8 - (((readOffset - 1) & 7) + 1);
}
void MemAddresser::alignWriteToByteBoundary(void) {
  if (numberOfBitsUsed & 7)
    numberOfBitsUsed += 8 - (((numberOfBitsUsed - 1) & 7) + 1);
}

void MemAddresser::writeAlignedBytes(uint8_t *input, length_t numberOfBytesToWrite) {
  alignWriteToByteBoundary();
  ADB_memcpy(data + BITS_TO_BYTES(numberOfBitsUsed), input, numberOfBytesToWrite);
  numberOfBitsUsed += BYTES_TO_BITS(numberOfBytesToWrite);
}
bool MemAddresser::readAlignedBytes(uint8_t *output, length_t numberOfBytesToRead) {

  if (numberOfBytesToRead <= 0)
    return false;
  alignReadToByteBoundary();
  if (readOffset + (numberOfBytesToRead << 3) > numberOfBitsAllocated)
    return false;
  ADB_memcpy(output, data + (readOffset >> 3), numberOfBytesToRead);
  readOffset += numberOfBytesToRead << 3;
  return true;
}