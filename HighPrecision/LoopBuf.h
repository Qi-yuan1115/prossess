#pragma once
struct FloatLoopBuffCtl{
	float * buffer; /* the buffer holding the data*/
	unsigned int size;		/* the size of the allocated buffer*/
	unsigned int reader;	/* data is added at offset (in % size)*/
	unsigned int writer;	/* data is extracted from off. (out % size)*/
};

struct DoubleLoopBuffCtl{
	double * buffer; /* the buffer holding the data*/
	unsigned int size;		/* the size of the allocated buffer*/
	unsigned int reader;	/* data is added at offset (in % size)*/
	unsigned int writer;	/* data is extracted from off. (out % size)*/
};

struct IntLoopBuffCtl{
	int * buffer; /* the buffer holding the data*/
	unsigned int size;		/* the size of the allocated buffer*/
	unsigned int reader;	/* data is added at offset (in % size)*/
	unsigned int writer;	/* data is extracted from off. (out % size)*/
};

class CLoopBuf
{
public:
	CLoopBuf(void);
	~CLoopBuf(void);

	void LoopBuffInit( struct FloatLoopBuffCtl * pLoopCtl, unsigned int size, float * buffer );
	void LoopBuffInit( struct DoubleLoopBuffCtl * pLoopCtl, unsigned int size, double * buffer );
	void LoopBuffInit( struct IntLoopBuffCtl * pLoopCtl, unsigned int size, int * buffer );
	unsigned int LoopBuffDataLength( struct FloatLoopBuffCtl * pLoopCtl );
	unsigned int LoopBuffDataLength( struct DoubleLoopBuffCtl * pLoopCtl );
	unsigned int LoopBuffDataLength( struct IntLoopBuffCtl * pLoopCtl );
	unsigned int LoopBuffFreeSpace( struct FloatLoopBuffCtl * pLoopCtl );
	unsigned int LoopBuffFreeSpace( struct DoubleLoopBuffCtl * pLoopCtl );
	unsigned int LoopBuffFreeSpace( struct IntLoopBuffCtl * pLoopCtl );
	unsigned int LoopBuffWrite( struct FloatLoopBuffCtl *, float * , unsigned int );
	unsigned int LoopBuffWrite( struct DoubleLoopBuffCtl *, double * , unsigned int );
	unsigned int LoopBuffWrite( struct IntLoopBuffCtl *, int * , unsigned int );
	unsigned int LoopBuffRead( struct FloatLoopBuffCtl *, float *, unsigned int );
	unsigned int LoopBuffRead( struct DoubleLoopBuffCtl *, double *, unsigned int );
	unsigned int LoopBuffRead( struct IntLoopBuffCtl *, int *, unsigned int );
};

//CLoopBuf类一共有5*3=15个成员函数，分别为Init,DataLength,FreeSpace,Write,Read