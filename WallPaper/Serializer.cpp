#include "Mask.cpp"
#include <fstream>
#include <vector>
//#define CENTER
#define BOTTOM_RIGHT
#define MASK
#define SUPERMAN
//#define EARTH

struct Info{
    int width,height,Bpp;
    Info(){}
    Info(int width,int height,int Bpp){
        this->width = width;
        this->height = height;
        this->Bpp = Bpp;
    }
};

class Serializer{
	#ifdef MASK
	Mask* m = NULL;
	#endif
    void diff(ofstream& ofs, Image* base){
        int idx;
        for(short i=0;i<base->width;++i){
            for(short j=0;j<base->height;++j){
                idx = base->index(i,j);
                ofs.write((char*)(base->pixels+idx),base->Bpp);
            }
        }
    }

    void diff(ofstream& ofs, Image* base,Image* next){
        if(!base)
            return diff(ofs,next);
        int count = 0, start, idx, buf_s;
        COLORREF b, c;
        bool flag;
        short len;
        start = ofs.tellp();
        
        for(int i=0;i<sizeof(int);++i)
            ofs.write("0",1);
        
        for(short j=0;j<base->height;++j){
            flag = false;
            for(short i=0;i<=base->width;++i){
                b = base->get(i,j);
                c = next->get(i,j);
                if (i<base->width && b^c){
                    if(!flag){
                        idx = next->index(i,j);
                        buf_s = idx;
                        flag = true;
                    }
                } else{
                    if(flag){
                        idx = next->index(i,j);
                        len = idx-buf_s;
                        flag = false;
                        ofs.write((char*)&buf_s,sizeof(int));
                        ofs.write((char*)&len,sizeof(short));
                        ofs.write((char*)(next->pixels+buf_s),len);
                        count+=len;
                    }
                }
            }
        }
        
        int end = ofs.tellp();
        ofs.seekp(start);
        ofs.write((char*)&count,sizeof(int));
        ofs.seekp(end);
    }
    
    Image* construct(ifstream& ifs, Info inf){
        int idx;
        Image* ans = new Image(inf.width,inf.height,inf.Bpp);
        for(short i=0;i<ans->width;++i){
            for(short j=0;j<ans->height;++j){
                idx = ans->index(i,j);
                ifs.read((char*)(ans->pixels+idx),ans->Bpp);
				#ifdef MASK
				ans->set(idx, m->color_mask(ans->get(idx), idx));
				#endif
            }
        }
        return ans;
    }

    Image* construct(ifstream& ifs, Info inf, Image* prev){
        if(!prev)
            return construct(ifs,inf);
        int count, idx;
        Image* ans = new Image(inf.width,inf.height,inf.Bpp);
        ifs.read((char*)&count,sizeof(int));
        memcpy(ans->pixels,prev->pixels,ans->real_width()*ans->height);
        short len;
        for(int i=0;i<count;){
            ifs.read((char*)&idx,sizeof(int));
            ifs.read((char*)&len,sizeof(short));
            for(int j=0;j<len;j+=ans->Bpp){
                ifs.read((char*)(ans->pixels+idx+j),ans->Bpp);
				#ifdef MASK
				ans->set(idx + j, m->color_mask(ans->get(idx + j), idx + j));
				#endif
            }
            i+= len;
        }
        return ans;
    }
public:
    vector<Image*>* deserialize(Info& inf){
        vector<Image*>* vec = new vector<Image*>();
        ifstream ifs;
        Image* prev = NULL;
        
        ifs.open("data.bin",ios::binary);
        ifs.read((char*)&inf,sizeof(Info));
    
        int x_off = width - inf.width;
        int y_off = height - inf.height;
		#ifdef BOTTOM_RIGHT
		Image* bg = GetCanvas(width, height, x_off, y_off);
		#endif
		#ifdef CENTER
		Image* bg = GetCanvas(width - x_off / 2, height - y_off / 2, x_off / 2, y_off / 2);
		#endif
		#ifdef MASK
		#ifdef EARTH
		m = new Mask(RGB(39, 253, 0), bg, 0.32);
		#endif
		#ifdef SUPERMAN
		m = new Mask(RGB(80, 240, 101), bg, 0.42);
		#endif
		#endif

        int i = 0;
        do{
            prev = construct(ifs,inf,prev);
            vec->push_back(prev);
        }while(!ifs.eof());
        ifs.close();
        delete bg;
		#ifdef MASK
        delete m;
		#endif
        return vec;
    }
    
    void serialize(vector<Image*>* vec){
        vector<Image*>::iterator it = vec->begin();
        Info inf((*it)->width,(*it)->height,(*it)->Bpp);
        
        ofstream ofs;
        ofs.open("data.bin",ios::binary);
        ofs.write((char*)&inf,sizeof(Info));
        
        Image* base = NULL;
        for (; it != vec->end(); ++it){
            diff(ofs,base,*it);
            base = *it;
        }
        ofs.close();
    }
};