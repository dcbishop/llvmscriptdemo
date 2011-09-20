all: scripttest bitcode/damage.bc

scripttest: src/scripttest.cpp obj/TestClass.o bitcode
	clang++ src/scripttest.cpp obj/TestClass.o -fpermissive -D __STDC_LIMIT_MACROS=1 -D __STDC_CONSTANT_MACROS=1 -o scripttest `llvm-config --cxxflags --ldflags --libs`

bitcode/damage.bc: scripts/damage.cpp
	clang++ -emit-llvm  -c scripts/damage.cpp -o bitcode/damage.bc

obj/TestClass.o: src/TestClass.cpp src/TestClass.hpp obj
	clang++ src/TestClass.cpp -c -o obj/TestClass.o

bitcode:
	mkdir bitcode

obj:
	mkdir obj

clean:
	rm -rf scripttest bitcode/*.bc obj/*.o
