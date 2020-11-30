#pragma once

struct LoopBuffCtl{
	float * buffer; /* the buffer holding the data*/
	unsigned int size;		/* the size of the allocated buffer*/
	unsigned int reader;	/* data is added at offset (in % size)*/
	unsigned int writer;	/* data is extracted from off. (out % size)*/
};

class CLoopBuf_Bomo
{
public:
	CLoopBuf_Bomo(void);
	~CLoopBuf_Bomo(void);

	void LoopBuffInit( struct LoopBuffCtl * pLoopCtl, unsigned int size, float * buffer );
	unsigned int LoopBuffDataLength( struct LoopBuffCtl * pLoopCtl );
	unsigned int LoopBuffFreeSpace( struct LoopBuffCtl * pLoopCtl );
	unsigned int LoopBuffWrite( struct LoopBuffCtl *, float * , unsigned int );
	unsigned int LoopBuffRead( struct LoopBuffCtl *, float *, unsigned int );
};

