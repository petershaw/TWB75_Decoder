CC = gcc
CFLAGS = -g -Wall -pedantic --std=gnu99 -DIGNOREINTESTS=1
LDFLAGS = -Lcu/ -lcu -DIGNOREINTESTS=1

OBJS = cu/cu.o \
	../src/ui/menu.o \
	menu/menuTest.o \
	lang/langTest.o \
	../src/control/cron.o \
	cron/cronTest.o \
    cron/timerTest.o \
	test.o 

all: test

test: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o test

.PHONY: all clean
