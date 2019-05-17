#include <iostream>
#include "lodepng.h"
#include <cstdlib>
#include <cmath>
class RGBAPixel {
	public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	
     RGBAPixel(unsigned char r,unsigned char g,unsigned char b,unsigned char a)
     {
      this->r=r;
      this->g=g;
      this->b=b;
      this->a=a;      
     }
     RGBAPixel(const RGBAPixel &p){
      this->r=p.r;
      this->g=p.g;
      this->b=p.b;
      this->a=p.a;      
     }
     RGBAPixel(){
      this->r=0;
      this->g=0;
      this->b=0;
      this->a=0;      

     }
    
  friend RGBAPixel operator - (RGBAPixel &x,RGBAPixel &y);
  friend RGBAPixel operator * (RGBAPixel &x,RGBAPixel &y);
  friend RGBAPixel operator + (RGBAPixel &x,RGBAPixel &y);

};
RGBAPixel operator - (RGBAPixel &x,RGBAPixel &y){
     RGBAPixel z;
     z.r=(x.r > y.r) ? x.r-y.r: y.r - x.r;
     z.g=(x.g > y.g) ? x.g-y.g: y.g - x.g;
     z.b=(x.b > y.b) ? x.b-y.b: y.b - x.b;
     z.a=(x.a > y.a) ? x.a-y.a: y.a - x.a;
     return z;
}

RGBAPixel operator * (RGBAPixel &x,RGBAPixel &y){
     RGBAPixel z;
     (z.r)=double(x.r) * double(y.r);
     (z.g)=double(x.g) * double(y.g);
     (z.b)=double(x.b) * double(y.b);
     (z.a)=double(x.a) * double(y.a);
     return z;
}

RGBAPixel operator + (RGBAPixel &x,RGBAPixel &y){
     RGBAPixel z;
     z.r=x.r+y.r;
     z.g=x.g+y.g;
     z.b=x.b+y.b;
     z.a=x.a+y.a;
     return z;
}
class Image {
	public:
	unsigned int w;
	unsigned int h;
	RGBAPixel*** pixels;
	Image(unsigned int w,unsigned int h)
	{
		this->w=w;
		this->h=h;
		this->init();
	}
      Image(){
      this->w=0;
      this->h=0;
      this->pixels=NULL; 
      }
      void init() {
		this->pixels = new RGBAPixel** [w];
		for(unsigned int i = 0; i < w; i ++){
			this->pixels[i] = new RGBAPixel* [h];
		}

      }


	void setPixelsFromBuf(std::vector<unsigned char> &image){
	  std::cout << "initializing my DS"<< std::endl;
	  unsigned long pos = 0;
	  for(unsigned int i = 0; i < w; i++) {
		  for(unsigned int j = 0; j < h; j++){
			  RGBAPixel* px = new RGBAPixel(image[pos], image[pos+1], image[pos+2], image[pos+3]);
			  this->pixels[i][j] = px;
			  pos += 4;
		  }
	  }

	}
	float mean()
	{
		unsigned long long r = 0, g = 0, b = 0, a = 0;
		unsigned long n = w * h;
		for(unsigned int i=0;i<w;i++){
		      for(unsigned int j=0;j<h;j++){
			r += (pixels[i][j])->r;
			g += (pixels[i][j])->g;
			b += (pixels[i][j])->b;
			a += (pixels[i][j])->a;

		      }
		}
		return float( (double(r)/double(n)) + (double(g)/double(n)) + (double(b)/double(n)) +(double(a)/double(n)) );
	}
	float calcbren() {
		unsigned int sOff = 2, eOff = 3;
		Image DH = Image(w, h);
		Image DV = Image(w, h);
	     	for(unsigned int i=sOff,j=0;i<w && j<w-eOff;i++,j++){
			for (unsigned int k = 0; k < h; k++){
			DV.pixels[j][k] = new RGBAPixel( (*(pixels[i][k])) - (*(pixels[j][k])) );
			}
		}
		for(unsigned int j = w-eOff; j < w; j++){
			for (unsigned int k = 0; k < h; k++){
				DV.pixels[j][k] = new RGBAPixel();
			}
		}
			
		for(unsigned int i=sOff,j=0;i<h && j<h-eOff;i++,j++){	
			for (unsigned int k = 0; k < w; k++){
			//std::cout << "i: "<<i<<" j: "<< j <<" k: " <<k << " w: "<<w<<" h: " << h << std::endl;
			DH.pixels[k][j] = new RGBAPixel( (*(pixels[k][i])) - (*(pixels[k][j])) );
			}
		}
		for(unsigned int i = 0; i < w; i++) {
			for (unsigned int j = h-eOff; j < h; j++) {
				DH.pixels[i][j] = new RGBAPixel();
			}
		}
	       
             /*   for(unsigned int i=0;i<w-2;i++){
			for(unsigned int j=0;j<h;j++){
				DV.pixels[i][j] =  ((pixels[i][j]));
			}
		}
		for(unsigned int i=2;i<w;i++){
			for(unsigned int j=0;j<h;j++){
				DV.pixels[i][j] = DV.pixels[i][j] -  ((pixels[i][j]));
			}
		}
		for(unsigned int i=0;i<w;i++){
                        for(unsigned int j=0;j<h-2;j++){
                                DV.pixels[i][j] =  ((pixels[i][j]));
                        }
                }
                for(unsigned int i=0;i<w;i++){
                        for(unsigned int j=2;j<h;j++){
                                DV.pixels[i][j] = DV.pixels[i][j] - ((pixels[i][j]));
                        }
                }*/

	     						
	        		      
		std::cout << "finished DH, DV" << std::endl;
		Image mx = maximum(DH, DV);
		std::cout << "finished max" << std::endl;
		mx = mx.squareOf();
		std::cout << "finished square" << std::endl;
		return mx.mean();
	}
	Image maximum(Image &a,Image &b)
	{
		Image c;
		if ((a.w==b.w)&&(a.h==b.h)){
			c.w = a.w;
			c.h = a.h;
			c.init();
			for(unsigned int i=0;i<a.w;i++){
				for(unsigned int j=0;j<a.h;j++){
					std::cout << i << " " << j << std::endl;
					RGBAPixel px;
					RGBAPixel* apx = a.pixels[i][j];
					RGBAPixel* bpx = b.pixels[i][j];
					px.r = (apx->r > bpx->r) ? apx->r : bpx-> r;
					px.g = (apx->g > bpx->g) ? apx->g : bpx-> g;
					px.b = (apx->b > bpx->b) ? apx->b : bpx-> b;
					px.a = (apx->a > bpx->a) ? apx->a : bpx-> a;
					c.pixels[i][j] = new RGBAPixel(px);

				}
			}
		}
		return c;
	}
	
	Image squareOf(){
		Image x(w, h);
		for(unsigned int i=0;i<w;i++){
			for(unsigned int j=0;j<h;j++){
			     x.pixels[i][j]= new RGBAPixel((*pixels[i][j]) * (*pixels[i][j]));
			}
		}
		return x;
	}

                                       
       friend Image operator - (Image &a,Image &b);
			      
};



Image operator - (Image &a,Image &b){
        Image c;
        if((a.w==b.w)&&(a.h==b.h))
        {
               c.w=b.w;
               c.h=a.h;
               c.init();
               for(unsigned int i=0;i<c.w;i++)
               {
                       for(unsigned int j=0;j<c.h;j++)
                       {      RGBAPixel diff =*(a.pixels[i][j]) - *(b.pixels[i][j]) ;
                               c.pixels[i][j]= new RGBAPixel(diff);
                       }
               }
               return c;
         }
         else
                 exit(0);
}



Image* createImageFromBuf(std::vector<unsigned char> &image, unsigned int w, unsigned int h) {
  Image* im = new Image(w, h);
  if(image.size() == w*h*4){
	  im->setPixelsFromBuf(image);
  }
  return im;

}


Image* openFile(const char *filename) {
  std::vector<unsigned char> png;
  std::vector<unsigned char> image; //the raw pixels
  unsigned w, h;
  std::cout << "Initial Values w:" << w << "h:" << h << std::endl;
  //load and decode
  unsigned error = lodepng::load_file(png, filename);
  if(!error) error = lodepng::decode(image, w, h, png);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
  std::cout << "Final Values w:" << w << "h:" << h << std::endl;
  std::cout << "Len of Vec" << image.size() << std::endl;
  Image* im = createImageFromBuf(image, w, h);
  std::cout << "im.w: " << im-> w << " im.h: " << im->h << std::endl;
  return im;
}

int main(int argc, char *argv[]){
	const char* filename = argc > 1 ? argv[1] : "pout.png";
	Image* im = openFile(filename);
	std::cout << im->calcbren();
}
