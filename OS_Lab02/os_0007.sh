#!/bin/bash

if [[ $# -lt 1 ]]; then
    echo "parametrs not found"
    exit 1
fi

pid=$1
fd=$2

if ! [ -e "/proc/$pid/status" ]; then
    echo "pid=$pid process not found" 
    exit 1
fi

file_name=$(basename "$0")

ppid=$(awk '/PPid/ {print $2}' /proc/$pid/status)

if [[ -n "$fd" ]]; then
    echo "Name: $file_name"
    echo "Pid: $pid"
    echo "PPid: $ppid"
    ls -l /proc/$pid/fd | awk '{print "fd =", $9}'
elif [[ -n "$pid" ]]; then
    echo "Name: $file_name"
    echo "Pid: $pid"
    echo "PPid: $ppid"
fi


