import os, sys
import argparse
from scipy.stats import mannwhitneyu, levene #non parametric tests to measure mean, variance and median (respectively)
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import numpy
import json

#global plot config assigned after argparse
PLOT_CONFIG = {}

with open("linux_intel_plot_config.json", "r") as f1:
    LINUX_INTEL_PLOT_CONFIG = json.load(f1)

with open("windows_intel_plot_config.json","r") as f2:
    WINDOWS_INTEL_PLOT_CONFIG = json.load(f2)

with open("linux_arm_plot_config.json","r") as f3:
    LINUX_ARM_PLOT_CONFIG = json.load(f3)

def parse_log_files(filename=None):
    if filename is None:
        print("[!] No log name given.")
        return []
    
    with open(filename,"r") as f:
        text = f.readlines()

    data = []
    for line in text:
        value = line.split(',')[1]
        value = int(value.split(' ')[0])
        data.append(value)

    return data

def getlogfiles(directory=None):
    # Get all log files in current directory
    if directory is None:
        directory = os.getcwd()
    dir_list = os.listdir(directory)
    log_list = []
    for f in dir_list:
        if f.endswith(".log"):
            log_list.append(f) 
    return log_list

def make_plot(data, log):
    global PLOT_CONFIG
    local_data = data[10:]
    df = pd.DataFrame(local_data)
    df.columns = ['Microseconds']
    sns.histplot(
        df, 
        x="Microseconds",
        binwidth=PLOT_CONFIG[log]['binwidth'],
        binrange=PLOT_CONFIG[log]['binrange'],
        color="blue").set_title(
            PLOT_CONFIG[log]['title']
        )
    plt.show()


def main():
    global PLOT_CONFIG
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--directory", type=str, default=os.getcwd(), help="The directory to look for .log files to parse. Default is current working directory. Don't add trailing slash.")
    parser.add_argument("-a", "--arch", type=str, choices=["windows", "linux-intel", "linux-arm"], default=None, required=True, help="Determines the plot config to use for the data. Required.")
    parser.add_argument("-e", "--export", action='store_true', help="Export data (Pandas DataFrames) to CSV files ending in .df for tests with p-value under 0.05.")
    parser.add_argument("--export-all", action='store_true', help="Export all dataframes regardless of pvalue.")
    parser.add_argument("-s", "--skip", action='store_true', help="Skip making plots. Default=False.")
    args = parser.parse_args()
    
    if args.arch == "windows":
        PLOT_CONFIG = WINDOWS_INTEL_PLOT_CONFIG
    elif args.arch == "linux-intel":
        PLOT_CONFIG = LINUX_INTEL_PLOT_CONFIG
    elif args.arch == "linux-arm":
        PLOT_CONFIG = LINUX_ARM_PLOT_CONFIG
    else:
        print("[!] Invalid plot configuration. Exiting.")
        sys.exit(1)

    #Setup data visualization
    sns.set_theme()

    #Get base data
    base_log = "basetest.log"
    if args.arch == "linux-arm":
        base_log = "basetest_arm.log"
    base_data = parse_log_files(args.directory+"\\"+base_log)
    base_data = base_data[10:]
    df = pd.DataFrame(base_data)
    df.columns = ['Microseconds']

    if not args.skip:
        sns.histplot(
            df, 
            x="Microseconds", 
                binwidth=PLOT_CONFIG[base_log]['binwidth'],
                binrange=PLOT_CONFIG[base_log]['binrange'],
                color="blue").set_title(
                    PLOT_CONFIG[base_log]['title']
            )
        plt.show()

    log_list = getlogfiles(args.directory)
    for log in log_list:
        data = parse_log_files(args.directory+"\\"+log)
        print(log)
        #print("Kruskal Test: ")
        #print(kruskal(base_data, data[10:]))
        #print("Independent t-test: ")
        #print(ttest_ind(base_data, data[10:], equal_var=False, alternative="less"))
        print("Mann-Whitney U Test:")
        mannwhitneyu_result = mannwhitneyu(base_data, data[10:], alternative="less")
        print(mannwhitneyu_result)
        print("Levene Test: ")
        levene_result = levene(base_data, data[10:], center='median') #heavily-skewed distributions, use median 
        print(levene_result)
        print("Quartiles: ")
        min, quartile, median, three_quartile, max = numpy.quantile(data[10:], [0,0.25,0.5,0.75,1])
        print(f"Min: {min}\n25%: {quartile}\n50%: {median}\n75%: {three_quartile}\nMax: {max}")
        if (args.export and levene_result.pvalue < 0.05) or (args.export_all):
            data_df = pd.DataFrame(data[10:])
            data_df.columns = ['Microseconds']
            data_df.to_csv(f"{args.directory}\\{log}.df", index=False)
        if not args.skip:
            make_plot(data, log)

if __name__ == "__main__":
    main()