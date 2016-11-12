#pragma once

#include "PixelHit.h"
#include "Tracklet.h"

class Propagation{
  public:
    // Standart Constructor
    Propagation(){};

    void GeneratePropagatedTracklets();

  private:
    Tracklets m_tracklets;
};
