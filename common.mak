COLOR_PREFIX := \033[1;31m
COLOR_POSTFIX := \033[0m

# Check verbose field
ifeq ("$(origin V)", "command line")
VERBOSE := $(V)
endif
ifneq ($(VERBOSE),1)
Q := @
endif

# Check color field
ifeq ("$(origin NC)", "command line")
NOT_COLOR := $(NC)
endif
ifeq ($(NOT_COLOR),1)
COLOR_PREFIX :=
COLOR_POSTFIX :=
endif

# Includes directory used by C files
C_INCLUDES := 			$(SOURCE_DIR)/

# Includes used by assembly files
ASM_INCLUDES :=   

# Output directory
OUTPUT_DIR := $(CURRENT_DIR)/bin

# Directory of object files
OBJDIR     := $(OUTPUT_DIR)/objs

# Dependency directory
DEPDIR     := $(OUTPUT_DIR)/Dependency

# Objects of c files
OBJS 	   := $(addprefix $(OBJDIR),$(subst $(realpath $(BASE_TREE_SRC)),,$(abspath $(C_SRC:.c=.o))))
OBJS_CPP   := $(addprefix $(OBJDIR),$(subst $(realpath $(BASE_TREE_SRC)),,$(abspath $(CPP_SRC:.cpp=.o))))

# Dependency files
DEPEND 	   := $(addprefix $(DEPDIR),$(subst $(realpath $(BASE_TREE_SRC)),,$(abspath $(C_SRC:.c=.d))))
DEPEND_CPP := $(addprefix $(DEPDIR),$(subst $(realpath $(BASE_TREE_SRC)),,$(abspath $(CPP_SRC:.cpp=.d))))

# Objects of assembly files
OBJS_ASM   := $(addprefix $(OBJDIR),$(subst $(realpath $(BASE_TREE_SRC)),,$(abspath $(ASM_SRC:.asm=.o))))

# Used to create the dependency file
DEPENDENCY_FOLDER   = $(subst $(abspath $(OBJDIR)),$(abspath $(DEPDIR)),$(dir $@))
DEPENDENCY_FLAG_C   = -MMD -MP -MF $(DEPENDENCY_FOLDER)$(subst .c,.d,$(notdir $<))
DEPENDENCY_FLAG_CPP = -MMD -MP -MF $(DEPENDENCY_FOLDER)$(subst .cpp,.d,$(notdir $<))

# Compile each C source file
# -MT : Set the name of the target in the generated dependency file.
# -MMD : Generate dependency information as a side-effect of compilation, not instead of compilation
# -MP : Adds a target for each prerequisite in the list, to avoid errors when deleting files
# -MF : Write the generated dependency file
$(OBJDIR)/%.o: 	$(abspath $(BASE_TREE_SRC))/%.cpp
	   	$(shell mkdir -p $(dir $@) >/dev/null)
	   	$(shell mkdir -p $(subst $(abspath $(OBJDIR)),$(abspath $(DEPDIR)),$(dir $@)) >/dev/null)
ifeq ($(Q),@)
		@printf "\t[$(COLOR_PREFIX)CPP$(COLOR_POSTFIX)] $(subst $(abspath $(BASE_TREE_SRC)),,$<)\n"
endif
		$(Q)$(CPP) $(addprefix -D, $(C_DEFINES)) $(addprefix -I, $(C_INCLUDES)) -c $(CPPFLAGS) $(DEPENDENCY_FLAG_CPP) -o $@ $<

$(OBJDIR)/%.o: 	$(abspath $(BASE_TREE_SRC))/%.c
	   	$(shell mkdir -p $(dir $@) >/dev/null)
	   	$(shell mkdir -p $(subst $(abspath $(OBJDIR)),$(abspath $(DEPDIR)),$(dir $@)) >/dev/null)
ifeq ($(Q),@)
		@printf "\t[$(COLOR_PREFIX)CC$(COLOR_POSTFIX)] $(subst $(abspath $(BASE_TREE_SRC)),,$<)\n"
endif
		$(Q)$(CC) $(addprefix -D, $(C_DEFINES)) $(addprefix -I, $(C_INCLUDES)) -c $(CFLAGS) $(DEPENDENCY_FLAG_C) -o $@ $<

$(OBJDIR)/%.o: 	$(abspath $(BASE_TREE_SRC))/%.asm
	   	$(shell mkdir -p $(dir $@) >/dev/null)
	   	$(shell mkdir -p $(subst $(abspath $(OBJDIR)),$(abspath $(DEPDIR)),$(dir $@)) >/dev/null)
ifeq ($(Q),@)
		@printf "\t[$(COLOR_PREFIX)ASM$(COLOR_POSTFIX)] $(subst $(abspath $(BASE_TREE_SRC)),,$<)\n"
endif
		$(Q)$(CC_ASM) $(addprefix -I, $(ASM_INCLUDES)) $(ASM_FLAGS) -o $@ $<

# default target of the makefile is to produce the output
.DEFAULT: $(OUTPUT)

# Generate the library
.PHONY: all clean CheckSharedLibrary
all: $(OUTPUT)

# Destroy object files, the dependency files and the output library
clean:  
	-$(Q)$(RM) $(OUTPUT)
ifeq ($(Q),@)
		-@printf "\n"
		@printf "\t[$(COLOR_PREFIX)CLEAN$(COLOR_POSTFIX)] $(OUTPUT)\n"
endif
	-$(Q)$(RM) $(OBJS_CPP) 
ifeq ($(Q),@)
		@printf "\t[$(COLOR_PREFIX)CLEAN$(COLOR_POSTFIX)] CPP_OBJS\n"
endif
	-$(Q)$(RM) $(OBJS) 
ifeq ($(Q),@)
		@printf "\t[$(COLOR_PREFIX)CLEAN$(COLOR_POSTFIX)] C_OBJS\n"
endif
	-$(Q)$(RM) $(OBJS_ASM)
ifeq ($(Q),@)
		@printf "\t[$(COLOR_PREFIX)CLEAN$(COLOR_POSTFIX)] ASM_OBJS\n"
endif
	-$(Q)$(RM) $(abspath $(OBJDIR)) $(abspath $(DEPDIR))
ifeq ($(Q),@)
		@printf "\t[$(COLOR_PREFIX)CLEAN$(COLOR_POSTFIX)] DEP_FILES\n"
endif
	-@printf "\n"

# Post-build action
post-build: 
ifneq ($(words $(BOARD_PATH_LIB)), 0)
	@printf "*** Copying $(OUTPUT) to $(BOARD_PATH_LIB) ***"
	$(shell scp $(OUTPUT) $(BOARD_PATH_LIB))
	@printf "\n"
endif

# Output library depends on the objs of the project
USER_LIBS_PATH := $(addprefix -L,$(dir $(LIBS_PATH))) $(addprefix -L,$(dir $(USR_LIBS)))
LIBS_COMMAND := $(addprefix -l, $(LIBS)) $(addprefix -l, $(basename $(notdir $(USR_LIBS))))

$(OUTPUT): 	$(OBJS_CPP) $(OBJS) $(OBJS_ASM)
ifeq ($(Q),@)
		@printf "\t[$(COLOR_PREFIX)LD$(COLOR_POSTFIX)] $(OUTPUT)\n"
endif
		$(Q)$(LINK) $(LNKFLAGS) $(USER_LIBS_PATH) -o $(OUTPUT) $(OBJS_CPP) $(OBJS) $(OBJS_ASM) $(SYS_STATIC_LIBS) $(LIBS_COMMAND) $(PKG_CONFIG_LIBS)
ifeq ($(Q),@)
		@$(MAKE) -s post-build
else
		$(MAKE) post-build
endif

.SECONDARY: post-build

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPEND_CPP)
-include $(DEPEND)
endif
