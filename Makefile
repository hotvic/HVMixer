CXX=g++ -g
LIBS=gtkmm-3.0

SRCDIR=src
SRCS := hvmicer.cpp settings.cpp main.cpp
OBJS := hvmixer.o settings.o main.o
TARGET=hvmixer

.PHONY : clean all

$(TARGET) : $(OBJS)
	$(CXX) `pkg-config --libs --cflags $(LIBS)` -o $@ $^

%.o : $(SRCDIR)/%.cpp
	$(CXX) -c `pkg-config --cflags --libs $(LIBS)` $< -o $@

clean :
	rm -rf $(OBJS) $(TARGET)

all : $(TARGET)
