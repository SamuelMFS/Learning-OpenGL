#!/bin/sh

function config
{
	cmake -S . -B ./build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
	rm compile_commands.json
	ln -s build/compile_commands.json .
}

function build
{
	cmake --build ./build
}

function run
{
	./build/cheese
}
