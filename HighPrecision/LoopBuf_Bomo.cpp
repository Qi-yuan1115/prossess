#include "StdAfx.h"
#include "LoopBuf_Bomo.h"
#include<cstring>

#define min(a,b)  ((a)>(b)) ? (b) : (a)





unsigned int CLoopBuf_Bomo::LoopBuffFreeSpace( struct LoopBuffCtl * pLoopCtl )
{
	return ( pLoopCtl->reader + pLoopCtl->size - pLoopCtl->writer - 1 ) & ( pLoopCtl->size - 1 );

}

unsigned int CLoopBuf_Bomo::LoopBuffDataLength( struct LoopBuffCtl * pLoopCtl )
{
	return ( pLoopCtl->writer + pLoopCtl->size - pLoopCtl->reader ) & ( pLoopCtl->size - 1 );
}

CLoopBuf_Bomo::CLoopBuf_Bomo(void)
{
}

CLoopBuf_Bomo::~CLoopBuf_Bomo(void)
{
}

void CLoopBuf_Bomo::LoopBuffInit( struct LoopBuffCtl * pLoopCtl, unsigned int size, float * buffer )
{
	pLoopCtl->reader = pLoopCtl->writer = 0;
	pLoopCtl->size = size;
	pLoopCtl->buffer = buffer;
}

unsigned int CLoopBuf_Bomo::LoopBuffWrite( struct LoopBuffCtl * pLoopCtl, float * buffer , unsigned int len )
{
	unsigned int l;

	len = min( len, pLoopCtl->size - ( pLoopCtl->writer - pLoopCtl->reader ));
	l = min( len, pLoopCtl->size - ( pLoopCtl->writer & ( pLoopCtl->size - 1 )));
	memcpy( pLoopCtl->buffer + ( pLoopCtl->writer & ( pLoopCtl->size - 1 )), buffer, l*sizeof(float) );
	if (len > l)
	{
		memcpy( pLoopCtl->buffer, buffer + l, (len - l)*sizeof(float) );
	}
	pLoopCtl->writer += len;
	return len;
}

unsigned int CLoopBuf_Bomo::LoopBuffRead( struct LoopBuffCtl * pLoopCtl, float * buffer , unsigned int len )
{
	unsigned int l;

	len = min( len, pLoopCtl->writer - pLoopCtl->reader );

	l = min( len, pLoopCtl->size - ( pLoopCtl->reader & ( pLoopCtl->size - 1 )));
	if( buffer != 0 )
	{
		memcpy( buffer, pLoopCtl->buffer + ( pLoopCtl->reader & ( pLoopCtl->size - 1 )), l*sizeof(float) );
		if (len > l)
		{
			memcpy( buffer + l, pLoopCtl->buffer, (len - l)*sizeof(float) );
		}
	}
	pLoopCtl->reader += len;    
	return len;
}
