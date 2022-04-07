library:main.o bookmanagement.o  lo_st.o library.o myutility.o show.o login_register.o
	gcc -std=c99 -Wall -o $@ $^
.c.o:
	gcc -std=c99 -Wall -c $<
clean:
	rm -rf *.o library