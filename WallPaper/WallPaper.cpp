#include "Serializer.cpp"
#include <wchar.h>
#include <time.h>
//#define CREATE_GIF
//#define ONE_PIC
//#define TEST_MASK
//#define SERIALIZE
const short FPS = 25;
clock_t t0;
vector<Image*>* imgs;
vector<Image*>::iterator it;
int x_off, y_off;

double msPassed()
{
	clock_t t1 = clock();
    double diffms=(t1-t0)/(CLOCKS_PER_SEC/1000);
	t0 = t1;
    return diffms;
}

#ifdef CREATE_GIF
bool hasEnding(char* filename, char* ending) {
	int filename_len = strlen(filename), len = strlen(ending);
	return (filename_len >= len && strcmp(filename + filename_len - len, ending) == 0);
}

void find() {
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(TEXT("*"), &ffd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			if (hasEnding(ffd.cFileName, ".bmp")) {
				imgs->push_back(loadImage(ffd.cFileName));
				#ifdef ONE_PIC
				return;
				#endif
			}
		} while (FindNextFile(hFind, &ffd) != 0);
		FindClose(hFind);
	}
}
#endif

void setup(){
	createCanvas();
	#ifdef CREATE_GIF
		imgs = new vector<Image*>();
		find();
		#ifdef SERIALIZE
			Serializer s;
			s.serialize(&imgs);
		#endif
		#ifdef TEST_MASK
			int idx;
			Image* bg = GetCanvas(width, height);

			//Replace with your mask
			Mask m(RGB(0, 0, 0), bg, 0.45);

			int i = 0;
			for (it = imgs->begin(); it != imgs->end(); ++it, ++i) {
				for (short i = 0; i<(*it)->width; ++i) {
					for (short j = 0; j<(*it)->height; ++j) {
						idx = (*it)->index(i, j);
						(*it)->set(idx, m.color_mask((*it)->get(idx), idx));
					}
				}
			}
		#endif
	#else
		Info inf;
		Serializer s;
		imgs = s.deserialize(inf);
		x_off = width - inf.width;
		y_off = height - inf.height;
	#endif
	it = imgs->begin();
    t0 = clock();
}

void draw(){
	#if defined(SERIALIZE) && defined(CREATE_GIF)
		system("pause");
		noLoop();
	#else
		if(it == imgs->end())
			it = imgs->begin();
		#ifdef CENTER
			drawImage(*(it++), x_off / 2, y_off / 2);
		#endif
		#ifdef BOTTOM_RIGHT
			drawImage(*(it++), x_off, y_off);
		#endif
		double delta = msPassed();
		if(delta < 1000.0/FPS)
            Sleep(1000.0/FPS - delta);
	#endif
}