
#ifndef FIFO_H_
#define FIFO_H_

#include <stdint.h>
#include "Student.h"


#define ROLL_NUMBER_UNIQUE	 0
#define ROLL_NUMBER_REPEATED 1


typedef struct{
	student *base;
	student *head;
	student *tail;
	unsigned int count;
	unsigned int length;

}FIFO_t;

typedef enum{
	FIFO_NO_ERROR,
	FIFO_NULL,
	FIFO_FULL,
	FIFO_EMPTY
}FIFO_state;


FIFO_state FIFO_init(FIFO_t *fifo, student *buffer, uint16_t length);
uint8_t FIFO_RollNum_Check(FIFO_t *fifo, uint32_t Number);
FIFO_state FIFO_Enqueue(FIFO_t *fifo, student item);
FIFO_state FIFO_IS_FULL(FIFO_t *fifo);
FIFO_state FIFO_Remove(FIFO_t *fifo, uint32_t Number);
FIFO_state FIFO_Print_RollNum(FIFO_t *fifo, uint32_t Number);
FIFO_state FIFO_Print_First_Name(FIFO_t *fifo, char Name[]);
FIFO_state FIFO_Print_Course(FIFO_t *fifo, uint16_t course_no);
FIFO_state FIFO_print_all(FIFO_t *fifo);
FIFO_state FIFO_Update_Student(FIFO_t *fifo, uint32_t Number);

#endif /* FIFO_H_ */
