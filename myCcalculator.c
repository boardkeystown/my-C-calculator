#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

/*
By: boardkeystown
https://github.com/boardkeystown

NOTE: For windows terminal only
LOL this is one awful little calculator made only to play around in C :)

last worked on 8/29/2018
Things To Work On:
(optional) Fix minor error where last digit of float changes val
  ex 1.123 is displayed 1.122 after call to doulbetoString()
(optional) Find away to check if there is a overflow if there is a operation 
*/

#define TRUE 1
#define FALSE 0

//Array
#define ROW 5
#define COL 4
#define STRINGCOUNT 12
#define STRINGMAX (STRINGCOUNT -2)

//OTher
#define BAR_LEN 15

//Characters 
#define ZERO 48 // 0
#define ONE 49 // 1
#define TWO 50  //2
#define THREE 51 //3
#define FOUR 52 //4
#define FIVE 53 //5
#define SIX 54 //6
#define SEVEN 55 //7
#define EIGHT 56 //8
#define NINE 57 //9
#define PLUS 43 //+
#define MINUS 45 //-
#define MULTIPLY 88 //X
#define DIVIDE 246 //÷
#define CLEAR 67 //C 
#define BACKSPACE 170 //¬
#define ENTER  219 //█ 
#define LIGHT_ENTER 177 //▒
#define LEFT_ELBOW_DOWN 218  // ┌ 
#define RIGHT_ELBOW_DOWN 191 // ┐ 
#define LEFT_ELBOW_UP 192   // └ 
#define RIGHT_ELBOW_UP 217  // ┘ 
#define VERTICAL_LINE 179   // │ 
#define HORZONTAL_LINE 196  // ─ 
#define DOUBLE_ARROW_LEFT 175 // » 
#define DOUBLE_ARROW_RIGHT 174 // « 
#define BIG_BAR 205 //═
#define BIG_BAR_WITH_BOTTOM 209 //╤
#define BLANK ' ' //255 //  
#define BIG_DOT 249 // ∙


//Keyboard Codes
#define UP      72
#define DOWN    80
#define LEFT    75
#define RIGHT   77
#define keycode_w 119
#define keycode_s 115
#define keycode_a 97
#define keycode_d 100
#define keycode_Enter 13
#define keycode_spacebar 32
#define keycode_Backspace 8
#define keycode_Divide 47
#define keycode_Multiply 42
#define keycode_Subtract 45
#define keycode_Del 83
#define keycode_Add 43
#define keycode_dot 46
#define keycode_ESC 27




//-------------------------- Arrays -----------------------------------//
//Numbers stored in numpad
int numPadKeycodes[COL][ROW] = {
	{ SEVEN, EIGHT, NINE,  keycode_Del,keycode_Backspace },
	{ FOUR,  FIVE,  SIX,   keycode_Add,keycode_Subtract },
	{ ONE,   TWO,   THREE, keycode_Multiply,keycode_Divide },
	{ -1,    ZERO,  -1,    keycode_dot,keycode_Enter }
};

//Numbers stored in numpad
int numPad[COL][ROW] = {
	{ 7, 8, 9, 10,14 },
	{ 4, 5, 6, 11,15 },
	{ 1, 2, 3, 12,16 },
	{ 0, 0, 0, 13,17 }
};


//Characters used to represent the numbers from numpad
char numPadChar[COL][ROW] = {
	{ SEVEN,EIGHT,NINE,  CLEAR,    BACKSPACE},
	{ FOUR, FIVE, SIX,   PLUS,     MINUS },
	{ ONE,  TWO,  THREE, MULTIPLY, DIVIDE },
	{ BLANK,ZERO, BLANK, BIG_DOT,  ENTER }
};

//String that holds numbers displayed and used to convert into respected int or float when needed
char displayval[STRINGCOUNT] = { BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK};

//array used to hold the location of the selector icon for the numpad
int selectorXY[2] = { 0,0 };
//---------------------------------------------------------------------//


//-------------------------- Values -----------------------------------//
//Keeps track of total numbers in the array displayval
int displayvalTrack = 0;

//Keeps track of total decimal numbers (maybe i need to remove 1 when using for precision?)
int displayvalDecimaltrack = 0;

//Saves the largest displayvalDecimalTrack
int decSave = 0;

//value used in update to hold the change in COL or ROW  
int _change = 0;

//Stores the value of the keypressed from processinput() 
int keypress = 0;


//Current operation track
int operationMode = 0;

//Values for math operations

long double val_A = 0;
long double val_B = 0;

//Values to store precision
int valp_A = 0;
int valp_B = 0;

//--------------------------------------------------------------------//

//-------------------------- FLAGS -----------------------------------//

//Flag for the second number val_B
int isSecondNumberSet = FALSE;

//Flag for the first number val_A
int isFirstNumberSet = FALSE;

//Flag for is negative
int isNegative = FALSE;

//Flag for decimal mode
int isDecimal = FALSE;

//Flag if a number key has been pressed used in update()
int numberIsPressed = FALSE;

//Flag is a modifier key is pressed used in update()
int modifierIsPressed = FALSE;

//Is the control for the update loop and the main loop
int loopCtrl = TRUE;
//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
//							 RENDER
//------------------------------------------------------------------------//

// Renders text to console 
void render();

//The display for the numbers
void display();

//Draws the lines for the number pad
void lines(int a);

//Draws the numberpad in console used in redner()
void numPaddisplay();

//Draws the bars for the number pad that go on the top and bottom
void drawBars(int numofbar, char elbowL, char elbowR);


//------------------------------------------------------------------------//
//							 INPUT
//------------------------------------------------------------------------//

//handles keyboard input 
void processInput();

//------------------------------------------------------------------------//
//							  UPDATE
//------------------------------------------------------------------------//

//Returns the state of the program preforms updates to the program (control flow) 
int update();

//small pop up menu for selecting either subtract operation or negative 
void subtractOrNegative();

//Actions taken if spacebar is pressed
void spacebarisPressed();

//removes number on the end of display val
void backspacePressed();

//actions taken if enter key is pressed
void enterKeypressed();

//takes the value of a long float and retruns it to displayval 
void stringTodouble(long double *val);

//Returns the number of digits in a long int has a int value 
int countNumberofDigits(long long int val);

//Set double(+) or (-) displayval 
void doubleTostring(long double val, char *str, int precision);

//Clear value by setting it to zero
void clearValue(long double *val);

//Clears all values of long int and long float by setting them to zero
void clearValues();

//Clears the display array
void clearDisplayVal();

//Clears the display value so you can type a new number in
void clearDisplayForNewInput();

//Gets the selector value from a key pressed so it can be updated on the numpad 
void getKeypressed();

//Checks to see if the selector is our of bounds 
void selectorCheck(int change, int xOry, int bound);

//returns TRUE if selector is on zero
int isZeroselected();

//Adjust the slector 
void selectorAdjust(int p1_COL, int p1_ROW, int COLorROWmovem, int amountMoved, int bounds, int p2_COL, int p2_ROW);

//Adds digits to the display numbers array
void addNumbertoDisplayVal();

//Adds zero to display val and makes sure only 1 zero can be added at the start
void addZerotoDisplay();

//Adds the negative sysmbol and sets isNegative flag
void addNegativeinDispaly();

//Add dot to displayval
void addDotindisplay();

//Compares dec size of val_a and val_b and sets the dec according 
void setValStringWithPrecision();

//Sets to max precision  
void setValStringWithPrecision_MAX();

//add functions 
void add_operation();

//subtraction function 
void subtraction_function();

//multiplication function
void multiplication_function();

//division function();
void division_function();

//=|==|==|==|==|==|==|==|==   MAIN   ==|==|==|==|==|==|==|==|==|=//
int main(void) {
	while (loopCtrl == TRUE) {
		render();
		processInput();
		loopCtrl = update();
	}
	return 0;
}
//=|==|==|==|==|==|==|==|==|==|==|==|==|==|==|==|==|==|==|==|==|=//

void render() {
	display();
	numPaddisplay();
	printf("\n Use ARROW KEYS to move \n and SPACEBAR to select \n ESC to exit");

	//Display values for testing
	/*	
	printf("\n\n TEST INFO");
	printf("\n selectorXY[ %d, %d ]", selectorXY[0], selectorXY[1]);
	printf("\n [%d ]\n", keypress);
	printf("\n isDecimal: %d", isDecimal);
	printf("\n isNegative: %d", isNegative);
	printf("\n displayvalTrack: %d", displayvalTrack);
	printf("\n displayvalDecimaltrack: %d", displayvalDecimaltrack);
	printf("\n val_A: %.10lf, valP_A: %d, isFirstNumberSet: %d", val_A, valp_A, isFirstNumberSet);
	printf("\n val_B: %.10lf, valp_B: %d, isSecondNumberSet: %d ", val_B, valp_B, isSecondNumberSet);
	printf("\n operationMode: %d", operationMode);
	printf("\n decSave: %d", decSave);
	*/

}

void lines(int a) {
	for (int i = 0; i < a; i++) {
		printf("%c", BIG_BAR);
	}
	printf("\n");
}

void display() {
	system("CLS");
	lines(19);
	printf("   %s \n",  displayval);
	lines(19);
}

void getKeypressed() {
	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			if (numPadKeycodes[i][j] == keypress) {
				selectorXY[0] = i;
				selectorXY[1] = j;
				return;
			}
		}
	}

}

void numPaddisplay() {
	//TOP BAR
	drawBars(BAR_LEN, LEFT_ELBOW_DOWN, RIGHT_ELBOW_DOWN);

	//number pad

	for (int i = 0; i < COL; i++) {
		printf("%c", VERTICAL_LINE);
		for (int j = 0; j < ROW; j++) {
			if (isZeroselected()) {
				if (3 == i && 1 == j) {
					printf("%c%c%c", DOUBLE_ARROW_LEFT, numPadChar[i][j], DOUBLE_ARROW_RIGHT);
				}
				else {
					printf(" %c ", numPadChar[i][j]);
				}
			} 
			else if (selectorXY[0] == i && selectorXY[1] == j) {
				printf("%c%c%c",DOUBLE_ARROW_LEFT, numPadChar[i][j], DOUBLE_ARROW_RIGHT);
			}
			else { 
				printf(" %c ", numPadChar[i][j]); 
			}

		}
		printf("%c", VERTICAL_LINE);
		printf("\n");
	}

	//Bottom BAR
	drawBars(BAR_LEN, LEFT_ELBOW_UP, RIGHT_ELBOW_UP);
}

void drawBars(int numofbar, char elbowL, char elbowR) {
	printf("%c", elbowL);

	for (int i = 0; i < numofbar; i++) {
		printf("%c", HORZONTAL_LINE);
	}
	printf("%c \n", elbowR);
}

void selectorCheck(int change, int xOry, int bound) {
	if (change >= bound) {
		change = 0;
		selectorXY[xOry] = change;
		return;
	}
	else if (change < 0) {
		selectorXY[xOry] = bound-1;
		return;
	}
	else
	{
		selectorXY[xOry] = change;
		return;
	}
}

int isZeroselected() {
	if (numPad[selectorXY[0]][selectorXY[1]] == 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void selectorAdjust(int p1_COL, int p1_ROW, int COLorROWmovem, int amountMoved, int bounds, int p2_COL, int p2_ROW) {
	if (isZeroselected()) {
		selectorXY[0] = p1_COL;
		selectorXY[1] = p1_ROW;
	}
	else if (!isZeroselected()) {
		_change = selectorXY[COLorROWmovem] + amountMoved;
		selectorCheck(_change, COLorROWmovem, bounds);
		if (isZeroselected()) {
			selectorXY[0] = p2_COL;
			selectorXY[1] = p2_ROW;
		}
	}
}

int update() {
	if (numberIsPressed) {
		clearDisplayForNewInput();
		addNumbertoDisplayVal();
		numberIsPressed = FALSE;
	} else if (modifierIsPressed) {
		switch (keypress)
		{
		case keycode_spacebar:
			spacebarisPressed();
			break;
		case ZERO:
			clearDisplayForNewInput();
			addZerotoDisplay();
			break;
		case keycode_Del:
			clearDisplayVal();
			clearValues();
			isFirstNumberSet = FALSE;
			isSecondNumberSet = FALSE;
			operationMode = 0;
			decSave = 0;
			break;
		case keycode_Enter:
			enterKeypressed();
			break;
		case keycode_Backspace:
			backspacePressed();
			break;
		case keycode_dot:
			clearDisplayForNewInput();
			addDotindisplay();
			break;
		case keycode_Subtract:
			subtractOrNegative();
			break;
		case keycode_Add:
			add_operation();
			break;
		case keycode_Multiply:
			multiplication_function();
			break;
		case keycode_Divide:
			division_function();
			break;
		default:
			break;
		}
		modifierIsPressed = FALSE;
	}

	return loopCtrl;
}

//subtract or negative 
void subtractOrNegative() {
	int choice = 0;
	int ctrl = TRUE;
	while (ctrl) {
		system("CLS");
		printf("\n ----------------------------");
		printf("\n|     Subtract  |  Negative  |");
		if (choice == 0) {
			printf("\n|       >-<     |    (-)     |");
		}
		else {
			printf("\n|        -      |   >(-)<    |");
		}
		printf("\n| PRESS: - or 1 |     2      |");
		printf("\n ----------------------------");
		printf("\n Arrow keys to move \n SPACEBAR or ENTER to select \n ESC to exit");


		keypress = _getch();
		switch (keypress)
		{
		case LEFT:
			choice--;
			if (choice > 1) {
				choice = 0;
			}
			else if (choice < 0) {
				choice = 1;
			}
			break;
		case RIGHT:
			choice++;
			if (choice > 1) {
				choice = 0;
			}
			else if (choice < 0) {
				choice = 1;
			}
			break;
		case keycode_Subtract: //subtract
			subtraction_function();
			ctrl = FALSE;
			break;
		case ONE: //subtract
			subtraction_function();
			ctrl = FALSE;
			break;
		case TWO: // negative
			if (!isNegative) {
				addNegativeinDispaly();
			}
			ctrl = FALSE;
			break;
		case keycode_spacebar:
			if (choice == 0) {
				subtraction_function();
				ctrl = FALSE;
			}
			else {
				if (!isNegative) { addNegativeinDispaly(); } 
				ctrl = FALSE;
			}
			break;
		case keycode_Enter:
			if (choice == 0) {
			   subtraction_function();
				ctrl = FALSE;
			}
			else {
				if (!isNegative) { addNegativeinDispaly(); }
				
				ctrl = FALSE;
			}
			break;
		case keycode_ESC:
			ctrl = FALSE;
			break;
		default:
			break;
		}
	}
}

void spacebarisPressed() {
	
	if (numPad[selectorXY[0]][selectorXY[1]] == 17) {
		enterKeypressed();
		return;
	}
	else {
		for (int i = 1; i <= 9; i++) {
			if (numPad[selectorXY[0]][selectorXY[1]] == i) {
				clearDisplayForNewInput();
				addNumbertoDisplayVal();
				return;
			}
		}
		//check for modifiers 
		switch (numPad[selectorXY[0]][selectorXY[1]])
		{
		case 0:
			clearDisplayForNewInput();
			addZerotoDisplay();
			break;
		case 10: //Clear
			clearDisplayVal();
			clearValues();
			isFirstNumberSet = FALSE;
			isSecondNumberSet = FALSE;
			operationMode = 0;
			decSave = 0;
			break;
		case 14: //Backsapce
			backspacePressed();
			break;
		case 13: //Dot
			clearDisplayForNewInput();
			addDotindisplay();
			break;
		case 11: // ADD +
			add_operation();
			break;
		case 15: //minus 
			subtractOrNegative();
			break;
		case 12: //multiply
			multiplication_function();
			break;
		case 16: // divide
			division_function();
			break;
		default:
			break;
		}
		return;
	}

}

void enterKeypressed() {
	switch (operationMode)
	{
	case PLUS:
		if (!isSecondNumberSet) {
			add_operation();
		}
		else {
			clearDisplayVal();
			val_A = val_A + val_B;
			isSecondNumberSet = TRUE;
			setValStringWithPrecision();
		}
		break;
	case MINUS:
		if (!isSecondNumberSet) {
			subtractOrNegative();
		}
		else {
			clearDisplayVal();
			val_A = val_A - val_B;
			isSecondNumberSet = TRUE;
			setValStringWithPrecision();
		}
		break;
	case MULTIPLY:
		if (!isSecondNumberSet) {
			multiplication_function();
		}
		else {
			clearDisplayVal();
			val_A = val_A * val_B;
			isSecondNumberSet = TRUE;
			setValStringWithPrecision();
		}
		break;
	case DIVIDE:
		if (!isSecondNumberSet) {
			division_function();
		}
		else {
			clearDisplayVal();
			val_A = val_A / val_B;
			isSecondNumberSet = TRUE;
			setValStringWithPrecision_MAX();
		}
		break;
	default:
		//Nothing
		break;
	}
}

void clearDisplayForNewInput() {
	if (isSecondNumberSet) {
		clearDisplayVal();
		isFirstNumberSet = FALSE; //MAYBE TURN THIS OFF???
		isSecondNumberSet = FALSE;
	}
}

void processInput() {
	keypress = _getch();
	switch (keypress)
	{
	case keycode_spacebar:
		modifierIsPressed = TRUE;
		break;
	case keycode_Enter:
		getKeypressed();
		modifierIsPressed = TRUE;
		break;
	case UP:
		_change = selectorXY[0] - 1;
		selectorCheck(_change, 0, COL);
		break;
	case DOWN:
		_change = selectorXY[0] + 1;
		selectorCheck(_change, 0, COL);
		break;
	case LEFT:
		selectorAdjust(3, 4, 1, -1, ROW, 3, 1);
		break;
	case RIGHT:
		selectorAdjust(3,3,1,1,ROW,3,1);
		break;
	case keycode_w:
		_change = selectorXY[0] - 1;
		selectorCheck(_change, 0, COL);
		break;
	case keycode_s:
		_change = selectorXY[0] + 1;
		selectorCheck(_change, 0, COL);
		break;
	case keycode_a:
		selectorAdjust(3, 4, 1, -1, ROW, 3, 1);
		break;
	case keycode_d:
		selectorAdjust(3, 3, 1, 1, ROW, 3, 1);
		break;
	case ZERO:
		getKeypressed();
		modifierIsPressed = TRUE;
		break;
	case ONE:
		getKeypressed();
		numberIsPressed = TRUE;
		break;
	case TWO:
		getKeypressed();
		numberIsPressed = TRUE;
		break;
	case THREE:
		getKeypressed();
		numberIsPressed = TRUE;
		break;
	case FOUR:
		getKeypressed();
		numberIsPressed = TRUE;
		break;
	case FIVE:
		getKeypressed();
		numberIsPressed = TRUE;
		break;
	case SIX:
		getKeypressed();
		numberIsPressed = TRUE;
		break;
	case SEVEN:
		getKeypressed();
		numberIsPressed = TRUE;
		break;
	case EIGHT:
		getKeypressed();
		numberIsPressed = TRUE;
		break;
	case NINE:
		getKeypressed();
		numberIsPressed = TRUE;
		break;
	case keycode_Del:
		modifierIsPressed = TRUE;
		getKeypressed();
		break;
	case keycode_Backspace:
		modifierIsPressed = TRUE;
		getKeypressed();
		break;
	case keycode_Divide:
		modifierIsPressed = TRUE;
		getKeypressed();
		break;
	case keycode_Multiply:
		modifierIsPressed = TRUE;
		getKeypressed();
		break;
	case keycode_Add:
		modifierIsPressed = TRUE;
		getKeypressed();
		break;
	case keycode_Subtract:
		modifierIsPressed = TRUE;
		getKeypressed();
		break;
	case keycode_dot:
		modifierIsPressed = TRUE;
		getKeypressed();
		break;
	case keycode_ESC:
		loopCtrl = FALSE;
		break;

	default:
		break;
	}
}

void addNumbertoDisplayVal() {
	if (isDecimal == FALSE) {
		if (displayvalTrack <= STRINGMAX) {
			displayval[displayvalTrack] = numPad[selectorXY[0]][selectorXY[1]] + '0';
			displayvalTrack++;
		}
	}
	else {
		if (displayvalTrack <= STRINGMAX) {
			displayval[displayvalTrack] = numPad[selectorXY[0]][selectorXY[1]] + '0';
			displayvalTrack++;
			displayvalDecimaltrack++;
		}
	}
}

void addZerotoDisplay() {
	if (isNegative == TRUE) {
		if (displayvalTrack != 1) {
			addNumbertoDisplayVal();
			return;
		}
		else {
			displayval[1] = '0';
			return;
		}
	} else if (displayvalTrack != 0) {
		addNumbertoDisplayVal();
		return;
	}
	else {
		displayval[0] = '0';
		return;
	}
}

void addDotindisplay() {
	if (isDecimal == FALSE && displayvalTrack <= STRINGMAX) {
		displayval[displayvalTrack] = '.';
		displayvalTrack++;
		displayvalDecimaltrack++;
		isDecimal = TRUE;
	}
}

void addNegativeinDispaly() {
	if (isNegative == FALSE && displayvalTrack == 0) {
		displayval[displayvalTrack] = '-';
		displayvalTrack++;
		isNegative = TRUE;
	}
}

void backspacePressed() {
	if (displayvalDecimaltrack == 0) {
		if (displayvalTrack > 0) {
			displayvalTrack--;
			displayval[displayvalTrack] = BLANK;
			if (displayvalTrack == 0) {
				clearDisplayVal();
			}
		}
	}
	else {
		if (displayvalTrack > 0) {
			displayvalTrack--;
			displayvalDecimaltrack--;
			displayval[displayvalTrack] = BLANK;
			if (displayvalDecimaltrack == 0) {
				isDecimal = FALSE;
			}
		}
	}
	
}

void stringTodouble(long double *val) {
	*val = 0;  // Clears the val from before 
	int dotPosition = 0;
	int n = 0;
	if (displayval[0] == '-') {
		n = 1;
	}

	for (; n < displayvalTrack; n++) {
		if (displayval[n] == '.') {
			dotPosition = displayvalTrack - n - 1;
		}
		else {
			*val = *val * 10.0f + (displayval[n] - '0');
		}
	}

	while (dotPosition--)
	{
		*val /= 10.0f;
	}

	if (displayval[0] == '-') {
		*val *= (-1);
	}
}

int countNumberofDigits(long long int val) {
	int count = 0;

	if (val == 0) {
		return 0;
	}
	else if (val < 0) {
		val *= (-1);
		while (val != 0)
		{
			count++;
			val /= 10;
		}
		return count; //Adjust for negative sign and for loop
	}
	else {
		while (val != 0)
		{
			count++;
			val /= 10;
		}
		return count - 1; //Adjust to for loop
	}
}

void doubleTostring(long double val, char *str, int precision) {
	displayvalTrack = 0; // Clear displayTrack

	long long int numBeforedot = (long long int)val;
	long double numAfterdot = val - (long double)numBeforedot;
	int count = countNumberofDigits(numBeforedot);
	long long int stripDecimal = 0;
	if (val == 0) {
		str[0] = '0';
	} else if (val < 0) {
		numBeforedot *= (-1.0f);
		numAfterdot *= (-1.0f);
		if (precision > 0) {
			str[count + 1] = '.'; //adjust for the '-'
			displayvalTrack++;
		}
		//The +2 adjust for '.' placement
		for (int i = count + 2; i < (2 + count + precision); i++) {
			numAfterdot *= 10.0f;
			stripDecimal = (long long int)numAfterdot;
			str[i] = stripDecimal + '0';
			numAfterdot = numAfterdot - (long double)stripDecimal;
			displayvalTrack++;
		}
		for (; count >= 0; count--) {
			str[count] = (numBeforedot % 10) + '0';
			numBeforedot /= 10;
			displayvalTrack++;
		}
		str[0] = '-';
		displayvalTrack++;

	}
	else {
		if (precision > 0) {
			str[count + 1] = '.';
			displayvalTrack++;
		}
		//The +2 adjust for '.' placement
		for (int i = count + 2; i < (2 + count + precision); i++) {
			numAfterdot *= 10.0f;
			stripDecimal = (long long int)numAfterdot;
			str[i] = stripDecimal + '0';
			numAfterdot = numAfterdot - (long double)stripDecimal;
			displayvalTrack++;
		}

		for (; count >= 0; count--) {
			str[count] = (numBeforedot % 10) + '0';
			numBeforedot /= 10;
			displayvalTrack++;
		}
	}
	return;
}

void clearDisplayVal() {
	for (int i = 0; i < displayvalTrack; i++) {
		displayval[i] = BLANK;
	}
	displayvalTrack = 0;
	displayvalDecimaltrack = 0;
	isDecimal = FALSE;
	isNegative = FALSE;
}

void clearValue(long double *val) {
	*val = 0;
}

void clearValues() {
	val_A = 0;
	val_B = 0;
	valp_A = 0;
	valp_B = 0;
}

void setValStringWithPrecision() {
	int precision = 0;
	int numLen = 0;
 
	if (valp_A >= valp_B) {
		precision = (valp_A - 1);
		numLen = countNumberofDigits((long int)val_A);

		if (decSave > precision) {
			precision = decSave;
		}
		else { decSave = precision; }

		if ((numLen + precision) <= STRINGMAX) {
			//doubleTostring(val_A, displayval, valp_A - 1);
			doubleTostring(val_A, displayval, precision);
		}
		else {
			while ((numLen + precision) > STRINGMAX)
			{
				precision--;
			}

			//carry over dec
			decSave = precision;

			if (precision > 0) {
				decSave = precision;
				doubleTostring(val_A, displayval, precision - 1);
			}
			else {
				decSave = 0;
				doubleTostring(val_A, displayval, 0);
			}
		}
	}
	else {
		precision = (valp_B - 1);
		numLen = countNumberofDigits((long int)val_A);

		//carry over dec
		if (decSave > precision) {
			precision = decSave;
		}
		else { decSave = precision; }

		if ((numLen + precision) <= STRINGMAX) {
			//doubleTostring(val_A, displayval, valp_B - 1); 
			doubleTostring(val_A, displayval, precision);
		}
		else {
			while ((numLen + precision) > STRINGMAX)
			{
				precision--;
			}

			//carry over dec
			decSave = precision;
			
			if (precision > 0) {
				decSave = precision;
				doubleTostring(val_A, displayval, precision - 1);
			}
			else {
				decSave = 0;
				doubleTostring(val_A, displayval, 0);
			}
		}
	}

}

void setValStringWithPrecision_MAX() {
	int precision = STRINGMAX;
	int numLen = countNumberofDigits((long int)val_A);

	while ((numLen + precision) > STRINGMAX)
	{
		precision--;
	}
	valp_A = precision;
	if (precision > 0) {
		//Carry over decSave
		if (decSave > precision) { precision = decSave; }
		else { decSave = precision; }
		doubleTostring(val_A, displayval, precision - 1);
	}
	else {
		decSave = 0;
		doubleTostring(val_A, displayval, 0);
	}
}

void add_operation() {
	if (operationMode != PLUS) {
		operationMode = PLUS; 
	}

	if (!isFirstNumberSet) {
		isFirstNumberSet = TRUE;
		stringTodouble(&val_A);
		valp_A = displayvalDecimaltrack;
		clearDisplayVal();
	}
	else if (!isSecondNumberSet) {
		isSecondNumberSet = TRUE;
		stringTodouble(&val_B);
		valp_B = displayvalDecimaltrack;
		clearDisplayVal();
		val_A = val_A + val_B;

		//SetValStringWithPrecision  
		setValStringWithPrecision();
	}
	else if (isFirstNumberSet == TRUE && isSecondNumberSet == TRUE) {
		valp_A = displayvalDecimaltrack;
		clearDisplayVal();
		isSecondNumberSet = FALSE;
	}
}

void subtraction_function() {
	if (operationMode != MINUS) {
		operationMode = MINUS;
	}

	if (!isFirstNumberSet) {
		isFirstNumberSet = TRUE;
		stringTodouble(&val_A);
		valp_A = displayvalDecimaltrack;
		clearDisplayVal();
	}
	else if (!isSecondNumberSet) {
		isSecondNumberSet = TRUE;
		stringTodouble(&val_B);
		valp_B = displayvalDecimaltrack;
		clearDisplayVal();
		val_A = val_A - val_B;

		//SetValStringWithPrecision  
		setValStringWithPrecision();

	}
	else if (isFirstNumberSet == TRUE && isSecondNumberSet == TRUE) {
		stringTodouble(&val_A);
		valp_A = displayvalDecimaltrack;
		clearDisplayVal();
		isSecondNumberSet = FALSE;
	}
}

void multiplication_function() {
	if (operationMode != MULTIPLY) {
		operationMode = MULTIPLY;
	}

	if (!isFirstNumberSet) {
		isFirstNumberSet = TRUE;
		stringTodouble(&val_A);
		valp_A = displayvalDecimaltrack;
		clearDisplayVal();
	}
	else if (!isSecondNumberSet) {
		isSecondNumberSet = TRUE;
		stringTodouble(&val_B);
		valp_B = displayvalDecimaltrack;
		clearDisplayVal();
		val_A = val_A * val_B;

		//SetValStringWithPrecision  
		setValStringWithPrecision();

	}
	else if (isFirstNumberSet == TRUE && isSecondNumberSet == TRUE) {
		stringTodouble(&val_A);
		valp_A = displayvalDecimaltrack;
		clearDisplayVal();
		isSecondNumberSet = FALSE;
	}
}

void division_function() {
	if (operationMode != DIVIDE) {
		operationMode = DIVIDE;
	}

	if (!isFirstNumberSet) {
		isFirstNumberSet = TRUE;
		stringTodouble(&val_A);
		valp_A = displayvalDecimaltrack;
		clearDisplayVal();
	}
	else if (!isSecondNumberSet) {
		isSecondNumberSet = TRUE;
		stringTodouble(&val_B);
		valp_B = displayvalDecimaltrack;
		clearDisplayVal();
		val_A = val_A / val_B;

		//SetValStringWithPrecision  
		setValStringWithPrecision_MAX();
	}
	else if (isFirstNumberSet == TRUE && isSecondNumberSet == TRUE) {
		stringTodouble(&val_A);
		valp_A = displayvalDecimaltrack;
		clearDisplayVal();
		isSecondNumberSet = FALSE;
	}
}