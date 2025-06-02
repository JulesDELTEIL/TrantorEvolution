##
## EPITECH PROJECT, 2025
## default_project_name
## File description:
## Dockerfile
##

FROM ubuntu:latest

RUN apt-get update

RUN apt-get install -y build-essential cmake git valgrind

########## CLONE PROJECT ##########
RUN git clone https://github.com/JulesDELTEIL/BaseProject.git

########## COMPILATION ##########
WORKDIR "/BaseProject/build"
RUN cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release && cmake --build .
WORKDIR "/BaseProject"
