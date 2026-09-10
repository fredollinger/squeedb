#!/usr/bin/env bash

#   CREATE TABLE table_name (
#     column1 datatype constraint,
#     column2 datatype constraint,
#     column3 datatype constraint,
#     ....
#   ); filename.db

# ./squee-create-table Employees First_Name CHAR Last_Name CHAR Age INT Hourly_Rate FLOAT file.db

# Both are valid
#lldb -- \
./squeectl \
CREATE TABLE Employees \
\( "First Name" CHAR \
   "Last Name" CHAR \
    "Age" INT \
    "Hourly Rate" FLOAT \
\) \
file.db;

#echo 
#$3./squeectl CREATE TABLE Employees \('First Name' CHAR\) file.db;
#echo 

# Test Invalid
#./squeectl CREATE TABLE Employees \("First Name" file.db;
