#ifndef CVAR_H
#define CVAR_H

typedef int CVarDllIdentifier_t;

// TODO moar headers

typedef struct ConCommandBase {
} ConCommandBase;

typedef struct ConCommand {
} ConCommand;

typedef struct ConVar {
} ConVar;

typedef struct SourceColor {
  unsigned char R, G, B, A;
} SourceColor;

typedef struct CCVarIteratorInternal {
  struct {
    void (*SetFirst)(struct CCVarIteratorInternal *self);
    void (*Next)(struct CCVarIteratorInternal *self);
    ConCommandBase *(*Get)(struct CCVarIteratorInternal *self);
  } vftable;
} CCVarIteratorInternal;

typedef struct ICvar {
  struct {
  } *IAppSystem_vftable;
  struct {
    CVarDllIdentifier_t (*AllocateDLLIdentifier)(struct ICvar *self);

    void (*RegisterConCommand
    )(struct ICvar *self, ConCommandBase *pCommandBase);
    void (*UnregisterConCommand
    )(struct ICvar *self, ConCommandBase *pCommandBase);
    void (*UnregisterConCommands)(struct ICvar *self, CVarDllIdentifier_t id);

    const char *(*GetCommandLineValue
    )(struct ICvar *self, const char *pVariableName);

    ConCommandBase *(*FindCommandBase)(struct ICvar *self, const char *name);
    const ConCommandBase *(*FindCommandBase_const
    )(const struct ICvar *self, const char *name);
    ConVar *(*FindVar)(struct ICvar *self, const char *name);
    const ConVar *(*FindVar_const)(const struct ICvar *self, const char *name);
    ConCommand *(*FindCommand)(struct ICvar *self, const char *name);
    const ConCommand *(*FindCommand_const
    )(const struct ICvar *self, const char *name);

    void (*sub_1)();
    void (*sub_2)();

    void (*sub_3)();
    void (*sub_4)();
    void (*sub_5)();

    void (*sub_6)();
    void (*sub_7)();

    void (*ConsoleColorPrintf
    )(struct ICvar *self, const SourceColor *clr, const char *pFormat, ...);
    void (*ConsolePrintf)(struct ICvar *self, const char *pFormat, ...);
    void (*ConsoleDPrintf)(struct ICvar *self, const char *pFormat, ...);

    void (*sub_8)();

    void (*sub_9)();

    void (*sub_10)();
    void (*sub_11)();

    void (*sub_12)();
    void (*sub_13)();

    void (*sub_14)();
    void (*sub_15)();
    void (*sub_16)();
    void (*sub_17)();
    void (*sub_18)();
    void (*sub_19)();

    CCVarIteratorInternal *(*FactoryInternalIterator)(struct ICvar *self);
  } *vftable;
} ICvar;

#endif
