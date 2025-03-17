SRC =	main.c \
		display.c \
		parse.c \
		network.c \

INC =	ft_traceroute.h \

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.$(SRC_EXT)=.o))
DEP = $(addprefix $(DEP_DIR), $(SRC:.$(SRC_EXT)=.d))

SRC_EXT = c
INC_EXT = h

SRC_DIR = ./
INC_DIR = ./
OBJ_DIR = ./obj/
DEP_DIR = ./dep/

vpath	%.h $(INC_DIR)
vpath	%.o $(OBJ_DIR)
vpath	%.d $(DEP_DIR)

CC = clang
FLAG = -Wall -Wextra -Werror
LIB =
NAME = ft_traceroute

####

all: $(OBJ_DIR) $(DEP_DIR) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAG) $(LIB) $^ -o $@

clean: clean_dep clean_obj

fclean: clean clean_bin

re: fclean
	@make all

####

clean_dep:
	rm -rf $(DEP_DIR)

clean_obj:
	rm -rf $(OBJ_DIR)

clean_bin:
	rm -f $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(DEP_DIR):
	@mkdir -p $(DEP_DIR)

$(OBJ_DIR)%.o:	%.$(SRC_EXT)
	@mkdir -p $(OBJ_DIR)$(dir $<)
	@mkdir -p $(DEP_DIR)$(dir $<)
	$(CC) $(FLAG) -MMD -MP -MF $(DEP_DIR)$*.d -c $< -o $@

####

-include $(DEP)

.PHONY: all clean fclean re