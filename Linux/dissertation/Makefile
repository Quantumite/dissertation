CC := g++
AARCH64CC := aarch64-linux-gnu-g++-11
OBJECTS := log_file.o timing.o run_scanning_tests.o run_timing_tests.o run_misc_tests.o base_test.o tracer_pid.o main.o print_usage.o timing_analysis.o code_obfuscation.o parent_process.o self_debugging.o memory_encryption.o clock_test.o clock_gettime_test.o rdtsc_test.o int3_scan_test.o int3_test.o code_checksum_test.o enum_process_test.o run_exception_tests.o trap_flag_test.o base_function.o
AARCH64_OBJECTS := log_file_arm.o timing_arm.o run_scanning_tests_arm.o run_timing_tests_arm.o run_misc_tests_arm.o base_test_arm.o tracer_pid_arm.o main_arm.o print_usage_arm.o timing_analysis_arm.o code_obfuscation_arm.o parent_process_arm.o self_debugging_arm.o memory_encryption_arm.o int3_test_arm.o clock_test_arm.o clock_gettime_test_arm.o int3_scan_test_arm.o code_checksum_test_arm.o enum_process_test_arm.o run_exception_tests_arm.o trap_flag_test_arm.o rdtsc_test_arm.o base_function_arm.o
OPTIONS := -O0 -DINTEL
AARCH64OPTIONS := -O0 -DAARCH64

log_file.o : LogFile.cpp LogFile.hpp
	$(CC) $(OPTIONS) -c -o log_file.o LogFile.cpp

log_file_arm.o : LogFile.cpp LogFile.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o log_file_arm.o LogFile.cpp

base_function.o : BaseFunction.cpp BaseFunction.hpp
	$(CC) $(OPTIONS) -c -o base_function.o BaseFunction.cpp

base_function_arm.o : BaseFunction.cpp BaseFunction.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o base_function_arm.o BaseFunction.cpp

timing.o : Timing.cpp Timing.hpp
	$(CC) $(OPTIONS) -c -o timing.o Timing.cpp

timing_arm.o : TimingAarch64.cpp Timing.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o timing_arm.o TimingAarch64.cpp

print_usage.o : PrintUsage.cpp PrintUsage.hpp
	$(CC) $(OPTIONS) -c -o print_usage.o PrintUsage.cpp

print_usage_arm.o : PrintUsage.cpp PrintUsage.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o print_usage_arm.o PrintUsage.cpp

base_test.o : BaseTest.cpp BaseTest.hpp
	$(CC) $(OPTIONS) -c -o base_test.o BaseTest.cpp

base_test_arm.o : BaseTest.cpp BaseTest.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o base_test_arm.o BaseTest.cpp

tracer_pid.o : IsTracerPidNonzero.cpp IsTracerPidNonzero.hpp
	$(CC) $(OPTIONS) -c -o tracer_pid.o IsTracerPidNonzero.cpp

tracer_pid_arm.o : IsTracerPidNonzero.cpp IsTracerPidNonzero.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o tracer_pid_arm.o IsTracerPidNonzero.cpp

timing_analysis.o : TimingAnalysis.cpp TimingAnalysis.hpp
	$(CC) $(OPTIONS) -c -o timing_analysis.o TimingAnalysis.cpp

timing_analysis_arm.o : TimingAnalysis.cpp TimingAnalysis.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o timing_analysis_arm.o TimingAnalysis.cpp

code_obfuscation.o : CodeObfuscation.cpp CodeObfuscation.hpp
	$(CC) $(OPTIONS) -c -o code_obfuscation.o CodeObfuscation.cpp

code_obfuscation_arm.o : CodeObfuscation.cpp CodeObfuscation.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o code_obfuscation_arm.o CodeObfuscation.cpp

parent_process.o : ParentProcess.cpp ParentProcess.hpp
	$(CC) $(OPTIONS) -c -o parent_process.o ParentProcess.cpp

parent_process_arm.o : ParentProcess.cpp ParentProcess.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o parent_process_arm.o ParentProcess.cpp

self_debugging.o : SelfDebugging2.cpp SelfDebugging.hpp
	$(CC) $(OPTIONS) -c -o self_debugging.o SelfDebugging2.cpp

self_debugging_arm.o : SelfDebugging2.cpp SelfDebugging.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o self_debugging_arm.o SelfDebugging2.cpp

memory_encryption.o : MemoryEncryption2.cpp MemoryEncryption.hpp
	$(CC) $(OPTIONS) -c -o memory_encryption.o MemoryEncryption2.cpp -lssl -lcrypto 

memory_encryption_arm.o : MemoryEncryption2.cpp MemoryEncryption.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o memory_encryption_arm.o MemoryEncryption2.cpp -lssl -lcrypto 

clock_test.o : ClockTest.cpp ClockTest.hpp
	$(CC) $(OPTIONS) -c -o clock_test.o ClockTest.cpp

clock_test_arm.o : ClockTest.cpp ClockTest.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o clock_test_arm.o ClockTest.cpp

clock_gettime_test.o : ClockGetTimeTest.cpp ClockGetTimeTest.hpp
	$(CC) $(OPTIONS) -c -o clock_gettime_test.o ClockGetTimeTest.cpp

clock_gettime_test_arm.o : ClockGetTimeTest.cpp ClockGetTimeTest.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o clock_gettime_test_arm.o ClockGetTimeTest.cpp

int3_scan_test.o : Int3Scan.cpp Int3Scan.hpp
	$(CC) $(OPTIONS) -c -o int3_scan_test.o Int3Scan.cpp

int3_scan_test_arm.o : Int3Scan.cpp Int3Scan.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o int3_scan_test_arm.o Int3Scan.cpp

code_checksum_test.o : CodeChecksum.cpp CodeChecksum.hpp
	$(CC) $(OPTIONS) -c -o code_checksum_test.o CodeChecksum.cpp

code_checksum_test_arm.o : CodeChecksum.cpp CodeChecksum.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o code_checksum_test_arm.o CodeChecksum.cpp

rdtsc_test.o : RdtscTest.cpp RdtscTest.hpp
	$(CC) $(OPTIONS) -c -o rdtsc_test.o RdtscTest.cpp

rdtsc_test_arm.o : RdtscTest.cpp RdtscTest.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o rdtsc_test_arm.o RdtscTest.cpp

enum_process_test.o : EnumProcess.cpp EnumProcess.hpp
	$(CC) $(OPTIONS) -c -o enum_process_test.o EnumProcess.cpp

enum_process_test_arm.o : EnumProcess.cpp EnumProcess.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o enum_process_test_arm.o EnumProcess.cpp

int3_test.o : int3.cpp int3.hpp
	$(CC) $(OPTIONS) -c -o int3_test.o int3.cpp

int3_test_arm.o : int3.cpp int3.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o int3_test_arm.o int3.cpp

trap_flag_test.o : TrapFlag.cpp TrapFlag.hpp
	$(CC) $(OPTIONS) -c -o trap_flag_test.o TrapFlag.cpp

trap_flag_test_arm.o : TrapFlag.cpp TrapFlag.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o trap_flag_test_arm.o TrapFlag.cpp

run_misc_tests.o : RunMiscTests.cpp RunMiscTests.hpp
	$(CC) $(OPTIONS) -c -o run_misc_tests.o RunMiscTests.cpp

run_misc_tests_arm.o : RunMiscTests.cpp RunMiscTests.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o run_misc_tests_arm.o RunMiscTests.cpp

run_timing_tests.o : RunTimingTests.cpp RunTimingTests.hpp
	$(CC) $(OPTIONS) -c -o run_timing_tests.o RunTimingTests.cpp

run_timing_tests_arm.o : RunTimingTests.cpp RunTimingTests.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o run_timing_tests_arm.o RunTimingTests.cpp

run_scanning_tests.o : RunScanningTests.cpp RunScanningTests.hpp
	$(CC) $(OPTIONS) -c -o run_scanning_tests.o RunScanningTests.cpp

run_scanning_tests_arm.o : RunScanningTests.cpp RunScanningTests.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o run_scanning_tests_arm.o RunScanningTests.cpp

run_exception_tests.o : RunExceptionTests.cpp RunExceptionTests.hpp
	$(CC) $(OPTIONS) -c -o run_exception_tests.o RunExceptionTests.cpp

run_exception_tests_arm.o : RunExceptionTests.cpp RunExceptionTests.hpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o run_exception_tests_arm.o RunExceptionTests.cpp

main.o : main.cpp
	$(CC) $(OPTIONS) -c -o main.o main.cpp

main_arm.o : main.cpp
	$(AARCH64CC) $(AARCH64OPTIONS) -c -o main_arm.o main.cpp

all : $(OBJECTS) child
	$(CC) $(OBJECTS) $(OPTIONS) -L /usr/lib -I/usr/include -o LinuxAntiDebuggingResearch -lssl -lcrypto
	
arm : $(AARCH64_OBJECTS) child_arm
	$(AARCH64CC) $(AARCH64_OBJECTS) $(AARCH64OPTIONS) -L /usr/lib -I/usr/include -o LinuxAntiDebuggingResearch_arm -lssl -lcrypto

child : SelfDebugging_child.cpp
	$(CC) $(OPTIONS) -o self_debugging_child SelfDebugging_child.cpp

child_arm : SelfDebugging_child.cpp
	$(AARCH64CC) $(AARCH64OPTIONS) -o self_debugging_child_arm SelfDebugging_child.cpp

clean : 
	rm -f *.o LinuxAntiDebuggingResearch

clean-logs :
	rm -f *.log