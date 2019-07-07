
#ifndef _PCRLIB_H_
#define _PCRLIB_H_



namespace pcrlib 
{
	typedef void(*PcrErrorHandler)(const char *pMessage);

	struct Camera {
		float pos[3];   //position x,y,z
		float lookAt[3];
		float up[3];
		float zNear;
		float zFar;
		float fovInRadians;
		bool isPerspective;
	};

    class  IPcrLib
	{
	public:
		virtual int runTest() = 0;
		virtual int render(const Camera &cam, int destWidth, int destHeight) = 0;

		static PcrErrorHandler setErrHandler(PcrErrorHandler errh) ;
		static IPcrLib* Init();
	};
}


#endif