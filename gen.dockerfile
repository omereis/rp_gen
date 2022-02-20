FROM ubuntu:16.04

RUN apt -y update
RUN apt -y upgrade
RUN apt install -y g++ sdb libjsoncpp-dev gdb
RUN apt install -y vim man make

ENV HOME=/home/oe

WORKDIR /home/oe/sim

# COPY ./ $HOME
COPY ./ /home/oe/
COPY ./vimrc $HOME/.vimrc
# RUN mv vimrc .vimrc
