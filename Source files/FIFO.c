#include "fifo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FIFO_state FIFO_init(FIFO_t *fifo, student *buffer, uint16_t length){
	FIFO_state state = FIFO_NO_ERROR;
	if((fifo == NULL) || (buffer == NULL)){
		PRINTF("[ERROR] Students database is not found!\n");
		state = FIFO_NULL;
	}
	else{
		fifo->base = buffer;
		fifo->head = buffer;
		fifo->tail = buffer;
		fifo->count = 0;
		fifo->length = length;
		PRINTF("[INFO] Students database is initialized successfully!\n");
	}
	return state;
}

uint8_t FIFO_RollNum_Check(FIFO_t *fifo, uint32_t Number){
	int Roll_Num_Flag = ROLL_NUMBER_UNIQUE;
	student *index_ptr = fifo->tail;
	int c = fifo->count;
	while(c--){
		if(Number == index_ptr->Roll_Number){
			Roll_Num_Flag = ROLL_NUMBER_REPEATED;
			break;
		}
		if(index_ptr == (fifo->base + (fifo->length * sizeof(student)))){
			index_ptr = fifo->base;
		}
		else{
			index_ptr++;
		}
	}
	return Roll_Num_Flag;
}

FIFO_state FIFO_Enqueue(FIFO_t *fifo, student item){
	FIFO_state state = FIFO_NO_ERROR;
	if(!fifo->base || !fifo->head || !fifo->tail){
		PRINTF("[ERROR] Students database is not found!\n");
		state = FIFO_NULL;
	}
	else{
		if(FIFO_IS_FULL(fifo) == FIFO_NO_ERROR){
			*(fifo->head) = item;
			fifo->count++;
			if(fifo->head == (fifo->base + (fifo->length * sizeof(student)))){
				fifo->head = fifo->base;
			}
			else{
				fifo->head++;
			}
		}
		else{
			state = FIFO_FULL;
		}
	}
	return state;
}

FIFO_state FIFO_IS_FULL(FIFO_t *fifo){
	FIFO_state state = FIFO_NO_ERROR;
	if(!fifo->base || !fifo->head || !fifo->tail){
		PRINTF("[ERROR] Students database is not found!\n");
		state = FIFO_NULL;
	}
	else{
		if(fifo->count >= fifo->length){
			state = FIFO_FULL;
		}
		else{ /* Do Nothing */ }
	}
	return state;
}

FIFO_state FIFO_Remove(FIFO_t *fifo, uint32_t Number){
	FIFO_state state = FIFO_NO_ERROR;
	student *index_ptr = fifo->tail;
	if(!fifo->base || !fifo->head || !fifo->tail){
		PRINTF("[ERROR] Students database is not found!\n");
		state = FIFO_NULL;
	}
	else{
		int counter = 0, found_flag = 0;
		if(!fifo->count){
			PRINTF("[ERROR] Students database is empty!\n");
			state = FIFO_EMPTY;
		}
		else{
			while(counter < fifo->count){
				if(Number == index_ptr->Roll_Number){
					found_flag = 1;
					break;
				}

				if(index_ptr == (fifo->base + (fifo->length * sizeof(student)))){
					index_ptr = fifo->base;
				}
				else{
					index_ptr++;
				}
				counter++;
			}
			if(found_flag){
				fifo->count--;
				while(counter < fifo->count){
					*(index_ptr) = *(index_ptr + 1);
					counter++;
					index_ptr++;
				}
				PRINTF("[INFO] The Roll Number is removed Successfully\n");
			}
			else{
				PRINTF("[ERROR] The roll number %d was not found!\n", Number);
			}
		}
	}
	return state;
}

FIFO_state FIFO_print_all(FIFO_t *fifo){
	FIFO_state state = FIFO_NO_ERROR;
	student *index_ptr = fifo->tail;
	if(!fifo->base || !fifo->head || !fifo->tail){
		PRINTF("[ERROR] Students database is not found!\n");
		state = FIFO_NULL;
	}
	else{
		int c = fifo->count;
		if(!c){
			PRINTF("[ERROR] Students database is empty!\n");
			state = FIFO_EMPTY;
		}
		else{
			while(c--){
				PRINTF("Student first name: %s\n", index_ptr->First_Name);
				PRINTF("Student last name: %s\n", index_ptr->Last_Name);
				PRINTF("Student roll number: %d\n", index_ptr->Roll_Number);
				PRINTF("Student GPA number: %.2f\n", index_ptr->GPA);
				for(int i = 0; i < 5; i++){
					PRINTF("Course %d ID is: %d\n", i+1, index_ptr->courses_ids[i]);
				}
				PRINTF("-----------------------------------\n");
				if(index_ptr == (fifo->base + (fifo->length * sizeof(student)))){
					index_ptr = fifo->base;
				}
				else{
					index_ptr++;
				}
			}
		}
	}
	return state;
}

FIFO_state FIFO_Print_RollNum(FIFO_t *fifo, uint32_t Number){
	FIFO_state state = FIFO_NO_ERROR;
	student *index_ptr = fifo->tail;
	int found_flag = 0;
	if(!fifo->base || !fifo->head || !fifo->tail){
		PRINTF("[ERROR] Students database is not found!\n");
		state = FIFO_NULL;
	}
	else{
		int c = fifo->count;
		if(!fifo->count){
			PRINTF("[ERROR] Students database is empty!\n");
			state = FIFO_EMPTY;
		}
		else{
			while(c--){
				if(Number == index_ptr->Roll_Number){
					found_flag = 1;
					PRINTF("[INFO] Student Found!\n");
					PRINTF("-----------------------------------\n");
					PRINTF("First name: %s\n", index_ptr->First_Name);
					PRINTF("Last name: %s\n", index_ptr->Last_Name);
					PRINTF("Student roll number: %d\n", index_ptr->Roll_Number);
					PRINTF("GPA: %.2f\n", index_ptr->GPA);
					for(int i = 0; i < 5; i++){
						PRINTF("Course %d is: %d\n", i+1, index_ptr->courses_ids[i]);
					}
					PRINTF("-----------------------------------\n");
					break;
				}
				if(index_ptr == (fifo->base + (fifo->length * sizeof(student)))){
					index_ptr = fifo->base;
				}
				else{
					index_ptr++;
				}
			}
			if(!found_flag){
				PRINTF("[ERROR] Roll Number %d is not found!\n", Number);
			}
		}
	}
	return state;
}

FIFO_state FIFO_Print_First_Name(FIFO_t *fifo, char Name[]){
	FIFO_state state = FIFO_NO_ERROR;
	student *index_ptr = fifo->tail;
	int found_flag = 0;
	if(!fifo->base || !fifo->head || !fifo->tail){
		PRINTF("[ERROR] Students database is not found!\n");
		state = FIFO_NULL;
	}
	else{
		int c = fifo->count;
		if(!fifo->count){
			PRINTF("[ERROR] Students database is empty!\n");
			state = FIFO_EMPTY;
		}
		else{
			while(c--){
				if(!strcmp(index_ptr->First_Name, Name)){
					found_flag++;
					PRINTF("[INFO] Student Found!\n");
					PRINTF("-----------------------------------\n");
					PRINTF("First name: %s\n", index_ptr->First_Name);
					PRINTF("Last name: %s\n", index_ptr->Last_Name);
					PRINTF("Student roll number: %d\n", index_ptr->Roll_Number);
					PRINTF("GPA: %.2f\n", index_ptr->GPA);
					for(int i = 0; i < 5; i++){
						PRINTF("Course %d is: %d\n", i+1, index_ptr->courses_ids[i]);
					}
					PRINTF("-----------------------------------\n");
				}
				if(index_ptr == (fifo->base + (fifo->length * sizeof(student)))){
					index_ptr = fifo->base;
				}
				else{
					index_ptr++;
				}
			}
			if(!found_flag){
				PRINTF("[ERROR] No students found with first name: %s!\n", Name);
			}
		}
	}
	return state;
}

FIFO_state FIFO_Print_Course(FIFO_t *fifo, uint16_t course_no){
	FIFO_state state = FIFO_NO_ERROR;
	student *index_ptr = fifo->tail;
	int found_flag = 0;
	if(!fifo->base || !fifo->head || !fifo->tail){
		PRINTF("[ERROR] Students database is not found!\n");
		state = FIFO_NULL;
	}
	else{
		int c = fifo->count;
		if(!fifo->count){
			PRINTF("[ERROR] Students database is empty!\n");
			state = FIFO_EMPTY;
		}
		else{
			while(c--){
				for(int i = 0; i < 5; i++){
					if(index_ptr->courses_ids[i] == course_no){
						found_flag++;
						PRINTF("[INFO] Student Found!\n");
						PRINTF("-----------------------------------\n");
						PRINTF("First name: %s\n", index_ptr->First_Name);
						PRINTF("Last name: %s\n", index_ptr->Last_Name);
						PRINTF("Student roll number: %d\n", index_ptr->Roll_Number);
						PRINTF("GPA: %.2f\n", index_ptr->GPA);
						PRINTF("-----------------------------------\n");
						break;
					}
				}
				if(index_ptr == (fifo->base + (fifo->length * sizeof(student)))){
					index_ptr = fifo->base;
				}
				else{
					index_ptr++;
				}
			}
			if(!found_flag){
				PRINTF("[ERROR] No students are enrolled in course: %d!\n", course_no);
			}
			else{
				PRINTF("[INFO] %d students are enrolled in course: %d!\n",found_flag, course_no);
			}
		}
	}
	return state;
}

FIFO_state FIFO_Update_Student(FIFO_t *fifo, uint32_t Number){
	FIFO_state state = FIFO_NO_ERROR;
	student *index_ptr = fifo->tail;
	int found_flag = 0;
	if(!fifo->base || !fifo->head || !fifo->tail){
		PRINTF("[ERROR] Students database is not found!\n");
		state = FIFO_NULL;
	}
	else{
		int c = fifo->count;
		if(!fifo->count){
			PRINTF("[ERROR] Students database is empty!\n");
			state = FIFO_EMPTY;
		}
		else{
			while(c--){
				if(Number == index_ptr->Roll_Number){
					found_flag = 1;
					break;
				}
				if(index_ptr == (fifo->base + (fifo->length * sizeof(student)))){
					index_ptr = fifo->base;
				}
				else{
					index_ptr++;
				}
			}
			if(0 == found_flag){
				PRINTF("[ERROR] No students found with roll number: %d!\n", Number);
			}
			else{
				int user_choice;
				char temp_entry[50];
				PRINTF("[INFO] Student found!\n");
				PRINTF("\nChoose what do you want to update: ");
				PRINTF("\n1. First Name\n");
				PRINTF("2. Last Name\n");
				PRINTF("3. Roll Number\n");
				PRINTF("4. GPA\n");
				PRINTF("5. Courses\n");
				PRINTF("6. Cancel\n");
				PRINTF("Your Choice: ");
				scanf("%d", &user_choice);
				getchar();
				switch(user_choice){
				case 1:
					PRINTF("Enter the new first name: ");
					gets(temp_entry);
					strcpy(index_ptr->First_Name, temp_entry);
					PRINTF("[INFO] First name updated successfully!");
					break;
				case 2:
					PRINTF("Enter the new last name: ");
					gets(temp_entry);
					strcpy(index_ptr->Last_Name, temp_entry);
					PRINTF("[INFO] Last name updated successfully!");
					break;
				case 3:
					PRINTF("Enter the new roll number: ");
					gets(temp_entry);
					if(ROLL_NUMBER_UNIQUE == FIFO_RollNum_Check(fifo, atoi(temp_entry))){
						index_ptr->Roll_Number = atoi(temp_entry);
						PRINTF("[INFO] Roll number updated successfully!\n");
					}
					else{
						PRINTF("[ERROR] Roll number repeated, aborting operation!\n");
					}
					break;
				case 4:
					PRINTF("Enter the new GPA: ");
					gets(temp_entry);
					index_ptr->GPA = atof(temp_entry);
					PRINTF("[INFO] GPA updated successfully!");
					break;
				case 5:
					PRINTF("Enter the new courses:\n");
					for(int i = 0; i < 5; i++){
						PRINTF("Course %d: ", i+1);
						gets(temp_entry);
						index_ptr->courses_ids[i] = atoi(temp_entry);
					}
					PRINTF("[INFO] Courses updated successfully!");
					break;
				case 6:
					PRINTF("Operation canceled!");
					break;
				default: PRINTF("Wrong choice, operation canceled!"); break;
				}
			}
		}
	}
	return state;
}

