import os, sys
import argparse
from scipy.stats import levene, ks_2samp
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

#WINDOWS_FOLDERS = [".\\antidebugging_research_windows_data\\", ".\\antidebugging_research_windows_data2\\",]
WINDOWS_FOLDER = ".\\antidebugging_research_windows_data\\"
LINUX_INTEL_FOLDER = ".\\antidebugging_research_linux_intel_data\\"
LINUX_ARM_FOLDER = ".\\antidebugging_research_linux_arm_data\\"

class AntiDebuggingModel():
    """Wrapper object for model information."""
    def __init__(self, log_file=None, data_frame=None, os_arch=None, pvalue=None):
        self.log_file = log_file[:log_file.index('.')]
        self.os_arch = os_arch
        self.data_frame = data_frame
        self.pvalue = pvalue

    def __repr__(self):
        return f"[AntiDebuggingModel({self.os_arch}): log: {self.log_file}, pvalue: {self.pvalue}]"

    def __lt__(self, other):
        return self.pvalue < other.pvalue

    def __equal__(self, other):
        return ((self.log_file == other.log_file) and (self.os_arch == other.os_arch))

def getdffiles(directory=None):
    # Get all DataFrame files in current directory
    if directory is None:
        directory = os.getcwd()
    dir_list = os.listdir(directory)
    df_list = []
    for f in dir_list:
        if f.endswith(".df"):
            df_list.append(f) 
    return df_list

def main():
    # Read test data from argument
    parser = argparse.ArgumentParser(usage="Anti-Debugging Performance Framework Artifact.\n\nProvide a file with comma-separated values which represent microseconds of execution time for program under evaluation.")
    parser.add_argument('-f',"--file", type=str, required=True, help="Provide file name of CSV data file to be evaluated.")
    parser.add_argument('-a', '--arch', type=str, choices=["all", "windows", "linux-intel", "linux-arm"], default="all", help="Select the OS/Architecture pair to evaluate the test data. Default='all'.")
    args = parser.parse_args()

    # Validate arguments - must provide a file, file must not be empty, file must be readable as csv
    # argument for OS/arch (windows, linux-intel, linux-arm, all) -- other values are invalid
    with open(args.file, "r") as f:
        test_data = pd.read_csv(f)

    # Create DF from provided data (make column Microseconds)
    test_data.columns = ['Microseconds']

    # Read all DataFrames into memory based on os/arch argument
    model_data_list = []
    if args.arch in ("windows", "all"):
        df_list = getdffiles(WINDOWS_FOLDER) #read in windows .df files
        for f in df_list:
            with open(WINDOWS_FOLDER+f, "r") as temp:
                temp_obj = AntiDebuggingModel(f, pd.read_csv(temp), 'windows', 0)
                model_data_list.append(temp_obj)

    if args.arch in ("linux-intel", "all"):
        df_list = getdffiles(LINUX_INTEL_FOLDER) #read in linux-intel .df files
        for f in df_list:
            with open(LINUX_INTEL_FOLDER+f, "r") as temp:
                temp_obj = AntiDebuggingModel(f, pd.read_csv(temp), 'linux-intel', 0)
                model_data_list.append(temp_obj)

    if args.arch in ("linux-arm", "all"):
        df_list = getdffiles(LINUX_ARM_FOLDER) #read in linux-arm .df files
        for f in df_list:
            with open(LINUX_ARM_FOLDER+f, "r") as temp:
                temp_obj = AntiDebuggingModel(f, pd.read_csv(temp), 'linux-arm', 0)
                model_data_list.append(temp_obj)

    # For every DF in memory, conduct test with provided data from file
    winner_models = []
    for model in model_data_list:
        result = levene(test_data['Microseconds'].tolist(), model.data_frame['Microseconds'].tolist(), center='median')
        model.pvalue = result.pvalue
        if result.pvalue > 0.05:
            winner_models.append(model)
        #winner_models.append(model)


    # Create list of tests that fail to reject the null hypothesis for Levene test
    print(sorted(winner_models, reverse=True)) #sort by highest pvalue


if __name__ == "__main__":
    main()