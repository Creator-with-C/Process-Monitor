A lightweight, high-performance Windows CLI process monitor built entirely with the native Windows API (WinAPI), tracking CPU, RAM, Disk I/O, and thread information while saving monitoring results to log files.<br>

The application scans running processes and captures resource usage, disk I/O activity, and thread information. The collected data can be used for monitoring, debugging, and basic performance analysis.<br>

1)Features<br>
2)Monitor running Windows processes<br>
3)Collect CPU usage<br>
4)Collect RAM / memory usage<br>
5)Collect Disk I/O information<br>
6)Monitor process threads<br>
7)Record thread IDs and priorities<br>
8)Save monitoring results to log files<br>
9)Command-line interface (CLI)<br>
10)Lightweight and designed for Windows<br>

Collected Information<br>
For each monitored process, the application can record information:<br>

1)CPU Usage:<br>
  Shows the CPU utilization of the monitored process.<br>
2)Memory Usage:<br>
  Shows the amount of memory currently used by the process and its percentage of total available      memory.<br>
3)Disk I/O:<br>
  The monitor records disk I/O activity performed by the process, including:<br>
  3a)Read operations<br>
  3b)Read bytes<br>
  3c)Write operations<br>
  3d)Write bytes<br>
  3e)Other I/O operations<br>
  3f)Other I/O bytes<br>
4)Thread Information:<br>
 The application also collects information about threads belonging to the monitored process.<br>
 For each thread, the monitor records:<br>
  4a)Thread ID<br>
  4b)Base Priority<br>
  4c)Delta Priority<br>

Example Output<br>
A typical monitoring result may look like:<br>

CPU usage:0.50%<br>

RAM usage:16.48 MB(0.2069%)<br>

DISK I/O information:<br>
Read Operation:1<br>
Read Operation Byte:60<br>
Write Operation:0<br>
Write Operation Bytes:0<br>
Other Operation:835<br>
Other Operation Bytes:41543<br>

Tread ID=0x00001828<br>
Base Priority=8<br>
Delta Priority=0<br>

Tread ID=0x00001EF4<br>
Base Priority=8<br>
Delta Priority=0<br>

Purpose:<br>
The main purpose of this project is to provide a lightweight command-line tool for inspecting the
behavior and resource consumption of Windows processes.<br>

Platform:<br>
This application is designed for: Windows<br>

Project Status:<br>
This project is currently under development.<br>

WARING: the log file it truncates every time the monitor runs if you want to keep the file rename it.<br>

Author:<br>
Creator-with-C
