

#ifndef ADB_INCLUDE_UTILS_LOGGER_HPP
#define ADB_INCLUDE_UTILS_LOGGER_HPP
#include <assert.h>
#include <math.h>
#include <float.h>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <CommonData/CommonData.hpp>

/// Arbitrary size, just picking something likely to be larger than most packets
#define BITSTREAM_STACK_ALLOCATION_SIZE 256
using namespace ADB;

/// The namespace RakNet is not consistently used.  It's only purpose is to avoid compiler errors for classes whose names are very common.
/// For the most part I've tried to avoid this simply by using names very likely to be unique for my classes.
namespace ADB {

class MemAddresser {

 public:
  /// Default ructor
  MemAddresser();

  /// Initialize the BitStream, immediately setting the data it contains to a predefined pointer.
  /// Set \a _copyData to true if you want to make an internal copy of the data you are passing. Set it to false to just save a pointer to the data.
  /// You shouldn't call Write functions with \a _copyData as false, as this will write to unallocated memory
  /// 99% of the time you will use this function to cast Packet::data to a bitstream for reading, in which case you should write something as follows:
  /// \code
  /// RakNet::BitStream bs(packet->data, packet->length, false);
  /// \endcode
  /// \param[in] _data An array of bytes.
  /// \param[in] lengthInBytes Size of the \a _data.
  /// \param[in] _copyData true or false to make a copy of \a _data or not.
  MemAddresser(uint8_t *_data, length_t lengthInBytes);

  /// Destructor
  ~MemAddresser();

  /// Resets the bitstream for reuse.
  void reset(void);
  void higherReset(uint8_t *data, length_t lengthInBytes);

  /// Gets the data that BitStream is writing to / reading from
  /// Partial bytes are left aligned.
  /// \return A pointer to the internal state
  inline uint8_t *getData(void) { return data; }

  /// Write numberToWrite bits from the input source Right aligned
  /// data means in the case of a partial byte, the bits are aligned
  /// from the right (bit 0) rather than the left (as in the normal
  /// internal representation) You would set this to true when
  /// writing user data, and false when copying bitstream data, such
  /// as writing one bitstream to another
  /// \param[in] input The data
  /// \param[in] numberOfBitsToWrite The number of bits to write
  /// \param[in] rightAlignedBits if true data will be right aligned

  /// Align the bitstream to the byte boundary and then write the
  /// specified number of bits.  This is faster than WriteBits but
  /// wastes the bits to do the alignment and requires you to call
  /// ReadAlignedBits at the corresponding read position.
  /// \param[in] input The data
  /// \param[in] numberOfBytesToWrite The size of data.
  void writeAlignedBytes(uint8_t *input, length_t numberOfBytesToWrite);

  bool readAlignedBytes(uint8_t *output, length_t numberOfBytesToRead);

  /// Align the next write and/or read to a byte boundary.  This can
  /// be used to 'waste' bits to byte align for efficiency reasons It
  /// can also be used to force coalesced bitstreams to start on byte
  /// boundaries so so WriteAlignedBits and ReadAlignedBits both
  /// calculate the same offset when aligning.
  void alignWriteToByteBoundary(void);
  void alignReadToByteBoundary(void);
  template<typename T>
  T readAlignedValue() {

    T ru = *(T *) (data + BITS_TO_BYTES(readOffset));
    readOffset += sizeof(T) << 3;
    return ru;
  }
  template<typename T>
  T readAlignedValue(void *memPtr) {
    T ru = *(T *) memPtr;
    return ru;
  }
  template<typename T>
  void writeAlignedValue(T a) {
    *(T *) (data + BITS_TO_BYTES(readOffset)) = a;
    numberOfBitsUsed += sizeof(T) << 3;
  }
  template<typename T>
  void writeAlignedValue(void *memPtr, T a) {
    *(T *) memPtr = a;
  }
  bool readBits(uint8_t *output, length_t numberOfBitsToRead);
  template<typename T>
  T readValue(length_t numberOfBitsToRead) {
    T *ru;
    uint8_t buf[sizeof(T) * 2];
    memset(buf, 0, sizeof(T) * 2);
    readBits(buf, numberOfBitsToRead);
    ru = (T *) buf;
    return *ru;
  }
  void writeBits(uint8_t *input, length_t numberOfBitsToWrite);
  template<typename T>
  void writeValue(T val, length_t numberOfBitsToWrite) {

    uint8_t *tbuf = (uint8_t *) &val;
    writeBits(tbuf, numberOfBitsToWrite);

  }
  /// Write a 0
  void write0(void);

  /// Write a 1
  void write1(void);

  /// Reads 1 bit and returns true if that bit is 1 and false if it is 0
  bool readBit(void);

  length_t numberOfBitsUsed;

  length_t numberOfBitsAllocated;

  length_t readOffset;
//in bits
  void setWritePos(length_t pos) {
    numberOfBitsUsed = pos;
  }
  //in bits
  void setReadPos(length_t pos) {
    readOffset = pos;
  }
  uint8_t *data;

  /// true if the internal buffer is copy of the data passed to the ructor
  bool copyData;

};
typedef std::shared_ptr<MemAddresser> MemAddresserPtr;
}

#endif


