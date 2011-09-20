#include <string>
#include <memory>
#include <iostream>
#include <limits.h>

#include <llvm/LLVMContext.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
//#include <llvm/ModuleProvider.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/ExecutionEngine/JIT.h>
#include "llvm/ExecutionEngine/GenericValue.h"

using namespace std;
using namespace llvm;

#include "TestClass.hpp"

int main()
{
   TestClass tc;
   tc.setHealth(100);
   tc.printHealth();
   
   InitializeNativeTarget();
   llvm_start_multithreaded();
   LLVMContext context;
   string error;

   // TODO: Check MemoryBuffer got a file or it will segfault
   Module *m = ParseBitcodeFile(MemoryBuffer::getFile("bitcode/damage.bc"), context, &error);
   if(!m) {
      cout << "ERROR: Failed to load script file." << endl;
      return 0;
   }
   
   ExecutionEngine *ee = ExecutionEngine::create(m);

   // NOTE: Function names are mangled by the compiler.
   Function* init_func = ee->FindFunctionNamed("_Z9initilizev");
   if(!init_func) {
      cout << "ERROR: Failed to find 'initilize' function." << endl;
      return 0;
   }

   Function* attack_func = ee->FindFunctionNamed("_Z6attackP9TestClass");
   if(!attack_func) {
      cout << "ERROR: Failed to find 'attack' function." << endl;
      return 0;
   }

   typedef void (*init_pfn)();
   init_pfn initilize = reinterpret_cast<init_pfn>(ee->getPointerToFunction(init_func));
   if(!initilize) {
      cout << "ERROR: Failed to cast 'initilize' function." << endl;
      return 0;
   }

   initilize();
   cout << "Running attacking script..." << endl;

   typedef void (*attack_pfn)(TestClass*);
   attack_pfn attack = reinterpret_cast<attack_pfn>(ee->getPointerToFunction(attack_func));
   if(!attack) {
      cout << "ERROR: Failed to cast 'attack' function." << endl;
      return 0;
   }

   attack(&tc);
   
   tc.printHealth();
   delete ee;
}
