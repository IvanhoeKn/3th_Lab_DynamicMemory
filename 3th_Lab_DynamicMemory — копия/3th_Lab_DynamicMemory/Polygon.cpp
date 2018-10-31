#include "Polygon.h"
#include <algorithm>

namespace Third_Lab{
	const float eps = 1e-9f;

	//Копирующий конструктор
	Polygon::Polygon(const Polygon &Tmp) : AmountNode(Tmp.AmountNode), NodeArray(new Point[Tmp.AmountNode]){
		for (int i = 0; i < AmountNode; i++){
			int j = i + 1;
			NodeArray[i] = Tmp[j];
		}
	}

	//------------------------------------------------------------

	//Входной/выходной потоки
	std::ostream & operator << (std::ostream &s, const Polygon &Figure){
		if (Figure.AmountNode == 0)
			s << "Polygon does not exist";
		else{
			s << "Amount of nodes --> " << Figure.AmountNode << std::endl;
			s << "Nodes:" << std::endl;
			for (int i = 0; i < Figure.AmountNode; i++)
				s << "{ " << Figure.NodeArray[i].x << "; " << Figure.NodeArray[i].y << " } ";
		}
		s << std::endl;
		return s;
	}

	//------------------------------------------------------------

	std::istream & operator >> (std::istream &s, Polygon &Figure) {
		int Amount;
		float x, y;
		if (s.good()){
			while (s >> x >> y){
				//float x, y;
				//s >> x >> y;
				if (s.good())
					Figure += Polygon(x, y);
				else
					break;
			}
		}
		s.clear();
		s.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return s;
	}

	//------------------------------------------------------------

	//Другие методы
	Polygon& Polygon::operator <<= (const Polygon &vector){
		int Amount = AmountNode;
		for (int i = 0; i < Amount; i++)
			NodeArray[i] += vector.NodeArray[0];
		return *this;
	}

	//------------------------------------------------------------

	Polygon& Polygon::operator ^= (RotatePolygon &Rotate){
		int Amount = AmountNode;
		
		Rotate.Angle = (Rotate.Angle * Pi) / 180;
		
		for (int i = 0; i < Amount; i++){
			Point NewPoint = { NULL, NULL };
			Point tmp = NodeArray[i];
			tmp -= Rotate.Dot;
			NewPoint.x = tmp.x * cos(Rotate.Angle) - tmp.y * sin(Rotate.Angle);
			NewPoint.y = tmp.x * sin(Rotate.Angle) + tmp.y * cos(Rotate.Angle);
			NewPoint += Rotate.Dot;
			NodeArray[i] = NewPoint;
		}
		return *this;
	}

	//------------------------------------------------------------

	bool RealLess(float a, float b){
		if (b - a > eps)
			return true;
		else
			return false;
	}

	float VektorMulti(float ax, float ay, float bx, float by){
		return ax * by - bx * ay;
	}

	int CheckPolygon(Point *NodeArr, Point Node, int Num, int Amount){
		Point Node01, Node02;
		Node02 = NodeArr[Amount];
		Node01 = NodeArr[1];
		//------------------------------------------------------------

		int Flag = 1;
		int count = 0;
		for (int i = 0; i < Amount - 1; i++){
			int tmp = count + 1;
		
			float v1 = VektorMulti(NodeArr[tmp].x - NodeArr[count].x, NodeArr[tmp].y - NodeArr[count].y, Node.x - NodeArr[count].x, Node.y - NodeArr[count].y);
			float v2 = VektorMulti(NodeArr[tmp].x - NodeArr[count].x, NodeArr[tmp].y - NodeArr[count].y, Node01.x - NodeArr[count].x, Node01.y - NodeArr[count].y);
			float v3 = VektorMulti(Node01.x - Node.x, Node01.y - Node.y, NodeArr[count].x - Node.x, NodeArr[count].y - Node.y);
			float v4 = VektorMulti(Node01.x - Node.x, Node01.y - Node.y, NodeArr[tmp].x - Node.x, NodeArr[tmp].y - Node.y);
			if (RealLess(v1 * v2, 0) && RealLess(v3 * v4, 0)){
				Flag = 0;
				break;
			}

			float v1_ = VektorMulti(NodeArr[tmp].x - NodeArr[count].x, NodeArr[tmp].y - NodeArr[count].y, Node.x - NodeArr[count].x, Node.y - NodeArr[count].y);
			float v2_ = VektorMulti(NodeArr[tmp].x - NodeArr[count].x, NodeArr[tmp].y - NodeArr[count].y, Node02.x - NodeArr[count].x, Node02.y - NodeArr[count].y);
			float v3_ = VektorMulti(Node02.x - Node.x, Node02.y - Node.y, NodeArr[count].x - Node.x, NodeArr[count].y - Node.y);
			float v4_ = VektorMulti(Node02.x - Node.x, Node02.y - Node.y, NodeArr[tmp].x - Node.x, NodeArr[tmp].y - Node.y);
			if (RealLess(v1_ * v2_, 0) && RealLess(v3_ * v4_, 0)){
				Flag = 0;
				break;
			}

			count++;
		}

		return Flag;
	}

	Polygon& Polygon::operator += (const Polygon &Figure){
		int location, tmp = 1;
		Point Node0 = Figure[tmp];
		int Flag;
		if (AmountNode < 3){
			Flag = 1;
		}
		else
			Flag = 0;

		int Copy = 0;
		for (int i = 0; i < AmountNode; i++)
			if (NodeArray[i].x - Node0.x == 0 && NodeArray[i].y - Node0.y == 0){
				Copy = 1;
				break;
			}

		if (!Flag){
			location = AmountNode;
			Flag = CheckPolygon(NodeArray, Node0, location, AmountNode);
		}

		//------------------------------------------------------------
		
		if (Flag && !Copy){
			AmountNode++;
			Point *ArrTmp = NodeArray;
			NodeArray = new Point[AmountNode];
			for (int i = 0; i < AmountNode - 1; i++)
				NodeArray[i] = ArrTmp[i];
			NodeArray[AmountNode - 1] = Node0;
			delete[] ArrTmp;
		}

		return *this;
	}

	//------------------------------------------------------------

	Point Polygon::GravityCenter() const{
		Point Barycenter = { 0, 0 };
		int Amount = AmountNode;
		float A = 0;
		for (int i = 0; i < Amount; i++)
			if (i + 1 == Amount){
				A += NodeArray[i].x * NodeArray[0].y - NodeArray[0].x * NodeArray[i].y;
				Barycenter.x += (NodeArray[i].x + NodeArray[0].x) * (NodeArray[i].x * NodeArray[0].y - NodeArray[0].x * NodeArray[i].y);
				Barycenter.y += (NodeArray[i].y + NodeArray[0].y) * (NodeArray[i].x * NodeArray[0].y - NodeArray[0].x * NodeArray[i].y);
			}
			else{
				A += NodeArray[i].x * NodeArray[i + 1].y - NodeArray[i + 1].x * NodeArray[i].y;
				Barycenter.x += (NodeArray[i].x + NodeArray[i + 1].x) * (NodeArray[i].x * NodeArray[i + 1].y - NodeArray[i + 1].x * NodeArray[i].y);
				Barycenter.y += (NodeArray[i].y + NodeArray[i + 1].y) * (NodeArray[i].x * NodeArray[i + 1].y - NodeArray[i + 1].x * NodeArray[i].y);
			}
		A = A / 2;
		Barycenter.x = Barycenter.x / (6 * A);
		Barycenter.y = Barycenter.y / (6 * A);
		return Barycenter;
	}

	//------------------------------------------------------------

	Polygon & Polygon::operator = (const Polygon &Tmp)
	{
		if (this != &Tmp){
			AmountNode = Tmp.GetAmountNode();
			NodeArray = new Point[AmountNode];
			for (int i = 0; i < AmountNode; i++)
				NodeArray[i] = Tmp.NodeArray[i];
		}
		return *this;
	}
}