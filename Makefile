####################################### BEG ####

NAME        := minishell

LIBS        := ft readline
LIBS_TARGET :=  lib/libft/libft.a

INCS        := \
            include \
            lib/libft/include

SRC_DIR     := src
SRCS        := \
			main.c \
			0_launch/set.c \
			0_launch/interactive.c \
			0_launch/non_interactive.c \
			1_parsing/checker.c \
			1_parsing/lexer.c \
			1_parsing/parser.c \
			1_parsing/parser_quotes.c \
			1_parsing/parser_redir.c \
			1_parsing/tokenizer.c \
			1_parsing/expander.c \
			1_parsing/utils_parsing.c \
			2_execution/child.c \
			2_execution/execution.c \
			2_execution/utils_exec.c \
			3_builtins/builtins.c \
			3_builtins/cd.c \
			3_builtins/echo.c \
			3_builtins/env.c \
			3_builtins/exit.c \
			3_builtins/export.c \
			3_builtins/pwd.c \
			3_builtins/unset.c \
			3_builtins/utils_builtins.c \
			4_signals/signals_act.c \
			4_signals/signals_scan.c \
			4_signals/utils_signals.c \
			utils/errors.c \
			utils/print_cmds.c \
			utils/one_shot_ft.c \
			utils/utils.c

# Prepend the source directory to each source file
SRCS        := $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
INCFLAGS    := $(addprefix -I,$(INCS))
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory #-j #remove to see relink + flags silence 
DIR_DUP     = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)
	$(RM) $(OBJS_BONUS) $(DEPS_BONUS)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"

.PHONY: clean fclean re
.SILENT: #remove to see relink + flags silence 

####################################### END ####
