struct find_near{
	struct Sphere *obj;
	float dist;
};

struct Vector *color_at(struct Sphere obj){
	return obj.material;
}

struct find_near find_nearest(struct Ray *ray, struct Scene *scene){
	float dist_min = INFINITY;
	struct Sphere *obj_hit = NULL;
	for(int i=0; i<1;i++){
		float dist = intersects(&scene->objects[i], ray);
		if(dist != 0){
			if(obj_hit != NULL || dist < dist_min){
				dist_min = dist;
				obj_hit = &scene->objects[i];
			}
		}
	}
	struct find_near fn2 = {obj_hit, dist_min};
	return fn2;
}

struct Vector ray_trace(struct Ray *ray, struct Scene scene){
	struct Vector color = {0, 0, 0};
	struct find_near fn = find_nearest(ray, &scene);
	float dist = fn.dist;
	struct Sphere *obj = fn.obj;

	if(obj == NULL){
		return color;
	}
	struct Vector *add_two = add(*ray->origin, *ray->direction);
	struct Vector *hit_pos = static_mul(*add_two, dist);

	color = *add(color, *color_at(*obj));

	free(hit_pos);
	free(add_two);

	return color;
}

struct Image *render(struct Scene scene){
	float width = scene.width;
	float height = scene.height;
	float aspect = width/height;

	float x0 = -1.0;
	float x1 =  1.0;
	float x_step = (x1 - x0)/(width -1);
	float y0 = -1.0/aspect;
	float y1 =  1.0/aspect;

	float y_step = (y1 - y0)/(height -1);

	struct Vector cam = *scene.camera;
	struct Image *img = malloc(sizeof(struct Image));

	for(int j= 0; j< HEIGHT; j++){
		float y = y0 + j*y_step;
		for(int i=0; i< WIDTH; i++){
			float x = x0 + i*x_step;
			struct Ray *ray = malloc(sizeof(struct Image));
			struct Vector point = {x,y,0.0};
			ray->origin = &cam;
			struct Vector *subtract = sub(point,cam);
			ray->direction = normalize(*subtract);
			set_pixel(img, i,j, ray_trace(ray, scene));
			free(ray->direction);
			free(ray);
			free(subtract);
		}
	}

	return img;
}

