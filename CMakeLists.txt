cmake_minimum_required( VERSION 3.9 )
project( LibCaca )

SET(CMAKE_C_COMPILER /usr/bin/x86_64-linux-gnu-g++-4.9)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -pedantic -Wfloat-equal -Wshadow \
-Weffc++ -Wstrict-overflow=5 -Wcast-align -Wconversion -ftrapv \
-Wuninitialized -Wuseless-cast -Wold-style-cast -Wnon-virtual-dtor -fPIC \
-D_GLIBCXX_USE_CXX11_ABI=0")

include_directories( Graphic_Includes/Libcaca Graphic_Includes Caca_Sources Core_Sources Snake_Sources )

link_directories( Graphic_Libs/Libcaca Graphic_Libs/Sfml)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_library( _arcade_libcaca SHARED
			 Graphic_Includes/Libcaca/caca.h
			 Graphic_Includes/Libcaca/caca++.h
			 Graphic_Includes/Libcaca/caca_types.h
			 Core_Sources/ILib.hpp
			 Core_Sources/ALib.cpp
			 Core_Sources/ALib.hpp
			 Caca_Sources/LibCaca.cpp
			 Caca_Sources/LibCaca.hpp
			 Core_Sources/ISprite.hpp )

add_library( _arcade_sfml SHARED
			 Graphic_Includes/SFML/Graphics.hpp
			 Core_Sources/ILib.hpp
			 Core_Sources/ALib.cpp
			 Core_Sources/ALib.hpp
			 Core_Sources/ISprite.hpp
			 Sfml_Sources/LibSfml.cpp
			 Sfml_Sources/LibSfml.hpp )

add_library( _arcade_sdl2 SHARED
			 Graphic_Includes/SFML/Graphics.hpp
			 Core_Sources/ILib.hpp
			 Core_Sources/ALib.cpp
			 Core_Sources/ALib.hpp
			 Core_Sources/ISprite.hpp
			 Sdl2_Sources/LibSdl2.cpp Sdl2_Sources/LibSdl2.hpp )


add_library( _arcade_nibbler SHARED
			 Core_Sources/ILib.hpp
			 Core_Sources/Vector2D.cpp
			 Core_Sources/Vector2D.hpp
			 Core_Sources/Sprite.cpp
			 Core_Sources/Sprite.hpp
			 Core_Sources/IGame.hpp
			 Core_Sources/AGame.hpp
			 Core_Sources/AGame.cpp
			 Snake_Sources/LibSnake.cpp
			 Snake_Sources/LibSnake.hpp
			 Core_Sources/GameMap.hpp
			 Core_Sources/GameMap.cpp
			 Core_Sources/IEntity.hpp
			 Core_Sources/Entity.cpp
			 Core_Sources/Entity.hpp
			 Snake_Sources/SnakeEntity.cpp
			 Snake_Sources/SnakeEntity.hpp
			 Snake_Sources/WallEntity.cpp
			 Snake_Sources/WallEntity.hpp
			 Core_Sources/DataBridge.hpp
			 Snake_Sources/SnakeDataBridge.hpp
			 Snake_Sources/SnakeBodyEntity.cpp
			 Snake_Sources/SnakeBodyEntity.hpp
			 Snake_Sources/FoodEntity.cpp
			 Snake_Sources/FoodEntity.hpp )

add_executable( arcade
				main.cpp
				Core_Sources/Sprite.cpp
				Core_Sources/LibLoader.cpp
				Core_Sources/LibLoader.hpp
				Core_Sources/Arcade.cpp
				Core_Sources/Arcade.hpp
				Core_Sources/GameMenu.cpp
				Core_Sources/GameMenu.hpp
				Core_Sources/Vector2D.cpp
				Core_Sources/Vector2D.hpp
				Core_Sources/GameManager.cpp
				Core_Sources/GameManager.hpp )

set_target_properties( _arcade_libcaca PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/libs" )
set_target_properties( _arcade_sfml PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/libs" )
set_target_properties( _arcade_sdl2 PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/libs" )
set_target_properties( _arcade_nibbler PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/games" )

target_link_libraries(_arcade_libcaca caca caca++)
target_link_libraries(_arcade_sfml sfml-graphics sfml-window sfml-system)
target_link_libraries(_arcade_sdl2 SDL2 SDL2_image SDL2_ttf)
target_link_libraries(arcade dl)