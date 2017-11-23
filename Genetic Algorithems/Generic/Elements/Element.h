enum ElementType { SQUARE, TRIANGLE, CIRCLE };

extern Image* originalImg;

class Element{
public:
	virtual void show(int x_offset, int y_offset) = 0;
	virtual void mutate() = 0;
};