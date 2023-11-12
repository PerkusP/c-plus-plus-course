#include <iomanip>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <math.h>
#include <cstdint>

class Figure
{
public:
    virtual std::string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure
{
public:
    Triangle(uint16_t a, uint16_t b, uint16_t c) : m_a(a),
                                                   m_b(b),
                                                   m_c(c)
    {
    }

    std::string Name() const final
    {
        return "TRIANGLE";
    }

    double Perimeter() const final
    {
        return m_a + m_b + m_c;
    }
    double Area() const final
    {
        double p = (m_a + m_b + m_c) / 2;
        return sqrt(p * (p - m_a) * (p - m_b) * (p - m_c));
    }

private:
    uint16_t m_a;
    uint16_t m_b;
    uint16_t m_c;
};

class Rectangle : public Figure
{
public:
    Rectangle(uint16_t width, uint16_t height) : m_width(width),
                                        m_height(height)
    {
    }

    std::string Name() const final
    {
        return "RECT";
    }

    double Perimeter() const final
    {
        return 2 * m_width + 2 * m_height;
    }

    double Area() const final
    {
        return m_width * m_height;
    }

private:
    uint16_t m_width;
    uint16_t m_height;
};

class Circle : public Figure
{
public:
    Circle(int radius) : m_radius(radius)
    {
    }

    std::string Name() const final
    {
        return "CIRCLE";
    }

    double Perimeter() const final
    {
        return 2 * m_pi * m_radius;
    }

    double Area() const final
    {
        return m_radius * m_radius * m_pi;
    }

private:
    uint16_t m_radius;
    const double m_pi = 3.14;
};

std::shared_ptr<Figure> CreateFigure(std::istream &is)
{
    std::string figure;
    is >> figure;
    is.ignore(1);
    if (figure == "RECT")
    {
        uint16_t a;
        uint16_t b;
        is >> a;
        is.ignore(1);
        is >> b;
        return std::make_shared<Rectangle>(a, b);
    }

    else if (figure == "TRIANGLE")
    {
        uint16_t a;
        uint16_t b;
        uint16_t c;
        is >> a;
        is.ignore(1);
        is >> b;
        is.ignore(1);
        is >> c;
        return std::make_shared<Triangle>(a, b, c);
    }

    else if (figure == "CIRCLE")
    {
        uint16_t radius;
        is >> radius;
        return std::make_shared<Circle>(radius);
    }

    return nullptr;
}

int main()
{
    std::vector<std::shared_ptr<Figure>> figures;
    for (std::string line; std::getline(std::cin, line);)
    {
        std::istringstream is(line);
        std::string command;
        is >> command;
        if (command == "ADD")
        {
            is >> std::ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT")
        {
            for (const auto &current_figure : figures)
            {
                std::cout << std::fixed << std::setprecision(3)
                          << current_figure->Name() << " "
                          << current_figure->Perimeter() << " "
                          << current_figure->Area() << std::endl;
            }
        }
    }
    return 0;
}
