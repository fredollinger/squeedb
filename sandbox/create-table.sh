#!/bin/bash

#./squee-create-table Employees First_Name 2 Last_Name 2 Age 0 Hourly_Rate 1 file.db
lldb -- ./squee-create-table Employees First_Name CHAR Last_Name CHAR Age INT Hourly_Rate FLOAT file.db

# Ideally we should have:

# ./squeectl CREATE TABLE Employees ( \
# First_Name CHAR,   \
# Last_Name CHAR,    \
# Age INT,           \
# Hourly_Rate FLOAT, \
# ) \
# file.db
