int Chicken(char weight)
{
	int a,x,y,z;
	x = weight - '0';
	x *= 12;
	y = x / 60;
	z = x % 60;
	a = y * 100 + z;
	return a;
}
