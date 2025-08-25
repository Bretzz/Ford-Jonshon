NAME		= merge
CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98

SRCS		= main.cpp \
				merge_insert.cpp

OBJ_DIR		= obj/
OBJS		= $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJ_DIR)* -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(OBJ_DIR) $(NAME)

re: fclean all

.PHONY: all clean fclean re
