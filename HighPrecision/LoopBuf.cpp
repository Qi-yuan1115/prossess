#include "StdAfx.h"
#include "LoopBuf.h"

//#define min(a,b)  ((a)>(b)) ? (b) : (a)

CLoopBuf::CLoopBuf(void)
{
}


CLoopBuf::~CLoopBuf(void)
{
}

unsigned int CLoopBuf::LoopBuffFreeSpace( struct FloatLoopBuffCtl * pLoopCtl )
{
	return ( pLoopCtl->reader + pLoopCtl->size - pLoopCtl->writer - 1 ) & ( pLoopCtl->size - 1 );
}
unsigned int CLoopBuf::LoopBuffFreeSpace( struct DoubleLoopBuffCtl * pLoopCtl )
{
	return ( pLoopCtl->reader + pLoopCtl->size - pLoopCtl->writer - 1 ) & ( pLoopCtl->size - 1 );
}
unsigned int CLoopBuf::LoopBuffFreeSpace( struct IntLoopBuffCtl * pLoopCtl )
{
	return ( pLoopCtl->reader + pLoopCtl->size - pLoopCtl->writer - 1 ) & ( pLoopCtl->size - 1 );
}
unsigned int CLoopBuf::LoopBuffDataLength( struct FloatLoopBuffCtl * pLoopCtl )
{
	return ( pLoopCtl->writer + pLoopCtl->size - pLoopCtl->reader ) & ( pLoopCtl->size - 1 );
}
unsigned int CLoopBuf::LoopBuffDataLength( struct DoubleLoopBuffCtl * pLoopCtl )
{
	return ( pLoopCtl->writer + pLoopCtl->size - pLoopCtl->reader ) & ( pLoopCtl->size - 1 );
}
unsigned int CLoopBuf::LoopBuffDataLength( struct IntLoopBuffCtl * pLoopCtl )
{
	return ( pLoopCtl->writer + pLoopCtl->size - pLoopCtl->reader ) & ( pLoopCtl->size - 1 );
}


void CLoopBuf::LoopBuffInit( struct FloatLoopBuffCtl * pLoopCtl, unsigned int size, float * buffer )
{
	pLoopCtl->reader = pLoopCtl->writer = 0;
	pLoopCtl->size = size;
	pLoopCtl->buffer = buffer;
}
void CLoopBuf::LoopBuffInit( struct DoubleLoopBuffCtl * pLoopCtl, unsigned int size, double * buffer )
{
	pLoopCtl->reader = pLoopCtl->writer = 0;
	pLoopCtl->size = size;
	pLoopCtl->buffer = buffer;
}

void CLoopBuf::LoopBuffInit( struct IntLoopBuffCtl * pLoopCtl, unsigned int size, int * buffer )
{
	pLoopCtl->reader = pLoopCtl->writer = 0;
	pLoopCtl->size = size;
	pLoopCtl->buffer = buffer;
}

unsigned int CLoopBuf::LoopBuffWrite( struct FloatLoopBuffCtl * pLoopCtl, float * buffer , unsigned int len )
{
	unsigned int l;

	len = min( len, pLoopCtl->size - ( pLoopCtl->writer - pLoopCtl->reader ));
	l = min( len, pLoopCtl->size - ( pLoopCtl->writer & ( pLoopCtl->size - 1 )));
	memcpy( pLoopCtl->buffer +( pLoopCtl->writer & ( pLoopCtl->size - 1 )), buffer, l*sizeof(float) );
	if (len > l)
	{
		memcpy( pLoopCtl->buffer, buffer + l, sizeof(float)*(len - l) );
	}
	pLoopCtl->writer += len;
	return len;
}
unsigned int CLoopBuf::LoopBuffWrite( struct DoubleLoopBuffCtl * pLoopCtl, double * buffer , unsigned int len )
{
	unsigned int l;

	len = min( len, pLoopCtl->size - ( pLoopCtl->writer - pLoopCtl->reader ));
	l = min( len, pLoopCtl->size - ( pLoopCtl->writer & ( pLoopCtl->size - 1 )));
	memcpy( pLoopCtl->buffer + ( pLoopCtl->writer & ( pLoopCtl->size - 1 )), buffer, sizeof(double)*l );
	if (len > l)
	{
		memcpy( pLoopCtl->buffer, buffer + l, sizeof(double)*(len - l) );
	}
	pLoopCtl->writer += len;
	return len;
}
unsigned int CLoopBuf::LoopBuffWrite( struct IntLoopBuffCtl * pLoopCtl, int * buffer , unsigned int len )
{
	unsigned int l;

	len = min( len, pLoopCtl->size - ( pLoopCtl->writer - pLoopCtl->reader ));
	l = min( len, pLoopCtl->size - ( pLoopCtl->writer & ( pLoopCtl->size - 1 )));
	memcpy( pLoopCtl->buffer + ( pLoopCtl->writer & ( pLoopCtl->size - 1 )), buffer, sizeof(int)*l );
	if (len > l)
	{
		memcpy( pLoopCtl->buffer, buffer + l, sizeof(int)*(len - l) );
	}
	pLoopCtl->writer += len;
	return len;
}

unsigned int CLoopBuf::LoopBuffRead( struct FloatLoopBuffCtl * pLoopCtl, float * buffer , unsigned int len )
{
	unsigned int l;

	len = min( len, pLoopCtl->writer - pLoopCtl->reader );

	l = min( len, pLoopCtl->size - ( pLoopCtl->reader & ( pLoopCtl->size - 1 )));
	if( buffer != 0 )
	{
		memcpy( buffer, pLoopCtl->buffer + ( pLoopCtl->reader & ( pLoopCtl->size - 1 )), sizeof(float)*l );
		if (len > l)
		{
			memcpy( buffer + l, pLoopCtl->buffer, sizeof(float)*(len - l) );
		}
	}
	pLoopCtl->reader += len;    
	return len;
}
unsigned int CLoopBuf::LoopBuffRead( struct DoubleLoopBuffCtl * pLoopCtl, double * buffer , unsigned int len )
{
	unsigned int l;

	len = min( len, pLoopCtl->writer - pLoopCtl->reader );

	l = min( len, pLoopCtl->size - ( pLoopCtl->reader & ( pLoopCtl->size - 1 )));
	if( buffer != 0 )
	{
		memcpy( buffer, pLoopCtl->buffer + ( pLoopCtl->reader & ( pLoopCtl->size - 1 )), sizeof(double)*l );
		if (len > l)
		{
			memcpy( buffer + l, pLoopCtl->buffer, sizeof(double)*(len - l) );
		}
	}
	pLoopCtl->reader += len;    
	return len;
}
unsigned int CLoopBuf::LoopBuffRead( struct IntLoopBuffCtl * pLoopCtl, int * buffer , unsigned int len )
{
	unsigned int l;

	len = min( len, pLoopCtl->writer - pLoopCtl->reader );

	l = min( len, pLoopCtl->size - ( pLoopCtl->reader & ( pLoopCtl->size - 1 )));
	if( buffer != 0 )
	{
		memcpy( buffer, pLoopCtl->buffer + ( pLoopCtl->reader & ( pLoopCtl->size - 1 )), sizeof(int)*l );
		if (len > l)
		{
			memcpy( buffer + l, pLoopCtl->buffer, sizeof(int)*(len - l) );
		}
	}
	pLoopCtl->reader += len;    
	return len;
}

