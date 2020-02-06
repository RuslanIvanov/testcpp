#pragma once
enum COLOR { RED, GREEN, BLUE, YELLOW, BLACK, WHITE };
enum SORT { COL, SQ };
class Shape
{
	static SORT m_sortType;
	protected:
	COLOR m_color;
	
	int m_S;
	public:
		Shape(const Shape&);
		Shape(COLOR c = RED);
		virtual ~Shape();
		//  т.к. создаем его объекты , то чисто вирт функцию не вводим  что б не был абстрактным,
		virtual void Inflate(int) = 0 ; 
		virtual int square() = 0;
		virtual void WhereAmI();
		virtual Shape* clone()  const = 0;
		virtual bool operator == (const Shape& s) const  { return ((s.m_color == m_color) && (s.m_S==m_S)); }
		virtual bool operator != (const Shape& s) const  { return ((s.m_color != m_color)||(s.m_S != m_S)); }
		virtual Shape& operator=(const Shape& s)
		{
			if (this == &s)return *this;

			m_color = s.m_color; 
			m_S = s.m_S;
			std::cout << "\nrecopy Shape";
			return *this;
		}

		virtual std::ostream& print(std::ostream& os)=0;
		virtual std::ifstream& read(std::ifstream& in) = 0;
		bool operator<(const Shape& s) const
		{
			if (m_sortType == SQ)
			{
				return m_S < s.m_S;
			}
			else 
			{ 
				return m_color < s.m_color; 
			}
		}

		COLOR getColor() { return m_color; }
		void setColor(COLOR color) {  m_color = color; }
		const char* getColorName();
		void setColorName(const char*);

		static const char* getTypeSort() 
		{
			switch (m_sortType)
			{
				case COL: 
					return "Sort by COLOR";
				case SQ: 
					return "Sort by Sq";
			}
		}

		static void setTypeSort(SORT type) 
		{ 
			m_sortType = type;			
		}
		
};

