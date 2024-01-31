#ifndef RECORDED_ANIMATION_H
#define RECORDED_ANIMATION_H

#include "squirrel/squirrel.h"
#include <assert.h>
#include <minwindef.h>
#include <stdbool.h>

#define NO_PACK _Pragma("pack(push, 1)")
#define PACK _Pragma("pack(pop)")
#define ASSERT_SIZE(type, size)                                                \
  static_assert(sizeof(type) == size, #type " is malformed.")

ASSERT_SIZE(bool, 1);

typedef unsigned char undefined;
ASSERT_SIZE(undefined, 1);

enum {
  UTAG_RECORDED_ANIMATION = -0x80008fffffffe,
};

typedef struct Vector3 {
  float x, y, z;
} Vector3;

ASSERT_SIZE(Vector3, 0xc);

typedef struct RecordedAnimation_Layer {
  int unk_0, sequence_index, unk_8, unk_c, unk_10, unk_14, unk_18, unk_1c,
      unk_20;
} RecordedAnimation_Layer;

ASSERT_SIZE(RecordedAnimation_Layer, 0x24);

typedef struct RecordedAnimation_Frame {
  int unk_0, unk_4, unk_8, unk_c, unk_10, unk_14, unk_18, unk_1c,
      sequence_index, unk_24, unk_28, unk_2c, layer_index, unk_34;
  char gap_38[11];
  bool unk_43;
} RecordedAnimation_Frame;

ASSERT_SIZE(RecordedAnimation_Frame, 0x44);

/*
NO_PACK
typedef struct UnknownAnimData {
  float unknown_0;
  float unknown_4;
  float unknown_8;
  char gap_c[10];
  float unknown_16;
} UnknownAnimData;

ASSERT_SIZE(UnknownAnimData, 0x1a);

// this might just be RecordedAnimation
typedef struct UnknownAnimData4 {
  char unk[816];
} UnknownAnimData4;
PACK

ASSERT_SIZE(UnknownAnimData4, 0x330);
*/

typedef struct RecordedAnimation {
  int unknown_0[44];
  undefined unknown_b0[64];
  const char* sequences[47];
  int unknown_268[34];
  Vector3 origin;
  Vector3 angles;
  RecordedAnimation_Frame* frames; // pointer to 3000 frames
  RecordedAnimation_Layer* layers; // pointer to 3000 layers
  unsigned int frame_count;        // max 3k
  unsigned int layer_count;        // max 3k
  unsigned long long loaded_index; // index in array of loaded animations
  int index;
  bool not_refcounted;
  // undefined padding
  unsigned short refcount;
} RecordedAnimation;

ASSERT_SIZE(RecordedAnimation, 0x330);

SQRESULT Script_CopyAnim(HSquirrelVM* sqvm);
SQRESULT Script_WriteTestAnim(HSquirrelVM* sqvm);
SQRESULT Script_ReadTestAnim(HSquirrelVM* sqvm);

void init_recorded_animation(HMODULE module);

#endif
