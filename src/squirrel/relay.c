#include "relay.h"
#include "interfaces/sys.h"

#define PTR_AT(offset) ((void *)(base + offset))

SQRelay g_sqsv = {0};
SQRelay g_sqcl = {0};

SQRelay *sqapi(ScriptContext context) {
  switch (context) {
  case SC_SERVER:
    return &g_sqsv;
  case SC_CLIENT:
  case SC_UI:
    return &g_sqcl;
  default:
    return 0;
  }
}

void init_relay_sv(HMODULE module) {
  uintptr_t base = (uintptr_t)module;

  g_sqsv.sq_pushroottable = PTR_AT(0x5840);
  g_sqsv.sq_pushstring = PTR_AT(0x3440);
  g_sqsv.sq_pushinteger = PTR_AT(0x36a0);
  g_sqsv.sq_pushfloat = PTR_AT(0x3800);
  g_sqsv.sq_pushbool = PTR_AT(0x3710);
  g_sqsv.sq_pushasset = PTR_AT(0x3560);
  g_sqsv.sq_pushvector = PTR_AT(0x3780);
  g_sqsv.sq_pushobject = PTR_AT(0x83a0);

  g_sqsv.sq_getstring = PTR_AT(0x60a0);
  g_sqsv.sq_getinteger = PTR_AT(0x60c0);
  g_sqsv.sq_getfloat = PTR_AT(0x60e0);
  g_sqsv.sq_getbool = PTR_AT(0x6110);
  g_sqsv.sq_getasset = PTR_AT(0x5ff0);
  g_sqsv.sq_get = PTR_AT(0x7c00);
  g_sqsv.sq_getvector = PTR_AT(0x6120);
  g_sqsv.sq_getthisentity = PTR_AT(0x203B0);
  g_sqsv.sq_getobject = PTR_AT(0x6140);
  g_sqsv.sq_getfunction = PTR_AT(0x6c80);
  g_sqsv.sq_getuserdata = PTR_AT(0x63b0);

  g_sqsv.sq_newarray = PTR_AT(0x39F0);
  g_sqsv.sq_arrayappend = PTR_AT(0x3c70);

  g_sqsv.sq_newtable = PTR_AT(0x3960);
  g_sqsv.sq_newslot = PTR_AT(0x7080);

  g_sqsv.sq_newstruct = PTR_AT(0x53e0);
  g_sqsv.sq_setmember = PTR_AT(0x5510);

  g_sqsv.sq_createuserdata = PTR_AT(0x38d0);
  g_sqsv.sq_setuserdatatypetag = PTR_AT(0x6470);

  g_sqsv.sq_stackinfos = PTR_AT(0x35920);
  g_sqsv.sq_compilebuffer = PTR_AT(0x3110);
  g_sqsv.sq_call = PTR_AT(0x8620);
  g_sqsv.sq_raiseerror = PTR_AT(0x8440);

  g_sqsv.c_sq_define_constant = PTR_AT(0x1f550);
}

void init_relay_cl(HMODULE module) {
  uintptr_t base = (uintptr_t)module;

  g_sqcl.sq_pushroottable = PTR_AT(0x5860);
  g_sqcl.sq_pushstring = PTR_AT(0x3440);
  g_sqcl.sq_pushinteger = PTR_AT(0x36a0);
  g_sqcl.sq_pushfloat = PTR_AT(0x3800);
  g_sqcl.sq_pushbool = PTR_AT(0x3710);
  g_sqcl.sq_pushasset = PTR_AT(0x3560);
  g_sqcl.sq_pushvector = PTR_AT(0x3780);
  g_sqcl.sq_pushobject = PTR_AT(0x83d0);

  g_sqcl.sq_getstring = PTR_AT(0x60c0);
  g_sqcl.sq_getinteger = PTR_AT(0x60e0);
  g_sqcl.sq_getfloat = PTR_AT(0x61100);
  g_sqcl.sq_getbool = PTR_AT(0x6130);
  g_sqcl.sq_getasset = PTR_AT(0x6010);
  g_sqcl.sq_get = PTR_AT(0x7c30);
  g_sqcl.sq_getvector = PTR_AT(0x6140);
  g_sqcl.sq_getthisentity = PTR_AT(0x12f80);
  g_sqcl.sq_getobject = PTR_AT(0x6160);
  g_sqcl.sq_getfunction = PTR_AT(0x6cb0);
  g_sqcl.sq_getuserdata = PTR_AT(0x63d0);

  g_sqcl.sq_newarray = PTR_AT(0x39F0);
  g_sqcl.sq_arrayappend = PTR_AT(0x3c70);

  g_sqcl.sq_newtable = PTR_AT(0x3960);
  g_sqcl.sq_newslot = PTR_AT(0x70b0);

  g_sqcl.sq_newstruct = PTR_AT(0x5400);
  g_sqcl.sq_setmember = PTR_AT(0x5530);

  g_sqcl.sq_createuserdata = PTR_AT(0x38d0);
  g_sqcl.sq_setuserdatatypetag = PTR_AT(0x6490);

  g_sqcl.sq_stackinfos = PTR_AT(0x35970);
  g_sqcl.sq_compilebuffer = PTR_AT(0x3110);
  g_sqcl.sq_call = PTR_AT(0x8650);
  g_sqcl.sq_raiseerror = PTR_AT(0x8740);

  g_sqcl.c_sq_define_constant = PTR_AT(0x12120);
}
