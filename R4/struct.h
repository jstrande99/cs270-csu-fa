/* CS270 - R4
 *
 * Author: Jordan Strande
 * Date:   2/7/2017
 */
 
/********** STRUCTURE DEFINITION **********************************************/

// Structure that represents a student
typedef struct
{
  // TODO: Add required members
	char firstName[80]; 
	float qualityPoints; 
	int numCredits;
} Student;

// Structure that represents a class roster
// TODO: Declare this structure
typedef struct
{ 
	int numStudents; 
	Student **students; 
} classRoster;

/********** FUNCTION PROTOTYPES ***********************************************/

void readStudentAndEnroll(Student **slot);

void displayStudent(Student s);
