DEPS = main.o baza.o zapis.o przedmioty.o oceny.o sortowanie.o sortowanie_p.o sortowanie_o.o

mydb:$(DEPS)
	gcc $(DEPS) -Wall --pedantic -o $@ 

%.o:%.c
	cc -c $^ -o $@

clean:
	rm -f main
	rm -f *.o

test-list: mydb
	./mydb baza.csv list_students
test-add-std: mydb
	./mydb baza.csv add student andrrzej mariusz 123123 56g@asd.pl 
test-add-crs: mydb
	./mydb baza.csv add course 1231 "jakis przedmiot" 1900Z
test-add-std-crs: mydb
	./mydb baza.csv add student_to_course 1274271 18321
test-set: mydb
	./mydb baza.csv set_grade 123131 312312 5 super_dziala
test-sr-std: mydb
	./mydb baza.csv student_average 000007
test-sort-crs: mydb
	./mydb baza.csv list_students_by_cours 1DE2103
test-sr-crs:mydb
	./mydb baza.csv course_average 1DA1245
test-ile-crs:mydb
	./mydb baza.csv course_grades 1DE2103
test-show-std: mydb
	./mydb baza.csv show students 
test-show-crs: mydb
	./mydb baza.csv show courses 
test-sort-std-dsc: mydb
	./mydb baza.csv sort students descending
test-sort-std-asc: mydb
	./mydb baza.csv sort students ascending
test-sort-crs-dsc: mydb
	./mydb baza.csv sort courses name descending
test-sort-crs-asc: mydb
	./mydb baza.csv sort courses name ascending
test-sort-crsid-asc: mydb
	./mydb baza.csv sort courses id ascending
test-sort-crsid-dsc: mydb
	./mydb baza.csv sort courses id descending
test-by-std: mydb
	./mydb baza.csv list_grades_by_student 000007
test-by-grd: mydb
	./mydb baza.csv grades_by_course 1DE2103
test-memory: mydb
	#valgrind ./mydb baza.csv list_students
	#valgrind ./mydb baza.csv add student andrrzej mariusz 123123 56g@asd.pl 
	#valgrind ./mydb baza.csv add course 1231 "jakis przedmiot" 1900Z
	#valgrind ./mydb baza.csv add student_to_course 1274271 18321
	#valgrind ./mydb baza.csv set_grade 123131 312312 5 super_dziala
	#valgrind ./mydb baza.csv student_average 000007
	#valgrind ./mydb baza.csv list_students_by_cours 1DE2103
	#valgrind ./mydb baza.csv course_average 000007
	#valgrind ./mydb baza.csv course_grades 1DE2103
	#valgrind ./mydb baza.csv show students 
	#valgrind ./mydb baza.csv show courses 
	valgrind ./mydb baza.csv list_students_by_cours 1DE2103