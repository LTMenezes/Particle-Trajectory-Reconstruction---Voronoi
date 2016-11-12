#pragma once

#include <vector>
#include <iostream>

class PixelHit
{

  public:
    // Standard constructor
    PixelHit();
    // Creates a tracklet from two hits
    PixelHit(float x, float y, float z);

    // Destructor
    virtual ~PixelHit() {}
    // Start a seed tracklet from two given hits
    void set(float x, float y, float z)
    {
      m_x = x;
      m_y = y;
      m_z = z;
      return;
    }

    bool compare_hit_z(PixelHit* hit)
    {
    	return m_z > hit->get_z();
    }

    float get_x()
    {
      return m_x;
    }

    float get_y()
    {
      return m_y;
    }

    float get_z()
    {
      return m_z;
    }

  private:
    float m_x;
    float m_y;
    float m_z;
    bool m_isUsed;
};

typedef std::vector<PixelHit *> PixelHits;
