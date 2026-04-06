BOOT_PATH=/Volumes/BOOT
BUILD_DIR=build
UTILS_DIR=/opt/homebrew/Cellar/arm-none-eabi-binutils/2.45.1/bin

CMAKE_CONFIG=$(BUILD_DIR)/CMakeCache.txt

.PHONY: all build_all clean link_boot flash

all: build_all

build_all: $(CMAKE_CONFIG)
	cmake --build $(BUILD_DIR) --target all


clean:
	rm -rf $(BUILD_DIR)	


$(CMAKE_CONFIG):
	mkdir -p $(BUILD_DIR)
	cmake -S . -B $(BUILD_DIR) -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain_config.cmake


link_boot:
	unlink BOOT 
	ln -s $(BOOT_PATH) .


flash:
	 cp $(BUILD_DIR)/src/kernel7.img $(BOOT_PATH)


