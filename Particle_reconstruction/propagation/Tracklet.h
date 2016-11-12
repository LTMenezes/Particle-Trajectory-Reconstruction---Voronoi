#pragma once

#include "PixelHit.h"

#include <iostream>

class Tracklet
{

  public:
    // Standard constructor
    Tracklet();
    // Creates a tracklet from two hits
    Tracklet(PixelHit* h1, PixelHit* h2, float dist);

    // Destructor
    virtual ~Tracklet() {}
    // Start a seed tracklet from two given hits
    void setHits(PixelHit *h1, PixelHit *h2)
    {
      m_hits.clear();
      m_hits.push_back(h1);
      m_hits.push_back(h2);
    }

    void setPropagationDistance(float dist)
    {
      m_dist = dist;
    }

    void propagate();

    float get_x() {return m_xPropagated;}

    float get_y() {return m_yPropagated;}

  private:
    PixelHits m_hits;
    // Straight-line fit parameters
    float m_tx;
    float m_ty;
    float m_x0;
    float m_y0;
    // Distance to propagate
    float m_dist;
    // Propagated x and y
    float m_xPropagated;
    float m_yPropagated;
};

typedef std::vector<Tracklet *> Tracklets;
