#include "recorded_animation.h"
#include "bindings/module.h"
#include "bindings/relay.h"
#include "interfaces/sys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FRAMES_SIZE sizeof(RecordedAnimation_Frame) * 3000
static_assert(FRAMES_SIZE == 0x31ce0, "too little space for frames");

#define LAYERS_SIZE sizeof(RecordedAnimation_Layer) * 3000
static_assert(LAYERS_SIZE == 0x1a5e0, "too little space for layers");

void (*sq_pushrecordedanimation)(HSquirrelVM* sqvm, RecordedAnimation* anim);
RecordedAnimation* (*sq_getrecordedanimation
)(HSquirrelVM* sqvm, SQInteger stackpos);

bool (*cache_recorded_animation)(RecordedAnimation* anim);
RecordedAnimation* (*get_cached_recorded_animation)(int index);
RecordedAnimation* (*new_recorded_animation)();
void (*deref_recorded_animation)(RecordedAnimation* anim);
void (*addref_recorded_animation)(RecordedAnimation* anim);

void init_recorded_animation(HMODULE module) {
  sq_pushrecordedanimation = ptr_at(module, 0x99c50);
  sq_getrecordedanimation = ptr_at(module, 0x99b30);

  cache_recorded_animation = ptr_at(module, 0x99270);
  get_cached_recorded_animation = ptr_at(module, 0x997e0);
  new_recorded_animation = ptr_at(module, 0x996e0);
  deref_recorded_animation = ptr_at(module, 0x99dc0);
  addref_recorded_animation = ptr_at(module, 0x996c0);
}

size_t used_sequences(RecordedAnimation* anim) {
  int i = 0;
  while(i <= 47 && anim->sequences[i]) i++;
  return i;
}

void serialize_recorded_animation(const char* path, RecordedAnimation* anim) {
  FILE* f = fopen(path, "wb");

  fwrite(anim, sizeof(int) * 44 + 64, 1, f);
  fwrite(&anim->origin, sizeof(Vector3) * 2, 1, f);
  fwrite(&anim->frame_count, sizeof(anim->frame_count) * 2, 1, f);

  fwrite(anim->frames, FRAMES_SIZE, 1, f);
  fwrite(anim->layers, LAYERS_SIZE, 1, f);

  int used = used_sequences(anim);
  ns_logf(LOG_INFO, "writing %d sequences", used);
  fwrite(&used, sizeof(int), 1, f);

  for(int i = 0; i < used; i++) {
    const char* sequence = anim->sequences[i];
    int len = strlen(sequence);
    fwrite(&len, sizeof(int), 1, f);
    fwrite(sequence, 1, len, f);
  }

  fclose(f);
}


RecordedAnimation* init_recorded_animation_from_file(const char* path) {
  RecordedAnimation* new = new_recorded_animation();
  FILE* f = fopen(path, "rb");

  fread(new, sizeof(int) * 44 + 64, 1, f);
  fread(&new->origin, sizeof(Vector3) * 2, 1, f);
  fread(&new->frame_count, sizeof(new->frame_count) * 2, 1, f);

  fread(new->frames, FRAMES_SIZE, 1, f);
  fread(new->layers, LAYERS_SIZE, 1, f);

  int used = 0;
  fread(&used, sizeof(int), 1, f);

  for(int i = 0; i < used; i++) {
    int len = 0;
    fread(&len, sizeof(int), 1, f);
    char* sequence = malloc(len + 1);
    fread(sequence, 1, len, f);
    sequence[len] = '\0';

    new->sequences[i] = sequence;
    ns_logf(LOG_INFO, "loaded sequence \"%s\"", new->sequences[i]);
  }

  fclose(f);

  return new;
}

void copy_recorded_animation(RecordedAnimation* dest, RecordedAnimation* src) {
  RecordedAnimation copy = {0};
  memcpy(&copy, dest, 0x330);

  dest->index = copy.index;
  dest->loaded_index = copy.loaded_index;
  dest->refcount = copy.refcount;

  memcpy(dest->unknown_0, src->unknown_0, sizeof(int) * 44);
  memcpy(dest->unknown_b0, src->unknown_b0, 64);
  memcpy(dest->sequences, src->sequences, sizeof(char*) * 47);
  memcpy(dest->unknown_268, src->unknown_268, sizeof(int) * 34);
  memcpy(&dest->origin, &src->origin, sizeof(Vector3) * 2);

  dest->frames = src->frames;
  dest->layers = src->layers;
  dest->frame_count = src->frame_count;
  dest->layer_count = src->layer_count;
}

RecordedAnimation* new_copy_anim(RecordedAnimation* src) {
  RecordedAnimation* new = new_recorded_animation();
  addref_recorded_animation(new);

  memcpy(new->unknown_0, src->unknown_0, sizeof(int) * 44);
  memcpy(new->unknown_b0, src->unknown_b0, 64);
  memcpy(new->sequences, src->sequences, sizeof(char*) * 47);
  memcpy(new->unknown_268, src->unknown_268, sizeof(int) * 34);
  memcpy(&new->origin, &src->origin, sizeof(Vector3) * 2);

  memcpy(new->frames, src->frames, FRAMES_SIZE);
  memcpy(new->layers, src->layers, LAYERS_SIZE);
  new->frame_count = src->frame_count;
  new->layer_count = src->layer_count;

  return new;
}

SQRESULT Script_CopyAnim(HSquirrelVM* sqvm) {
  RecordedAnimation* anim = sq_getrecordedanimation(sqvm, 2);
  ns_logf(LOG_INFO, "loaded %d frames", anim->frame_count);

  //  RecordedAnimation* new = new_recorded_animation();
  //  copy_recorded_animation(new, anim);
  //  sq_pushrecordedanimation(sqvm, new);

  for (int i = 0; i < 47; i++) {
    const char* sequence = anim->sequences[i];
    if (sequence)
      ns_log(LOG_INFO, sequence);
  }

//  RecordedAnimation* cpy = new_copy_anim(anim);
  RecordedAnimation* cpy = init_recorded_animation_from_file("./test.anim");
  memcpy(cpy->sequences, anim->sequences, sizeof(char*) * 47);
  memcpy(cpy->unknown_0, anim->unknown_0, sizeof(int) * 44);
  memcpy(cpy->unknown_b0, anim->unknown_b0, 64);
  memcpy(cpy->unknown_268, anim->unknown_268, sizeof(int) * 34);

  sq_pushrecordedanimation(sqvm, cpy);

  return SQRESULT_NOTNULL;
}

SQRESULT Script_WriteTestAnim(HSquirrelVM* sqvm) {
  ns_log(LOG_INFO, "writing");

  RecordedAnimation* anim = sq_getrecordedanimation(sqvm, 2);
  serialize_recorded_animation("./test.anim", anim);

  ns_log(LOG_INFO, "serialized animation");

  return SQRESULT_NULL;
}

SQRESULT Script_ReadTestAnim(HSquirrelVM* sqvm) {
  ns_log(LOG_INFO, "reading");

  RecordedAnimation* anim = init_recorded_animation_from_file("./test.anim");
  sq_pushrecordedanimation(sqvm, anim);

  ns_log(LOG_INFO, "deserialized animation");

  return SQRESULT_NOTNULL;
}
