#pragma once
class Point
{
	int m_x;
	int m_y;

	public:
		Point(int x = 0, int y = 0);
		Point(const Point& r);

        int GetX() const {return m_x;}
        int GetY() const {return m_y;}

		Point& operator=(const Point&);
		
		Point operator+(const Point&); // РєРѕРїРёСЋ РѕР±СЉРµРєС‚Р° РґРѕР»Р¶РµРЅ РІРѕР·РІСЂ, С‚.С‚. РёСЃРјРµРЅСЏС‚СЊ СЃР°РјРѕРіРѕ СЃРµР±СЏ РЅРµ РЅР°РґРѕ
		Point operator+(int);
        Point& operator+=(const Point&);

		Point operator+();

        bool operator>(const Point& p) const;
        bool operator<(const Point& p) const;
        bool operator==(const Point& p) const;
		
		friend Point& operator+=(Point&, int);
		friend Point operator-(Point& rl, int i);
		friend Point operator-(Point& rl, const Point& rr);
		friend Point operator+(int, Point& r);
		friend Point operator-(const Point& r);

		friend std::ostream& operator<<( std::ostream& os, const Point& p);
		friend std::ostream& operator<<(std::ostream& os, const Point* p);
		void print();
		std::ostream& print(std::ostream& os);
};

Point& operator+=(Point&, int);
Point operator-(Point& rl, int i);
Point operator-(Point& rl, const Point& rr);
Point operator+(int, Point& r);
Point operator-(const Point& r);

std::ostream& operator<<(std::ostream& os, const Point& p);
std::ostream& operator<<(std::ostream& os, const Point* p);
