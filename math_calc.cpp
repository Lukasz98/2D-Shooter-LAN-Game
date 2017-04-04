#include "math_calc.h"
#include <iostream>


/*
     dest /|beta
         / |
        /  |
   c   /   | a
      /    |
	 /     |
alfa/______|
 pos   b
*/


sf::Vector2f Math_calc::Get_xy_SpeedRatio(sf::Vector2f _pos, sf::Vector2f _dirPos)
{
	float b =  _dirPos.x - _pos.x;
	//b = Math_calc::MakePositive(b);
	
	float a = _dirPos.y - _pos.y;
	//float a = _pos.y -_dirPos.y;
	//a = Math_calc::MakePositive(a);
	
	float c = sqrt( b * b + a * a );
	//c = Math_calc::MakePositive(c);
	
	float xRatio = b / c;
	float yRatio = a / c;
//std::cout<<"xRatio: "<<xRatio<<", yRatio: "<<yRatio<<", c: "<<c<<std::endl;	
//std::cout<<_dirPos.y<<std::endl;
	return sf::Vector2f(xRatio, yRatio);
}


float Math_calc::MakePositive(float _num)
{
	return _num > 0.0f ? _num : _num * -1.0f;
}


float Math_calc::GetSinus(sf::Vector2f _pos, sf::Vector2i _dirPos)
{
	float b =  _dirPos.x - _pos.x;
	float a = _dirPos.y - _pos.y;
	float c = sqrt( b * b + a * a );
	b = Math_calc::MakePositive(b);
	a = Math_calc::MakePositive(a);
	
	std::cout << "asin a / c = " << (float) ((asin(a / c) *57.0f)) <<std::endl;
	
	return -(180 - (asin(a / c) / 2*3.14f * 360)) ; //sin(a / c);
}
