# Makefile for server client

# Parameters

CLIENT = named_pipes_client
SERVER = named_pipes_server

TARGETS_SERVER = server.c
TARGETS_CLIENT = client.c

OBJECTS_CLIENT = $(TARGETS_CLIENT.c:%.c=%.o)
OBJECTS_SERVER = $(TARGETS_SERVER.c:%.c=%.o)

COMPILER = gcc

# Compiler Flags
CFLAGS += -g

# Targets

all : $(CLIENT) $(SERVER)

$(CLIENT) : $(OBJECTS_CLIENT)
	$(COMPILER) -o $(CLIENT) $(TARGETS_CLIENT)

$(SERVER) : $(OBJECTS_SERVER)
	$(COMPILER) -o $(SERVER) $(TARGETS_SERVER)



