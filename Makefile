bins=constexpr_fun if_initializer nested_namespace structured_binding template_arg_deduction
all: $(bins)
clean:
	rm -f $(bins) *.o

%: %.cpp
	g++ -std=c++17 -g $^ -o $@

#if_initializer: if_initializer.cpp
#	g++ -std=c++17 $^ -o $@
#nested_namespace: nested_namespace.cpp
#	g++ -std=c++17 $^ -o $@
#structured_binding: structured_binding.cpp
#	g++ -std=c++17 $^ -o $@
#constexpr_fun: constexpr_fun.cpp
#	g++ -std=c++17 $^ -o $@
#template_arg_deduction: template_arg_deduction.cpp
#	g++ -std=c++17 $^ -o $@
