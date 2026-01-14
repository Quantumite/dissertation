CC := g++
OBJECTS := research_timer.o base_test.o tracer_pid.o main.o print_usage.o timing_analysis.o code_obfuscation.o parent_process.o self_debugging.o memory_encryption.o debug_registers.o
OPTIONS := -O0


research_timer.o : research_timer.cpp research_timer.hpp
	$(CC) $(OPTIONS) -c -lrt -o research_timer.o research_timer.cpp

print_usage.o : PrintUsage.cpp PrintUsage.hpp
	$(CC) $(OPTIONS) -c -o print_usage.o PrintUsage.cpp

base_test.o : BaseTest.cpp BaseTest.hpp
	$(CC) $(OPTIONS) -c -o base_test.o BaseTest.cpp 

tracer_pid.o : IsTracerPidNonzero.cpp IsTracerPidNonzero.hpp
	$(CC) $(OPTIONS) -c -o tracer_pid.o IsTracerPidNonzero.cpp

timing_analysis.o : TimingAnalysis.cpp TimingAnalysis.hpp
	$(CC) $(OPTIONS) -c -o timing_analysis.o TimingAnalysis.cpp

code_obfuscation.o : CodeObfuscation.cpp CodeObfuscation.hpp
	$(CC) $(OPTIONS) -c -o code_obfuscation.o CodeObfuscation.cpp

debug_registers.o : DebugRegisters.cpp DebugRegisters.hpp
	$(CC) $(OPTIONS) -c -o debug_registers.o DebugRegisters.cpp

parent_process.o : ParentProcess.cpp ParentProcess.hpp
	$(CC) $(OPTIONS) -c -o parent_process.o ParentProcess.cpp

self_debugging.o : SelfDebugging.cpp SelfDebugging.hpp
	$(CC) $(OPTIONS) -c -o self_debugging.o SelfDebugging2.cpp

memory_encryption.o : MemoryEncryption.cpp MemoryEncryption.hpp
	$(CC) $(OPTIONS) -c -o memory_encryption.o MemoryEncryption2.cpp -lssl -lcrypto 

main.o : main.cpp
	$(CC) $(OPTIONS) -c -o main.o main.cpp

all : $(OBJECTS)
	$(CC) $(OBJECTS) $(OPTIONS) -L /usr/lib -I/usr/include -o LinuxAntiDebuggingResearch -lssl -lcrypto

clean : 
	rm -f *.o LinuxAntiDebuggingResearch
