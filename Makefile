bins=constexpr_fun if_initializer nested_namespace structured_binding template_arg_deduction if_constexpr variant any template_auto fold_expr rvo_mandatory inline_variable string_view optional invoke filesystem byte parallel
all: $(bins)
clean:
	rm -f $(bins) *.o

CFLAGS:=-std=c++17 -pthread

filesystem: filesystem.cpp
	c++ $(CFLAGS) filesystem.cpp -o filesystem -lstdc++fs

%: %.cpp
	g++ $(CFLAGS) -g $^ -o $@

