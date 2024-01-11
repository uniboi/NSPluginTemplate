#include "native_closures.h"
#include "bindings/module.h"
#include "interfaces/sys.h"
#include <string.h>

/*
 * you'll probably want put the implementation into a different file to avoid
 * clutter here
 */
SQRESULT P4Test(HSquirrelVM *sqvm) {
  ns_log(LOG_INFO, "Hello, Squirrel");
  return SQRESULT_NULL;
}

struct SQFunctionRegistrationList {
  SQFunctionRegistration reg;
  struct SQFunctionRegistrationList *next;
};

struct SQFunctionRegistrationList *_sv_regs = 0;
struct SQFunctionRegistrationList *_cl_regs = 0;
struct SQFunctionRegistrationList *_ui_regs = 0;

SQNativeClosureReturnType get_ret_ty(const char *ret_ty) {
  if (strcmp(ret_ty, "bool"))
    return SQ_RET_BOOL;
  if (strcmp(ret_ty, "vector"))
    return SQ_RET_VEC;
  if (strcmp(ret_ty, "int"))
    return SQ_RET_INT;
  if (strcmp(ret_ty, "entity"))
    return SQ_RET_ENT;
  if (strcmp(ret_ty, "string"))
    return SQ_RET_STR;
  if (strcmp(ret_ty, "array"))
    return SQ_RET_ARR;
  if (strcmp(ret_ty, "asset"))
    return SQ_RET_ASSET;
  if (strcmp(ret_ty, "table"))
    return SQ_RET_TABLE;

  return SQ_RET_DEFAULT;
}

void bind_native_closure(void *module, struct SQFunctionRegistrationList *prev,
                         CSquirrelVM *sqvm, const char *return_type,
                         const char *name, const char *args_signature,
                         const char *help_text,
                         SQNativeClosureImplementation implementation) {
  RegisterSquirrelFunctionTy register_squirrel_function =
      ptr_at(module, 0x108E0);

  struct SQFunctionRegistrationList *fn_entry =
      malloc(sizeof(struct SQFunctionRegistrationList));
  fn_entry->next = prev;

  SQFunctionRegistration *fn = &fn_entry->reg;
  fn->sq_name = name;
  fn->native_name = name;
  fn->help_text = help_text;
  fn->raw_ret_ty = return_type;
  fn->args_signature = args_signature;
  fn->unknown1 = 0;
  fn->dev_level = 0;
  fn->short_name = name;
  fn->unknown2 = 0;
  fn->return_type = get_ret_ty(return_type);
  fn->external_buffer = 0;
  fn->external_buffer_size = 0;
  fn->unknown3 = 0;
  fn->unknown4 = 0;
  fn->implementation = implementation;

  register_squirrel_function(sqvm, fn, 1);
}

void cl_register_native_closures(CSquirrelVM *sqvm) {}

void ui_register_native_closures(CSquirrelVM *sqvm) {}

void sv_register_native_closures(CSquirrelVM *sqvm) {
  sv_bind_native_closure(sqvm, "void", "P4Test", "",
                         "an example squirrel function provided by a plugin",
                         P4Test);
}

void cl_bind_native_closure(CSquirrelVM *sqvm, const char *return_type,
                            const char *name, const char *args_signature,
                            const char *help_text,
                            SQNativeClosureImplementation implementation) {
  bind_native_closure(g_server, _sv_regs, sqvm, return_type, name,
                      args_signature, help_text, implementation);
}

void ui_bind_native_closure(CSquirrelVM *sqvm, const char *return_type,
                            const char *name, const char *args_signature,
                            const char *help_text,
                            SQNativeClosureImplementation implementation) {
  bind_native_closure(g_client, _ui_regs, sqvm, return_type, name,
                      args_signature, help_text, implementation);
}
void sv_bind_native_closure(CSquirrelVM *sqvm, const char *return_type,
                            const char *name, const char *args_signature,
                            const char *help_text,
                            SQNativeClosureImplementation implementation) {
  bind_native_closure(g_client, _cl_regs, sqvm, return_type, name,
                      args_signature, help_text, implementation);
}

void _deregister_native_closures(struct SQFunctionRegistrationList *list) {
  struct SQFunctionRegistrationList *c = list;
  while (c) {
    struct SQFunctionRegistrationList *l = c;
    c = c->next;
    free(l);
  }
}

void deregister_native_closures() {
  _deregister_native_closures(_sv_regs);
  _deregister_native_closures(_ui_regs);
  _deregister_native_closures(_cl_regs);
}
