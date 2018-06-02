#################################################################################
#
# Makefile for smartTFT library and example
#
#     Copyright (C) 2018 Dreamshader (Dirk Schanz)
#	
#################################################################################
# This Makefile is part of my smartTFT project
#	git://github.com/dreamshader/smartTFT.git
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#################################################################################
#
CXX = g++
CC  = gcc
AR  = ar
#
CCDEBUG  = -g
CXXDEBUG = -g
#
CXXFLAGS = -Wall
CXXLIBSOFLAGS = -fPIC -shared 
#
SOURCEDIR = ../src
LIBSRC = $(SOURCEDIR)/serialConnection.cpp $(SOURCEDIR)/smartTFT.cpp
LIBOBJ = serialConnection.o smartTFT.o
SOLIBNAME = smartTFT.so
STATLIBNAME = smartTFT.a
#
#
all: lib-static lib-shared

lib-static:
	$(CXX) $(CXXFLAGS) -c $(LIBSRC)

lib-shared:
	$(CXX) $(CXXFLAGS) $(CXXLIBSOFLAGS) -c $(LIBSRC)
	$(CXX) -shared  -Wl,-soname,$(SOLIBNAME) -o $(SOLIBNAME) $(LIBOBJ)


#g++ -fPIC -shared myclass.cc -o myclass.so
#g++ class_user.cc -ldl -o class_user
#-Wall
#ar -cvq libctest.a ctest1.o ctest2.o
#ar -t libctest.a
#
#main: libshared.so main.o
    #$(CXX) -o main  main.o -L. -lshared
#
#libshared.so: shared.cpp
    #$(CXX) -fPIC -c shared.cpp -o shared.o
    #$(CXX) -shared  -Wl,-soname,libshared.so -o libshared.so shared.o
#
#clean:
    #$rm *.o *.so

