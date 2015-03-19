#include "Material.hpp"

Material::Material()
	:diffuseColor( RGB(0,0,0) ), specularColor( RGB(1,1,1) ),
	luminosity(RGB(0,0,0)), shininess( 5.0f ), reflectiveness( 0.1 )
{
}

Material::~Material(){}

RGB Material::calcIllumination( const glm::vec3 _normal, const LightRay _light, const glm::vec3 _view )
{
	RGB result;
	result = glm::dot( _light.direction, _normal ) * diffuseColor * _light.color;

	glm::vec3 light_reflect = reflect( _light.direction, _normal );
	float reflect_factor = glm::dot( light_reflect, _view );
	if( reflect_factor > 0 )
	{
		reflect_factor = pow(reflect_factor, shininess);
		result += reflect_factor * specularColor;
	}

	result = glm::clamp( result, 0.0f, 1.0f );

	return result;
}

RGB Material::combineColors( const RGB material, const RGB reflected )
{
	return material + reflectiveness*reflected;
}
