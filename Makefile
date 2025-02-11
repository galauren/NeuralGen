NAME     =      Matrix.exe


CC       =      cc
CFLAGS   =      -Wall -Wextra -Werror 
DFLAGS   =      -g3
SFLAGS   =      -fsanitize=address

HEADER_P =      ./includes
HEADER_N =      matix.h \
				layer.h

HEADER   =      $(HEADER_P)/$(HEADER_N)

SRC_P =			./srcs
SRC_N =			matrix_op.c \
				matrix_create.c \
				layer.c

SRC_NAME   =      $(addprefix $(SRC_P)/, $(SRC_N))

OBJ_PATH =      ./.objs
DEP_PATH =      ./.deps
OBJ      =      $(patsubst $(SRC_P)/%.c,$(OBJ_PATH)/%.o,$(SRC_NAME))
DEP      =      $(patsubst %.o,$(DEP_PATH)/%.d,$(OBJ))

-include $(DEP)

COLOR = \e[38;5;140m
RESET = \e[0m


$(OBJ_PATH)/%.o : $(SRC_P)/%.c
	@mkdir -p $(OBJ_PATH) $(DEP_PATH)
	@$(CC) $(CFLAGS) -MMD -I$(HEADER_P) -o $@ -c $<
	@mv $(@:.o=.d) $(DEP_PATH)/
	@printf "\n#        $(COLOR)Compiling: \e[1;37m%-41s\e[1;32m✔\$(RESET)" "$<"
	@printf "\n             \
						$(COLOR)Compiled √\e[1;0m $(RESET)\n"


###############################
#    CREATION  DE FICHIERS    #
###############################

all : header $(NAME) bottom

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@
	@echo "       \e[1;32mBuild completed successfully.\e[1;0m"


debug : $(OBJ)
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJ) -o $@
	@echo "       \e[1;32mDebug Mode successfully activated.\e[1;0m"

sanitize : $(OBJ)
	@$(CC) $(CFLAGS) $(DFLAGS) $(SFLAGS) $(OBJ) -o $@
	@echo "       \e[1;32mDebug Mode successfully activated.\e[1;0m"


###############################
#        BEL AFFICHAGE        #
###############################
clear :
		@printf "\e[2J\e[H"

bottom :
		@printf "$(COLOR)#                                                             #\n"
		@printf "#                            \e[1;36mDONE\e[0m$(COLOR)                             #\n"
		@printf "#                                                             #\n"
		@printf "###############################################################$(RESET)\n\n"

header : clear
		@printf "$(COLOR)###############################################################\n"
		@printf "#                                                             #\n"
		@printf "#                         \e[1;36mMATRIX.EXE\e[0m$(COLOR)                          #\n"
		@printf "#                                                             #\n"
		@printf "###############################################################$(RESET)\n"

###############################
#   DESTRUCTION DE FICHIERS   #
###############################

.PHONY : clean fclean re save

clean :
	@rm -rf $(OBJ_PATH) $(DEP_PATH)
	@echo "\e[1;33mObject files and dependencies removed.\e[1;0m"

fclean : clear clean
	@rm -f $(NAME)
	@echo "\e[1;31mExecutable removed.\e[1;0m"

re : fclean all

save : fclean
	@git add .
	@git commit -m "$(m)"
	@git push
	@echo "\e[1;34mCode saved to group repository.\e[1;0m"
