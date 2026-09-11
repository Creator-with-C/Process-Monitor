A lightweight, high-performance Windows CLI process monitor built entirely with the native Windows API (WinAPI), tracking CPU, RAM, Disk I/O, and thread information while saving monitoring results to log files.

The application scans running processes and captures resource usage, disk I/O activity, and thread information. The collected data can be used for monitoring, debugging, and basic performance analysis.

1)Features
2)Monitor running Windows processes
3)Collect CPU usage
4)Collect RAM / memory usage
5)Collect Disk I/O information
6)Monitor process threads
7)Record thread IDs and priorities
8)Save monitoring results to log files
9)Command-line interface (CLI)
10)Lightweight and designed for Windows

Collected Information
For each monitored process, the application can record information:

1)CPU Usage:
  Shows the CPU utilization of the monitored process.
2)Memory Usage:
  Shows the amount of memory currently used by the process and its percentage of total available      memory.
3)Disk I/O:
  The monitor records disk I/O activity performed by the process, including:
  3a)Read operations
  3b)Read bytes
  3c)Write operations
  3d)Write bytes
  3e)Other I/O operations
  3f)Other I/O bytes
4)Thread Information:
 The application also collects information about threads belonging to the monitored process.
 For each thread, the monitor records:
  4a)Thread ID
  4b)Base Priority
  4c)Delta Priority

Example Output
A typical monitoring result may look like:

CPU usage:0.50%

RAM usage:16.48 MB(0.2069%)

DISK I/O information:
Read Operation:1
Read Operation Byte:60
Write Operation:0
Write Operation Bytes:0
Other Operation:835
Other Operation Bytes:41543

Tread ID=0x00001828
Base Priority=8
Delta Priority=0

Tread ID=0x00001EF4
Base Priority=8
Delta Priority=0

Purpose
The main purpose of this project is to provide a lightweight command-line tool for inspecting the behavior and resource consumption of Windows processes.

Platform
This application is designed for: Windows

Project Status
This project is currently under development.

Author
Creator-with-C
