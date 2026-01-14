import os
import statistics
from scipy.stats import f_oneway #ANOVA one_way test


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

base_log = "basetest.log"
base_data = parse_log_files(base_log)
log_list = getlogfiles(os.getcwd())
for log in log_list:
    data = parse_log_files(log)
    print(log)
    print(f_oneway(base_data, data))
    input()
