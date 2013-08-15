CXXFLAGS = -MD -g -std=c++11 -Icontrol -Wall -Wextra -Werror

app = euler

units = euler \
    control/EulerCommandLine \
    control/EulerRegistry \
    control/EulerRunner \
    001/brute_force \
    001/closed_form

all: compile

compile: $(app)

clean:
	-rm $(app) *.o *.d */*.o */*.d

$(app): %: %.o $(units:=.o)
	g++ -g -std=c++11 $^ -o $@

-include $(units:=.d) $(apps:=.d)
