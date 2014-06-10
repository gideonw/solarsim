//
//  main.cpp
//  ntw
//
//  Created by Gideon on 6/1/14.
//  Copyright (c) 2014 Gideon. All rights reserved.
//

// standard C++ libraries
#include <iostream>
#include <stdexcept>
#include <locale>


// My Classes
#include "game/Game.h"

int main(int argc, const char * argv[])
{
	std::locale::global( std::locale( "" ) );
	
	try{
		Game::start();
	} catch (const std::exception& e){
		std::cerr << "ERROR: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


