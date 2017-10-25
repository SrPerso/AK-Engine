#include "Configuration.h"
#include "Color.h"

Configuration::Configuration(const char* string)
{
	valueRoot = json_parse_file(string);
	objectRoot = json_value_get_object(valueRoot);
}

Configuration::Configuration(JSON_Object* section)
{
	objectRoot = section;
}

Configuration::~Configuration()
{
	if (valueRoot != nullptr)
	{
		json_value_free(valueRoot);
	}
}

Configuration Configuration::GetSection(const char * name) const
{
	return Configuration(json_object_dotget_object(objectRoot, name));
}

Configuration Configuration::AddSection(const char * name)
{
	json_object_set_value(objectRoot, name, json_value_init_object());
	return GetSection(name);
}

bool Configuration::IsValueValid() const
{
	if (valueRoot != nullptr && objectRoot != nullptr)
	{
		return true;
	}
	return false;
}

bool Configuration::GetBool(const char * fieldName) const
{
	if (objectRoot != nullptr)
	{
		return json_object_dotget_boolean(objectRoot, fieldName);
	}
	return false;
}

int Configuration::GetInt(const char * fieldName) const
{
	if (objectRoot != nullptr)
	{
		return (int)json_object_dotget_number(objectRoot, fieldName);
	}
	return 0;
}

float Configuration::GetFloat(const char * fieldName) const
{
	if (objectRoot != nullptr)
	{
		return (float)json_object_dotget_number(objectRoot, fieldName);
	}
	return 0.0f;
}

const char * Configuration::GetString(const char * fieldName) const
{
	if (objectRoot != nullptr)
	{
		return json_object_dotget_string(objectRoot, fieldName);
	}
	return nullptr;
}

bool Configuration::SetBool(const char * fieldName, bool value)
{
	if (json_object_dotset_boolean(objectRoot, fieldName, value) == JSONSuccess)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Configuration::SetInt(const char * fieldName, int value)
{
	if (json_object_dotset_number(objectRoot, fieldName, value) == JSONSuccess)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Configuration::SetFloat(const char * fieldName, float value)
{
	if (json_object_dotset_number(objectRoot, fieldName, value) == JSONSuccess)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Configuration::SetString(const char * fieldName, const char * value)
{
	if (json_object_dotset_string(objectRoot, fieldName, value) == JSONSuccess)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Configuration::SetColor(const char * fieldName, Color value)
{
	if (AddArrayFloat("fieldName", &value, 4))
	{
		return true;
	}
	return false;
}

bool Configuration::AddArrayFloat(const char * fieldName, const float * value, int size)
{
	if (value != nullptr && size > 0)
	{
		JSON_Value* tmp = json_value_init_array();
		arrayConfig = json_value_get_array(tmp);
		json_object_set_value(objectRoot, fieldName, tmp);

		for (int i = 0; i < size; ++i)
		{
			if (json_array_append_number(arrayConfig, value[i]) != JSONSuccess)
			{
				return false;
			}
		}
	}
	return false;
}

bool Configuration::SerializeToFile(const char * fileName)
{
	bool ret = false;
	if (valueRoot != nullptr)
	{
		if (json_serialize_to_file(valueRoot, fileName) == JSONSuccess)
		{
			ret = true;
		}
	}
	return ret;
}
