#ifndef FILEPATHS_H_
#define FILEPATHS_H_

#include <string>

//#define DEF_DEBUG
#define DEF_RELEASE

#ifdef DEF_DEBUG
	const std::string PATH_RES = "../Project/res/";
	const std::string PATH_RES_FONTS = "../Project/res/fonts/";
#endif

#ifdef DEF_RELEASE
	const std::string PATH_RES = "res/";
	const std::string PATH_RES_FONTS = "res/fonts/";
#endif

#endif 