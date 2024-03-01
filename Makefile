.if !exists(./build)
MAKE_BUILD_DIR = mkdir build
.endif

Mergen:
	${MAKE_BUILD_DIR}
	c++ -std=c++20 -lpthread -I /usr/local/include -o build/Mergen main.cpp \
	aud/microphone.cpp aud/sound_card.cpp aud/speaker.cpp \
	hpt/touchpad.cpp \
	vis/camera.cpp vis/memory.cpp vis/segmentation.cpp vis/visual_stm.cpp
	echo "Now run: $ build/Mergen"
