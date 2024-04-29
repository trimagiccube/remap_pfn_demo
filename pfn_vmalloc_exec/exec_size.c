unsigned int test_call(unsigned int arg)
{
	if(arg > 256) {
		return 2;
	} else if(arg < 256) {
		return 1;
	} else {
		return 0;
	}
}
