#!/usr/bin/env bash

#   CREATE TABLE table_name (
#     column1 datatype constraint,
#     column2 datatype constraint,
#     column3 datatype constraint,
#     ....
#   ); filename.db

# ./squee-create-table Employees First_Name CHAR Last_Name CHAR Age INT Hourly_Rate FLOAT file.db

#lldb -- \
./squeectl \
CREATE TABLE Employees \
\( "First Name" CHAR \
   "Last Name" CHAR \
    "Age" INT \
    "Hourly Rate" FLOAT \
\) \
file.db;

#lldb -- \
./squeectl \
CREATE TABLE Employees2 \
\( "First Name" CHAR \
   "Last Name" CHAR \
    "Age" INT \
    "Hourly Rate" FLOAT \
\) \
file.db;
