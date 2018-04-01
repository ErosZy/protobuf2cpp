add_library(protocol
            protocol.h
            {{{files}}}
)
set_target_properties(protocol PROPERTIES LINKER_LANGUAGE CXX)