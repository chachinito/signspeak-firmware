ifeq ($(OS),Windows_NT)
	# TODO: Determine Arduino installation paths for Windows
	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
	else
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		endif
	endif
else
	UNAME := $(shell uname -s)

	ifeq ($(UNAME),Linux)
		ARDUINO := arduino
	endif

	ifeq ($(UNAME),Darwin)
		ARDUINO := /Applications/Arduino.app/Contents/MacOS/arduino
	endif
endif

FLAGS := --board arduino:avr:uno

ifdef PORT
	FLAGS += --port $(PORT)
endif

all: upload

verify:
	$(ARDUINO) --verify $(FLAGS) src/main.ino

upload:
	$(ARDUINO) --upload $(FLAGS) src/main.ino
