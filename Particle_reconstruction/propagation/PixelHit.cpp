#include "PixelHit.h"

PixelHit::PixelHit() : m_x(0.0f), m_y(0.0f), m_z(0.0f) {}

PixelHit::PixelHit(float x, float y, float z)
{
  m_x = x;
  m_y = y;
  m_z = z;
}
