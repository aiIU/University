cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(Worker)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(WORKER_HEADERS_QT
	worker.h)

set(WORKER_HEADERS
	stdafx.h
	${WORKER_HEADERS_QT})