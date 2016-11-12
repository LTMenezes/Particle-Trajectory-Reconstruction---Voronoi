# -*- coding: utf-8 -*-
"""
Particles are ordered by z in montecarlo object
"""

import numpy as np
import json
import ROOT

DIS_INF = 1000
#g.GetXaxis().SetTitle("x")
#g.GetYaxis().SetTitle("y")

with open(r'0.json') as json_data:
    input = json.load(json_data)

pid_collection = input["event"]["hit_id"]
px_collection = input["event"]["hit_x"]
py_collection = input["event"]["hit_y"]
pz_collection = input["event"]["hit_z"]

event_collection = input["montecarlo"]["particles"]

outputx = []
outputy = []
th2flist = []
th2fxy = ROOT.TH2F("XY","XY",1000,-40,40,1000,-40,40)
ihist=-1

print len(event_collection)
for event in event_collection:
    last_particle_id = 0
    print event[0]
    ihist+=1
    th2ftmp = ROOT.TH2F("XY"+str(ihist),"XY",1000,5,15,1000,-15,-5)
    th2flist.append(th2ftmp)

    for particle in event[15]:
        index = pid_collection.index(particle)
        if(last_particle_id == 0):
            last_particle_id = index
        else:
            x1 = px_collection[index]
            y1 = py_collection[index]
            z1 = pz_collection[index]
            x2 = px_collection[last_particle_id]
            y2 = py_collection[last_particle_id]
            z2 = pz_collection[last_particle_id]
            if(z1 == z2):
                continue
            else:
                a = (x2 - x1) / (z2 - z1)
                bx = x2 - (a * z2)
                c = (y2 - y1) / (z2 - z1)
                by = y2 - (c * z2)
                x = a * DIS_INF + bx
                y = c * DIS_INF + by
                outputx.append(x)
                outputy.append(y)
                th2fxy.Fill(x,y)
                th2flist[ihist].Fill(x,y)
with open(r"clean_output.txt", "w+") as output_file:
    for x, y in zip(outputx, outputy):
        output_file.write("%s %s \n" % (x, y))

f = ROOT.TFile("output.root", "recreate")
for h2 in th2flist:
    h2.Write()
th2fxy.Write()
f.Close()
