bins=constexpr_fun if_initializer nested_namespace structured_binding template_arg_deduction if_constexpr variant any template_auto fold_expr inline_variable string_view optional invoke filesystem byte
all: $(bins)
clean:
	rm -f $(bins) *.o

filesystem: filesystem.cpp
	c++ -std=c++17 filesystem.cpp -o filesystem -lstdc++fs

%: %.cpp
	g++ -std=c++17 -g $^ -o $@

