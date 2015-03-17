/*
 * llvmscriptdemp.cpp - Example LLVM 'script'. Integrates LLVM bitcode with
 * native C++.
 *
 * Written in 2011 by David C. Bishop <david@davidbishop.org>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <string>
#include <memory>
#include <iostream>
#include <limits.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
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
   LLVMContext context;
   string error;

   auto mb = MemoryBuffer::getFile("bitcode/damage.bc");
   if (!mb) {
      cout << "ERROR: Failed to getFile" << endl;
      return 0;
   }

   auto m = parseBitcodeFile(mb->get(), context);
   if(!m) {
      cout << "ERROR: Failed to load script file." << endl;
      return 0;
   }
   
   ExecutionEngine *ee = ExecutionEngine::create(m.get());

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
