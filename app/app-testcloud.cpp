#include "math.h"
#include "stdlib.h"
#include <string>
#include "../PcrLib/pcrlib.h"
#include "./data/bunny.h"

namespace pcrapp
{
#if 0
	void generateWave(int w, int h, pcrlib::IPcrLib* pLib)
	{
	//	float sz = 10.0f;
        float step_u = 1.0f/(float)w;
        float step_v = 1.0f/(float)h;
		float nf = 2.0f;
        for (int vv = -h/2;  vv< h/2; vv++)
		{
            for (int uu = -w/2; uu < w/2; uu++)
			{
                float u = step_u * (float)uu;
                float v = step_v * (float)vv;
                float up = 2.0f * 3.1415f* u;
                float vp = 2.0f * 3.1415f* v;
                float r = 100.0f*(float)( 0.2f + cos(up*nf)*cos(up*nf) *sin(vp*1.1f) * sin(vp*1.1f));
 				r = (float)fabs(r);
                float xx  =  r* (float) ( sin(vp) * cos(up));
                float yy  =  r* (float) ( sin(vp) * sin(up));
                float zz  =  r * (float)cos(vp);
                //unsigned char c = (unsigned char)(255.0f * cos(vp*nf)*cos(vp*nf));
				unsigned short c555 =  (31 << 5) ;
                pLib->addPoint(xx, yy, zz*0.5f, c555);
			}
		}
	}

	
#endif

	

	static int total_points = 0;
	static void addBunny(float cx, float cy, float cz, pcrlib::IPcrLib* pLib,unsigned  int col,float sc)
	{
		static int n_call = 0;
		float ySzie = 0.154334;
		int numFloats = sizeof(bunny_points) / sizeof(float);
		int skip_ndx = 1;
		unsigned char val = rand() & 0xFF;
		float ang =  (float)val;
		float sinF = (float)sin(ang);
		float cosF = (float)cos(ang);
		float *pt = bunny_points;
		for (int i = 0; i < numFloats; i += 3 * skip_ndx)
		{
			float xr = pt[0] * cosF + pt[2] * sinF;
			float yr = pt[1] ;
			float zr = -pt[0] * sinF + pt[2] * cosF;
			float xf = xr * sc + cx;
			float yf = yr * sc + cy + ySzie*sc*0.5f;
			float zf = zr * sc + cz;
			pLib->addPoint(xf, zf, yf, col);
			total_points++;
			pt += 3 * skip_ndx;
		}
		n_call++;
	}

	static void prepareData(int w, int h, pcrlib::IPcrLib* pLib, pcrlib::LibCallback *pCb)
	{
		int numFloats = sizeof(bunny_points) / sizeof(float);
		//Get bdbox
		float *pt = bunny_points;
		float x_min = pt[0], x_max = pt[0];
		float y_min = pt[1], y_max = pt[1]; 
		float z_min = pt[2], z_max = pt[2];
		for (int i = 0; i < numFloats; i += 3,pt+=3 ) 
		{
			if (pt[0] < x_min) x_min = pt[0];
			if (pt[1] < y_min) y_min = pt[1];
			if (pt[2] < z_min) z_min = pt[2];
			if (pt[0] > x_max) x_max = pt[0];
			if (pt[1] > y_max) y_max = pt[1];
			if (pt[2] > z_max) z_max = pt[2];
		}

		//printf("%f %f %f %f %f %f \n", x_min, x_max, y_min, y_max, z_min, z_max);
		//printf("ysize =%f\n ", y_max - y_min);
		
		float cx = (x_min + x_max) *0.5f;
		float cy = (y_min + y_max) *0.5f;
		float cz = (z_min + z_max) *0.5f;
		pt = bunny_points;
		for (int i = 0; i < numFloats; i += 3, pt += 3)
		{
			pt[0] -= cx;
			pt[1] -= cy;
			pt[2] -= cz;
		}
	}

	void generateWave(int w, int h, pcrlib::IPcrLib* pLib, pcrlib::LibCallback *pCb)
	{
		prepareData(w, h, pLib, pCb);
		unsigned int floorColor =  15 | (15 << 5) | (15 << 10);
		srand(12345);
		float step = 0.3f;
		for (int y = 0; y < 60; y++) {
			for (int x = 0; x < 60; x++) {
				unsigned int color = rand() & 0xFFFF;
				float scale = 0.25f +(float)(rand() & 0xFF) / 255.0f;
				addBunny((float)x*step, 0.0f, (float)y*step, pLib,color,scale);

				float xb = (float)x*step;
				float yb = (float)y*step;
				for (int t = 0; t < 100; t++) {
					float pp1 = (float)(rand() & 0xFF) / 255.0f;
					float pp2 = (float)(rand() & 0xFF) / 255.0f;
					pLib->addPoint(xb + step * pp1,  yb + step * pp2, 0.0f, floorColor);
					total_points++;
				}
			}
		}
		
		pCb->message(std::string("\n NUMBER OF POINTS: " + std::to_string(total_points) + "\n").c_str());
	}

}//namespace pcrapp
