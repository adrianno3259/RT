CC=g++
INCLUDE=
DEBUG=
CPP_FLAGS=

#obtém a lista de arquivos .cpp
CPP_SOURCES= $(wildcard *.cpp)

# regra make all
all: rt

# linker
# rt -> executável final
# $(CPP_SOURCES:.cpp=.o) -> substitui na lista a extensão de .cpp para .o
# $@ -> target
# $^ -> dependências do target
rt: $(CPP_SOURCES:.cpp=.o)
	$(CC) -o $@ $^

# compilação
# compila os arquivos .cpp em arquivos.o
%.o: %.cpp
	$(CC) -c $< $(CPP_FLAGS) -o $@

clean:
	-rm -f *.o rt *~

# clean + make
# $(MAKE) chamada ao comando make de dentro do Makefile
remake:
	$(MAKE) clean
	$(MAKE)