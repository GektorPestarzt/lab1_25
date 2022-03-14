all:
	gcc main.c testing.c str_library.c menu.c error_treat.c -lreadline -D TESTS_ON
