

#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>


#define PRINTF(...) fflush(stdin); fflush(stdout);\
		printf(__VA_ARGS__);\
		fflush(stdin); fflush(stdout);


typedef struct Sdata{
	char First_Name[50];
	char Last_Name[50];
	int Roll_Number;
	float GPA;
	int courses_ids[5];
}student;



void Add_Student_File();
void Add_Student_Manually();
void Find_By_RollNum();
void Find_By_FirstName();
void Find_By_Courses();
void Get_Students_Count();
void Delete_Student();
void Update_Student();
void Print_Students();

#endif
