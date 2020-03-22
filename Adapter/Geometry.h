#pragma once
#include <iostream>
#include <vector>
#include <boost/functional/hash.hpp>
struct Point{
    int x, y;
    friend std::size_t hash_value(const Point &obj){
        std::size_t seed = 0x1E44943F;
        boost::hash_combine(seed,obj.x);
        boost::hash_combine(seed,obj.x);
        return seed;
    }
};
struct Line{
    Point start,end;
    friend std::size_t hash_value(const Point &obj){
        std::size_t seed = 0x52E4F07A;
        boost::hash_combine(seed,obj.x);
        boost::hash_combine(seed,obj.x);
        return seed;
    }
};

struct VectorObject {
    virtual std::vector<Line>::iterator begin() = 0;
    virtual std::vector<Line>::iterator end() = 0;
};
struct VectorRectangle : VectorObject {
    VectorRectangle(int x,int y,int width,int height){
        lines.emplace_back(Line{Point{x,y},Point{x+width,y}});
        lines.emplace_back(Line{Point{x + width,y},Point{x+width,y+height}});
        lines.emplace_back(Line{Point{x,y},Point{x,y+height}});
        lines.emplace_back(Line{Point{x,y + height},Point{x+width,y+height}});
        std::vector<Line>::iterator begin() override {
            return lines.begin();
        };
        std::vector<Line>::iterator end() override {
            return lines.end();
        };
    };
    private:
    std::vector<Line> lines;
};