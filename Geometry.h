//Blake Lockley - 44587643

#ifndef GEOMETRY_H
#define GEOMETRY_H

struct Point {
  float x, y;
  Point(float _x, float _y): x(_x), y(_y) {}
};

struct Rect {
  float width, height;
  Rect(float w, float h): width(w), height(h) {}
};

//TODO: possibly do implementation
struct Frame {
  Point centre;
  Rect rect;

  Frame(Point p, Rect r): centre(p), rect(r) {}
  Frame(float x, float y, float width, float height):
  	centre(Point(x,y)), rect(Rect(width, height)) {}

  bool contains(Point point) {
    float px = point.x, py = point.y;
    float cx = centre.x, cy = centre.y;
    float w = rect.width / 2.0f, h = rect.height / 2.0f;

    return (cx - w < px && px < cx + w) && (cy - h < py && py < cy + h);
  }

  Point topLeft(void) { return Point(	centre.x - rect.width / 2.0f,
                                    	centre.y + rect.height / 2.0f); }

  Point topRight(void) { return Point(	centre.x + rect.width / 2.0f,
                                    	centre.y + rect.height / 2.0f); }

  Point bottomRight(void) { return Point(centre.x + rect.width / 2.0f,
                                         centre.y - rect.height / 2.0f); }

  Point bottomLeft(void) { return Point(	centre.x - rect.width / 2.0f,
                                    	centre.y - rect.height / 2.0f); }

  bool intersects(Frame other) {
    //checks if another corners of the two rects are in the other rect

    bool test = contains(other.topLeft()) ||
            		contains(other.topRight()) ||
              	contains(other.bottomLeft()) ||
              	contains(other.bottomRight());

    if (test)
    	return true; //save doing the extra proccessing

    test = 			other.contains(topLeft()) ||
    						other.contains(topRight()) ||
    						other.contains(bottomLeft()) ||
              	other.contains(bottomRight());

    return test;
  }

  //not named well but tests if part of the other frame is partially outside of the current frame
  // returns: true if any point of other is outside this frame
  bool doesNotFullyContain(Frame other) {
    Point points[] = { 	other.topLeft(), other.topRight(),
                      	other.bottomLeft(), other.bottomRight() };

    for (int i = 0; i < 4; i++)
    	if (contains(points[i]) == false)
    	return true;

    return false;
  }

};

#endif
