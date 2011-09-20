all: llvmscriptdemo bitcode/damage.bc

llvmscriptdemo: src/llvmscriptdemo.cpp obj/TestClass.o
	clang++ src/llvmscriptdemo.cpp obj/TestClass.o -fpermissive -D __STDC_LIMIT_MACROS=1 -D __STDC_CONSTANT_MACROS=1 -o llvmscriptdemo `llvm-config --cxxflags --ldflags --libs`

bitcode/TestClass.o.bc: bitcode
	clang++ -emit-llvm src/TestClass.cpp -c -o bitcode/TestClass.o.bc

bitcode/damage.bc.unlinked: scripts/damage.cpp bitcode
	clang++ -emit-llvm -c scripts/damage.cpp -o bitcode/damage.bc.unlinked
	
bitcode/damage.bc: bitcode/damage.bc.unlinked bitcode/TestClass.o.bc bitcode
	llvm-link bitcode/damage.bc.unlinked bitcode/TestClass.o.bc -o bitcode/damage.bc

obj/TestClass.o: src/TestClass.cpp src/TestClass.hpp obj
	clang++ src/TestClass.cpp -c -o obj/TestClass.o

bitcode:
	mkdir bitcode

obj:
	mkdir obj

clean:
	rm -rf llvmscriptdemo bitcode/*.bc obj/*.o bitcode/*.bc.unlinked bitcode/*.o.bc
