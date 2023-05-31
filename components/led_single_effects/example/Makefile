SRC = $(wildcard ../*.c)
INC = ../
INC += ./

OUTPUT = build

all: $(OUTPUT)
	gcc $(SRC) main.c $(addprefix -I,$(INC)) -o $(OUTPUT)/main

$(OUTPUT):
	mkdir -p $@

clean:
	rm -R -f build