#ifndef _Polygon_
#define _Polygon_

#include <iostream>
#include <cmath>

#define Pi  3.141592f
#define Rad 180 / Pi
#define epsilon 1.0e-3f

namespace Third_Lab{

	//Структура задания точки на плоскости в декартовой системе координат
	struct Point{
		float x, y;
		
		Point() : x(0), y(0){}
		
		Point(float x0, float y0){
			x = x0;
			y = y0;
		}

		Point& Point::operator += (const Point &Node){
			x += Node.x;
			y += Node.y;
			return *this;
		}

		Point& Point::operator -= (const Point &Node){
			x -= Node.x;
			y -= Node.y;
			return *this;
		}
	};

	struct RotatePolygon{
		float Angle;
		Point Dot;
		RotatePolygon(Point Dot0, float Angle0){
			Angle = Angle0;
			Dot = Dot0;
		}
	};

	//Класс определяет многоугольник
	class Polygon{
	private:
		static const int QUOTA = 1;
		int AmountNode = 0;
		Point *NodeArray;
	public:
		//Конструкторы/Деструктор
		Polygon() :AmountNode(0), NodeArray(new Point[0]){};

		Polygon(const Point &Node) : AmountNode(QUOTA), NodeArray(new Point[QUOTA]){ NodeArray[0] = Node; }

		Polygon(float x0, float y0) : AmountNode(QUOTA), NodeArray(new Point[QUOTA]){ NodeArray[0] = Point(x0, y0); }

		Polygon(int AmountNodePreset, Point *NodeArrayPreset){
			AmountNode = 0;
			for (int i = 0; i < AmountNodePreset; i++){
				Point NodeTmp = NodeArrayPreset[i];
				Polygon FigureTmp(NodeTmp);
				Polygon:: operator += (FigureTmp);
			}
		}

		Polygon(const Polygon &);

		~Polygon(){ AmountNode = 0; delete[] NodeArray; }

		//Входной/выходной потоки

		friend std::ostream & operator <<(std::ostream &, const Polygon &);
		friend std::istream & operator >>(std::istream &, Polygon &);

		//Геттеры
		int GetAmountNode() const { return AmountNode; }

		const Point operator [] (int Number) const {
			if (Number > AmountNode || Number < 1)
				throw std::exception("invalid parameter \"Number\"");
			else
				return NodeArray[Number - 1];
		}

		//Другие методы
		Polygon& operator <<= (const Polygon &vector);

		Polygon& operator ^= (RotatePolygon &Rotate);

		Polygon& operator += (const Polygon &Figure);

		Point GravityCenter() const;

		//Перегруженный оператор присваивания
		Polygon& operator = (const Polygon &);
	};
}

#endif