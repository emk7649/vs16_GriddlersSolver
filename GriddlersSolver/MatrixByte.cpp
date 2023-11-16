#include "pch.h"
#include "MatrixByte.h"

MatrixByte::MatrixByte()
    : m_sizeX(0)
    , m_sizeY(0)
    , m_buffer(nullptr)
{
}

MatrixByte::MatrixByte(long sizeX, long sizeY)
{
    Create(sizeX, sizeY);
}

MatrixByte::~MatrixByte()
{
    if (m_buffer)
    {
        for (long y = 0; y < m_sizeY; y++)
        {
            BYTE* abc = m_buffer[y];
            if (m_buffer[y])
            {
                delete[] m_buffer[y];
            }
        }
        delete[] m_buffer;
    }
}

void MatrixByte::Create(long sizeX, long sizeY)
{
    if (m_buffer) // 크기 같으면 안 지워도 됨.
    {
        for (long y = 0; y < m_sizeY; y++)
        {
            if (m_buffer[y])
            {
                delete[] m_buffer[y];
            }
        }
        delete[] m_buffer;
    }

    m_sizeX = sizeX;
    m_sizeY = sizeY;

    m_buffer = new BYTE * [sizeY];
    for (long y = 0; y < sizeY; y++)
    {
        m_buffer[y] = new BYTE[sizeX];
        BYTE* pSrc = m_buffer[0];
        BYTE* pDst = m_buffer[y];
        if (y == 0)
        {
            for (long x = 0; x < sizeX; x++)
            {
                pSrc[x] = 0;
            }
        }
        else
        {
            memcpy(pDst, pSrc, sizeX * sizeof(**m_buffer));
        }
    }
}

long MatrixByte::GetSizeX()
{
    return m_sizeX;
}
long MatrixByte::GetSizeY()
{
    return m_sizeY;
}
BYTE** MatrixByte::GetBuffer()
{
    return m_buffer;
}

void MatrixByte::Fill(BYTE value)
{
    if (m_sizeX == 0 || m_sizeY == 0)
        return;

    for (long y = 0; y < m_sizeY; y++)
    {
        BYTE* pSrc = m_buffer[0];
        BYTE* pDst = m_buffer[y];
        if (y == 0)
        {
            for (long x = 0; x < m_sizeX; x++)
            {
                pSrc[x] = value;
            }
        }
        else
        {
            memcpy(pDst, pSrc, m_sizeX * sizeof(**m_buffer));
        }
    }
}

BYTE* MatrixByte::operator[](long y)
{
    return m_buffer[y];  // y range error?
}
MatrixByte& MatrixByte::operator= (const MatrixByte& rhs)
{
    //m_sizeX = rhs.m_sizeX;
    //m_sizeY = rhs.m_sizeY;
    //m_buffer = rhs.m_buffer;
    memcpy(this, &rhs, sizeof(MatrixByte));
    return *this;
}
