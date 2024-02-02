# make file
# runing in single rule where all cpp and h file, we not need to mention target name in the make command in terminal .
#Demerit:but in the target Singlerule change one cpp will change all, so we create target program with multiple rules



#this is single rule the first line is Prerequisites the second line is the Command
msdscript: main.cpp cmdline.cpp cmdline.h
	c++ main.cpp cmdline.cpp -o msdscript


cmdline.o: cmdline.cpp cmdline.h
	c++ -c cmdline.cpp

main.o: main.cpp
	c++ -c main.cpp


#to delete derived files such as .o files
clean:
	rm -f *.o *.out msdscript

run: msdscript
	./msdscript
