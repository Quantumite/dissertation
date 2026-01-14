import os
import statistics
from scipy.stats import ttest_ind, levene, kruskal #ANOVA one_way test, independent t-test, levene
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import numpy
import json

WINDOWS_PLOT_CONFIG = {
    "BaseTest.log": {
        "title": "Base Test",
        "binwidth": 100,
        "binrange": (0,5000)
    },
    "checkremotedebuggerpresent.log": {
        "title": "CheckRemoteDebuggerPresent Test",
        "binwidth": 100,
        "binrange": (0,6000)
    },
    "closehandle.log": {
        "title": "CloseHandle Test",
        "binwidth": 100,
        "binrange": (0,6000)
    },
    "codechecksum.log": {
        "title": "Code Checksum Test",
        "binwidth": 100,
        "binrange": (0,5000)
    },
    "codeobfuscation.log": {
        "title": "Code Obfuscation Test",
        "binwidth": 1000,
        "binrange": (0,100000)
    },
    "csrgetprocessid.log": {
        "title": "CsrGetProcessID Test",
        "binwidth": 100,
        "binrange": (0,5000)
    },
    "debugregisters.log": {
        "title": "Debug Registers Test",
        "binwidth": 100,
        "binrange": (0,6000)
    },
    "enumprocess.log": {
        "title": "Process Enumeration Test",
        "binwidth": 100000,
        "binrange": (0,5000000)
    },
    "eventpairhandles.log": {
        "title": "Event Pair Handle Test",
        "binwidth": 100,
        "binrange": (0,4000)
    },
    "getlocaltime.log": {
        "title": "GetLocalTime Test",
        "binwidth": 100,
        "binrange": (0,6000)
    },
    "getsystemtime.log": {
        "title":"GetSystemTime Test",
        "binwidth": 100,
        "binrange": (0,6000)
    },
    "gettickcount.log": {
        "title":"GetTickCount Test",
        "binwidth": 100,
        "binrange": (0,6000)
    },
    "guardpage.log": {
        "title": "Guard Page Test",
        "binwidth": 10000,
        "binrange": (0,2000000)
    },
    "heapflag.log": {
        "title": "Heap Flag Test",
        "binwidth": 50,
        "binrange": (0,5000)
    },
    "int2d.log": {
        "title":"INT 0x2d Test",
        "binwidth": 10,
        "binrange": (0,1000)
    },
    "int3.log": {
        "title":"INT3 Test",
        "binwidth": 50,
        "binrange": (0,6000)
    },
    "int3scan.log": {
        "title":"INT3 Scanning Test",
        "binwidth": 10,
        "binrange": (0,2000)
    },
    "isdebuggerpresent.log": {
        "title":"IsDebuggerPresent Test",
        "binwidth": 100,
        "binrange": (0,5000)
    },
    "memoryencryption.log": {
        "title": "Memory Encryption Test",
        "binwidth": 1000,
        "binrange": (0,1000000)
    },
    "ntglobalflag.log": {
        "title":"NtGlobalFlag Test",
        "binwidth": 100,
        "binrange": (0,5000)
    },
    "ntqueryinformationprocess.log": {
        "title":"NtQueryInformationProcess Test",
        "binwidth": 100,
        "binrange": (0,6000)
    },
    "ntqueryobject.log": {
        "title":"NtQueryObject Test",
        "binwidth": 100,
        "binrange": (0,100000)
    },
    "ntqueryperformancecounter.log": {
        "title":"NtQueryPerformanceCounter Test",
        "binwidth": 100,
        "binrange": (0,15000)
    },
    "ntsetdebugfilterstate.log": {
        "title":"NtSetDebugFilterState Test",
        "binwidth": 100,
        "binrange": (0,8000)
    },
    "ntsetinformationthread.log": {
        "title":"NtSetInformationThread Test",
        "binwidth": 100,
        "binrange": (0,12000)
    },
    "outputdebugstring.log": {
        "title":"OutputDebugString Test",
        "binwidth": 100,
        "binrange": (0,8000)
    },
    "parentprocess.log": {
        "title":"Parent Process Test",
        "binwidth": 10000,
        "binrange": (0,10000000)
    },
    "rdtsc.log": {
        "title":"RDTSC Test",
        "binwidth": 100,
        "binrange": (0,12000)
    },
    "selfdebugging.log": {
        "title":"Self-Debugging Test",
        "binwidth": 10000,
        "binrange": (0,10000000)
    },
    "timegettime.log": {
        "title":"timeGetTime Test",
        "binwidth": 100,
        "binrange": (0,6000)
    },
    "trapflag.log": {
        "title":"Trap Flag Test",
        "binwidth": 10,
        "binrange": (0,1500)
    },
    "unhandledexceptionfilter.log": {
        "title":"UnhandledExceptionFilter Test",
        "binwidth": 100,
        "binrange": (0,15000)
    }
}

with open("windows_intel_plot_config.json","w") as f:
    f.write(json.dumps(WINDOWS_PLOT_CONFIG))
quit()

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
    local_data = data[10:]
    df = pd.DataFrame(local_data)
    df.columns = ['Microseconds']
    #sns.histplot(df, x="Microseconds", binrange=(0,5000), binwidth=100).set_title(title)
    sns.histplot(
        df, 
        x="Microseconds",
        binwidth=WINDOWS_PLOT_CONFIG[log]['binwidth'],
        binrange=WINDOWS_PLOT_CONFIG[log]['binrange']).set_title(
            WINDOWS_PLOT_CONFIG[log]['title']
        )
    plt.show()


#Setup data visualization
sns.set_theme()

#Get base data
base_log = "basetest.log"
base_data = parse_log_files(base_log)
base_data = base_data[10:]
df = pd.DataFrame(base_data)
df.columns = ['Microseconds']
print(df)
sns.histplot(
    df, 
    x="Microseconds", 
    binrange=WINDOWS_PLOT_CONFIG['BaseTest.log']['binrange'], 
    binwidth=WINDOWS_PLOT_CONFIG['BaseTest.log']['binwidth']).set_title(
        WINDOWS_PLOT_CONFIG['BaseTest.log']['title']
    )
plt.show()

log_list = getlogfiles(os.getcwd())
for log in log_list:
    data = parse_log_files(log)
    print(log)
    #print("One-way ANOVA Test: ")
    #print(f_oneway(base_data, data[10:]))
    print("Kruskal Test: ")
    print(kruskal(base_data, data[10:]))
    print("Independent t-test: ")
    print(ttest_ind(base_data, data[10:], equal_var=False, alternative="less"))
    print("Levene Test: ")
    print(levene(base_data, data[10:], center='median')) #heavily-skewed distributions, use median 
    print("Quartiles: ")
    min, quartile, median, three_quartile, max = numpy.quantile(data[10:], [0,0.25,0.5,0.75,1])
    print(f"Min: {min}\n25%: {quartile}\n50%: {median}\n75%: {three_quartile}\nMax: {max}")
    make_plot(data, log)