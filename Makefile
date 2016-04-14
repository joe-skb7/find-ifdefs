CXX = g++
SOURCES = \
	  src/main.cpp \
	  src/params.cpp \
	  src/parser.cpp
APP = find-ifdef
CPPFLAGS = -std=c++11 -Wall -O2 -Iinclude
PREFIX ?= /usr/local

default: $(APP)

$(APP): $(SOURCES)
	$(CXX) $(CPPFLAGS) $(SOURCES) -o $(APP)

clean:
	-rm -f $(APP)

install: $(APP)
	install -m 0755 $(APP) $(PREFIX)/bin

.PHONY: default clean install
