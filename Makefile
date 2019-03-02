all: drive app unit

drive: intlist.h intlist.c ilist-test-basic.c
	gcc intlist.c ilist-test-basic.c -o drive

app: intlist.h intlist.c ilist-test-app.c
	gcc intlist.c ilist-test-app.c -o app

unit: intlist.h intlist.c ilist-test-unit.c
	gcc intlist.c ilist-test-unit.c -o unit

clean:
	@rm -f *.o drive app unit
  