##
## EPITECH PROJECT, 2018
##
## File description:
## Makefile
##

CC = g++ -fPIC
CC-4.9 = x86_64-linux-gnu-g++-4.9
RM = rm -rf
DYN_LIB += -shared

# ==== arcade ====
BIN = arcade
BIN_LINKS += -ldl
# ==== ============== ====

# ==== test ====
CANON = canon
CANON_LINKS += -ldl
# ==== ============== ====

# ==== libcaca ====
CACA = lib_arcade_libcaca.so
CACA_LINKS += -lcaca -lcaca++
# ==== ============== ====


# ==== sfml ====
SFML = lib_arcade_sfml.so
SFML_LINKS += -lsfml-graphics -lsfml-window -lsfml-system
# ==== ============== ====


# ==== sdl ====
SDL2 = lib_arcade_sdl2.so
SDL2_LINKS += -lSDL2 -lSDL2_image -lSDL2_ttf
# ==== ============== ====


# ==== nibbler ====
NIBBLER = lib_arcade_nibbler.so
# ==== ============== ====


# ==== FAKE ====
FAKE = lib_arcade_pacman.so
# ==== ============== ====


# ==== directories ====
GAMES_DIR = games
GRAPHICS_DIR = libs
# ==== ============== ====


# ==== complation flags ====
CXXFLAGS += -std=c++14
CXXFLAGS += -Wall
CXXFLAGS += -Werror
CXXFLAGS += -Wextra
CXXFLAGS += -pedantic
CXXFLAGS += -Wfloat-equal
CXXFLAGS += -Wshadow
CXXFLAGS += -Weffc++
CXXFLAGS += -Wstrict-overflow=5
CXXFLAGS += -Wcast-align
CXXFLAGS += -Wconversion
CXXFLAGS += -ftrapv
CXXFLAGS += -Wuninitialized
CXXFLAGS += -Wuseless-cast
CXXFLAGS += -Wold-style-cast
CXXFLAGS += -Wnon-virtual-dtor
CXXFLAGS += -fPIC
CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0
# ==== ============== ====


# ==== include dirs ====
CXXFLAGS += -I./Graphic_Includes/Libcaca
CXXFLAGS += -I./Graphic_Includes
CXXFLAGS += -I./Caca_Sources
CXXFLAGS += -I./Core_Sources
CXXFLAGS += -I./Snake_Sources
# ==== ============== ====


# ==== librairies dirs ====
CXXFLAGS += -L./Graphic_Libs/Libcaca
CXXFLAGS += -L./Graphic_Libs/Sfml
# ==== ============== ====


# ==== arcade sources ====
BIN_SRCS += main.cpp
BIN_SRCS += Core_Sources/Sprite.cpp
BIN_SRCS += Core_Sources/LibLoader.cpp
BIN_SRCS += Core_Sources/Arcade.cpp
BIN_SRCS += Core_Sources/GameMenu.cpp
BIN_SRCS += Core_Sources/Vector2D.cpp
BIN_SRCS += Core_Sources/GameManager.cpp

BIN_OBJS = $(BIN_SRCS:.cpp=.o)
# ==== ============== ====

# ==== test sources ====
CANON_SRCS += canon.cpp
CANON_SRCS += Core_Sources/Sprite.cpp
CANON_SRCS += Core_Sources/LibLoader.cpp
CANON_SRCS += Core_Sources/Vector2D.cpp

CANON_OBJS = $(CANON_SRCS:.cpp=.o)
# ==== ============== ====


# ==== libcaca sources ====
CACA_SRCS += Core_Sources/ALib.cpp
CACA_SRCS += Caca_Sources/LibCaca.cpp

CACA_OBJS = $(CACA_SRCS:.cpp=.o)
# ==== ============== ====


# ==== sfml sources ====
SFML_SRCS += Core_Sources/ALib.cpp
SFML_SRCS += Sfml_Sources/LibSfml.cpp

SFML_OBJS = $(SFML_SRCS:.cpp=.o)
# ==== ============== ====


# ==== sfml sources ====
SDL2_SRCS += Core_Sources/ALib.cpp
SDL2_SRCS += Sdl2_Sources/LibSdl2.cpp

SDL2_OBJS = $(SDL2_SRCS:.cpp=.o)
# ==== ============== ====


# ==== nibbler sources ====
NIBBLER_SRCS += Core_Sources/Vector2D.cpp
NIBBLER_SRCS += Core_Sources/Sprite.cpp
NIBBLER_SRCS += Core_Sources/AGame.cpp
NIBBLER_SRCS += Snake_Sources/LibSnake.cpp
NIBBLER_SRCS += Core_Sources/GameMap.cpp
NIBBLER_SRCS += Core_Sources/Entity.cpp
NIBBLER_SRCS += Snake_Sources/SnakeEntity.cpp
NIBBLER_SRCS += Snake_Sources/WallEntity.cpp
NIBBLER_SRCS += Snake_Sources/SnakeBodyEntity.cpp
NIBBLER_SRCS += Snake_Sources/FoodEntity.cpp

NIBBLER_OBJS = $(NIBBLER_SRCS:.cpp=.o)
# ==== ============== ====


# ==== fake sources ====
FAKE_SRCS += Core_Sources/Vector2D.cpp
FAKE_SRCS += Core_Sources/Sprite.cpp
FAKE_SRCS += Core_Sources/AGame.cpp
FAKE_SRCS += Snake_Sources/LibSnake2.cpp
FAKE_SRCS += Core_Sources/GameMap.cpp
FAKE_SRCS += Core_Sources/Entity.cpp
FAKE_SRCS += Snake_Sources/SnakeEntity.cpp
FAKE_SRCS += Snake_Sources/WallEntity.cpp
FAKE_SRCS += Snake_Sources/SnakeBodyEntity.cpp
FAKE_SRCS += Snake_Sources/FoodEntity.cpp

FAKE_OBJS = $(FAKE_SRCS:.cpp=.o)
# ==== ============== ====


all: core games graphicals

test: $(CANON)

core: $(BIN) $(CANON)

games: $(NIBBLER) $(FAKE)

graphicals: $(CACA) $(SFML) $(SDL2)


$(BIN): $(BIN_OBJS)
		$(CC) $(BIN_OBJS) $(CXXFLAGS) $(BIN_LINKS) -o $(BIN)

$(CANON): $(CANON_OBJS)
		$(CC) $(CANON_OBJS) $(CXXFLAGS) $(CANON_LINKS) -o $(CANON)

$(CACA): $(CACA_OBJS)
		$(CC) $(DYN_LIB) $(CACA_OBJS) $(CXXFLAGS) $(CACA_LINKS) -o $(CACA)
		@mkdir -p $(GRAPHICS_DIR)
		@mv $(CACA) $(GRAPHICS_DIR)

$(SFML): $(SFML_OBJS)
		$(CC) $(DYN_LIB) $(SFML_SRCS) $(CXXFLAGS) $(SFML_LINKS) -o $(SFML)
		@mkdir -p $(GRAPHICS_DIR)
		@mv $(SFML) $(GRAPHICS_DIR)

$(SDL2): $(SDL2_OBJS)
		$(CC) $(DYN_LIB) $(SDL2_SRCS) $(CXXFLAGS) $(SDL2_LINKS) -o $(SDL2)
		@mkdir -p $(GRAPHICS_DIR)
		@mv $(SDL2) $(GRAPHICS_DIR)

$(NIBBLER): $(NIBBLER_OBJS)
		$(CC) $(DYN_LIB) $(NIBBLER_OBJS) $(CXXFLAGS) $(NIBBLER_LINKS) -o $(NIBBLER)
		@mkdir -p $(GAMES_DIR)
		@mv $(NIBBLER) $(GAMES_DIR)

$(FAKE): $(FAKE_OBJS)
		$(CC) $(DYN_LIB) $(FAKE_OBJS) $(CXXFLAGS) $(FAKE_LINKS) -o $(FAKE)
		@mkdir -p $(GRAPHICS_DIR)
		@mv $(FAKE) $(GAMES_DIR)

clean:
		$(RM) $(BIN_OBJS) $(CACA_OBJS) $(SFML_OBJS) $(NIBBLER_OBJS) $(SDL2_OBJS) $(CANON_OBJS) $(FAKE_OBJS)

fclean: clean
		$(RM) $(BIN) $(CACA) $(SFML) $(NIBBLER) $(SDL2) $(CANON) $(FAKE)

re: fclean all