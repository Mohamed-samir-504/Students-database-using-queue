#include "Student.h"
#include "FIFO.h"

FIFO_t FIFO_Students;

student myStudents[50];


int main(){
	FIFO_init(&FIFO_Students, myStudents, 50);
	int user_choice;
	PRINTF("\nWelcome to the Student Management System\n");
	while(1){

		PRINTF("\nChoose the task that you want to perform: \n");
		PRINTF("\n1. Add the Student Details Manually\n");
		PRINTF("2. Add the Student Details From Text File\n");
		PRINTF("3. Find the Student Details by Roll Number\n");
		PRINTF("4. Find the Student Details by First Name\n");
		PRINTF("5. Find the Student Details by Course ID\n");
		PRINTF("6. Find the Total number of Students\n");
		PRINTF("7. Delete a Student Details by Roll Number\n");
		PRINTF("8. Update a Student Details by Roll Number\n");
		PRINTF("9. Show all students information\n");
		PRINTF("10. Exit\n");
		PRINTF("\nEnter your choice: ");
		scanf("%d", (int*)&user_choice);
		switch(user_choice){
		case 1:
			Add_Student_Manually();
			break;
		case 2:
			Add_Student_File();
			break;
		case 3:
			Find_By_RollNum();
			break;
		case 4:
			Find_By_FirstName();
			break;
		case 5:
			Find_By_Courses();
			break;
		case 6:
			Get_Students_Count();
			break;
		case 7:
			Delete_Student();
			break;
		case 8:
			Update_Student();
			break;
		case 9:
			Print_Students();
			break;
		case 10:
			PRINTF("\nSystem exit\n");
			return 1;
			break;
		default:
			PRINTF("\n[ERROR] Enter a valid choice\n");

		break;
		}
	}
	return 0;
}

