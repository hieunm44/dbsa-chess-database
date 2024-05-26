EXTENSION    = chess
MODULES      = chess
DATA         = chess--1.0.sql chess.control

PG_CONFIG   ?= pg_config
PGXS         = $(shell $(PG_CONFIG) --pgxs)

MODULE_big = chess
OBJS = chess.o

PG_CPPFLAGS = $(shell python3.11-config --cflags)
SHLIB_LINK = $(shell python3-config --embed --ldflags)

include $(PGXS)