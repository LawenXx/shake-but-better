#include "pch.h"

vec3_t::vec3_t()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

vec3_t::vec3_t(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0.f;
}

vec3_t::vec3_t(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

bool vec3_t::operator==(vec3_t& coords)
{
	return (this->x >= coords.x && this->y >= coords.y && this->z >= coords.z);
}

bool vec3_t::operator!=(vec3_t& coords)
{
	return !(this->x == coords.x && this->y == coords.y && this->z == coords.z);
}

bool vec3_t::operator>=(vec3_t& coords)
{
	return (this->x >= coords.x && this->y >= coords.y && this->z >= coords.z);
}

bool vec3_t::operator<=(vec3_t& coords)
{
	return (this->x <= coords.x && this->y <= coords.y && this->z <= coords.z);
}

const vec3_t vec3_t::operator-()
{
	return vec3_t(-x, -y, -z);
}

const vec3_t vec3_t::operator-(vec3_t const& coords)
{
	return vec3_t(this->x - coords.x, this->y - coords.y, this->z - coords.z);
}

const vec3_t vec3_t::operator+(vec3_t const& coords)
{
	return vec3_t(this->x + coords.x, this->y + coords.y, this->z + coords.z);
}

const vec3_t vec3_t::operator*(vec3_t const& coords)
{
	return vec3_t(this->x * coords.x, this->y * coords.y, this->z * coords.z);
}

const vec3_t vec3_t::operator/(vec3_t const& coords)
{
	return vec3_t(this->x / coords.x, this->y / coords.y, this->z / coords.z);
}

const vec3_t vec3_t::operator-=(vec3_t const& coords)
{
	return vec3_t(this->x -= coords.x, this->y -= coords.y, this->z -= coords.z);
}

const vec3_t vec3_t::operator+=(vec3_t const& coords)
{
	return vec3_t(this->x += coords.x, this->y += coords.y, this->z += coords.z);
}

const vec3_t vec3_t::operator*=(vec3_t const& coords)
{
	return vec3_t(this->x *= coords.x, this->y *= coords.y, this->z *= coords.z);
}

const vec3_t vec3_t::operator/=(vec3_t const& coords)
{
	return vec3_t(this->x /= coords.x, this->y /= coords.y, this->z /= coords.z);
}

const float vec3_t::Length(void)
{
	return sqrtf(x * x + y * y + z * z);
}

const vec3_t vec3_t::normalize(void)
{
	float Len = Length();

	if (!Len)
		return vec3_t(0, 0, 1);
	Len = 1 / Len;
	return vec3_t(x * Len, y * Len, z * Len);
}

const float vec3_t::GetDistance(vec3_t coords)
{
	float x = this->x - coords.x;
	float y = this->y - coords.y;
	float z = this->z - coords.z;
	return sqrtf((x * x) + (y * y) + (z * z)) * 0.03048f;
}

const float vec3_t::DotProduct(vec3_t coords)
{
	return (this->x * coords.x) + (this->y * coords.y) + (this->z * coords.z);
}

const vec3_t vec3_t::Radian()
{
	return vec3_t(this->z * (M_PI / 180.f), this->x * (M_PI / 180.f), this->y * (M_PI / 180.f));
}

void vec3_t::CoordsText(vec3_t coords)
{

}

vec4_t::vec4_t()
{
	this->r = this->g = this->b = this->a = 0.0f;
}

vec4_t::vec4_t(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

vec2_t::vec2_t()
{
	x = 0.f;
	y = 0.f;
}

vec2_t::vec2_t(float x, float y)
{
	this->x = x;
	this->y = y;
}

vec2_t::vec2_t(float x, float y, float z)
{
	this->x = x;
	this->y = y;
}

bool vec2_t::operator==(vec2_t& coords)
{
	return (this->x >= coords.x && this->y >= coords.y);
}

bool vec2_t::operator!=(vec2_t& coords)
{
	return !(this->x == coords.x && this->y == coords.y);
}

bool vec2_t::operator>=(vec2_t& coords)
{
	return (this->x >= coords.x && this->y >= coords.y);
}

bool vec2_t::operator<=(vec2_t& coords)
{
	return (this->x <= coords.x && this->y <= coords.y);
}

const vec2_t vec2_t::operator-()
{
	return vec2_t(-x, -y);
}

const vec2_t vec2_t::operator-(vec2_t const& coords)
{
	return vec2_t(this->x - coords.x, this->y - coords.y);
}

const vec2_t vec2_t::operator+(vec2_t const& coords)
{
	return vec2_t(this->x + coords.x, this->y + coords.y);
}

const vec2_t vec2_t::operator*(vec2_t const& coords)
{
	return vec2_t(this->x * coords.x, this->y * coords.y);
}

const vec2_t vec2_t::operator/(vec2_t const& coords)
{
	return vec2_t(this->x / coords.x, this->y / coords.y);
}

const vec2_t vec2_t::operator-=(vec2_t const& coords)
{
	return vec2_t(this->x -= coords.x, this->y -= coords.y);
}

const vec2_t vec2_t::operator+=(vec2_t const& coords)
{
	return vec2_t(this->x += coords.x, this->y += coords.y);
}

const vec2_t vec2_t::operator*=(vec2_t const& coords)
{
	return vec2_t(this->x *= coords.x, this->y *= coords.y);
}

const vec2_t vec2_t::operator/=(vec2_t const& coords)
{
	return vec2_t(this->x /= coords.x, this->y /= coords.y);
}

const float vec2_t::Length(void)
{
	return sqrtf(x * x + y * y);
}

const vec2_t vec2_t::normalize(void)
{
	float Len = Length();

	if (!Len)
		return vec2_t(0, 0, 1);
	Len = 1 / Len;
	return vec2_t(x * Len, y * Len);
}

const float vec2_t::GetDistance(vec2_t coords)
{
	float x = this->x - coords.x;
	float y = this->y - coords.y;
	return sqrtf((x * x) + (y * y)) * 0.03048f;
}

const float vec2_t::DotProduct(vec2_t coords)
{
	return (this->x * coords.x) + (this->y * coords.y);
}
