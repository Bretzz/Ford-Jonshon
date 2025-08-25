NAME		= PmergeMe
CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98

DEQUE		= $(NAME)_deque
VECTOR		= $(NAME)_vector

SRCS_VECTOR	= main_vector.cpp merge_insert_vector.cpp
SRCS_DEQUE	= main_deque.cpp merge_insert_deque.cpp

OBJ_DIR		= obj/
OBJS_VECTOR	= $(addprefix $(OBJ_DIR), $(SRCS_VECTOR:.cpp=.o))
OBJS_DEQUE	= $(addprefix $(OBJ_DIR), $(SRCS_DEQUE:.cpp=.o))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(VECTOR): $(OBJS_VECTOR)
	$(CXX) $(CXXFLAGS) $(OBJS_VECTOR) -o $(VECTOR)

$(DEQUE): $(OBJS_DEQUE)
	$(CXX) $(CXXFLAGS) $(OBJS_DEQUE) -o $(DEQUE)

$(NAME): $(VECTOR) $(DEQUE)


clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(OBJ_DIR) $(NAME) $(VECTOR) $(DEQUE)

re: fclean all

.PHONY: all clean fclean re
