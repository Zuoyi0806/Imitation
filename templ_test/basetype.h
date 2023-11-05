#ifndef _TEST_BASETYPE_H_
#define _TEST_BASETYPE_H_

#include <stdint.h>
#include <assert.h>

#ifndef ASSERT
#define ASSERT(x) assert(x)
#endif

typedef char           i8 ;
typedef unsigned char  u8 ;
typedef int16_t        i16;
typedef uint16_t       u16;
typedef int            i32;
typedef uint32_t       u32;
typedef int64_t        i64;
typedef uint64_t       u64;

typedef enum {
	PASS = 0,
	FAILED,
	NOT_SUPPORT,
} STATUS;

typedef enum {
	true  = 0,
	false = 1,
} boolen;

#endif

