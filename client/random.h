#ifndef  __my_random_h_
#define  __my_random_h_

#include <boost/random.hpp>
class SRand
{
public:
	SRand()
	:_randmaker((boost::rand48::result_type)(time(NULL) ))
	{

	}
	bool  RandBool()
	{
		boost::uniform_int<int> ui(0, 1);
		return  ui(_randmaker) > 0; 
	}
 	float RandFloat()
 	{
  		return  RandFloat(0.0f, 1.0f); 
 	}
 	float RandFloat(float fMin, float fMax)
 	{
 		boost::uniform_real<float> ur(fMin, fMax);
 		return  ur(_randmaker); 
 	}
	double RandDouble()
	{
		return  RandDouble(0.0f, 1.0f); 
	}
	double RandDouble(double fMin, double fMax)
	{
		boost::uniform_real<double> ur(fMin, fMax);
		return  ur(_randmaker); 
	}
	unsigned char RandUChar()
	{
		boost::uniform_int<unsigned char> ui(0, 255);
		return  (unsigned char) ui(_randmaker) ; 
	}
	s32  RandS32(s32 nMin, s32 nMax )
	{
		boost::uniform_int<s32> ui(nMin, nMax);
		return  ui(_randmaker); 
	}
	u32  RandU32()
	{
		boost::uniform_int<u32> ui(0, 100);
		return  ui(_randmaker); 
	}
	u32  RandU32(u32 nMax)
	{
		boost::uniform_int<u32> ui(0, nMax);
		return  ui(_randmaker); 
	}
	u32  RandU32(u32 nMin, u32 nMax)
	{
		boost::uniform_int<u32> ui(nMin, nMax);
		return  ui(_randmaker); 
	}
protected:
	boost::random::rand48 _randmaker;
};

#endif

