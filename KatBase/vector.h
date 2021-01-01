#pragma once

#define M_PI 3.141592654f
typedef float vec_t;

struct vec3_t
{
	float x, y, z;

	vec3_t();
	vec3_t(float x, float y);
	vec3_t(float x, float y, float z);

	bool operator==(vec3_t& coords);
	bool operator!=(vec3_t& coords);
	bool operator>=(vec3_t& coords);
	bool operator<=(vec3_t& coords);

	const vec3_t operator-();
	const vec3_t operator-(vec3_t const& coords);
	const vec3_t operator+(vec3_t const& coords);
	const vec3_t operator*(vec3_t const& coords);
	const vec3_t operator/(vec3_t const& coords);

	const vec3_t operator-=(vec3_t const& coords);
	const vec3_t operator+=(vec3_t const& coords);
	const vec3_t operator*=(vec3_t const& coords);
	const vec3_t operator/=(vec3_t const& coords);

	const float Length(void);
	const vec3_t normalize(void);
	const float GetDistance(vec3_t coords);
	const float DotProduct(vec3_t coords);
	const vec3_t Radian();

	void CoordsText(vec3_t coords);
};

struct vec2_t
{
	float x, y;

	vec2_t();
	vec2_t(float x, float y);
	vec2_t(float x, float y, float z);

	bool operator==(vec2_t& coords);
	bool operator!=(vec2_t& coords);
	bool operator>=(vec2_t& coords);
	bool operator<=(vec2_t& coords);

	const vec2_t operator-();
	const vec2_t operator-(vec2_t const& coords);
	const vec2_t operator+(vec2_t const& coords);
	const vec2_t operator*(vec2_t const& coords);
	const vec2_t operator/(vec2_t const& coords);

	const vec2_t operator-=(vec2_t const& coords);
	const vec2_t operator+=(vec2_t const& coords);
	const vec2_t operator*=(vec2_t const& coords);
	const vec2_t operator/=(vec2_t const& coords);

	const float Length(void);
	const vec2_t normalize(void);
	const float GetDistance(vec2_t coords);
	const float DotProduct(vec2_t coords);
};


struct vec4_t
{
	float r, g, b, a;

	vec4_t();
	vec4_t(float r, float g, float b, float a);
};