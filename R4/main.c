/* CS270 - R4
 *
 * Author: Your name here
 * Date:   2/7/2017
 */

#include <stdlib.h>
#include "struct.h"

int main(int argc, const char **argv)
{
  // TODO: Complete the main function 
	int numStudents;  
	scanf("%d", &numStudents); 

	classRoster roster; 
	roster.numStudents = numStudents; 
	roster.students = (students**)calloc(numStudents, sizeOf(students*));

	for(int i =0; i < numStudents; i++){ 
		readStudentAndEnroll(roster.students + i);
	}		
		
}
