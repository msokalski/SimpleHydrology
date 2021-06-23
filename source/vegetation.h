struct Plant{
  Plant(int i, glm::ivec2 d){
    index = i;
    pos = glm::vec2(i/d.y, i%d.y);
  };

  Plant(glm::vec2 p, glm::ivec2 d){
    pos = p;
    index = (int)p.x*d.y+(int)p.y;
  };

  glm::vec2 pos;
  int index;
  float size = 0.5;
  const float maxsize = 5.0;
  const float rate = 0.05;

  void grow();
  void root(double* density, glm::ivec2 dim, double factor);

  Plant& operator=(const Plant& o){
    if(this != &o){  //Self Check
      pos = o.pos;
      index = o.index;
      size = o.size;
    }
    return *this;
  };
};


void Plant::grow(){
  size += rate*(maxsize-size);
};


void Plant::root(double* density, glm::ivec2 dim, double f){

  int ix = index / dim.y;
  int iy = index % dim.y;

  int r = (int)round(maxsize);

  int x_lo = max(ix-r,0);
  int x_hi = min(ix+r,dim.x-1);
  int y_lo = max(iy-r,0);
  int y_hi = min(iy+r,dim.y-1);

  for (int x=x_lo; x<=x_hi; x++)
  {
    int dx = x-ix;
    for (int y=y_lo; y<=y_hi; y++)
    {
      int dy = y-iy;
      double m = 1+dx*dx+dy*dy;
      density[x*dim.y+y] += f; // /m;
    }
  }

  return;

  //Can always do this one
  density[index]       += f*1.0;

  if(pos.x > 0){
    //
    density[index - dim.y] += f*0.6;      //(-1, 0)

    if(pos.y > 0)
      density[index - dim.y - 1] += f*0.4;    //(-1, -1)

    if(pos.y < dim.y - 1)
      density[index - dim.y + 1] += f*0.4;    //(-1, 1)
  }

  if(pos.x < dim.x - 1){
    //
    density[index + dim.y] += f*0.6;    //(1, 0)

    if(pos.y > 0)
      density[index + dim.y - 1] += f*0.4;    //(1, -1)

    if(pos.y < dim.y - 1)
      density[index + dim.y + 1] += f*0.4;    //(1, 1)
  }

  if(pos.y > 0)
    density[index - 1]   += f*0.6;    //(0, -1)

  if(pos.y < dim.y - 1)
    density[index + 1]   += f*0.6;    //(0, 1)
}

