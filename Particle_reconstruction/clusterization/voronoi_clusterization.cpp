#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <fstream>

#define CLUSTER_LIMIT 1

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Face_iterator Face_iterator;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Vertex_iterator Vertex_iterator;
typedef Triangulation::Point Point;
typedef Triangulation::Vertex_handle Vh;
using namespace std;

int main( )
{
        std::ifstream in("out.txt");
        std::istream_iterator<Point> begin(in);
        std::istream_iterator<Point> end;

        vector<float> vectorx;
        vector<float> vectory;

        Triangulation T;
        T.insert(begin, end);

        int ns = 0;
        int nr = 0;
        int removals = 0;
        int ft =0;
        // only for reference
        Edge_iterator eit =T.edges_begin();
        for (; eit !=T.edges_end(); ++eit) {
              ft++;
                CGAL::Object o = T.dual(eit);
                if (CGAL::object_cast<K::Segment_2>(&o)) {++ns; }
                else if (CGAL::object_cast<K::Ray_2>(&o)) {++nr; }
        }
        int i, j;
        Vh vh1, vh2;
        double sm1, sm2, distance;
        int maxLoop = 0;
        int isRemoved =0;
        std::cout<<T.number_of_vertices()<<endl;
        // iterate through every face in the voronoi diagram
        //while(maxLoop != T.number_of_faces()){
        while(maxLoop != 5){
          Face_iterator fit = T.faces_begin();
          for (; fit !=T.faces_end(); ++fit) {
                  for(i = 0; i <= 2; i++) {
                          j = i + 1;
                          if(j == 3) {j = 0; }

                          sm1 = T.triangle(fit)[i].x() - T.triangle(fit)[j].x();
                          sm2 = T.triangle(fit)[i].y() - T.triangle(fit)[j].y();
                          distance = sqrt(sm1 * sm1 + sm2 * sm2);
                          if(distance <= CLUSTER_LIMIT) {
                                  sm1 = sm1/2 + T.triangle(fit)[j].x();
                                  sm2 = sm2/2 + T.triangle(fit)[j].y();

                                  vectorx.push_back(T.triangle(fit)[i].x());
                                  vectorx.push_back(T.triangle(fit)[j].x());
                                  vectory.push_back(T.triangle(fit)[i].y());
                                  vectory.push_back(T.triangle(fit)[j].y());

                                  Point cluster_result(sm1,sm2);
                                  T.move(fit->vertex(i),cluster_result);
                                  T.remove(T.nearest_vertex(cluster_result));
                                  removals++;
                          }
                  }
            }
            maxLoop++;
        }

        //output for cgal
      	ofstream outfile;
      	outfile.open("out_after_cluster.txt");
        Vertex_iterator vit =T.vertices_begin();
        for (; vit !=T.vertices_end(); ++vit) {
          //CGAL::Object o = T.dual(vit);

          outfile << vit->point().x() << " "
          << vit->point().y()<<endl;
        }
      	outfile.close();

        ofstream outfile2;
      	outfile2.open("clusterizeds.txt");
        for (int it = 0; it < vectorx.size(); ++it) {
          outfile2 << vectorx.at(it) << " "
          << vectory.at(it)<<endl;

        }
      	outfile2.close();

        std::cout << "The Voronoi diagram has " << ns << " finite edges "
                  << ", " << nr << " rays"<< std::endl;
        cout << "Total of removals :" << removals << " "<<T.number_of_vertices()<< endl;
        return 0;
}
