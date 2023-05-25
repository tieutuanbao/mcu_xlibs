SRC = $(wildcard ../*.c)
INC = ../

OUTPUT = build

all: $(OUTPUT)
	gcc $(SRC) main.c -I$(INC) -o $(OUTPUT)/main

$(OUTPUT):
	mkdir -p $@

clean:
	rm -R build