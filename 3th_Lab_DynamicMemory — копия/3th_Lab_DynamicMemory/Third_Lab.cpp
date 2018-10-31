// Application.cpp: определяет точку входа для консольного приложения.
//

#include "Polygon.h"
#include <iostream>

//------------------------------------------------------------

using namespace Third_Lab;

//------------------------------------------------------------

template <class Number>
bool GetNumber(Number &);
int GetInteger();
float GetFloat();
int dialog(const char *, int);
int D_CreationSingleVertex(Polygon &);
int D_CreatingArrayVertex(Polygon &);
int D_OutputInstances(Polygon &);
int D_GetCoordinates(Polygon &);
int D_GetCenterGravity(Polygon &);
int D_Rotate(Polygon &);
int D_Move(Polygon &);
int D_Add(Polygon &);

//------------------------------------------------------------

template <class Number>
bool GetNumber(Number &x){
	std::cout << "--> ";
	std::cin >> x;
	if (!std::cin.good())
		return false;

	return true;
}

int GetInteger(){
	int x, Flag = 0;
	const char *FlagError = "";
	do{
		std::cout << FlagError;
		FlagError = "You are wrong! Please, repeat enter!\n";
		Flag = 0;
		if (!GetNumber(x)){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			Flag = -1;
		}
	} while (Flag < 0);

	return x;
}

//------------------------------------------------------------

float GetFloat(){
	float x;
	int Flag = 0;
	const char *FlagError = "";
	do{
		std::cout << FlagError;
		FlagError = "You are wrong! Please, repeat enter!\n";
		Flag = 0;
		if (!GetNumber(x)){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			Flag = -1;
		}
	} while (Flag < 0);

	return x;
}

//------------------------------------------------------------

int dialog(const char *msgs[], int N)
{
	char *errmsg = "";
	int rc;
	int i;
	do{
		puts(errmsg);
		errmsg = "You are wrong. Repeate, please!";
		for (i = 0; i < N; ++i)
			puts(msgs[i]);
		puts("Make your choice: ");
		rc = GetInteger();
	} while (rc < 0 || rc >= N);
	return rc;
}

//------------------------------------------------------------

int D_CreationSingleVertex(Polygon &Figure){
	float x, y;
	const char *InputError = "";
	std::cout << "Enter Point\n";
	//------------------------------------------------------------
	std::cout << "Enter x\n";
	x = GetFloat();

	std::cout << "Enter y\n";
	y = GetFloat();
	//------------------------------------------------------------
	Figure = Polygon(Point(x, y));

	return 1;
}

//------------------------------------------------------------

int D_CreatingArrayVertex(Polygon &Figure){
	/*int Amount;
	const char *InputError = "";
	std::cout << " Enter amount of vertices\n";
	do{
		std::cout << InputError;
		Amount = GetInteger();
		InputError = "You are wrong! Repeat enter!\n";
	} while (Amount < 2);
	//------------------------------------------------------------
	Point NodeArr[13];
	for (int i = 0; i < Amount; i++){
		float x, y;
		std::cout << "Enter Point [" << i + 1 << "]\n";
		//------------------------------------------------------------
		std::cout << "Enter x\n";
		x = GetFloat();

		std::cout << "Enter y\n";
		y = GetFloat();
		//------------------------------------------------------------
		NodeArr[i] = { x, y };
	}



	Polygon Figure0(Amount, NodeArr);
	Figure = Figure0;
	std::cout << Figure;*/
	std::cin >> Figure;

	return 1;
}

//------------------------------------------------------------

int D_OutputInstances(Polygon &Figure){
	std::cout << Figure;

	return 1;
}

//------------------------------------------------------------

int D_GetCoordinates(Polygon &Figure){
	int Number;
	Point Node;
	const char *InputError = "";

	int AmountNode = Figure.GetAmountNode();

	std::cout << " Enter amount of vertices\n";
	do{
		std::cout << InputError;
		Number = GetInteger();
		InputError = "You are wrong! Repeat enter!\n";
	} while (Number < 1 || Number > AmountNode);

	Node = Figure[Number];
	std::cout << "Coordinates of choosing Node:" << std::endl;
	std::cout << "{ " << Node.x << ", " << Node.y << " }" << std::endl;

	return 1;
}

//------------------------------------------------------------

int D_GetCenterGravity(Polygon &Figure){
	Point Node = Figure.GravityCenter();
	std::cout << "Gravity center of Polygon:" << std::endl;
	std::cout << "{ " << Node.x << ", " << Node.y << " }" << std::endl;

	return 1;
}

//------------------------------------------------------------

int D_Rotate(Polygon &Figure){
	Point Node = { NULL, NULL };
	float x, y, Angle;
	const char *InputError = "";
	std::cout << "Enter Point\n";
	//------------------------------------------------------------
	std::cout << "Enter x\n";
	x = GetFloat();

	std::cout << "Enter y\n";
	y = GetFloat();
	//------------------------------------------------------------
	Node = { x, y };

	std::cout << "Enter Angle\n";
	Angle = GetFloat();

	Figure ^= RotatePolygon(Node, Angle);;

	return 1;
}

//------------------------------------------------------------

int D_Move(Polygon &Figure){
	Point Node = { NULL, NULL };
	float x, y;
	const char *InputError = "";
	std::cout << "Enter Point\n";
	//------------------------------------------------------------
	std::cout << "Enter x\n";
	x = GetFloat();

	std::cout << "Enter y\n";
	y = GetFloat();
	//------------------------------------------------------------
	Node = { x, y };

	Figure <<= Polygon(Node);

	return 1;
}

//------------------------------------------------------------

int D_Add(Polygon &Figure){
	float x, y;
	const char *InputError = "";
	std::cout << "Enter Point\n";
	//------------------------------------------------------------
	std::cout << "Enter x\n";
	x = GetFloat();

	std::cout << "Enter y\n";
	y = GetFloat();
	//------------------------------------------------------------

	Figure += Polygon(Point(x, y));

	return 1;
}

//------------------------------------------------------------

int main(){

	//------------------------------------------------------------

	Polygon Figure;
	int NMenuMain, NMenu;

	int(*PtrMainMenu[])(Polygon &) = { NULL, D_CreationSingleVertex, D_CreatingArrayVertex };
	//int(*PtrMainMenu[])(Polygon &) = { NULL, D_CreationSingleVertex};
	const char *MainMsgs[] = { "0. Quit", "1. Creation of a single vertex", "2. Creating a vertex array" };
	const int MainNMsgs = sizeof(MainMsgs) / sizeof(MainMsgs[0]);

	int(*PtrMenu[])(Polygon &) = { NULL, D_OutputInstances, D_GetCoordinates, D_GetCenterGravity, D_Rotate, D_Move, D_Add };
	const char *Msgs[] = { "0. Finish working with this polygon", "1. Output class instances", "2. Get the coordinates of a point by its number", "3. Get the center of gravity of the polygon", "4. Rotate the polygon", "5. Move the polygon", "6. Add vertex to polygon" };
	const int NMsgs = sizeof(Msgs) / sizeof(Msgs[0]);

	//------------------------------------------------------------

	std::cout << " ***Hello***" << std::endl;

	while (NMenuMain = dialog(MainMsgs, MainNMsgs))
		if (!PtrMainMenu[NMenuMain](Figure))
			break;
		else
			while (NMenu = dialog(Msgs, NMsgs))
				if (!PtrMenu[NMenu](Figure))
					break;

	std::cout << " ***Bye***" << std::endl;

	//------------------------------------------------------------

	return 0;
}