#include "AdapterVisualDlg.h"
#include <map>
#include "Geometry.h"
#include <memory>
#include <vector>
std::vector<std::shared_ptr<VectorObject>> vectorObjects{
    std::make_shared<VectorRectangle>(10,10,100,100),
    std::make_shared<VectorRectangle>(30,30,60,60)
};
// to paint the lines in a raster form
// you need to build an Adapter

struct LineToPointAdapter{
    typedef std::vector<Point> Points;
    LineToPointAdapter(Line &line){
        int left = std::min(line.start.x,line.end.x);
        int right = std::max(line.start.x,line.end.x);
        int top = std::min(line.start.y,line.end.y);
        int bottom = std::max(line.start.y,line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;
        static int count = 0;
        std::cout << "Number of LinePointAdapter created: " << count << std::endl;
        //vertical line
        if (dx == 0){
            for (int y = top;y <= bottom;++y){
                points.emplace_back(Point{left,y});
            }
        }
        else if (dy == 0){
            for(int x = left;x <= right;++x){
                points.emplace_back(Point{x,top});
            }
        }
    };
    private:
        Points points;
};

struct LineToPointCachingAdapter{
    typedef std::vector<Point> Points;
    LineToPointCachingAdapter(Line &line){
        boost::hash<Line> hash;
        line_hash = hash(line);
        if(cache.find(line_hash) != cache.end()){
            return;
        }
        static int count = 0;
        std::cout << "Number of LinePointAdapter created: " << count << std::endl;
        int left = std::min(line.start.x,line.end.x);
        int right = std::max(line.start.x,line.end.x);
        int top = std::min(line.start.y,line.end.y);
        int bottom = std::max(line.start.y,line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;
        //vertical line
        if (dx == 0){
            for (int y = top;y <= bottom;++y){
                points.emplace_back(Point{left,y});
            }
        }
        else if (dy == 0){
            for(int x = left;x <= right;++x){
                points.emplace_back(Point{x,top});
            }
        }
        cache[line_hash] = points;
    }
    virtual Points::iterator begin() {return cache[line_hash].begin()};
    virtual Points::iterator end() {return cache[line_hash].end()};
    private:
    Points points;
    size_t line_hash;
    static std::map<size_t,std::vector<Point>> cache;

};