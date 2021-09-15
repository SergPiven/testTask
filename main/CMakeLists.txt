# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

file(GLOB_RECURSE COMPONENT_SRCS "*.c" "./sources/*.c")

set(COMPONENT_ADD_INCLUDEDIRS "./headers")

register_component()