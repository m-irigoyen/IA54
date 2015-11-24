#ifndef FILEPATHS_H_
#define FILEPATHS_H_

#include <string>

#define DEF_DEBUG
//#define DEF_RELEASE

#ifdef DEF_DEBUG
	const std::string PATH_RES = "../Project/res/";
#endif

#ifdef DEF_RELEASE
	const std::string PATH_RES = "res/";
#endif

	const std::string PATH_RES_FONTS = "Fonts/";
	const std::string PATH_RES_TERRAINS = "Terrains/";

#endif 