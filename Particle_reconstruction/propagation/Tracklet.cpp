#include "Tracklet.h"

Tracklet::Tracklet(PixelHit* h1, PixelHit* h2, float dist)
{
  m_hits.push_back(h1);
  m_hits.push_back(h2);
  m_dist = dist;
}

void Tracklet::propagate()
{
  float hit1_x, hit1_y, hit1_z, hit2_x, hit2_y, hit2_z;

  hit1_x =  m_hits.at(0)->get_x();
  hit1_y =  m_hits.at(0)->get_y();
  hit1_z =  m_hits.at(0)->get_z();
  hit2_x =  m_hits.at(1)->get_x();
  hit2_y =  m_hits.at(1)->get_y();
  hit2_z =  m_hits.at(1)->get_z();

  m_tx = (hit2_x - hit1_x) /
            (m_hits.at(1)->get_z() - hit1_z);

  m_x0 =  hit2_x - (m_tx * m_hits.at(1)->get_z());

  m_ty = (hit2_y - hit1_y) /
            (hit2_z - hit1_z);

  m_y0 = hit2_y - (m_ty * hit2_z);

  m_xPropagated = m_tx * m_dist + m_x0;
  m_yPropagated = m_ty * m_dist + m_y0;
  return;
}
