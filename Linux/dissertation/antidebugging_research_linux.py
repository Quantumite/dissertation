from re import X
import sys, os
import argparse
import pandas as pd
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt

# Globals
BASE_TEST = "base_test.txt"
WINDOWS_API_TEST = "linux_api_test.txt"
CODE_OBFUSCATION_TEST = "code_obfuscation_test.txt"
DEBUG_REGISTERS_TEST = "debug_registers_test.txt"
MEMORY_ENCRYPTION_TEST = "memory_encryption_test.txt"
PARENT_PROCESS_TEST = "parent_process_test.txt"
SELFDEBUGGING_TEST = "selfdebugging_test.txt"
TIMING_ANALYSIS_TEST = "timing_analysis_test.txt"

def generate_data(verbose=False):
    if verbose:
        print("Beginning Data Generation for (Linux) AntiDebugging Research...\n")
    if verbose:
        print("Starting Base Test...\n")
    os.system(f"./LinuxAntiDebuggingResearch b > {BASE_TEST}")
    if verbose:
        print("Starting Windows API Test...\n")
    os.system(f"./LinuxAntiDebuggingResearch a > {WINDOWS_API_TEST}")
    if verbose:
        print("Starting Code Obfuscation Test...\n")
    os.system(f"./LinuxAntiDebuggingResearch c > {CODE_OBFUSCATION_TEST}")
    if verbose:
        print("Starting Debug Registers Test...\n")
    os.system(f"./LinuxAntiDebuggingResearch d > {DEBUG_REGISTERS_TEST}")
    if verbose:
        print("Starting Memory Encryption Test...\n")
    os.system(f"./LinuxAntiDebuggingResearch m > {MEMORY_ENCRYPTION_TEST}")
    if verbose:
        print("Starting Parent Process Test...\n")
    os.system(f"./LinuxAntiDebuggingResearch p > {PARENT_PROCESS_TEST}")
    if verbose:
        print("Starting Self-debugging Test...\n")
    os.system(f"rm -f {SELFDEBUGGING_TEST} && touch {SELFDEBUGGING_TEST}")
    for i in range(1000000):
        os.system(f"./LinuxAntiDebuggingResearch s >> {SELFDEBUGGING_TEST}")
    if verbose:
        print("Starting Timing Analysis Test...\n")
    os.system(f"./LinuxAntiDebuggingResearch t > {TIMING_ANALYSIS_TEST}")
    if verbose:
        print("Data generation Completed")


def process_data(verbose=False):
    file_series_array = [BASE_TEST, WINDOWS_API_TEST, CODE_OBFUSCATION_TEST, DEBUG_REGISTERS_TEST, MEMORY_ENCRYPTION_TEST, PARENT_PROCESS_TEST, SELFDEBUGGING_TEST, TIMING_ANALYSIS_TEST]
    
    for fn in file_series_array:
        data = []
        with open(fn,'r') as f:
            for line in f:
                try:
                    if '(ns)' in line:
                        data.append(int(line.split(' ')[3].strip()[:-4]))
                except:
                    continue
            s = pd.Series(data, name=f"{fn.split('.')[0]}")
        print(s)
        s.describe()
        s.to_csv(path_or_buf=f"{fn.split('.')[0]}.csv", index=False)

def generate_visualizations(verbose=False):
    #file_series_array = [BASE_TEST, WINDOWS_API_TEST, CODE_OBFUSCATION_TEST, MEMORY_ENCRYPTION_TEST, PARENT_PROCESS_TEST, SELFDEBUGGING_TEST, TIMING_ANALYSIS_TEST]
    file_series_array = [MEMORY_ENCRYPTION_TEST, PARENT_PROCESS_TEST, SELFDEBUGGING_TEST, TIMING_ANALYSIS_TEST]
    for fn in file_series_array:
        s = pd.read_csv(f"{fn.split('.')[0]}.csv", dtype="int64")
        s = s[1:-1]
        s_filtered = s[np.abs(stats.zscore(s)) < 3]
        print(s_filtered.describe())

        #histogram
        bins = int(s_filtered.max().max() - s_filtered.min().min())
        ax = s_filtered.plot.hist(bins=bins)
        ax.set_xlabel("Nanoseconds")
        plt.show()

def main():
    arg_parse = argparse.ArgumentParser()
    arg_parse.add_argument('-g', '--generate-data', action='store_true') 
    arg_parse.add_argument('-p', '--process-data', action='store_true')
    arg_parse.add_argument('-z', '--generate-visualizations', action='store_true')
    arg_parse.add_argument('-v', '--verbose', action='store_true')
    args = arg_parse.parse_args()


    if args.generate_data:
        generate_data(verbose=args.verbose)

    if args.process_data:
        process_data(verbose=args.verbose)

    if args.generate_visualizations:
        generate_visualizations(verbose=args.verbose)



if __name__ == '__main__':
    main()
