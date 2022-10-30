FROM ubuntu:16.04

RUN apt -y update
RUN apt -y upgrade
RUN apt install -y g++ sdb libjsoncpp-dev gdb
RUN apt install -y vim man make

RUN apt update
RUN apt install -y wget
RUN apt install -y python3.5

#RUN cd /usr/src \
#	wget https://www.python.org/ftp/python/3.5.9/Python-3.5.9.tgz \
#	tar xzf Python-3.5.9.tgz
#	& cd Python-3.5.9
#	& ./configure --enable-optimizations
#	& make altinstall

ENV HOME=/home/oe

WORKDIR /home/oe/sim

# COPY ./ $HOME
COPY ./ /home/oe/
COPY ./vimrc.txt $HOME/.vimrc

RUN python3.5 /home/oe/get-pip.py
# RUN mv vimrc .vimrc
