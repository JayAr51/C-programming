#ifndef __KV_H__
#define __KV_H__


struct _kvpair_t { 
  char * key; //DEFINE ME!
  char * value;
i  };
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t { 
  kvpair_t ** kv;//array of pointers to key/value pairs
  int entries;
};
typedef struct _kvarray_t kvarray_t;


kvarray_t * readKVs(const char * fname);

void freeKVEntry(kvarray_t * pairs,int i);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
