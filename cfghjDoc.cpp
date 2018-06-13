// cfghjDoc.cpp : implementation of the CCfghjDoc class
//

#include "stdafx.h"
#include "cfghj.h"

#include "cfghjDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCfghjDoc

IMPLEMENT_DYNCREATE(CCfghjDoc, CDocument)

BEGIN_MESSAGE_MAP(CCfghjDoc, CDocument)
	//{{AFX_MSG_MAP(CCfghjDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCfghjDoc construction/destruction

CCfghjDoc::CCfghjDoc():m_pImage(0),m_coverage(160), m_sharpeness(0.9f), m_bNoise2(false)
{
	// TODO: add one-time construction code here
	srand(time(NULL));
}

CCfghjDoc::~CCfghjDoc()
{
	if(m_pImage) 
		free(m_pImage);
}

BOOL CCfghjDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCfghjDoc serialization

void CCfghjDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		TGA_HDR	tgaHeader;
		unsigned long* ptr;
		unsigned char r,g,b;

		ar.Read(&tgaHeader, sizeof(TGA_HDR));
		m_w= tgaHeader.imgWidth;
		m_h= tgaHeader.imgHeight;

		if(m_pImage) 
			free(m_pImage);
		ptr= m_pImage= (unsigned long*)malloc(sizeof(unsigned long)*m_w*m_h);
		memset(m_pImage, 0x0, sizeof(unsigned long)*m_w*m_h);

		for(int j= 0; j<(signed)m_h; ++j){
			for(int i= 0; i<(signed)m_w; ++i){
				ar.Read(ptr, sizeof(BIT888));
				r= ((*ptr)&0xFF0000)>>16;
				g= ((*ptr)&0x00FF00)>>8;
				b= ((*ptr)&0x0000FF)>>0;
				*ptr= (b<<16)|(g<<8)|(r<<0);
				++ptr;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCfghjDoc diagnostics

#ifdef _DEBUG
void CCfghjDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCfghjDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCfghjDoc commands

void CCfghjDoc::ClampBpp()
{
	unsigned long* ptr;
	unsigned char r,g,b;
	ptr= m_pImage;

	for(int j= 0; j<(signed)m_h; ++j){
		for(int i= 0; i<(signed)m_w; ++i){

			r= (((*ptr)&0xFF0000)>>16);
			g= (((*ptr)&0x00FF00)>>8);
			b= (((*ptr)&0x0000FF)>>0);

			r= (r<<2)>>8;
			g= (g<<2)>>8;
			b= (b<<2)>>8;

			r= ((r<<8)>>2)|0x3F;
			g= ((g<<8)>>2)|0x3F;
			b= ((b<<8)>>2)|0x3F;
			*ptr= (r<<16)|(g<<8)|(b<<0);
			++ptr;
		}
	}
}

void CCfghjDoc::Smooth1()
{
  unsigned long*  bptr;
  
  bptr = m_pImage + m_w + 1;

  for ( int i = 1; i < (m_h - 1); i++ ) {
	{
		register int			j		= m_w-2;		//Apply this filter
		register int			cumul	= 0;			//0 1 0
		register unsigned long*	ptr		= bptr;			//1 4 1
		register int	r;								//0 1 0
		register int	g;
		register int	b;
		
		while(j--){
			r= ((ptr[0]&0xFF0000)>>16)<<2;
			g= ((ptr[0]&0x00FF00)>>8)<<2;
			b= ((ptr[0]&0x0000FF)>>0)<<2;
			r+= ((ptr[1]&0xFF0000)>>16);
			g+= ((ptr[1]&0x00FF00)>>8);
			b+= ((ptr[1]&0x0000FF)>>0);
			r+= ((ptr[-1]&0xFF0000)>>16);
			g+= ((ptr[-1]&0x00FF00)>>8);
			b+= ((ptr[-1]&0x0000FF)>>0);
			r+= ((ptr[m_w]&0xFF0000)>>16);
			g+= ((ptr[m_w]&0x00FF00)>>8);
			b+= ((ptr[m_w]&0x0000FF)>>0);
			r+= ((ptr[-m_w]&0xFF0000)>>16);
			g+= ((ptr[-m_w]&0x00FF00)>>8);
			b+= ((ptr[-m_w]&0x0000FF)>>0);
			r>>= 3;
			g>>= 3;
			b>>= 3;
			ptr[0]= (r<<16)|(g<<8)|(b<<0);
			++ptr;
		}
	}
    bptr += m_w;
  }
}

void CCfghjDoc::Smooth2()
{
  unsigned long*  bptr;
  
  bptr = m_pImage + m_w + 1;

  for ( int i = 1; i < (m_h - 1); i++ ) {
	{
		register int			j		= m_w-2;		//Apply this filter
		register int			cumul	= 0;			//0 1 0
		register unsigned long*	ptr		= bptr;			//1 2 1
		register int	r;								//0 1 0
		register int	g;
		register int	b;
		
		while(j--){
			r= ((ptr[0]&0xFF0000)>>16)<<1;
			g= ((ptr[0]&0x00FF00)>>8)<<1;
			b= ((ptr[0]&0x0000FF)>>0)<<1;
			r+= ((ptr[1]&0xFF0000)>>16);
			g+= ((ptr[1]&0x00FF00)>>8);
			b+= ((ptr[1]&0x0000FF)>>0);
			r+= ((ptr[-1]&0xFF0000)>>16);
			g+= ((ptr[-1]&0x00FF00)>>8);
			b+= ((ptr[-1]&0x0000FF)>>0);
			r+= ((ptr[m_w]&0xFF0000)>>16);
			g+= ((ptr[m_w]&0x00FF00)>>8);
			b+= ((ptr[m_w]&0x0000FF)>>0);
			r+= ((ptr[-m_w]&0xFF0000)>>16);
			g+= ((ptr[-m_w]&0x00FF00)>>8);
			b+= ((ptr[-m_w]&0x0000FF)>>0);
			r>>= 2;
			g>>= 2;
			b>>= 2;
			ptr[0]= (r<<16)|(g<<8)|(b<<0);
			++ptr;
		}
	}
    bptr += m_w;
  }
}

void CCfghjDoc::Edge()
{
  unsigned long*  imageTemp= (unsigned long*)malloc(sizeof(unsigned long)*m_w*m_h);
  unsigned long*  bptr;
  unsigned long*  optr= imageTemp;
  
  memset(imageTemp, 0x0, sizeof(unsigned short)*m_w*m_h);
  bptr = m_pImage + m_w + 1;

  for ( int i = 1; i < (m_h - 1); i++ ) {
	{
		register int			j		= m_w-2;
		register __int64		cumul	= 0;	
		register unsigned long*	ptrS	= bptr;	
		register unsigned long*	ptrD	= optr;	
		register int	r;						
		register int	g;
		register int	b;
		register int	m;
		
		while(j--){
/*			cumul= ptrS[1];
			cumul+= ptrS[-1];
			cumul+= ptrS[m_w];
			cumul+= ptrS[-m_w];
			cumul>>=2;
			cumul= ptrS[0]-cumul;
			cumul>>=1;
			ptrD[0]= (unsigned long)cumul;*/
			r= ((ptrS[1]&0xFF0000)>>16);
			g= ((ptrS[1]&0x00FF00)>>8);
			b= ((ptrS[1]&0x0000FF)>>0);
			m= (r+g+b)>>4;
			r= ((ptrS[-1]&0xFF0000)>>16);
			g= ((ptrS[-1]&0x00FF00)>>8);
			b= ((ptrS[-1]&0x0000FF)>>0);
			m+= (r+g+b)>>4;
			r= ((ptrS[m_w]&0xFF0000)>>16);
			g= ((ptrS[m_w]&0x00FF00)>>8);
			b= ((ptrS[m_w]&0x0000FF)>>0);
			m+= (r+g+b)>>4;
			r= ((ptrS[-m_w]&0xFF0000)>>16);
			g= ((ptrS[-m_w]&0x00FF00)>>8);
			b= ((ptrS[-m_w]&0x0000FF)>>0);
			m+= (r+g+b)>>4;
			m>>=2;
			r= ((ptrS[0]&0xFF0000)>>16);
			g= ((ptrS[0]&0x00FF00)>>8);
			b= ((ptrS[0]&0x0000FF)>>0);
			cumul= ((r+g+b)>>4)-m;
			cumul&=0x000000FE;
			cumul>>=1;
			cumul= (cumul<<16)|(cumul<<8)|cumul;
			ptrD[0]= (unsigned long)(cumul);
/*			r= ((ptrS[0]&0xFF0000)>>16)-r;
			g= ((ptrS[0]&0x00FF00)>>8)-g;
			b= ((ptrS[0]&0x0000FF)>>0)-b;
			r>>= 1;
			g>>= 1;
			b>>= 1;

			ptrD[0]= (r<<16)|(g<<8)|(b<<0);*/
			++ptrD;
			++ptrS;
		}
	}
    bptr += m_w;
    optr += m_w;
  }
  {
	for(int j= 0; j<(signed)m_h; ++j){
		for(int i= 0; i<(signed)m_w; ++i){
			if((imageTemp[j*m_w+i]&0xF0))
				m_pImage[j*m_w+i]= 0;
		}
	}
  }
//  memcpy(m_pImage, imageTemp, sizeof(unsigned long)*m_w*m_h);
  free(imageTemp);
}
#include <math.h>
/* Coherent noise function over 1, 2 or 3 dimensions */
/* (copyright Ken Perlin) */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define B 0x100
#define BM 0xff
#define N 0x1000
#define NP 12   /* 2^N */
#define NM 0xfff

#define s_curve(t) ( t * t * (3. - 2. * t) )
#define lerp(t, a, b) ( a + t * (b - a) )
#define setup(i,b0,b1,r0,r1)\
        t = vec[i] + N;\
        b0 = ((int)t) & BM;\
        b1 = (b0+1) & BM;\
        r0 = t - (int)t;\
        r1 = r0 - 1.;
#define at2(rx,ry) ( rx * q[0] + ry * q[1] )
#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

void init(void);
double noise1(double);
double noise2(double *);
double noise3(double *);
void normalize3(double *);
void normalize2(double *);

double PerlinNoise1D(double,double,double,int);
double PerlinNoise2D(double,double,double,double,int);
double PerlinNoise3D(double,double,double,double,double,int);



static int p[B + B + 2];
static double g3[B + B + 2][3];
static double g2[B + B + 2][2];
static double g1[B + B + 2];
static int start = 1;

double noise1(double arg)
{
   int bx0, bx1;
   double rx0, rx1, sx, t, u, v, vec[1];

   vec[0] = arg;
   if (start) {
      start = 0;
      init();
   }

   setup(0,bx0,bx1,rx0,rx1);

   sx = s_curve(rx0);
   u = rx0 * g1[ p[ bx0 ] ];
   v = rx1 * g1[ p[ bx1 ] ];

   return(lerp(sx, u, v));
}

double noise2(double vec[2])
{
   int bx0, bx1, by0, by1, b00, b10, b01, b11;
   double rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
   int i, j;

   if (start) {
      start = 0;
      init();
   }

   setup(0, bx0,bx1, rx0,rx1);
   setup(1, by0,by1, ry0,ry1);

   i = p[ bx0 ];
   j = p[ bx1 ];

   b00 = p[ i + by0 ];
   b10 = p[ j + by0 ];
   b01 = p[ i + by1 ];
   b11 = p[ j + by1 ];

   sx = s_curve(rx0);
   sy = s_curve(ry0);

   q = g2[ b00 ] ; u = at2(rx0,ry0);
   q = g2[ b10 ] ; v = at2(rx1,ry0);
   a = lerp(sx, u, v);

   q = g2[ b01 ] ; u = at2(rx0,ry1);
   q = g2[ b11 ] ; v = at2(rx1,ry1);
   b = lerp(sx, u, v);

   return lerp(sy, a, b);
}

double noise3(double vec[3])
{
   int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
   double rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
   int i, j;

   if (start) {
      start = 0;
      init();
   }

   setup(0, bx0,bx1, rx0,rx1);
   setup(1, by0,by1, ry0,ry1);
   setup(2, bz0,bz1, rz0,rz1);

   i = p[ bx0 ];
   j = p[ bx1 ];

   b00 = p[ i + by0 ];
   b10 = p[ j + by0 ];
   b01 = p[ i + by1 ];
   b11 = p[ j + by1 ];

   t  = s_curve(rx0);
   sy = s_curve(ry0);
   sz = s_curve(rz0);

   q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
   q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
   a = lerp(t, u, v);

   q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
   q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
   b = lerp(t, u, v);

   c = lerp(sy, a, b);

   q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
   q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
   a = lerp(t, u, v);

   q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
   q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
   b = lerp(t, u, v);

   d = lerp(sy, a, b);

   return lerp(sz, c, d);
}

void normalize2(double v[2])
{
   double s;

   s = sqrt(v[0] * v[0] + v[1] * v[1]);
   v[0] = v[0] / s;
   v[1] = v[1] / s;
}

void normalize3(double v[3])
{
   double s;

   s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
   v[0] = v[0] / s;
   v[1] = v[1] / s;
   v[2] = v[2] / s;
}

void init(void)
{
   int i, j, k;

   for (i = 0 ; i < B ; i++) {
      p[i] = i;
      g1[i] = (double)((rand() % (B + B)) - B) / B;

      for (j = 0 ; j < 2 ; j++)
         g2[i][j] = (double)((rand() % (B + B)) - B) / B;
      normalize2(g2[i]);

      for (j = 0 ; j < 3 ; j++)
         g3[i][j] = (double)((rand() % (B + B)) - B) / B;
      normalize3(g3[i]);
   }

   while (--i) {
      k = p[i];
      p[i] = p[j = rand() % B];
      p[j] = k;
   }

   for (i = 0 ; i < B + 2 ; i++) {
      p[B + i] = p[i];
      g1[B + i] = g1[i];
      for (j = 0 ; j < 2 ; j++)
         g2[B + i][j] = g2[i][j];
      for (j = 0 ; j < 3 ; j++)
         g3[B + i][j] = g3[i][j];
   }
}

/* --- My harmonic summing functions - PDB --------------------------*/

/*
   In what follows "alpha" is the weight when the sum is formed.
   Typically it is 2, As this approaches 1 the function is noisier.
   "beta" is the harmonic scaling/spacing, typically 2.
*/

double PerlinNoise1D(double x,double alpha,double beta,int n)
{
   int i;
   double val,sum = 0;
   double p,scale = 1;

   p = x;
   for (i=0;i<n;i++) {
      val = noise1(p);
      sum += val / scale;
      scale *= alpha;
      p *= beta;
   }
   return(sum);
}

double PerlinNoise2D(double x,double y,double alpha,double beta,int n)
{
   int i;
   double val,sum = 0;
   double p[2],scale = 1;

   p[0] = x;
   p[1] = y;
   for (i=0;i<n;i++) {
      val = noise2(p);
      sum += val / scale;
      scale *= alpha;
      p[0] *= beta;
      p[1] *= beta;
   }
   return(sum);
}

double PerlinNoise3D(double x,double y,double z,double alpha,double beta,int n)
{
   int i;
   double val,sum = 0;
   double p[3],scale = 1;

   p[0] = x;
   p[1] = y;
   p[2] = z;
   for (i=0;i<n;i++) {
      val = noise3(p);
      sum += val / scale;
      scale *= alpha;
      p[0] *= beta;
      p[1] *= beta;
      p[2] *= beta;
   }
   return(sum);
}


void CCfghjDoc::CreateParticule()
{
	int delta;
	int pow2R= 4;
	int rayon= 1<<pow2R;
	int diam= 2<<pow2R;
	unsigned long* ptr;
	unsigned char r=255,g=255,b=255;

	if(m_pImage) free(m_pImage);
	ptr= m_pImage= (unsigned long*) malloc(sizeof(unsigned long) * (m_h= diam)*(m_w= diam));

	for(int j= 0; j<diam; ++j){
		for(int i= 0; i<diam; ++i){
			delta= sqrt(((i-rayon)*(i-rayon))+((j-rayon)*(j-rayon)));
			delta= rayon-delta;
			if(delta<0) delta=0;
			*ptr++= (((r*delta)>>pow2R)<<16)|((((g*delta)>>pow2R))<<8)|((((b*delta)>>pow2R))<<0);
		}
	}
}

void CCfghjDoc::CreateFlare()
{
	int delta;
	int pow2R= 4;
	int rayon= 1<<pow2R;
	int diam= 2<<pow2R;
	unsigned long* ptr;
	unsigned char r=255,g=255,b=255;

	if(m_pImage) free(m_pImage);
	ptr= m_pImage= (unsigned long*) malloc(sizeof(unsigned long) * (m_h= diam)*(m_w= diam));

	for(int j= 0; j<diam; ++j){
		for(int i= 0; i<diam; ++i){
			delta= sqrt(((i-rayon)*(i-rayon))+((j-rayon)*(j-rayon)));
			delta= rayon-delta;
			if(delta<0) delta=0;
			else				delta= (1<<pow2R)-delta;
			*ptr++= (((r*delta)>>pow2R)<<16)|((((g*delta)>>pow2R))<<8)|((((b*delta)>>pow2R))<<0);
		}
	}
}

void CCfghjDoc::CreateNoise()
{
	int pow2R= 6;
	int diam= 2<<pow2R;
	float xfreq= 40.00f/diam;
	float yfreq= 40.00f/diam;
	unsigned long* ptr;

	if(m_pImage) free(m_pImage);
	ptr= m_pImage= (unsigned long*) malloc(sizeof(unsigned long) * (m_nbText= diam)*(m_h= diam)*(m_w= diam));

	for(int j= 0; j<diam; ++j){
		for(int i= 0; i<diam; ++i){
			float toto;
			toto= 128.0f*PerlinNoise2D(i * xfreq, j * yfreq, 1.5, 1.5, 1)+128.0f;
			 unsigned char v = (toto);
			if(v > 136)
				v=255;
			if(v < 128)
				v=0;
			*ptr++= (v<<16)|(v<<8)|(v<<0);
		}
	}
}
int CloudExpCurve(int v, int coverness, float sharpness)
{
	int c = v - coverness;
  if(c < 0)
		c=0;
	return(255 - (pow(sharpness, c) * 255));
}


void CCfghjDoc::CreatePinceaux()
{
	int delta;
	int pow2R= 5;
	int rayon= 1<<pow2R;
	int diam= 2<<pow2R;
	float xfreq= 25.00f/diam;
	float yfreq= 2.00f/diam;
	unsigned long* ptr;

	if(m_pImage) free(m_pImage);
	ptr= m_pImage= (unsigned long*) malloc(sizeof(unsigned long) * (m_nbText= diam)*(m_h= diam)*(m_w= diam));

	for(int j= 0; j<diam; ++j){
		for(int i= 0; i<diam; ++i){
			float toto;
			toto= 128.0f*PerlinNoise2D(i * xfreq, j * yfreq, 1.5, 1.5, 1)+128.0f;
			delta= sqrt(((i-rayon)*(i-rayon))+((j-rayon)*(j-rayon)));
			unsigned char v = (toto*CloudExpCurve(toto, 56+(m_coverage*(delta<<4))/256, m_sharpeness))/256;
			if(v > 128)
				v=255;
			*ptr++= (v<<16)|(v<<8)|(v<<0);
		}
	}
}

void CCfghjDoc::CreateNoise2(int k)
{
	int pow2R= 7;
	int diam= 2<<pow2R;
	float xfreq= 5.00f/diam;
	float yfreq= 5.00f/diam;
	float zfreq= 4.00f/diam;
	unsigned long* ptr;

	if(m_pImage) free(m_pImage);
	ptr= m_pImage= (unsigned long*) malloc(sizeof(unsigned long) * (m_nbText= diam)*(m_h= diam)*(m_w= diam));

	for(int j= 0; j<diam; ++j){
		for(int i= 0; i<diam; ++i){
			float toto;
			toto= 128.0f*PerlinNoise3D(i * xfreq, ((k<<1)+j) * yfreq, k * zfreq, 1.5, 1.5, 5)+128.0f;
			unsigned char v = (toto*CloudExpCurve(toto, m_coverage, m_sharpeness))/256;
			*ptr++= (v<<16)|(v<<8)|(v<<0);
		}
	}
}