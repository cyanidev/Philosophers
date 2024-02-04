#Program name
NAME = philo

#headers
HEADERS = -I ./includes/

#Sources (command 'find' to locate all source files in 'src' directory with
#the extension '.c')
SRCS = ${shell find ./src -iname "*.c"}

#Objects
OBJS = ${SRCS:.c=.o}

#Compiler flags
CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=leak #-fsanitize=thread 

#Compile
CC = gcc

#Force remove
RM = rm -f

#########################COLORS####################################

BLACK =	\033[0;30m
RED	=	\033[0;31m
GREEN =	\033[0;32m
YELLOW =	\033[0;33m
BLUE  =	\033[0;34m
MAGENTA =	\033[0;35m
CYAN =	\033[0;36m
LGRAY = \033[0;37m
DGRAY = \033[1;30m
LBLUE = \033[1;34m
LGREEN = \033[1;32m
LCYAN = \033[1;36m
LRED = \033[1;31m
LMAGENTA =\033[1;35m
LYELLOW = \033[1;33m
WHITE = \033[1;37m
RESET = \033[0m

###################################################################

#compiles program
all: ${NAME}

#Compiles the program by linking the object files with the libraries and outputting an ex file
${NAME}: ${OBJS}
		@printf "${LCYAN}Making......$@\n${RESET}"
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${HEADERS} ${LFLAGS}
		@printf "${GREEN}✨Complete✨${RESET}"

#Defines a rule for generating object files 
%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@ ${HEADERS}

#Removes all objects files
clean:
	@rm -fr ${OBJS}
	@printf "${LGREEN}Objects cleaned from ${WHITE}${CURDIR}${RESET}"

#calls the 'clean' rule also removes executable file
fclean: clean
	${RM} ${NAME}
	@printf "${LRED}Binary ${LYELLOW}${NAME} ${LRED}has been deleted....${RESET}"

#removes all and compiles program
re: fclean all

#Defines a list of targets that do not correspond to files(make will always 
#execute the recipes for these targets, even if there are files or directories
#with the same names)
.PHONY: all clean fclean re
