
long function(long a, long b, long c, long d) {
	long xx = a * b * c * d;
	long yy = a + b + c + d;
	long zz = utilfunc(xx, yy, xx % yy);
	return zz + 20;
}
