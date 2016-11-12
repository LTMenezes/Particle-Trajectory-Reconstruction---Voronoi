#pragma once

#include "../PixelHit.h"
#include "../Tracklet.h"
#include "../../config/config.cpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <functional>

using namespace std;

class Hits_input
{
  public:
    // Standard constructor
    Hits_input(){};

    PixelHits* inputFromFile()
    {
      PixelHits* input = new PixelHits;
      float x, y, z;

      fstream file_x(file_x_adr, ios_base::in);
    	fstream file_y(file_y_adr, ios_base::in);
    	fstream file_z(file_z_adr, ios_base::in);

      while(file_x >> x && file_y >> y && file_z >> z){
        PixelHit* hit = new PixelHit(x, y, z);
        input->push_back(hit);
      }

      // TODO: Implement sort
      return input;
    }
};
