LDFLAGS =
CFLAGS = \
	-g -D_GNU_SOURCE \
	-I. -I./src \

CFLAGS += -Wall
CFLAGS += -O3
CXXFLAGS = $(CFLAGS)

LIST_SRC = src/list.o

TEST = tests/list_test.o \
	   $(LIST_SRC)

PROGRAMS = \
	list_test \

all: $(PROGRAMS)

list_test: $(TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so ./*/*.o ./*/*.so