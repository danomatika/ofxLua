
SWIG = swig

SRC_DIR = ../src
OF_HEADERS = ../../../libs/openFrameworks

CFLAGS = -I$(OF_HEADERS)
CXXFLAGS = $(CFLAGS)

.PHONY: bindings clean

bindings:
	$(SWIG) -c++ -lua -fcompact -fvirtual $(CXXFLAGS) openFrameworks.i
	for i in *.cxx; do mv $$i $${i%%.cxx}.cpp; done
	mv *.cpp $(SRC_DIR)

debug:
	$(SWIG) -c++ -lua -debug-lsymbols $(CXXFLAGS) openFrameworks.i > debug.txt
	rm -f *.cxx

clean:
	rm -f $(SRC_DIR)/*_wrap.cpp
	rm -f debug.txt
