//homeguard-test.c
//tcc_out=/build/homeguard-test.exe
//tcc_run=1
//tcc_kill=1
//tcc_param=
//version 0.13.0

//2016-08-01 雪星(997596@gmail.com)   Primes_1

#include <stdio.h>
#include <string.h>

void test(char* string){
	//char *str;
	//str = strchr(string, ' ');
	printf("INPUT: %s\n", string);
	char *path = strchr(string, ' ') + 1;
	strchr(path, ' ')[0] = '\0';

	char *query = strchr(path, '?');
	
	if(NULL != query){
		query[0] = '\0';
		query++;
		printf("query: %s\n", query);
	}

	printf("path: %s\n", path);

	printf("respond: ");
	if(!strcmp(path, "/")){
		printf("mainpage");
	}else if(!strcmp(path, "/favicon.ico")){
		printf("404");
	}else{
		printf("404");
	}

	printf("\n");
	return;
}

int main(){
    system("title homeguard-test");

    test("GET / HTTP/1.1");
    test("GET /? HTTP/1.1");
    test("GET /?asdfasdf HTTP/1.1");
    test("GET /favicon.ico HTTP/1.1");

    system("pause");
    return 0;
}