#ifndef __SERVER_CONFIG_H__
#define __SERVER_CONFIG_H__

#include <yaml-cpp/yaml.h>

namespace ServerConfig {
	static YAML::Node Config = YAML::LoadFile("../server_config.yml");
}

#endif
