#pragma once

#ifdef max
#undef max
#endif // max

#define max(a, b) (((a) > (b)) ? (a) : (b))

#ifdef min
#undef min
#endif // min

#define min(a, b) (((a) < (b)) ? (a) : (b))

#ifdef clamp
#undef clamp
#endif // clamp

#define clamp(value, lowest, highest) max(lowest, min(value, highest))

#ifdef saturate
#undef saturate
#endif // saturate

#define saturate(value) clamp(value, 0, 1)

#ifdef SAFE_DELETE
#undef SAFE_DELETE
#endif // SAFE_DELETE

#define SAFE_DELETE(ptr) delete ptr; ptr = nullptr

#ifdef SAFE_DELETE_ARRAY
#undef SAFE_DELETE_ARRAY
#endif // SAFE_DELETE_ARRAY

#define SAFE_DELETE_ARRAY(ptr) delete[] ptr; ptr = nullptr

#ifdef BEGIN
#undef BEGIN
#endif // BEGIN

#define BEGIN {

#ifdef END
#undef END
#endif // END

#define END }

#ifdef FLOOP
#undef FLOOP
#endif // FLOOP

#define FLOOP(NUMBER) for (int i = 0; i < (NUMBER); ++i) BEGIN

#ifdef FLOOPY
#undef FLOOPY
#endif // FLOOPY

#define FLOOPY(TYPE, NUMBER) for (TYPE i = 0; i < (NUMBER); ++i) BEGIN

#ifdef BREAK_POINT_HERE
#undef BREAK_POINT_HERE
#endif // BREAK_POINT_HERE

#define BREAK_POINT_HERE { int br = 0; br++; } (void)0