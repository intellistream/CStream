//
// Created by tony on 13/04/22.
//
//The multithread-safe, single buckter hash table
#ifndef _UTILS_MTSBHASHTABLE_H_
#define _UTILS_MTSBHASHTABLE_H_
#include <stdint.h>
#include <vector>
#include <Utils/MultiCore/SPSCQueue.hpp>
#include <memory>
using namespace std;
using namespace INTELLI;
namespace ADB {
class MTSBHashTable_element {
 public:
  uint32_t value;
  uint32_t offset;
  MTSBHashTable_element() {}
  ~MTSBHashTable_element() {}
  MTSBHashTable_element(uint32_t v, uint32_t o) {
    value = v;
    offset = o;
  }
};
class MTSBHashTable_bucket {
 protected:
  // MTSBHashTable_element current;
vector<MTSBHashTable_element> history;
  MTSBHashTable_element mainEle;
  vector<size_t> map_offsetToEditTime;
  vector<size_t> map_editTimeToOffset;
  vector<size_t> map_offsetToIdx;
  size_t sizeMax = 0;
  size_t historyWritePtr=0;

  std::mutex m_mut;
  size_t lastAccess=0;
  size_t historyBase=0;
  size_t editTimes=0;

  //size_t validHistories=0;
  //size_t historyIdx=0;
 public:
  MTSBHashTable_bucket() {
  }
  ~MTSBHashTable_bucket() {}
  void init(size_t historyEntries) {
    sizeMax = historyEntries;
    history = vector<MTSBHashTable_element>(historyEntries);
    map_offsetToEditTime=vector<size_t>(historyEntries);
    map_editTimeToOffset=vector<size_t>(historyEntries);
    map_offsetToIdx=vector<size_t>(historyEntries);
    lastAccess=0;
  }
  MTSBHashTable_element getElement(size_t offset) {
   // return history[idx];
   //size_t readIdx=checkPoints[offset-historyBase];
   return  history[offset];
  }
  void printTables()
  {
    for (size_t i=0;i<editTimes;i++)
    {size_t  offset=map_editTimeToOffset[i];
       if(offset<historyBase)
       {
         continue;
       }
      cout<< to_string(i)+" th edit happens at offset="+ to_string(offset)<<endl;
      cout<< "offset "+to_string(offset)+" happens edit="+ to_string(map_offsetToEditTime[offset-historyBase])<<endl;
      size_t idx=map_offsetToIdx[offset-historyBase];
      cout<<"value="+ to_string(history[idx].value)<<endl;
      cout<<"/****/"<<endl;
    }
  }
  void appendElement(MTSBHashTable_element ele) {
    while ( historyWritePtr<sizeMax)
    {
      if(history[historyWritePtr].offset<=historyBase)// find a valid, out overwrite expired items
      {
        history[historyWritePtr]=ele;
        if(lastAccess<ele.offset)
        {
          lastAccess=ele.offset;
        }
        map_offsetToIdx[ele.offset-historyBase]=historyWritePtr;
        if(editTimes<1)
        {
          map_editTimeToOffset[editTimes]=ele.offset;
          map_offsetToEditTime[ele.offset-historyBase]=editTimes;
          editTimes++;
          //cout<<" first order append"<<endl;
        } else{
          size_t ahead=0,after=0;
          if(map_editTimeToOffset[0]>ele.offset)
          {
            //cout<<"less than any one in"+ to_string(editTimes)<<endl;
            ahead=0;
          }
          else {
            for (ahead = 0; map_editTimeToOffset[ahead] <= ele.offset && ahead < editTimes; ahead++);
          }
            for(after=editTimes;after>ahead;after--)
            { size_t offset=map_editTimeToOffset[after-1];
              map_editTimeToOffset[after]= offset;
              map_offsetToEditTime[offset-historyBase]++;
            }
            map_editTimeToOffset[ahead]=ele.offset;
            map_offsetToEditTime[ele.offset-historyBase]=ahead;
            editTimes++;
        }

        historyWritePtr++;
        if(historyWritePtr==sizeMax)
        {
          historyWritePtr=0;
        }
        return;
      }
      //for next
      historyWritePtr++;
      if(historyWritePtr==sizeMax)
      {
        historyWritePtr=0;
      }
    }

  }
  MTSBHashTable_element getMain()
  {
    return mainEle;
  }
  MTSBHashTable_element getNewest()
  {
    size_t idx=map_offsetToIdx[lastAccess-historyBase];
    return history[idx];
  }
  //after the write at this version
  MTSBHashTable_element getElementAtVersion(size_t offset)
  {
    size_t idx=map_offsetToIdx[offset-historyBase];
    return history[idx];
  }
  //before write of this version
  MTSBHashTable_element getElementBeforeVersion(size_t offset)
  { size_t edit=map_offsetToEditTime[offset-historyBase];
    if(edit==0)
    {
      return mainEle;
    }
    size_t offsetPrev=map_editTimeToOffset[edit-1];
    size_t idx=map_offsetToIdx[offsetPrev-historyBase];
    return history[idx];
  }
  void reset(size_t hb)
  {
    size_t offset=map_editTimeToOffset[editTimes-1];
    size_t idx=map_offsetToIdx[offset-historyBase];
    mainEle=history[idx];
    historyBase=hb;
    editTimes=0;
  }
  void lock() {
    while (!m_mut.try_lock());
  }
  void unlock() {
    m_mut.unlock();
  }

};
typedef std::shared_ptr<MTSBHashTable_bucket> MTSBHashTable_bucketPtr;
class MTSBHashTable {
 protected:
  vector<MTSBHashTable_bucket> buckets;
  uint32_t myBits = 0;
  vector<size_t> checkPoints;
 public:
  MTSBHashTable() {}
  ~MTSBHashTable() {}
  /**
   *@param
   * _bits Total bits, there will be 2^(_bs) buckets
   * hs Total history entries for each bucket
   */
  MTSBHashTable(uint32_t _bits, size_t hs);
  size_t numOfBuckets()
  {
    return buckets.size();
  }
  void resetBucket(size_t bk,size_t offset)
  {
    buckets[bk].reset(offset);
  }
  void overWrite(uint32_t hash,uint32_t key,uint32_t offset)
  {  buckets[hash].lock();
    buckets[hash].appendElement(MTSBHashTable_element(key,offset));
    buckets[hash].unlock();
    buckets[hash].printTables();
    cout<<endl;
  }
  void overWrite(uint32_t key,uint32_t offset)
  { uint32_t  hash=mtsb_hash(key,myBits);
    buckets[hash].lock();
    buckets[hash].appendElement(MTSBHashTable_element(key,offset));
    buckets[hash].unlock();
  }
  bool probe(uint32_t key,uint32_t offset)
  {
    uint32_t  hash=mtsb_hash(key,myBits);
    MTSBHashTable_element ele=buckets[hash].getElementBeforeVersion(offset);
 //   cout<<"v,offset="+to_string(ele.value)+","+ to_string(ele.offset)<<endl;
    if(ele.value==key)
    {
      return true;
    }
    return  false;
  }
  bool probe(uint32_t hash,uint32_t key,uint32_t offset)
  {
    MTSBHashTable_element ele=buckets[hash].getElementBeforeVersion(offset);
   // cout<<"v,offset="+to_string(ele.value)+","+ to_string(ele.offset)<<endl;
    if(ele.value==key)
    {
      return true;
    }
    return  false;
  }
  static uint32_t mtsb_hash(uint32_t x, uint32_t bits) { return (x * 2654435761U) >> (32 - bits); }
};
}
#endif //ALIANCEDB_INCLUDE_UTILS_MTSBHASHTABLE_H_
