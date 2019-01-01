
#ifndef _CAMERA_H
#define _CAMERA_H

class Camera {
	float m_screenX, m_screenY, m_devSize;
public:
	struct vector3 {
		float v[3];
		vector3() { v[0] = v[1] = v[2] = 0.0f; }
		vector3(float x, float y, float z) { v[0] = x; v[1] = y; v[2]=z; }
		float& operator[] (int i) { return v[i]; }
	};
	vector3 m_P,m_D,m_U,m_R,m_L; // position, dir, up, right, look-at.
	float m_zNear, m_zFar;
	Camera();
	static Camera *GetCamera();	
	void FromWorld(float *pWorldIn, float *pInCamOut);
	void ToWorld(float *pCamIn, float *pWorldOut);
	void SetPivotCamera(float teta, float fi, float dist);
	void RotateAroundPivot(float dx, float dy);
	void MoveInPivotDir(float dd);
	void ShiftPivot(float dx, float dy);
	void ConvertTo4x4(float *pOut);
	void SetScreenPixSize(int sx, int sy);
	float *GetUp();
	float *GetRight();
	float *GetDir();
	float *GetPos();
	float *GetPivot();
	int GetScreenX();
	int GetScreenY();
	void Print4x4(float *pDat);
};

#endif