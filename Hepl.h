#pragma once


//////////////////////////////////////////////////////////////////////////
// Создаем прямоугольник размером 70х100
sf::RectangleShape rectangle(sf::Vector2f(70.f, 100.f));

// Перемещаем его в нижний ряд справа от многоугольника
rectangle.move(165, 150);

// Устанавливаем ему цвет
rectangle.setFillColor(sf::Color(175, 180, 240));

//window.clear();
///////////////////////////////////////////////////////////////////////////

// Создаем круг радиусом 50
CircleShape circle(50.f);
circle.setFillColor(Color(230, 0, 230)); // закрашиваем наш круг 
circle.setOutlineThickness(15.f); // устанавливаем толщину контура круга
circle.setOutlineColor(Color(80, 220, 50)); // устанавливаем цвет контура
circle.move(15, 15); // перемещаем наш круг для корректного отображения в окне
window.draw(circle); // отрисовка круга

// Создаем треугольник
CircleShape triangle(65.f, 3);
triangle.setPosition(125, 0); // устанавливаем начальную позицию справа от круга
triangle.setFillColor(Color::Blue); // устанавливаем цвет треугольника - синий
window.draw(triangle); // отрисовка треугольника

// Создаем квадрат
CircleShape square(60.f, 4);
square.setPosition(250, 0); // устанавливаем начальную позицию справа от треугольника
square.setFillColor(Color::Red); // устанавливаем цвет квадрата - красный
window.draw(square); // отрисовка квадрата

// Создаем октагон
CircleShape octagon(60.f, 8);
octagon.setPosition(380, 0); // устанавливаем начальную позицию справа от квадрата
octagon.setFillColor(Color::Cyan); // устанавливаем цвет октагона - бирюзовый
window.draw(octagon); // отрисовка октагона

// Отрисовка прямоугольника
window.draw(rectangle);

// Отрисовка октагона
window.draw(octagon);

// Заготовка фигуры многоугольника 
ConvexShape convex;

// Устанавливаем ему 5 вершин
convex.setPointCount(5);

// Устанавливаем координаты вершин
convex.setPoint(0, Vector2f(0.f, 0.f));
convex.setPoint(1, Vector2f(150.f, 10.f));
convex.setPoint(2, Vector2f(120.f, 90.f));
convex.setPoint(3, Vector2f(30.f, 100.f));
convex.setPoint(4, Vector2f(5.f, 50.f));

// Устанавливаем цвет многоугольника - черный
convex.setFillColor(Color::Black);

// Теперь сдвинем его вниз и чуть-чуть вправо
convex.move(1, 150);

// Отрисовка многоугольника
window.draw(convex);

// Линия с заданной толщиной
RectangleShape line_with_thickness(Vector2f(130.f, 5.f));

// Поворачиваем её на 45 градусов
line_with_thickness.rotate(45.f);

// Устанавливаем цвет
line_with_thickness.setFillColor(Color(15, 180, 140));

// Перемещаем её в нижний ряд справа от прямоугольника
line_with_thickness.move(250, 150);

// Отрисовка линии
window.draw(line_with_thickness);

// Линия с нулевой толщиной. Создаём её в качестве массива вершин типа Vertex
Vertex line_without_thickness[] =
{
	// Координата первой вершины
	Vertex(Vector2f(390.f, 240.f)),
	// Координата второй вершины
	Vertex(Vector2f(470.f, 150.f))
};

// Устанавливаем цвет линии - черный
line_without_thickness->color = Color::Black;

// Отрисовка линии
window.draw(line_without_thickness, 2, Lines);