#include "Student.h"
#include "FIFO.h"

extern FIFO_t FIFO_Students;


void Add_Student_File(){
	student new_student;
	FILE *file = fopen("students_data.txt", "r");
	int found_count = 0;
	if(!file){
		PRINTF("[ERROR] Couldn't import data from file (file was not found)!\n");

	}
	else{
		while(!feof(file)){
			fscanf(file, "%d", &(new_student.Roll_Number));
			if(ROLL_NUMBER_REPEATED == FIFO_RollNum_Check(&FIFO_Students, new_student.Roll_Number)){
				PRINTF("[ERROR] Roll Number %d is repeated!\n", new_student.Roll_Number);
				fscanf(file, "%*[^\n]");
			}
			else{
				fscanf(file, "%s", new_student.First_Name);
				fscanf(file, "%s", new_student.Last_Name);
				fscanf(file, "%f", &(new_student.GPA));
				for(int i = 0; i < 5; i++){
					fscanf(file, "%u", &(new_student.courses_ids[i]));
				}
				if(FIFO_NO_ERROR == FIFO_Enqueue(&FIFO_Students, new_student)){
					PRINTF("[INFO] Added %s with roll number %d!\n", new_student.First_Name, new_student.Roll_Number);
					found_count++;
				}
				else{
					PRINTF("[ERROR] Couldn't add user with roll number: %d", new_student.Roll_Number);
				}
			}
			PRINTF("----------------------\n");
		}
		PRINTF("[INFO] Added %d users!\n", found_count);
		PRINTF("--------------------------------------------\n");
		PRINTF("\n[INFO] The total number of students is %d\n", FIFO_Students.count);
		PRINTF("\n[INFO] You can add up to %d Students\n", FIFO_Students.length);
		PRINTF("\n[INFO] You can add %d more students\n", (FIFO_Students.length - FIFO_Students.count));

	}
}

void Add_Student_Manually(){
	student new_student;
	char temp[50];
	PRINTF("Add the students Details\n");
	PRINTF("------------------------\n\n");
	PRINTF("Enter the unique Roll Number: ");
	gets(temp);
	if(FIFO_RollNum_Check(&FIFO_Students, atoi(temp))){
		PRINTF("Roll number is not unique, please retry with another one!\n");

	}
	else{
		new_student.Roll_Number = atoi(temp);
		PRINTF("Enter the first name of student: ");
		gets(temp);
		strcpy((char*)new_student.First_Name, temp);
		PRINTF("Enter the last name of student: ");
		gets(temp);
		strcpy((char*)new_student.Last_Name, temp);
		PRINTF("Enter the GPA of student: ");
		gets(temp);
		new_student.GPA = (float)atof(temp);
		PRINTF("Enter the course ID of each course\n");
		for(int i = 0; i < 5; i++){
			PRINTF("Course %d id: ", i+1);
			gets(temp);
			new_student.courses_ids[i] = (uint16_t)atoi(temp);
		}
		FIFO_Enqueue(&FIFO_Students, new_student);
		PRINTF("[INFO] Student Details is added Successfully\n");
		PRINTF("--------------------------------------------\n");
		PRINTF("[INFO] The total number of students is %d\n", FIFO_Students.count);
		PRINTF("[INFO] You can add up to %d Students\n", FIFO_Students.length);
		PRINTF("[INFO] You can add %d more students\n", (FIFO_Students.length - FIFO_Students.count));

	}
}

void Find_By_RollNum(){
	char temp[50];
	PRINTF("Enter the roll number of the student: ");

	gets(temp);
	FIFO_Print_RollNum(&FIFO_Students, atoi(temp));

}

void Find_By_FirstName(){
	char temp[50];
	PRINTF("Enter the first name of the student: ");

	gets(temp);
	FIFO_Print_First_Name(&FIFO_Students, temp);

}

void Find_By_Courses(){
	char temp[50];
	PRINTF("Enter the course ID: ");

	gets(temp);
	FIFO_Print_Course(&FIFO_Students, atoi(temp));

}

void Get_Students_Count(){
	PRINTF("[INFO] The total number of students is %d\n", FIFO_Students.count);
	PRINTF("[INFO] You can add up to %d Students\n", FIFO_Students.length);
	PRINTF("[INFO] You can add %d more students\n", (FIFO_Students.length - FIFO_Students.count));

}

void Delete_Student(){
	char temp[50];
	PRINTF("Enter the roll number you want to delete: ");

	gets(temp);
	FIFO_Remove(&FIFO_Students, atoi(temp));

}

void Update_Student(){
	char temp[50];
	PRINTF("Enter the roll number you want to update: ");
	gets(temp);
	FIFO_Update_Student(&FIFO_Students, atoi(temp));

}

void Print_Students(){
	FIFO_print_all(&FIFO_Students);
}
