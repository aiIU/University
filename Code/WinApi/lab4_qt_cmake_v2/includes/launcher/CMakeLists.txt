cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(Launcher)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(WORKER_HEADERS_QT
	LauncherGui.h)
	
set(LAUNCHER_HEADERS
	stdafx.h
	Launcher.h
	${WORKER_HEADERS_QT})
