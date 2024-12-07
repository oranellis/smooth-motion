default: compiledb build

build:
	@pio run

flash:
	@pio run --target flash

compiledb:
	@pio run --target compiledb
