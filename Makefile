NAME		= PmergeMe
CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98

DEQUE		= $(NAME)_deque
VECTOR		= $(NAME)_vector
LIST		= $(NAME)_list
SORT		= $(NAME)_sort

SRCS_VECTOR	= main_vector.cpp merge_insert_vector.cpp
SRCS_DEQUE	= main_deque.cpp merge_insert_deque.cpp
SRCS_LIST	= main_list.cpp merge_insert_list.cpp
SRCS_SORT	= main_sort.cpp
SRCS_MAIN	= PmergeMe.cpp

OBJ_DIR		= obj/
OBJS_VECTOR	= $(addprefix $(OBJ_DIR), $(SRCS_VECTOR:.cpp=.o))
OBJS_DEQUE	= $(addprefix $(OBJ_DIR), $(SRCS_DEQUE:.cpp=.o))
OBJS_LIST	= $(addprefix $(OBJ_DIR), $(SRCS_LIST:.cpp=.o))
OBJS_SORT	= $(addprefix $(OBJ_DIR), $(SRCS_SORT:.cpp=.o))
OBJS_MAIN	= $(addprefix $(OBJ_DIR), $(SRCS_MAIN:.cpp=.o))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(VECTOR): $(OBJS_VECTOR)
	$(CXX) $(CXXFLAGS) $(OBJS_VECTOR) -o $(VECTOR)

$(DEQUE): $(OBJS_DEQUE)
	$(CXX) $(CXXFLAGS) $(OBJS_DEQUE) -o $(DEQUE)

$(LIST): $(OBJS_LIST)
	$(CXX) $(CXXFLAGS) $(OBJS_LIST) -o $(LIST)

$(SORT): $(OBJS_SORT)
	$(CXX) $(CXXFLAGS) $(OBJS_SORT) -o $(SORT)

$(NAME): $(VECTOR) $(DEQUE) $(LIST) $(SORT) $(OBJS_MAIN)
	$(CXX) $(CXXFLAGS) $(OBJS_MAIN) -o $(NAME)

clean:
	rm -rf $(OBJS_DEQUE) $(OBJS_VECTOR) $(OBJS_SORT) $(OBJS_MAIN) $(VECTOR).out $(DEQUE).out $(SORT).out

fclean: clean
	rm -rf $(OBJ_DIR) $(NAME) $(VECTOR) $(DEQUE) $(SORT)

re: fclean all

.PHONY: all clean fclean re
