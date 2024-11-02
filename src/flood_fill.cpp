#include "flood_fill.h"

#include <godot_cpp/core/class_db.hpp>
#include <stack>


using namespace godot;

FloodFill::FloodFill()
{
}

FloodFill::~FloodFill()
{
}

void FloodFill::set_grid(BitMap *p_grid)
{
    grid = p_grid;
    grid_size = grid->get_size();
}

TypedArray<Vector2i> FloodFill::fill(int x, int y) const
{
    TypedArray<Vector2i> res = TypedArray<Vector2i>();
    std::stack<Vector2i> q;
    q.push(Vector2i(x, y));
    grid->set_bitv(Vector2i(x, y), true);
    while(!q.empty()){
        Vector2i pt = q.top();
        q.pop();
        res.append(pt);
        Vector2i left = Vector2i(pt.x - 1, pt.y);
        Vector2i right = Vector2i(pt.x + 1, pt.y);
        Vector2i top = Vector2i(pt.x, pt.y - 1);
        Vector2i bottom = Vector2i(pt.x, pt.y + 1);
        if(left.x >= 0 && !grid->get_bitv(left)){
            q.push(left);
            grid->set_bitv(left, true);
        }            
        if(right.x < grid_size.x && !grid->get_bitv(right)){
            q.push(right);
            grid->set_bitv(right, true);
        }
        if(top.y >= 0 && !grid->get_bitv(top)){
            q.push(top);
            grid->set_bitv(top, true);
        }
        if(bottom.y < grid_size.y && !grid->get_bitv(bottom)){
            q.push(bottom);
            grid->set_bitv(bottom, true);
        }
    }
    return res;
}

void FloodFill::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("fill", "x", "y"), &FloodFill::fill);
    ClassDB::bind_method(D_METHOD("set_grid", "grid"), &FloodFill::set_grid);
}