
#include <iostream>
#include <fstream>
void mystop()
{
    std::cout << "\nPause\n";
    getchar();
}

#define  stop  {mystop();}

class Point
{
private:
    double m_x, m_y, m_z;

public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0) : m_x(x), m_y(y), m_z(z)
    {
    }

    friend std::ostream& operator<< (std::ostream& out, const Point& point);
    friend std::ofstream& operator<< (std::ofstream& out, const Point& point);
    friend std::istream& operator>> (std::istream& in, Point& point);
    friend std::ifstream& operator>> (std::ifstream& in, Point& point);
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ")";
    return out;
}

std::ofstream& operator<< (std::ofstream& out, const Point& point)
{
 
    out << "Point: m_x =" << point.m_x << ",m_y = " << point.m_y << ", m_z = " << point.m_z << ")";
    return out;
}

std::istream& operator>> (std::istream& in, Point& point)
{
    std::cout<<"\nistream";

    in >> point.m_x;
    in >> point.m_y;
    in >> point.m_z;

    return in;
}

std::ifstream& operator>> (std::ifstream& in, Point& point)
{
    std::cout<<"\nifstream";

    char buff[100]="";

    in >> buff;
    in >> buff;
    in >> point.m_x;
    in >> buff;
    in >> point.m_y;
    in >> buff;
    in >> point.m_z;
    in >> buff;
    return in;
}

int main()
{
    //std::cout << "Enter a point: \n";
    //Point point;
    //std::cin >> point;
    //std::cout << "You entered: " << point << '\n';

    Point point2(1.,2.,3.);
    std::ofstream fout("point.txt");
    fout << "\npoint:\n" << point2 << std::endl;
    fout.close();
    stop
    std::ifstream fin;
    fin.open("./point.txt");
    
    Point p;
    if (fin.is_open())
    {
        std::cout << "\nfile is opened";
    	fin >> p;
    } else std::cout << "\nfile open is error";

    fin.close();
    stop
    std::cout<<"\n"<< p << ";";
    stop
    return 0;
}
