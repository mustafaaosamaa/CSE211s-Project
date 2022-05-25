int Beef(char weight)
{
	int a,x,y,z;
	x = weight - '0';
	x *= 30;
	y = x / 60;
	z = x % 60;
	a = y * 100 + z;
	return a;
}
