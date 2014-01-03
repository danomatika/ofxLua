
SWIG = swig

SRC_DIR = ../src
OF_HEADERS = ../../../libs/openFrameworks

CFLAGS = -I$(OF_HEADERS)
CXXFLAGS = $(CFLAGS)

.PHONY: bindings clean

bindings:
	$(SWIG) -c++ -lua -fcompact -fvirtual $(CXXFLAGS) openFrameworks.i
	mv *.cxx $(SRC_DIR)

clean:
	rm -f $(SRC_DIR)/*_wrap.cxx
