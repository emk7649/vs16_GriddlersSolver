#pragma once
#include <vector>
using namespace std;

#include <Algorithm>

class MatrixByte
{
public:
	MatrixByte();
	MatrixByte(long sizeX, long sizeY);
	virtual ~MatrixByte();
	void Create(long sizeX, long sizeY);

	long GetSizeX();
	long GetSizeY();
	BYTE** GetBuffer();

	void Fill(BYTE value);

	BYTE* operator[](long y);
	MatrixByte& operator= (const MatrixByte& rhs);

private:
	BYTE** m_buffer;
	long m_sizeX;
	long m_sizeY;
};





