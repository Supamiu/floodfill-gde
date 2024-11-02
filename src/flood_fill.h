//© Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef SUMMATOR_CLASS_H
#define SUMMATOR_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/bit_map.hpp>

using namespace godot;

class FloodFill : public RefCounted
{
    GDCLASS(FloodFill, RefCounted);

    BitMap *grid;

protected:
    Vector2i grid_size;
    TypedArray<Vector2i> points;
    static void _bind_methods();

public:
    FloodFill();
    ~FloodFill();

    void set_grid(BitMap *p_grid);
    Array get_areas() const;
    TypedArray<Vector2i> fill(int x, int y) const;
};

#endif // SUMMATOR_CLASS_H