#include "Object.h"

namespace Twili
{
	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);
	}
}