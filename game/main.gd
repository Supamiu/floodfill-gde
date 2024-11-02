extends Node

func _ready() -> void:
	var bitmap: BitMap = BitMap.new()
	bitmap.create(Vector2i(1024,1024))
	var bitmap_copy: BitMap = bitmap.duplicate()
	var fill = FloodFill.new()
	var start = Time.get_ticks_msec()
	fill.set_grid(bitmap)
	var res = fill.fill(0,0)
	print("C++: %fms, (%dx%d)"%[(Time.get_ticks_msec() - start), sqrt(res.size()), sqrt(res.size())])
	var start_gd = Time.get_ticks_msec()
	var res_gd = gds_flood_fill(bitmap_copy, 0, 0)
	print("GDScript: %fms, (%dx%d)"%[(Time.get_ticks_msec() - start_gd), sqrt(res_gd.size()), sqrt(res_gd.size())])

func gds_flood_fill(grid: BitMap, tilex: int, tiley: int):
	var area = {}
	var to_fill = [Vector2(tilex, tiley)]
	var to_fill_dict = {Vector2(tilex, tiley): true}
	while to_fill:
		var tile = to_fill.pop_back()
		if !area.has(tile):
			area[tile] = true
			#check adjacent cells
			var north = Vector2i(tile.x, tile.y-1)
			var south = Vector2i(tile.x, tile.y+1)
			var east  = Vector2i(tile.x+1, tile.y)
			var west  = Vector2i(tile.x-1, tile.y)
			for dir in [north,south,east,west]:
				if dir.x >= 0 and dir.y >= 0:
					if dir.x < grid.get_size().x and dir.y < grid.get_size().y and grid.get_bit(dir.x, dir.y) == false:
						if !to_fill_dict.has(dir) and !area.has(dir):
							to_fill.append(dir)
							to_fill_dict[dir] = true
	var area_array = area.keys()
	if area_array.size() >= 0:
		return area_array
