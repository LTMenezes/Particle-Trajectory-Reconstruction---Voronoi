#include "PixelHit.h"
#include "Tracklet.h"
#include "../config/config.cpp"
#include "utils/Hits_input.h"
#include "Propagation.h"

#include <iostream>
#include <algorithm>
#include <fstream>

void Propagation::GeneratePropagatedTracklets()
{
    m_tracklets.clear();

    Hits_input* util = new Hits_input();
    PixelHits* in = util->inputFromFile();

    PixelHits::iterator itr1 = in->begin();

    while(itr1 != in->end())
    {
      PixelHits::iterator itr2 = in->begin();
        while(itr2 != in->end())
        {
          if((*itr1)->get_z() >= (*itr2)->get_z()){itr2++; continue;}
          Tracklet* tracklet = new Tracklet((*itr1), (*itr2), PropagateDistance);
          tracklet->propagate();
          m_tracklets.push_back(tracklet);
          itr2++;
        }
        itr1++;
    }

    //output for reference only
  	ofstream outfile;
  	outfile.open(propagation_output_adr);
  	outfile<< m_tracklets.size()<< endl;
  	for(int i=0; i < m_tracklets.size(); i++){
  		outfile << m_tracklets.at(i)->get_x()<<" " << m_tracklets.at(i)->get_y()<<endl;
  	}
    outfile.close();

    cout<<"Hits: "<<in->size()<<endl;
  	cout<<"Tracklets: "<<m_tracklets.size()<<endl;
    return;
};
